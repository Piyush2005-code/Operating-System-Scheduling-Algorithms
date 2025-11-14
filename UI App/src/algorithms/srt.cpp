#include "scheduler.h"
#include "util.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

// min-heap item: (remaining time, arrival, index)
struct SRTItem {
    int remaining;
    int arrival;
    int idx;
};
struct SRTComp {
    bool operator()(const SRTItem &a, const SRTItem &b) const {
        if (a.remaining != b.remaining) return a.remaining > b.remaining; // smaller remaining time first
        if (a.arrival != b.arrival) return a.arrival > b.arrival;
        return a.idx > b.idx;
    }
};

void srt(std::vector<Process> processes) {
    int n = (int)processes.size();
    if (n == 0) { std::cout << "No processes.\n"; return; }

    // sort by arrival for feeding the heap
    std::vector<int> order(n);
    for (int i = 0; i < n; ++i) order[i] = i;
    std::sort(order.begin(), order.end(), [&](int a, int b){
        if (processes[a].arrival != processes[b].arrival) return processes[a].arrival < processes[b].arrival;
        return processes[a].pid < processes[b].pid;
    });

    std::priority_queue<SRTItem, std::vector<SRTItem>, SRTComp> heap;
    int time = 0, oi = 0, completed = 0;
    std::vector<GanttEntry> chart;

    while (completed < n) {
        // push arrived processes into heap
        while (oi < n && processes[order[oi]].arrival <= time) {
            int idx = order[oi++];
            heap.push({processes[idx].burst, processes[idx].arrival, idx});
        }

        if (heap.empty()) {
            // advance to next arrival
            if (oi < n) time = processes[order[oi]].arrival;
            continue;
        }

        auto top = heap.top(); heap.pop();
        int idx = top.idx;
        int start = std::max(time, processes[idx].arrival);
        time = start + 1; // increment time by 1 unit

        processes[idx].remaining = top.remaining - 1; // decrement remaining time

        if (processes[idx].remaining == 0) {
            int end = time;
            processes[idx].completion = end;
            processes[idx].turnaround = end - processes[idx].arrival;
            processes[idx].waiting = processes[idx].turnaround - processes[idx].burst;
            ++completed;

            chart.push_back({processes[idx].pid, start, end});
        } else {
            heap.push({processes[idx].remaining, processes[idx].arrival, idx});
            chart.push_back({processes[idx].pid, start, time});
        }
    }

    std::cout << "\n--- SRT Scheduling (min-heap) ---\n";
    print_result(processes);
    std::cout << "\nGantt Chart (SRT):\n";
    print_gantt(chart);
}