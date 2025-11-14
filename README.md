# Operating System Scheduling Algorithms

## Overview

This repository contains implementations of CPU scheduling algorithms in two forms:
1. **C++ CLI Application**: Command-line scheduler with multiple algorithm implementations
2. **Electron Desktop Application**: Interactive GUI built with React and TypeScript for visualizing scheduling algorithms

The project is designed for teaching, experiments, and demonstrations of various CPU scheduling algorithms including FCFS, SJF, SRTF, Round Robin, HRRN, and Multi-Level Feedback Queue.

## Project Structure

```
Operating-System-Scheduling-Algorithms/
├── App/                          # Electron desktop application
│   ├── src/
│   │   ├── main.ts               # Electron main process
│   │   ├── preload.ts            # Preload script for IPC
│   │   ├── renderer.tsx          # React UI entry point
│   │   ├── algorithms/           # Algorithm implementations
│   │   └── components/           # React UI components
│   ├── public/
│   │   └── index.html            # HTML template
│   ├── dist/                     # Build output directory
│   ├── package.json              # Node.js dependencies
│   ├── tsconfig.json             # TypeScript configuration
│   └── webpack.config.js         # Webpack build configuration
├── testcases/                    # Example input files for testing
├── main.cpp                      # CLI driver for C++ scheduler
├── scheduler.h                   # Scheduler function declarations
├── process.h                     # Process structure definition
├── util.h                        # Utility function declarations
├── util.cpp                      # Input/output utilities
├── fcfs.cpp                      # FCFS algorithm implementation
├── sjf.cpp                       # SJF algorithm implementation
├── srt.cpp                       # SRTF algorithm implementation
├── rr.cpp                        # Round Robin implementation
├── hrrn.cpp                      # HRRN algorithm implementation
├── feedback.cpp                  # MLFQ implementation
├── Makefile                      # Build configuration for C++ code
└── Dockerfile                    # Container setup for reproducible builds
```

## Implemented Algorithms

### C++ CLI Algorithms
1. **FCFS (First-Come, First-Served)**: Non-preemptive scheduling based on arrival order
2. **SJF (Shortest Job First)**: Non-preemptive scheduling selecting shortest burst time
3. **SRTF (Shortest Remaining Time First)**: Preemptive version of SJF
4. **Round Robin**: Time-sliced preemptive scheduling with configurable quantum
5. **HRRN (Highest Response Ratio Next)**: Non-preemptive scheduling optimizing response ratio
6. **Multi-Level Feedback Queue**: Multi-level queue with priority aging

### Electron App Algorithms
All algorithms from the C++ CLI, plus:
- Interactive process input
- Real-time Gantt chart visualization
- Results table with calculated metrics (completion time, turnaround time, waiting time)

## Getting Started

### Prerequisites

#### For C++ CLI Application
- C++ compiler with C++17 support (g++, clang++)
- make
- Optional: Docker for containerized builds

#### For Electron Desktop Application
- Node.js (LTS version 18+)
- npm (comes with Node.js)

### Building and Running the C++ CLI

#### Native Build

1. Build the scheduler:
```bash
make
```

2. Run with a specific input file:
```bash
./scheduler testcases/test_short_jobs.txt
```

3. Run all testcases in batch mode:
```bash
./scheduler --all-tests
```

4. Run with interactive menu:
```bash
./scheduler input.txt
```

5. Clean build artifacts:
```bash
make clean
```

#### Docker Build

1. Build Docker image:
```bash
make docker-build
```

2. Run in container:
```bash
docker run -it scheduler:latest
```

### Building and Running the Electron App

1. Navigate to the App directory:
```bash
cd App
```

2. Install dependencies:
```bash
npm install
```

3. Build the application:
```bash
npm run build
```

4. Start the application:
```bash
npm start
```

#### Development Mode

For iterative development:
```bash
npm run dev
```

The app opens with DevTools enabled for debugging.

### Using the Electron App

1. **Select an Algorithm**: Choose from the dropdown menu (FCFS, RR, HRRN, MLFQ, SJF, SRT)
2. **Add Processes**: 
   - Enter Process ID (e.g., "P1")
   - Enter Arrival Time (e.g., 0)
   - Enter Burst Time (e.g., 5)
   - Click "Add Process"
   - Repeat to add more processes
3. **Run Algorithm**: Click "Run Algorithm" to execute and view results
4. **View Results**:
   - Results table shows completion time, turnaround time, and waiting time
   - Gantt chart displays visual timeline of process execution

## Input File Format

The C++ CLI reads process data from text files with the following format:

```
# Lines starting with # are comments
# Format: ProcessID ArrivalTime BurstTime
1 0 5
2 1 3
3 2 2
```

Example testcases are provided in the `testcases/` directory.

## Testing

### C++ CLI Tests
Test files are located in `testcases/` and cover various scenarios:
- `test_short_jobs.txt`: Testing SJF advantages
- `test_convoy.txt`: Demonstrating convoy effect in FCFS
- `test_rr_fairness.txt`: Round Robin time-slicing behavior
- `test_preempt_advantage.txt`: Benefits of preemptive scheduling
- `test_starvation_vs_hrrn.txt`: HRRN preventing starvation
- `test_feedback_mixed.txt`: Multi-level feedback queue behavior

Run all tests:
```bash
./scheduler --all-tests
```

### Electron App Testing

The Electron app currently uses mocked algorithm results for UI development. To integrate actual C++ algorithms:

**Option 1**: Spawn the compiled C++ binary from the main process using `child_process`
**Option 2**: Create a Node.js native addon (N-API) for direct function calls
**Option 3**: Compile algorithms to WebAssembly

## Development

### C++ Code Structure
- `main.cpp`: Entry point, command-line argument parsing
- `scheduler.h/cpp files`: Individual algorithm implementations
- `util.cpp`: Input parsing and output formatting
- `process.h`: Process data structure

### Electron App Structure
- `main.ts`: Electron main process, window management, IPC handlers
- `preload.ts`: Secure bridge between renderer and main process
- `renderer.tsx`: React application root
- `components/`: React components for UI sections
- `webpack.config.js`: Multi-compiler configuration for bundling

### IPC Communication Flow
1. Renderer calls `window.api.runAlgorithm(algorithm, processes)`
2. Preload script forwards to main process via `ipcRenderer.invoke`
3. Main process handles request in `ipcMain.handle('run-algorithm')`
4. Result is returned to renderer via Promise

## Known Issues and Notes

### Electron App
- `window.api` undefined: Ensure `dist/preload.js` exists after build
- Build issues: Make sure all dependencies are installed with `npm install`
- Node version warnings: Upgrade to Node 18+ for best compatibility

### C++ CLI
- Interactive mode requires user input via stdin
- Use batch mode (`--batch` flag) for automated testing

## CI/CD and Reproducibility

The project includes:
- `Makefile` for automated C++ builds
- `Dockerfile` for containerized builds
- Test scripts for validation
- Consistent build environment setup

## Next Steps

Potential improvements:
- Integrate C++ algorithms into Electron app main process
- Add automated tests for algorithm correctness
- Implement hot reload for React development
- Add export/save functionality for results
- Add historical results tracking
- Pin dependency versions for reproducibility

## License

MIT

## Contributing

Contributions are welcome! Please feel free to submit issues or pull requests for:
- Bug fixes
- New algorithm implementations
- UI improvements
- Documentation enhancements
- Test coverage expansion
