#include "util.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>

// Robust input reader: ignores blank lines and lines starting with '#'
// Accepts lines with at least three integers: pid arrival burst
std::vector<Process> read_input(const std::string &filename) {
    std::vector<Process> procs;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: cannot open input file: " << filename << "\n";
        return procs;
    }

    std::string line;
    while (std::getline(file, line)) {
        // Trim leading spaces
        size_t pos = line.find_first_not_of(" \t\r\n");
        if (pos == std::string::npos) continue; // blank
        if (line[pos] == '#') continue;         // comment

        std::istringstream iss(line);
        int id, a, b;
        if (!(iss >> id >> a >> b)) {
            std::cerr << "Warning: skipping invalid line: \"" << line << "\"\n";
            continue;
        }
        Process p;
        p.pid = id;
        p.arrival = a;
        p.burst = b;
        p.remaining = b;
        p.waiting = 0;
        p.turnaround = 0;
        p.completion = 0;
        p.priority = 0;
        procs.push_back(p);
    }

    return procs;
}

void print_result(const std::vector<Process>& p) {
    if (p.empty()) {
        std::cout << "No processes to display.\n";
        return;
    }

    double total_wt = 0.0, total_tat = 0.0;
    std::cout << "\nProcess  Arrival  Burst  Waiting  Turnaround  Completion\n";
    for (const auto &x : p) {
        total_wt += x.waiting;
        total_tat += x.turnaround;
        std::cout << "P" << std::setw(3) << x.pid
                  << std::setw(9) << x.arrival
                  << std::setw(7) << x.burst
                  << std::setw(9) << x.waiting
                  << std::setw(11) << x.turnaround
                  << std::setw(11) << x.completion
                  << "\n";
    }

    double n = static_cast<double>(p.size());
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "\nAvg Waiting Time     : " << (total_wt / n) << "\n";
    std::cout << "Avg Turnaround Time  : " << (total_tat / n) << "\n";
}

// Simple ASCII Gantt chart printer
void print_gantt(const std::vector<GanttEntry>& chart) {
    if (chart.empty()) {
        std::cout << "Gantt: (no entries)\n";
        return;
    }

    // Top border
    std::cout << " ";
    for (size_t i = 0; i < chart.size(); ++i) std::cout << "------+";
    std::cout << "\n|";

    // Process labels centered roughly
    for (const auto &g : chart) {
        std::cout << "  P" << g.pid << "  |";
    }
    std::cout << "\n ";

    // Bottom border
    for (size_t i = 0; i < chart.size(); ++i) std::cout << "------+";
    std::cout << "\n";

    // Time markers: print start times then last end time
    for (const auto &g : chart) {
        std::cout << std::setw(3) << g.start << "   ";
    }
    std::cout << chart.back().end << "\n";
}
