#include "scheduler.h"
#include "util.h"
#include <iostream>
#include <vector>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

static void run_all_schedulers_for(const std::string &label, std::vector<Process> processes) {
    if (processes.empty()) {
        std::cerr << "Warning: no processes for " << label << "\n";
        return;
    }
    std::cout << "\n=== Results for: " << label << " ===\n";
    fcfs(processes);
    std::cout << "\n";
    sjf(processes);
    std::cout << "\n";
    srt(processes);
    std::cout << "\n";
    // default quantum 2 for RR when run in batch
    rr(processes, 2);
    std::cout << "\n";
    hrrn(processes);
    std::cout << "\n";
    feedback(processes);
}

int main(int argc, char** argv) {
    // If a filename is provided, use it. If --all-tests given, iterate testcases/
    if (argc > 1) {
        std::string arg = argv[1];
        if (arg == "--all-tests") {
            const fs::path tests_dir = "testcases";
            if (!fs::exists(tests_dir) || !fs::is_directory(tests_dir)) {
                std::cerr << "No testcases directory found.\n";
                return 1;
            }
            for (auto &entry : fs::directory_iterator(tests_dir)) {
                if (!entry.is_regular_file()) continue;
                auto path = entry.path();
                auto procs = read_input(path.string());
                run_all_schedulers_for(path.filename().string(), procs);
            }
            return 0;
        } else {
            std::string infile = arg;
            bool batch_mode = false;
            if (argc > 2) {
                std::string a2 = argv[2];
                if (a2 == "--batch" || a2 == "-b") batch_mode = true;
            }
            auto processes = read_input(infile);
            if (processes.empty()) {
                std::cerr << "Error: no processes loaded from '" << infile << "'.\n";
                return 1;
            }

            if (batch_mode) {
                // Run all schedulers non-interactively for this file
                run_all_schedulers_for(infile, processes);
                return 0;
            }

            std::cout << "\nCPU Scheduling Algorithms\n";
            std::cout << "1. FCFS\n2. SJF (Non-preemptive)\n3. SRTF (Preemptive SJF)\n4. Round Robin\n5. HRRN\n6. Multilevel Feedback Queue\n";
            std::cout << "Enter your choice: ";

            int choice = 0;
            if (!(std::cin >> choice)) {
                std::cerr << "Invalid input. Exiting.\n";
                return 1;
            }

            switch (choice) {
                case 1:
                    fcfs(processes);
                    break;
                case 2:
                    sjf(processes);
                    break;
                case 3:
                    srt(processes);
                    break;
                case 4: {
                    int quantum;
                    std::cout << "Enter quantum: ";
                    if (!(std::cin >> quantum)) { quantum = 2; }
                    rr(processes, quantum);
                    break;
                }
                case 5:
                    hrrn(processes);
                    break;
                case 6:
                    feedback(processes);
                    break;
                default:
                    std::cerr << "Invalid choice. Exiting.\n";
                    return 1;
            }
            return 0;
        }
    }

    // No args: use default interactive flow on input.txt
    std::vector<Process> processes = read_input("input.txt");
    if (processes.empty()) {
        std::cerr << "Error: no processes loaded. Check input.txt (remove non-data lines or add data).\n";
        return 1;
    }

    std::cout << "\nCPU Scheduling Algorithms\n";
    std::cout << "1. FCFS\n2. SJF (Non-preemptive)\n3. SRTF (Preemptive SJF)\n4. Round Robin\n5. HRRN\n6. Multilevel Feedback Queue\n";
    std::cout << "Enter your choice: ";

    int choice = 0;
    if (!(std::cin >> choice)) {
        std::cerr << "Invalid input. Exiting.\n";
        return 1;
    }

    switch (choice) {
        case 1:
            fcfs(processes);
            break;
        case 2:
            sjf(processes);
            break;
        case 3:
            srt(processes);
            break;
        case 4: {
            int quantum;
            std::cout << "Enter quantum: ";
            if (!(std::cin >> quantum)) { quantum = 2; }
            rr(processes, quantum);
            break;
        }
        case 5:
            hrrn(processes);
            break;
        case 6:
            feedback(processes);
            break;
        default:
            std::cerr << "Invalid choice. Exiting.\n";
            return 1;
    }

    return 0;
}

