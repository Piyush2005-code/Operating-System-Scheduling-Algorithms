#include "scheduler.h"
#include "util.h"
#include <iostream>
#include <vector>
#include <algorithm>

void hrrn(std::vector<Process> processes) {
    int n = (int)processes.size();
    if (n == 0) { std::cout << "No processes.\n"; return; }

    int time = 0, completed = 0;
    std::vector<GanttEntry> chart;

    while (completed < n) {
        // Calculate response ratios
        std::vector<std::pair<double, int>> ratios; // (ratio, index)
        for (int i = 0; i < n; ++i) {
            if (processes[i].completion == 0 && processes[i].arrival <= time) {
                double response_ratio = (time - processes[i].arrival + processes[i].burst) / (double)processes[i].burst;
                ratios.emplace_back(response_ratio, i);
            }
        }

        if (ratios.empty()) {
            // Advance time if no process is ready
            time++;
            continue;
        }

        // Find the process with the highest response ratio
        auto max_ratio = std::max_element(ratios.begin(), ratios.end());
        int idx = max_ratio->second;

        int start = time;
        time += processes[idx].burst;
        processes[idx].completion = time;
        processes[idx].turnaround = processes[idx].completion - processes[idx].arrival;
        processes[idx].waiting = processes[idx].turnaround - processes[idx].burst;
        completed++;

        chart.push_back({processes[idx].pid, start, time});
    }

    std::cout << "\n--- HRRN Scheduling ---\n";
    print_result(processes);
    std::cout << "\nGantt Chart (HRRN):\n";
    print_gantt(chart);
}