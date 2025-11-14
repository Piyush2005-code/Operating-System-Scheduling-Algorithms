# Scheduling Algorithms App

This Electron application implements various CPU scheduling algorithms, allowing users to input process details and visualize the scheduling results. The following algorithms are included:

- First-Come, First-Served (FCFS)
- Round Robin (RR)
- Highest Response Ratio Next (HRRN)
- Multi-Level Feedback Queue (MLFQ)
- Shortest Job First (SJF)
- Shortest Remaining Time (SRT)

## Project Structure

```
scheduling-algorithms-app
├── src
│   ├── main.ts                # Main entry point of the Electron application
│   ├── preload.ts             # Preload script for exposing APIs to the renderer
│   ├── renderer.ts            # Rendering logic and UI management
│   ├── algorithms             # Contains implementations of scheduling algorithms
│   │   ├── fcfs.cpp           # FCFS scheduling algorithm implementation
│   │   ├── rr.cpp             # RR scheduling algorithm implementation
│   │   ├── hrrn.cpp           # HRRN scheduling algorithm implementation
│   │   ├── mlfq.cpp           # MLFQ scheduling algorithm implementation
│   │   ├── sjf.cpp            # SJF scheduling algorithm implementation
│   │   ├── srt.cpp            # SRT scheduling algorithm implementation
│   │   ├── scheduler.h        # Header file for scheduling algorithms
│   │   └── util.h             # Utility functions and definitions
│   ├── components             # React components for the application
│   │   ├── AlgorithmSelector.ts # Component for selecting scheduling algorithm
│   │   ├── ProcessInput.ts    # Component for inputting process details
│   │   └── ResultDisplay.ts    # Component for displaying results
│   └── styles                 # Styles for the application
│       └── main.css           # Main CSS file
├── public
│   └── index.html             # Main HTML file for the Electron application
├── package.json               # npm configuration file
├── tsconfig.json              # TypeScript configuration file
├── webpack.config.js          # Webpack configuration file
└── README.md                  # Project documentation
```

## Setup Instructions

