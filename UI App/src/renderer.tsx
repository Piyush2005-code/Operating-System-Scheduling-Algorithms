import React, { useState } from 'react';
import ReactDOM from 'react-dom';
import AlgorithmSelector from './components/AlgorithmSelector';
import ProcessInput from './components/ProcessInput';
import ResultDisplay from './components/ResultDisplay';
import './styles/main.css';

// Declare the window API exposed by preload
declare const window: any;

const App = () => {
    const [algorithm, setAlgorithm] = useState<string>('');
    const [processes, setProcesses] = useState<any[]>([]);
    const [results, setResults] = useState<any>(null);

    const handleAlgorithmChange = (selectedAlgorithm: string) => {
        setAlgorithm(selectedAlgorithm);
    };

    const handleProcessInput = (inputProcess: any) => {
        setProcesses([...processes, inputProcess]);
    };

    const handleRunAlgorithm = async () => {
        try {
            if (!algorithm) {
                alert('Please select an algorithm');
                return;
            }
            if (processes.length === 0) {
                alert('Please add at least one process');
                return;
            }
            const response = await window.api.runAlgorithm(algorithm, processes);
            setResults(response);
        } catch (error) {
            console.error('Error running algorithm:', error);
            alert('Error running algorithm: ' + error);
        }
    };

    return (
        <div className="app">
            <h1>Scheduling Algorithms Simulator</h1>
            <AlgorithmSelector onSelect={handleAlgorithmChange} />
            <ProcessInput onSubmit={handleProcessInput} />
            <div>
                <p>Processes added: {processes.length}</p>
                {processes.length > 0 && (
                    <ul>
                        {processes.map((p, i) => (
                            <li key={i}>PID: {p.pid}, Arrival: {p.arrival}, Burst: {p.burst}</li>
                        ))}
                    </ul>
                )}
            </div>
            <button onClick={handleRunAlgorithm} disabled={!algorithm || processes.length === 0}>
                Run Algorithm
            </button>
            {results && <ResultDisplay results={results.results || results} ganttChart={results.ganttChart || []} />}
        </div>
    );
};

const rootElement = document.getElementById('root');
if (rootElement) {
    ReactDOM.render(<App />, rootElement);
} else {
    console.error('Root element not found');
}