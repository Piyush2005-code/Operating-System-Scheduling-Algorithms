#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <vector>
#include <tuple>

// Process structure to hold process information
struct Process {
    int pid; // Process ID
    int arrival; // Arrival time
    int burst; // Burst time
    int completion; // Completion time
    int turnaround; // Turnaround time
    int waiting; // Waiting time
};

// Gantt chart entry structure
struct GanttEntry {
    int pid; // Process ID
    int start; // Start time
    int end; // End time
};

// Function declarations for scheduling algorithms
void fcfs(std::vector<Process> processes);
void rr(std::vector<Process> processes, int quantum);
void hrrn(std::vector<Process> processes);
void mlfq(std::vector<Process> processes);
void sjf(std::vector<Process> processes);
void srt(std::vector<Process> processes);

// Utility functions
void print_result(const std::vector<Process>& processes);
void print_gantt(const std::vector<GanttEntry>& chart);

#endif // SCHEDULER_H