1. Clone the repository:
   ```
   # Scheduling Algorithms Simulator (Electron + React + TypeScript)

   This is the Scheduling Algorithms Simulator desktop app (Electron renderer uses React + TypeScript). It provides a UI to enter processes, choose scheduling algorithms, run simulations, and view results (table + Gantt chart).

   The app currently uses a mocked IPC handler for algorithm results to make UI development easier. The repository includes C/C++ algorithm sources which can be integrated into the main process later.

   ## Where you are

   Project folder: `App/scheduling-algorithms-app`

   Key files:
   - `src/main.ts` — Electron main process (creates BrowserWindow, sets preload).
   - `src/preload.ts` — Preload script which exposes a safe `window.api` for renderer IPC.
   - `src/renderer.tsx` — React entry for the UI.
   - `src/components/` — React components (AlgorithmSelector, ProcessInput, ResultDisplay).
   - `src/styles/main.css` — App styling.
   - `webpack.config.js` — Multi-compiler config (main, preload, renderer).
   - `dist/` — Compiled output after running the build (contains `main.js`, `preload.js`, `renderer.js`, `index.html`).

   ---

   ## Prerequisites

   - Node.js (recommended LTS: Node 18+). The project was debugged on Node 12, but upgrading to Node 16/18 reduces warnings and improves compatibility with modern packages.
   - npm (the Node package manager)
   - `npx` (comes with npm 5.2+)

   If you use `nvm`, you can set a local Node version quickly:

   ```bash
   nvm install 18
   nvm use 18
   ```

   ---

   ## Install dependencies

   From the app folder:

   ```bash
   cd App/scheduling-algorithms-app
   npm install
   ```

   Note: if you see warnings about "Unsupported engine", it means your global Node version is older than some packages require — upgrading Node is recommended.

   ---

   ## Build & Run

   1. Build (produces `dist/` with `main.js`, `preload.js`, `renderer.js`, `index.html`):

   ```bash
   npx webpack --mode production
   # or
   npm run build
   ```

   2. Start Electron:

   ```bash
   npm start
   ```

   Important: The Electron main process expects `dist/main.js` and the BrowserWindow preload path to point to `dist/preload.js`. Make sure you build before `npm start`. If `dist/preload.js` is missing, `window.api` will not be exposed and the renderer will fail to call `window.api.runAlgorithm()`.

   ---

   ## Development

   For iterative development you can use the dev build (this project uses webpack to bundle both renderer and main/preload):

   ```bash
   npm run dev
   # then in a separate terminal (after build completes) run
   npm start
   ```

   The app's `main.ts` currently opens DevTools automatically for debugging.

   ---

   ## Quick manual checks (helpful when debugging runtime issues)

   - Confirm `dist/preload.js` exists after the build:

   ```bash
   ls -la dist/preload.js
   ```

   - If `window.api` is undefined in the DevTools console, check preload loaded correctly:

   ```js
   // In the app's DevTools console
   !!window.api            // should be true
   typeof window.api.runAlgorithm  // should be 'function'
   ```

   - If a runtime problem occurs, check the app log (I sometimes redirect start output to `/tmp/app.log` during debugging):

   ```bash
   tail -f /tmp/app.log
   ```

   - If Electron complains about `Cannot find module 'dist/main.js'`, ensure you built successfully (see `dist/` files) and that `package.json` `main` entry points to `dist/main.js`.

   ---

   ## How IPC currently works

   - `src/preload.ts` exposes a safe API in the renderer via `contextBridge.exposeInMainWorld('api', {...})`.
   - The renderer calls `window.api.runAlgorithm(algorithm, processes)` and receives a Promise result.
   - `src/main.ts` registers an IPC handler (`ipcMain.handle('run-algorithm', ...)`) that currently returns mocked scheduling results.

   This separation (preload ↔ main ↔ renderer) preserves context isolation and follows Electron's recommended secure pattern.

   ---

   ## Integrating the native algorithms (C/C++)

   Currently the main process returns mock results for quick UI testing. The C/C++ algorithm implementations are present in the repo (look in `src/algorithms` or the sibling top-level folder). To integrate:

   Options:
   1. Build the C/C++ files as a command-line binary and spawn it from the main process (use `child_process.spawn` or `exec`). Pass process data via stdin or command-line args and parse stdout.
   2. Create a Node native addon (N-API / node-gyp) and call functions directly from `main.ts` — more performant but more involved.
   3. Use WebAssembly to compile algorithm code and call from the renderer — viable for small code but requires exposing data across IPC.

   When implementing, validate input sanitization and keep heavy computation off the renderer thread (do it in main or a worker thread).

   ---

   ## Known issues & notes

   - If `window.api` is undefined in the renderer, the most common reason is missing `dist/preload.js` (build step omitted) or the BrowserWindow preload path is wrong.
   - Webpack multi-config builds previously used `clean-webpack-plugin` incorrectly which caused `preload.js`/`main.js` to be removed. The config was adjusted so builds emit all entries without deleting other outputs unexpectedly.
   - You may see `Unsupported engine` warnings during `npm install` if your Node version is older than some dependency requirements — upgrading Node is recommended.

   ---

   ## Next steps / suggestions

   - Replace mock algorithm results with actual algorithm outputs (spawn compiled C++ binaries or implement native addon).
   - Add tests that validate each scheduling algorithm with known testcases (there is a `testcases/` folder in the top-level project that can be used).
   - Add a `dev:watch` script and a proper hot reload setup for the renderer.
   - Pin dependencies to specific versions if you want reproducible installs across machines.

   ---

   ## Contact / Help

   If you'd like, I can:
   - Wire the C/C++ algorithm implementations into the main process (spawn or native addon),
   - Add automated tests for algorithms,
   - Add a `Makefile` / helper scripts to build the native code and run the Electron app.

   Open an issue or reply here with which integration you'd like next.

   ---

   Thank you — the app is currently building and running (UI wired to a mocked IPC backend). Let me know if you want the algorithms hooked up to native code next.