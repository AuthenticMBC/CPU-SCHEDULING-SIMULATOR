#ifndef rr_h
#define rr_h

#include <stdlib.h>
#include "definitions.h"
#include "file_operations.h"
#include "data_structure_operations.h"
#include "sub_func.h"

void RoundRobin(int time_quantum, char* input_file, char* output_file)
{
    struct ProcessNode* head = readDataInFile(input_file);
    struct ProcessNode* temp = head;
    struct Queue* queue = NULL;
    int currentTime = 0, tat;

    while (checkterminated(head) == 0) {
        queue = InsertArrivalProcessToQueue(temp, queue, currentTime);
        if (temp && temp->justExecuted == 1) { // This won't be true for the first iteration but true for the seconde one so we'll
            // be able to insert at the end end of the queue after inserting the new coming processes
            queue = InsertToQueue(queue, temp);
            temp->justExecuted = 0;
        }
        if (IsQueueEmpty(queue) == 1) {
            currentTime++;
        } else {
            temp = queue->process;
            queue = DeleteToQueue(queue);
            if (temp->decrease_burst_time <= time_quantum) {
                currentTime += temp->decrease_burst_time;
                temp->decrease_burst_time = 0;
                tat = currentTime - temp->arrival_time;
                temp->waiting_time = tat - temp->burst_time;
                temp->terminate = 1;
            } else {
                currentTime += time_quantum;
                temp->decrease_burst_time -= time_quantum;
                temp->justExecuted = 1;
            }
        }
    }
    saveResult(head, output_file, 6); // Round Robin

    // Free memory
    FreeProcessList(head);
}


#endif