#include "scheduler.h"
#include "util.h"
#include <iostream>
#include <queue>
#include <vector>

void rr(std::vector<Process> processes, int quantum) {
    int n = (int)processes.size();
    if (n == 0) { std::cout << "No processes.\n"; return; }

    std::queue<int> queue;
    int time = 0, completed = 0;
    std::vector<GanttEntry> chart;

    std::vector<int> remaining_burst(n);
    for (int i = 0; i < n; ++i) {
        remaining_burst[i] = processes[i].burst;
    }

    queue.push(0);

    while (!queue.empty()) {
        int idx = queue.front(); queue.pop();

        if (remaining_burst[idx] > 0) {
            int start = time;
            int time_slice = std::min(quantum, remaining_burst[idx]);
            time += time_slice;
            remaining_burst[idx] -= time_slice;

            chart.push_back({processes[idx].pid, start, time});

            if (remaining_burst[idx] == 0) {
                processes[idx].completion = time;
                processes[idx].turnaround = time - processes[idx].arrival;
                processes[idx].waiting = processes[idx].turnaround - processes[idx].burst;
                ++completed;
            } else {
                queue.push(idx);
            }

            for (int i = 0; i < n; ++i) {
                if (processes[i].arrival <= time && remaining_burst[i] > 0 && i != idx) {
                    queue.push(i);
                }
            }
        }
    }

    std::cout << "\n--- RR Scheduling (Time Quantum = " << quantum << ") ---\n";
    print_result(processes);
    std::cout << "\nGantt Chart (RR):\n";
    print_gantt(chart);
}
