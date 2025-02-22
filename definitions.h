#ifndef definitions_h
#define definitions_h

struct ProcessNode
{
    int burst_time, decrease_burst_time;
    int arrival_time, priority;
    int waiting_time, terminate;
    int process_id, justExecuted;
    struct ProcessNode* next;
};

struct Queue
{
    struct ProcessNode* process;
    struct Queue* next;
};


#endif