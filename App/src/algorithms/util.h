#ifndef UTIL_H
#define UTIL_H

#include <vector>
#include <iostream>

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

void print_result(const std::vector<Process>& processes) {
    std::cout << "PID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n";
    for (const auto& p : processes) {
        std::cout << p.pid << "\t" << p.arrival << "\t" << p.burst << "\t"
                  << p.completion << "\t\t" << p.turnaround << "\t\t" << p.waiting << "\n";
    }
}

void print_gantt(const std::vector<GanttEntry>& chart) {
    for (const auto& entry : chart) {
        std::cout << entry.pid << " ";
    }
    std::cout << "\n";

    for (const auto& entry : chart) {
        std::cout << entry.start << " ";
    }
    std::cout << "\n";
}

#endif
