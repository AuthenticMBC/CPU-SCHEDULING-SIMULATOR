#ifndef sub_func_h
#define sub_func_h

#include <stdlib.h>
#include "definitions.h"
#include "data_structure_operations.h"

int checkterminated(struct ProcessNode* head)
{
    while (head) {
        if (head->terminate == 0)
            return 0;
        head = head->next;
    }
    return 1;
}

struct ProcessNode* getFirstProcess(struct ProcessNode* head, int currentTime)
{
    struct ProcessNode* first = NULL;
    while (head != NULL) {
        if (head->terminate == 0 && head->arrival_time <= currentTime) {
            if (first == NULL) first = head;
            else if (head->arrival_time < first->arrival_time) first = head;
        }
        head = head->next;
    }
    return first;
}

struct ProcessNode* getShortProcess(struct ProcessNode* head, int currentTime)
{
    struct ProcessNode* shortPr = NULL;
    while (head != NULL) {
        if (head->terminate == 0 && head->arrival_time <= currentTime) {
            if (shortPr == NULL) shortPr = head;
            else if (head->decrease_burst_time < shortPr->decrease_burst_time) shortPr = head;
        }
        head = head->next;
    }
    return shortPr;
}

struct ProcessNode* getHighPriorityProcess(struct ProcessNode* head, int currentTime)
{
    // Lower number --> Higher priority
    struct ProcessNode* higherPriorityProcess = NULL;

    while (head != NULL) {
        if (head->terminate == 0 && head->arrival_time <= currentTime) {
            if (higherPriorityProcess == NULL) higherPriorityProcess = head;
            else if (head->priority < higherPriorityProcess->priority) higherPriorityProcess = head;
        }
        head = head->next;
    }
    return higherPriorityProcess;
}

struct Queue* InsertArrivalProcessToQueue(struct ProcessNode* head, struct Queue* q, int currentTime)
{
    while (head != NULL) {
        if (head->terminate == 0 && head->justExecuted == 0 && head->arrival_time <= currentTime && InQueue(q, head->process_id) == 0) { // If process not terminated and not the one just being executed
            q = InsertToQueue(q, head);
        }
        head = head->next;
    }
    return q;
}

void FreeProcessList(struct ProcessNode* p)
{
    struct ProcessNode* t = p;
    while (p) {
        p = p->next;
        free(t);
        t = p;
    }
}

#endif