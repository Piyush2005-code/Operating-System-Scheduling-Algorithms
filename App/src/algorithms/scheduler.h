#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <vector>
#include <tuple>

struct Process {
    int pid;
    int arrival;
    int burst;
    int completion;
    int turnaround;
    int waiting;
};

struct GanttEntry {
    int pid;
    int start;
    int end;
};

void fcfs(std::vector<Process> processes);
void rr(std::vector<Process> processes, int quantum);
void hrrn(std::vector<Process> processes);
void mlfq(std::vector<Process> processes);
void sjf(std::vector<Process> processes);
void srt(std::vector<Process> processes);

void print_result(const std::vector<Process>& processes);
void print_gantt(const std::vector<GanttEntry>& chart);

#endif
