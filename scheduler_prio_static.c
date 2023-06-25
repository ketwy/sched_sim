#include <stdio.h>
#include <stdlib.h>

#include "queue.h" // contem funções uteis para filas
#include "proc.h"  // possui as funções dos processos
#include "stats.h" // possui as funções de estatisticas 
#include "utils.h" // possui funções uteis 

// Utilizando as variáveis globais definidas no 'main'
extern struct queue *ready;    // fila de aptos
extern struct queue *ready2;   // segunda fila de aptos
extern struct queue *blocked;  // fila de bloqueados
extern struct queue *finished; // fila de finalizados
// NOTE: essa fila de finalizados é utilizada apenas para
// as estatisticas finais

// variavel global que indica o tempo maximo que um processo pode executar ao todo
extern int MAX_TIME;

struct proc *scheduler(struct proc *current)
{
    struct proc *selected;

    // Verifica se a fila 1 (ready) possui processos
    if (!isempty(ready))
    {
        // Seleciona um processo da fila 1 (ready) usando a estratégia FIFO (80% de probabilidade)
        if (random() <= 0.8)
        {
            selected = dequeue(ready); // Remove o processo selecionado da fila 1 (ready)
            return selected;
        }
    }
    // Verifica se a fila 2 (ready2) possui processos
    if (!isempty(ready2))
    {
        // Seleciona um processo da fila 2 (ready2) usando a estratégia FIFO (20% de probabilidade)
        if (random() <= 0.2)
        {
            selected = dequeue(ready2); // Remove o processo selecionado da fila 2 (ready2)
            return selected;
        }
    }

    return NULL; // Retorna NULL se nenhuma fila tiver processos
}