#include "scheduler.h"
#include "util.h"
#include <iostream>
#include <queue>
#include <vector>
#include <climits>
#include <algorithm>

void feedback(std::vector<Process> processes) {
    int n = (int)processes.size();
    if (n == 0) { std::cout << "No processes.\n"; return; }

    for (auto &p : processes) p.remaining = p.burst;
    
    std::vector<std::queue<int>> q(3);
    std::vector<bool> inQueue(n, false);
    const int tq0 = 2, tq1 = 4; 

    std::vector<int> order(n);
    for (int i = 0; i < n; ++i) order[i] = i;
    std::sort(order.begin(), order.end(), [&](int a, int b){
        if (processes[a].arrival != processes[b].arrival) return processes[a].arrival < processes[b].arrival;
        return processes[a].pid < processes[b].pid;
    });

    int oi = 0, time = 0, completed = 0;
    std::vector<GanttEntry> chart;

    while (completed < n) {
        while (oi < n && processes[order[oi]].arrival <= time) {
            int idx = order[oi++];
            q[0].push(idx);
            inQueue[idx] = true;
        }

        int idx = -1;
        int level = -1;
        if (!q[0].empty()) { idx = q[0].front(); q[0].pop(); level = 0; }
        else if (!q[1].empty()) { idx = q[1].front(); q[1].pop(); level = 1; }
        else if (!q[2].empty()) { idx = q[2].front(); q[2].pop(); level = 2; }
        else {
            if (oi < n) time = processes[order[oi]].arrival;
            else ++time;
            continue;
        }

        if (level == 0) {
            int exec = std::min(tq0, processes[idx].remaining);
            int start = time; time += exec; processes[idx].remaining -= exec;
            chart.push_back({processes[idx].pid, start, time});

            while (oi < n && processes[order[oi]].arrival <= time) {
                int j = order[oi++]; q[0].push(j); inQueue[j] = true;
            }
            if (processes[idx].remaining > 0) q[1].push(idx);
            else {
                processes[idx].completion = time;
                processes[idx].turnaround = processes[idx].completion - processes[idx].arrival;
                processes[idx].waiting = processes[idx].turnaround - processes[idx].burst;
                ++completed;
            }
        } else if (level == 1) {
            int exec = std::min(tq1, processes[idx].remaining);
            int start = time; time += exec; processes[idx].remaining -= exec;
            chart.push_back({processes[idx].pid, start, time});
            while (oi < n && processes[order[oi]].arrival <= time) {
                int j = order[oi++]; q[0].push(j); inQueue[j] = true;
            }
            if (processes[idx].remaining > 0) q[2].push(idx);
            else {
                processes[idx].completion = time;
                processes[idx].turnaround = processes[idx].completion - processes[idx].arrival;
                processes[idx].waiting = processes[idx].turnaround - processes[idx].burst;
                ++completed;
            }
        } else {
            int start = time; time += processes[idx].remaining; processes[idx].remaining = 0;
            chart.push_back({processes[idx].pid, start, time});
            while (oi < n && processes[order[oi]].arrival <= time) {
                int j = order[oi++]; q[0].push(j); inQueue[j] = true;
            }
            processes[idx].completion = time;
            processes[idx].turnaround = processes[idx].completion - processes[idx].arrival;
            processes[idx].waiting = processes[idx].turnaround - processes[idx].burst;
            ++completed;
        }
    }

    std::cout << "\n--- Multilevel Feedback Queue (vector<queue>) ---\n";
    print_result(processes);
    std::cout << "\nGantt Chart (Feedback):\n";
    print_gantt(chart);
}
