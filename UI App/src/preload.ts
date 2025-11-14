import { contextBridge, ipcRenderer } from 'electron';

contextBridge.exposeInMainWorld('api', {
    runAlgorithm: (algorithm: string, processes: any[]) => 
        ipcRenderer.invoke('run-algorithm', { algorithm, processes }),
    onResult: (callback: any) => ipcRenderer.on('algorithm-result', (event: any, result: any) => callback(result)),
});