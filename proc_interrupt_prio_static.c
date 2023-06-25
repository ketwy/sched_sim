#include <stdio.h>

#include "queue.h"
#include "proc.h"
#include "stats.h"

// Utilizando as variáveis globais definidas no 'main'
extern struct queue * ready;    // fila de aptos
extern struct queue * ready2;   // segunda fila de aptos

// para tratar o que fazer com o processo ao ocorrer a 
// interrupçao que define sua saída da fila de bloqueados
void proc_interrupt(struct proc * p)
{
    // Verifica em qual fila o processo estava antes de ser bloqueado
    if (p->queue == 1)
    {
        // Processo estava na primeira fila (ready)
        // insere o processo no final da mesma fila
        enqueue(ready, p);
    }
    else
    {
        // Processo estava na segunda fila (ready2)
        // insere o processo no final da mesma fila
        enqueue(ready2, p);
    }

    // alterando o status para apto
    p->state = READY;

    // Realizando as estatísticas para o processo que
    // entra na fila de aptos correspondente
    count_ready_in(p);
}