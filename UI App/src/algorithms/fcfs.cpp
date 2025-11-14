#include "scheduler.h"
#include "util.h"
#include <iostream>
#include <vector>

void fcfs(std::vector<Process> processes) {
    int n = (int)processes.size();
    if (n == 0) { std::cout << "No processes.\n"; return; }

    int time = 0;
    std::vector<GanttEntry> chart;

    for (int i = 0; i < n; ++i) {
        if (processes[i].arrival > time) {
            time = processes[i].arrival; // advance time if the process hasn't arrived yet
        }
        int start = time;
        time += processes[i].burst;
        int end = time;

        processes[i].completion = end;
        processes[i].turnaround = end - processes[i].arrival;
        processes[i].waiting = processes[i].turnaround - processes[i].burst;

        chart.push_back({processes[i].pid, start, end});
    }

    std::cout << "\n--- FCFS Scheduling ---\n";
    print_result(processes);
    std::cout << "\nGantt Chart (FCFS):\n";
    print_gantt(chart);
}