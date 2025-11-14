#include "scheduler.h"
#include "util.h"
#include <iostream>
#include <set>
#include <vector>
#include <limits>
#include <cmath>
#include <algorithm>

// Comparator not used directly because ratio changes with time;
// We'll rebuild a multiset of (ratio, idx) at each decision point.
void hrrn(std::vector<Process> processes) {
    int n = (int)processes.size();
    if (n == 0) { std::cout << "No processes.\n"; return; }

    std::vector<bool> done(n, false);
    int completed = 0, time = 0;
    std::vector<GanttEntry> chart;

    // Sort indices by arrival for scanning
    std::vector<int> order(n);
    for (int i = 0; i < n; ++i) order[i] = i;
    std::sort(order.begin(), order.end(), [&](int a, int b){
        if (processes[a].arrival != processes[b].arrival) return processes[a].arrival < processes[b].arrival;
        return processes[a].pid < processes[b].pid;
    });

    while (completed < n) {
        // build multiset of currently available processes keyed by ratio
        std::multiset<std::pair<double,int>, std::greater<>> ms; // max-first by pair.first
        bool anyReady = false;
        for (int idx = 0; idx < n; ++idx) {
            if (!done[idx] && processes[idx].arrival <= time) {
                anyReady = true;
                int wait = time - processes[idx].arrival;
                double ratio = double(wait + processes[idx].burst) / double(processes[idx].burst);
                ms.insert({ratio, idx});
            }
        }

        if (!anyReady) {
            // advance to next arrival
            int nextArrival = std::numeric_limits<int>::max();
            for (int i = 0; i < n; ++i) if (!done[i]) nextArrival = std::min(nextArrival, processes[i].arrival);
            time = std::max(time + 1, nextArrival);
            continue;
        }

        // pick highest ratio
        auto it = ms.begin();
        int idx = it->second;

        int start = time;
        time += processes[idx].burst;
        int end = time;

        processes[idx].completion = end;
        processes[idx].turnaround = end - processes[idx].arrival;
        processes[idx].waiting = processes[idx].turnaround - processes[idx].burst;
        done[idx] = true;
        ++completed;

        chart.push_back({processes[idx].pid, start, end});
    }

    std::cout << "\n--- HRRN Scheduling (multiset rebuild) ---\n";
    print_result(processes);
    std::cout << "\nGantt Chart (HRRN):\n";
    print_gantt(chart);
}
