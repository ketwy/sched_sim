#include <stdio.h>
#include "queue.h"
#include "proc.h"
#include "stats.h"
#include "utils.h"

extern struct queue *ready;    // fila de aptos
extern struct queue *ready2;   // segunda fila de aptos
extern struct queue *blocked;  // fila de bloqueados
extern struct queue *finished; // fila de finalizados

extern int MAX_TIME; // variável global que indica o tempo máximo que um processo pode executar ao todo

struct proc *scheduler(struct proc *current)
{
    if (current != NULL)
    {
        switch (current->state)
        {
        case READY:
            // Adiciona o processo atual à fila correspondente (ready ou ready2)
            if (current->queue == 1)
            {
                enqueue(ready, current);
            }
            else
            {
                enqueue(ready2, current);
            }
            count_ready_in(current); // Atualiza estatísticas de entrada de processos aptos
            break;
        case BLOCKED:
            enqueue(blocked, current); // Adiciona o processo atual à fila de bloqueados
            count_blocked_in(current); // Atualiza estatísticas de entrada de processos bloqueados
            break;
        case FINISHED:
            enqueue(finished, current); // Adiciona o processo atual à fila de finalizados
            count_finished_in(current); // Atualiza estatísticas de entrada de processos finalizados
            break;
        default:
            printf("@@ ERRO no estado de saída do processo %d\n", current->pid);
        }
    }

    // Verifica se ambas as filas de aptos estão vazias
    if (isempty(ready) && isempty(ready2))
    {
        return NULL; // Retorna NULL se não houver mais processos aptos para executar
    }

    struct proc *selected = NULL;

    // Seleciona o próximo processo a ser escalonado
    if (!isempty(ready) && make_rand(100) <= 80)
    {
        selected = dequeue(ready); // Remove o processo selecionado da fila ready
    }
    else if (!isempty(ready2))
    {
        selected = dequeue(ready2); // Remove o processo selecionado da fila ready2
    }

    if (selected != NULL)
    {
        count_ready_out(selected); // Atualiza estatísticas de saída de processos aptos
        selected->state = RUNNING; // Define o estado do processo selecionado como RUNNING
    }

    return selected; // Retorna o processo selecionado para ser escalonado
}
