/* This Project was developed by Maroyi Bisoka */
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
// #include <bits/getopt_core.h>

#include "fcfs.h"
#include "sjf.h"
#include "ps.h"
#include "rr.h"

#define STRING_LENGTH 50

void GetArgument(char* argv[], int argc, char input_file[], char output_file[], int* time_quantum)
{
    int flags = 0, opt;
    while ((opt = getopt(argc, argv, "t:o:f:")) != -1) {
        switch (opt) {
        case 't':
            flags++;
            *time_quantum = atoi(optarg);
            break;
        case 'o':
            flags++;
            strcpy(output_file, optarg);
            break;
        case 'f':
            flags++;
            strcpy(input_file, optarg);
            break;
        default:
            fprintf(stderr, "Usage: %s [-t time_quantum] [-f input_file_name] [-o output_file_name] \n", argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    if (flags != 3) {
        fprintf(stderr, "Usage: %s [-t time_quantum] [-f input_file_name] [-o output_file_name] \n", argv[0]);
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char* argv[])
{
    int time_quantum;
    char input_file[STRING_LENGTH], output_file[STRING_LENGTH];

    GetArgument(argv, argc, input_file, output_file, &time_quantum);

    // Performing Scheduling Algorithms
    fclose(fopen(output_file, "w")); // clear output File for overwriting 
    FirstComeFistServe(input_file, output_file);
    ShortestJobFirst(input_file, output_file);
    PriorityScheduling(input_file, output_file);
    RoundRobin(time_quantum, input_file, output_file);

    return 0; // EXIT_SUCCESS
}