#include <stdio.h>

#include "queue.h"
#include "proc.h"
#include "stats.h"

// Esta é a função a ser alterada caso mude a forma de inicialização dos processos
// Assim como a seleção da fila que ele será inserido

// Quantidade de processos a serem criados
extern int NPROC;

// Utilizando as variáveis globais das filas definidas no 'main'
extern struct queue * ready;    // fila de aptos
extern struct queue * ready2;   // segunda fila de aptos
extern struct queue * blocked;  // fila de bloqueados
extern struct queue * finished; // fila de finalizados

// Tempo máximo de execução total de um processo
extern int MAX_TIME;

// Inicializa os 'NPROC' processos informados
void proc_init()
{
    struct proc *p;

    for (int i = 0; i < NPROC; i++)
    {
        // criando um novo processo
        p = createproc();

        // cria a thread do processo
        p->tid = createproc_thread(p);

        // Verifica a prioridade do processo com base no tempo restante
        if (p->remaining_time <= (0.2 * MAX_TIME))
        {
            p->queue = 1;
            // Adiciona o processo na primeira fila de aptos
            enqueue(ready, p);
        }
        else
        {
            p->queue = 2;
            // Adiciona o processo na segunda fila de aptos
            enqueue(ready2, p);
        }

        count_ready_in(p);
    }
}