#include "scheduler.h"
#include "util.h"
#include <iostream>
#include <queue>
#include <vector>
#include <climits>
#include <algorithm>

void rr(std::vector<Process> processes, int quantum) {
    int n = (int)processes.size();
    if (n == 0) { std::cout << "No processes.\n"; return; }
    if (quantum <= 0) quantum = 1;

    for (auto &p : processes) p.remaining = p.burst;

    std::queue<int> q;
    std::vector<bool> inQueue(n, false);
    std::vector<GanttEntry> chart;

    
    std::vector<int> order(n);
    for (int i = 0; i < n; ++i) order[i] = i;
    std::sort(order.begin(), order.end(), [&](int a, int b){
        if (processes[a].arrival != processes[b].arrival) return processes[a].arrival < processes[b].arrival;
        return processes[a].pid < processes[b].pid;
    });

    int oi = 0, time = 0, completed = 0;

   
    while (oi < n && processes[order[oi]].arrival <= time) { q.push(order[oi]); inQueue[order[oi]] = true; ++oi; }

    while (completed < n) {
        if (q.empty()) {
            
            if (oi < n) time = processes[order[oi]].arrival;
            while (oi < n && processes[order[oi]].arrival <= time) { q.push(order[oi]); inQueue[order[oi]] = true; ++oi; }
            continue;
        }

        int idx = q.front(); q.pop();

        int exec = std::min(quantum, processes[idx].remaining);
        int start = time;
        time += exec;
        processes[idx].remaining -= exec;
        chart.push_back({processes[idx].pid, start, time});

       
        while (oi < n && processes[order[oi]].arrival <= time) {
            if (!inQueue[order[oi]] && processes[order[oi]].remaining > 0) {
                q.push(order[oi]);
                inQueue[order[oi]] = true;
            }
            ++oi;
        }

        if (processes[idx].remaining == 0) {
            processes[idx].completion = time;
            processes[idx].turnaround = processes[idx].completion - processes[idx].arrival;
            processes[idx].waiting = processes[idx].turnaround - processes[idx].burst;
            ++completed;
        } else {
            q.push(idx); 
        }
    }

    std::cout << "\n--- Round Robin Scheduling (queue) ---\n";
    print_result(processes);
    std::cout << "\nGantt Chart (RR):\n";
    print_gantt(chart);
}
