#ifndef UTIL_H
#define UTIL_H

#include "process.h"
#include <vector>
#include <string>

struct GanttEntry {
    int pid;
    int start;
    int end;
};

std::vector<Process> read_input(const std::string &filename);
void print_result(const std::vector<Process>& processes);
void print_gantt(const std::vector<GanttEntry>& chart);

#endif
