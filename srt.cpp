#include "scheduler.h"
#include "util.h"
#include <iostream>
#include <queue>
#include <vector>
#include <limits>
#include <algorithm>
using namespace std;

struct SRTItem {
    int rem;
    int arrival;
    int idx;
};
struct SRTComp {
    bool operator()(const SRTItem &a, const SRTItem &b) const {
        if (a.rem != b.rem) return a.rem > b.rem;
        if (a.arrival != b.arrival) return a.arrival > b.arrival;
        return a.idx > b.idx;
    }
};

void srt(vector<Process> processes) {
    int n = (int)processes.size();
    if (n == 0) { cout << "No processes.\n"; return; }

    for (auto &p : processes) p.remaining = p.burst;

    vector<int> order(n);
    for (int i = 0; i < n; ++i) order[i] = i;
    sort(order.begin(), order.end(), [&](int a, int b){
        if (processes[a].arrival != processes[b].arrival) return processes[a].arrival < processes[b].arrival;
        return processes[a].pid < processes[b].pid;
    });

    priority_queue<SRTItem, std::vector<SRTItem>, SRTComp> heap;
    int oi = 0, time = 0, completed = 0;
    vector<GanttEntry> chart;
    int runningIdx = -1;
    int lastStart = -1;

    while (completed < n) {
        while (oi < n && processes[order[oi]].arrival <= time) {
            int idx = order[oi++];
            heap.push({processes[idx].remaining, processes[idx].arrival, idx});
        }

        if (heap.empty()) {
            if (oi < n) time = processes[order[oi]].arrival;
            continue;
        }

        SRTItem cur = heap.top(); heap.pop();
        int idx = cur.idx;

        if (runningIdx != idx) {
            if (runningIdx != -1) {
                chart.push_back({processes[runningIdx].pid, lastStart, time});
            }
            runningIdx = idx;
            lastStart = time;
        }

        processes[idx].remaining -= 1;
        time += 1;

        while (oi < n && processes[order[oi]].arrival <= time) {
            int j = order[oi++];
            heap.push({processes[j].remaining, processes[j].arrival, j});
        }

        if (processes[idx].remaining > 0) {
            heap.push({processes[idx].remaining, processes[idx].arrival, idx});
        } else {
            processes[idx].completion = time;
            processes[idx].turnaround = processes[idx].completion - processes[idx].arrival;
            processes[idx].waiting = processes[idx].turnaround - processes[idx].burst;
            ++completed;
            chart.push_back({processes[idx].pid, lastStart, time});
            runningIdx = -1;
            lastStart = -1;
        }
    }

    std::cout << "\n--- SRTF Scheduling (min-heap preemptive) ---\n";
    print_result(processes);
    std::cout << "\nGantt Chart (SRTF):\n";
    print_gantt(chart);
}
