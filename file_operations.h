#ifndef file_operations_h
#define file_operations_h

#include <stdio.h>
#include <stdlib.h>
#include "definitions.h"
#include "data_structure_operations.h"

struct ProcessNode* readDataInFile(char* name_of_file)
{
    int burst_time, arrival_time, priority, id = 1;
    struct ProcessNode* p = NULL;
    FILE* file = fopen(name_of_file, "r");
    if (file == NULL) {
        printf("Unble to open file %s file\n", name_of_file);
        exit(EXIT_FAILURE);
    }

    while (fscanf(file, "%d:%d:%d", &burst_time, &arrival_time, &priority) != EOF)
        p = insertNodeBack(p, burst_time, arrival_time, priority, id++);

    return p;
}

void saveResult(struct ProcessNode* head, char* output_file, int code)
{
    int total_wt = 0, cnt = 0;
    struct ProcessNode* temp = head;
    FILE* file;
    file = fopen(output_file, "a");
    if (file == NULL) {
        printf("Error while opening file %s occurred !\n", output_file);
        exit(EXIT_FAILURE);
    }
    printf("%d:", code);
    fprintf(file, "%d:", code);
    while (temp) {
        printf("%d:", temp->waiting_time);
        fprintf(file, "%d:", temp->waiting_time);
        total_wt += temp->waiting_time;
        cnt++;
        temp->terminate = 0; //Clear terminate field for other preemptive mode 
        temp = temp->next;
    }
    printf("%.2f\n", (float)total_wt / cnt);
    fprintf(file, "%.2f\n", (float)total_wt / cnt);
    fclose(file);
}

#endif