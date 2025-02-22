#ifndef data_structure_operations_h
#define data_structure_operations_h

#include <stdlib.h>
#include "definitions.h"

struct ProcessNode* createNode(int burst_time, int arrival_time, int priority, int process_id)
{
    struct ProcessNode* temp = (struct ProcessNode*)malloc(sizeof(struct ProcessNode));
    temp->arrival_time = arrival_time;
    temp->burst_time = burst_time;
    temp->decrease_burst_time = burst_time;
    temp->priority = priority;
    temp->process_id = process_id;
    temp->justExecuted = temp->terminate = 0;
    temp->next = NULL;
    return temp;
}

struct ProcessNode* insertNodeBack(struct ProcessNode* p, int burst_time, int arrival_time, int priority, int process_id)
{
    struct ProcessNode* temp = createNode(burst_time, arrival_time, priority, process_id);
    if (p == NULL) {
        p = temp;
        return p;
    }
    struct ProcessNode* iter = p;
    while (iter->next != NULL) iter = iter->next;
    iter->next = temp;
    return p;
};

struct Queue* InsertToQueue(struct Queue* q, struct ProcessNode* p)
{
    struct Queue* t, * i;
    t = (struct Queue*)malloc(sizeof(struct Queue));
    t->process = p;
    t->next = NULL;
    if (q == NULL) return t;
    i = q;
    while (i->next) i = i->next;
    i->next = t;
    return q;
}

struct Queue* DeleteToQueue(struct Queue* q)
{
    struct Queue* t;
    if (q == NULL) return NULL;
    t = q;
    q = q->next;
    free(t);
    return q;
}

int InQueue(struct Queue* queue, int process_id)
{
    while (queue) {
        if (queue->process->process_id == process_id)
            return 1;
        queue = queue->next;
    }
    return 0;
}

int IsQueueEmpty(struct Queue* q)
{
    return q == NULL;
}


#endif