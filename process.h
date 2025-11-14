#ifndef PROCESS_H
#define PROCESS_H

struct Process {
    int pid;            // Process ID
    int arrival;        // Arrival time
    int burst;          // Burst time
    int remaining;      // Remaining time
    int waiting;        // Waiting time
    int turnaround;     // Turnaround time
    int completion;     // Completion time
    int priority;       // For feedback/aging (optional)
};

#endif
