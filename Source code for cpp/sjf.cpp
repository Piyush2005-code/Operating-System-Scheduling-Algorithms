#include "scheduler.h"
#include "util.h"
#include <iostream>
#include <queue>
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;

struct SJFItem {
    int burst;
    int arrival;
    int idx;
};
struct SJFComp {
    bool operator()(const SJFItem &a, const SJFItem &b) const {
        if (a.burst != b.burst) return a.burst > b.burst; 
        if (a.arrival != b.arrival) return a.arrival > b.arrival;
        return a.idx > b.idx;
    }
};

void sjf(vector<Process> processes) {
    int n = (int)processes.size();
    if (n == 0) {cout << "No processes.\n"; return; }

    
    vector<int> order(n);
    for (int i = 0; i < n; ++i) order[i] = i;
    sort(order.begin(), order.end(), [&](int a, int b){
        if (processes[a].arrival != processes[b].arrival) return processes[a].arrival < processes[b].arrival;
        return processes[a].pid < processes[b].pid;
    });

    priority_queue<SJFItem,vector<SJFItem>, SJFComp> heap;
    int time = 0, oi = 0, completed = 0;
    vector<GanttEntry> chart;

    while (completed < n) {
    
        while (oi < n && processes[order[oi]].arrival <= time) {
            int idx = order[oi++];
            heap.push({processes[idx].burst, processes[idx].arrival, idx});
        }

        if (heap.empty()) {
           
            if (oi < n) time = processes[order[oi]].arrival;
            continue;
        }

        auto top = heap.top(); heap.pop();
        int idx = top.idx;
        int start = max(time, processes[idx].arrival);
        int end = start + processes[idx].burst;
        time = end;

        processes[idx].completion = end;
        processes[idx].turnaround = end - processes[idx].arrival;
        processes[idx].waiting = processes[idx].turnaround - processes[idx].burst;
        ++completed;

        chart.push_back({processes[idx].pid, start, end});
    }

    cout << "\n--- SJF Scheduling (min-heap) ---\n";
    print_result(processes);
    cout << "\nGantt Chart (SJF):\n";
    print_gantt(chart);
}
