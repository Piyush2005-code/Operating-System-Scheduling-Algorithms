#include "scheduler.h"
#include "util.h"
#include <algorithm>
#include <iostream>
#include <queue>

void fcfs(std::vector<Process> processes) {
    // Sort by arrival then pid
    std::sort(processes.begin(), processes.end(), [](const Process &a, const Process &b){
        if (a.arrival != b.arrival) return a.arrival < b.arrival;
        return a.pid < b.pid;
    });

    int n = (int)processes.size();
    std::queue<int> q;                // queue of indices
    int time = 0, i = 0, completed = 0;
    std::vector<GanttEntry> chart;

    while (completed < n) {
        // push arrivals into queue
        while (i < n && processes[i].arrival <= time) {
            q.push(i);
            ++i;
        }

        if (q.empty()) {
            // no ready process, jump to next arrival
            if (i < n) time = processes[i].arrival;
            continue;
        }

        int idx = q.front(); q.pop();

        int start = std::max(time, processes[idx].arrival);
        int end = start + processes[idx].burst;
        time = end;

        processes[idx].completion = end;
        processes[idx].turnaround = end - processes[idx].arrival;
        processes[idx].waiting = processes[idx].turnaround - processes[idx].burst;
        ++completed;

        chart.push_back({processes[idx].pid, start, end});

        // any processes that arrived exactly at this time are queued by top of loop
    }

    std::cout << "\n--- FCFS Scheduling (queue) ---\n";
    print_result(processes);
    std::cout << "\nGantt Chart (FCFS):\n";
    print_gantt(chart);
}
