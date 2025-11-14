#include "scheduler.h"
#include "util.h"
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

struct MLFQProcess {
    int pid;
    int burst;
    int arrival;
    int remaining;
    int priority;
    int waiting;
    int turnaround;
};

void mlfq(std::vector<MLFQProcess> processes) {
    int n = (int)processes.size();
    if (n == 0) { std::cout << "No processes.\n"; return; }

    std::vector<std::queue<MLFQProcess>> queues(3);
    std::vector<int> time_quantum = {4, 8, 16}; // Time quantums for each queue
    int time = 0, completed = 0;

    // Initialize the queues based on arrival time
    for (auto &process : processes) {
        process.remaining = process.burst;
        process.priority = 0; // Start in the highest priority queue
        queues[0].push(process);
    }

    while (completed < n) {
        for (int i = 0; i < queues.size(); ++i) {
            if (!queues[i].empty()) {
                MLFQProcess current = queues[i].front();
                queues[i].pop();

                int time_slice = std::min(time_quantum[i], current.remaining);
                time += time_slice;
                current.remaining -= time_slice;

                if (current.remaining == 0) {
                    current.turnaround = time - current.arrival;
                    current.waiting = current.turnaround - current.burst;
                    processes[current.pid] = current;
                    completed++;
                } else {
                    // Move to the next lower priority queue
                    if (i < queues.size() - 1) {
                        current.priority++;
                        queues[i + 1].push(current);
                    } else {
                        queues[i].push(current); // Stay in the same queue
                    }
                }
                break; // Break to restart the outer loop
            }
        }
    }

    std::cout << "\n--- MLFQ Scheduling ---\n";
    print_result(processes);
}