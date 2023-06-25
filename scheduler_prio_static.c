#include <stdio.h>
#include <stdlib.h>

#include "queue.h" // contem funções uteis para filas
#include "proc.h"  // possui as funções dos processos
#include "stats.h" // possui as funções de estatisticas 
#include "utils.h" // possui funções uteis 

// Utilizando as variáveis globais definidas no 'main'
extern struct queue * ready;    // fila de aptos
extern struct queue * ready2;   // segunda fila de aptos
extern struct queue * blocked;  // fila de bloqueados
extern struct queue * finished; // fila de finalizados
// NOTE: essa fila de finalizados é utilizada apenas para
// as estatisticas finais

// variavel global que indica o tempo maximo que um processo pode executar ao todo
extern int MAX_TIME;

struct proc * scheduler(struct proc * current)
{
    struct proc *selected;

    if (current != NULL)
    {
        switch (current->state)
        {
            case READY:
                if (current->queue == 1) {
                    enqueue(ready, current);
                } else {
                    enqueue(ready2, current);
                }
                count_ready_in(current);
                break;
            case BLOCKED:
                enqueue(blocked, current);
                count_blocked_in(current);
                break;
            case FINISHED:
                enqueue(finished, current);
                count_finished_in(current);
                break;
            default:
                printf("@@ ERRO no estado de saída do processo %d\n", current->pid);
        }
    }

    if (isempty(ready) && isempty(ready2))
    {
        return NULL;
    }

    // Verifica se a fila 1 (ready) possui processos
    if (!isempty(ready) && make_rand(100) <= 80)
    {
        selected = dequeue(ready); // Remove o processo selecionado da fila 1 (ready)
    }
    // Verifica se a fila 2 (ready2) possui processos
    else if (!isempty(ready2))
    {
        // Seleciona um processo da fila 2 (ready2) usando a estratégia FIFO (20% de probabilidade)
        selected = dequeue(ready2); // Remove o processo selecionado da fila 2 (ready2)
    }

    count_ready_out(selected);
    selected->state = RUNNING;
    return selected;
}