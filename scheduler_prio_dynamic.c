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

    // Verificar se há processos bloqueados aguardando E/S
    if (!isempty(blocked))
    {
        struct proc *blockedProc = dequeue(blocked);
        enqueue(ready, blockedProc); // Inserir o processo na Fila 1 (ready)
    }

    // Verificar se houve preempção
    if (current != NULL && current->remaining_time < MAX_TIME)
    {
        enqueue(ready2, current); // Inserir o processo na Fila 2 (ready2)
    }

    // Selecionar um processo para execução
    if (!isempty(ready) && (isempty(ready2) || rand()%100 <= 80))
    {
        selected = dequeue(ready); // Selecionar um processo da Fila 1 (ready) com 80% de probabilidade
    }
    else
    {
        selected = dequeue(ready2); // Selecionar um processo da Fila 2 (ready2) com 20% de probabilidade
    }

    return selected;
}