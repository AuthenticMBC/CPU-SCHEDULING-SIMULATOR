#ifndef ps_h
#define ps_h

#include <stdlib.h>
#include "definitions.h"
#include "file_operations.h"
#include "sub_func.h"
void PriorityScheduling(char* input_file, char* output_file)
{
    // Lower Number --> Higher priority
    struct ProcessNode* head = readDataInFile(input_file);
    struct ProcessNode* temp = head;
    int currentTime = 0, ct, tat;

    //Non-preemptive
    while (checkterminated(head) == 0) {
        temp = getHighPriorityProcess(head, currentTime);
        if (temp == NULL) {
            currentTime++;
        } else {
            currentTime += temp->burst_time;
            tat = currentTime - temp->arrival_time;
            temp->waiting_time = tat - temp->burst_time;
            temp->terminate = 1;
        }
    }
    saveResult(head, output_file, 4); // Priority Non-Preemptive
    // ---------------------------------------------------------------------------------

    //Preemptive
    currentTime = 0;
    while (checkterminated(head) == 0)
    {
        temp = getHighPriorityProcess(head, currentTime);
        if (temp != NULL) {
            if (--temp->decrease_burst_time == 0) {
                ct = currentTime + 1;
                tat = ct - temp->arrival_time;
                temp->waiting_time = tat - temp->burst_time;
                temp->terminate = 1;
            }
        }
        currentTime++;
    }
    saveResult(head, output_file, 5); // Priority Preemptive

    // Free memory
    FreeProcessList(head);
}


#endif