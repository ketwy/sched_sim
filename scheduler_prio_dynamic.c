#include <stdio.h>
#include "queue.h"
#include "proc.h"
#include "stats.h"
#include "utils.h"

// Variáveis globais definidas no 'main'
extern struct queue *ready;    // fila de processos aptos
extern struct queue *ready2;   // segunda fila de processos aptos
extern struct queue *blocked;  // fila de processos bloqueados
extern struct queue *finished; // fila de processos finalizados
// OBS: A fila 'finished' é usada apenas para estatísticas finais

extern int MAX_TIME; // tempo máximo que um processo pode executar ao todo

struct proc *scheduler(struct proc *current)
{
    if (current != NULL)
    {
        switch (current->state)
        {
        case READY:
            enqueue(ready2, current); // Coloca o processo atual na segunda fila de aptos (ready2)
            count_ready_in(current);  // Atualiza as estatísticas de processos aptos
            break;
        case BLOCKED:
            enqueue(blocked, current); // Coloca o processo atual na fila de bloqueados (blocked)
            count_blocked_in(current); // Atualiza as estatísticas de processos bloqueados
            break;
        case FINISHED:
            enqueue(finished, current); // Coloca o processo atual na fila de finalizados (finished)
            count_finished_in(current); // Atualiza as estatísticas de processos finalizados
            break;
        default:
            printf("@@ ERRO no estado de saída do processo %d\n", current->pid);
            // Caso o estado do processo atual não seja reconhecido, exibe uma mensagem de erro
        }
    }

    if (isempty(ready) && isempty(ready2))
    {
        return NULL; // Se ambas as filas de aptos estiverem vazias, retorna NULL indicando que não há mais processos a serem executados
    }

    struct proc *selected;

    if (!isempty(ready) && (isempty(ready2) || make_rand(100) <= 80))
    {
        selected = dequeue(ready); // Seleciona um processo da primeira fila de aptos (ready) com 80% de probabilidade
    }
    else
    {
        selected = dequeue(ready2); // Seleciona um processo da segunda fila de aptos (ready2) com 20% de probabilidade
    }

    count_ready_out(selected); // Atualiza as estatísticas de processos aptos
    selected->state = RUNNING; // Define o estado do processo selecionado como RUNNING (em execução)
    return selected;           // Retorna o processo selecionado para ser executado
}
