#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "process.h"
#include <vector>

// Scheduling algorithms (take processes by value so main copy stays intact)
void fcfs(std::vector<Process> processes);
void sjf(std::vector<Process> processes);
void srt(std::vector<Process> processes);
void rr(std::vector<Process> processes, int quantum);
void hrrn(std::vector<Process> processes);
void feedback(std::vector<Process> processes);

#endif // SCHEDULER_H
