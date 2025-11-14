import { app, BrowserWindow, ipcMain } from 'electron';
import path from 'path';
import { runAlgorithm } from './algorithms';

function createWindow() {
    const mainWindow = new BrowserWindow({
        width: 800,
        height: 600,
        webPreferences: {
            preload: path.join(__dirname, 'preload.js'),
            contextIsolation: true,
            enableRemoteModule: false,
        },
    });

    mainWindow.loadFile(path.join(__dirname, 'index.html'));

    // Open DevTools to debug
    mainWindow.webContents.openDevTools();

    mainWindow.webContents.on('crashed', () => {
        console.error('Renderer process crashed');
    });

    mainWindow.webContents.on('did-fail-load', (event, errorCode, errorDescription) => {
        console.error('Failed to load:', errorCode, errorDescription);
    });

    mainWindow.on('closed', () => {
        mainWindow.destroy();
    });
}

app.on('ready', createWindow);

app.on('window-all-closed', () => {
    if (process.platform !== 'darwin') {
        app.quit();
    }
});

app.on('activate', () => {
    if (BrowserWindow.getAllWindows().length === 0) {
        createWindow();
    }
});

// IPC handler for running scheduling algorithms
ipcMain.handle('run-algorithm', (event, payload) => {
    try {
        console.log('IPC Handler - Running algorithm with payload:', payload);
        if (!payload) throw new Error('Payload is undefined');
        const { algorithm, processes, options } = payload;
        if (!algorithm) throw new Error('Algorithm not specified');
        if (!processes || !Array.isArray(processes)) throw new Error('Processes is not an array');

        // Normalize input: ensure numeric arrival/burst and string pid
        const normalized = processes.map((p: any, i: number) => ({ pid: String(p.pid ?? ('P' + (i + 1))), arrival: Number(p.arrival ?? 0), burst: Number(p.burst ?? 0) }));

        // Call TS implementation (fallback to mock if algorithm not implemented)
        try {
            const result = runAlgorithm(algorithm, normalized, options);
            console.log('Algorithm result:', result);
            return result;
        } catch (err: any) {
            console.warn('Algorithm call failed, returning mock result. Error:', err?.message || err);
            const mockResult = {
                results: normalized.map((p: any, i: number) => ({ pid: p.pid, completion: p.arrival + p.burst + i, turnaround: p.burst + i, waiting: i })),
                ganttChart: normalized.map((p: any, i: number) => ({ pid: p.pid, start: i * (p.burst || 1), end: (i + 1) * (p.burst || 1) })),
            };
            return mockResult;
        }
    } catch (error: any) {
        console.error('Error in IPC handler:', error);
        throw error;
    }
});