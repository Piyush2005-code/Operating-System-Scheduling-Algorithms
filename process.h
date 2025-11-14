#ifndef PROCESS_H
#define PROCESS_H

struct Process {
    int pid;
    int arrival;
    int burst;
    int remaining;
    int waiting;
    int turnaround;
    int completion;
    int priority;
};

#endif
