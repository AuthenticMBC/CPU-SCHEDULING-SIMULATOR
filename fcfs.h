#ifndef fcfs_h
#define fcfs_h

#include <stdlib.h>
#include "definitions.h"
#include "file_operations.h"
#include "sub_func.h"

void FirstComeFistServe(char* input_file, char* output_file)
{
    struct ProcessNode* head = readDataInFile(input_file);
    struct ProcessNode* temp = head;
    int currentTime = 0, total_wt = 0, cnt = 0, tat;
    //Performing FCFS algorithm
    while (checkterminated(head) == 0) { // Check if all process are already terminated
        temp = getFirstProcess(head, currentTime);
        if (temp == NULL) {
            currentTime++;
        } else {
            currentTime += temp->burst_time;
            tat = currentTime - temp->arrival_time;
            temp->waiting_time = tat - temp->burst_time;
            temp->terminate = 1;
        }
    }
    // Save Result to output file and print no terminal screen
    saveResult(head, output_file, 1);
}


#endif