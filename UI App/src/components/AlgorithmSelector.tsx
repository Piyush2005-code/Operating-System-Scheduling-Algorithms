import React from 'react';

const algorithms = [
    { name: 'First-Come, First-Served (FCFS)', value: 'fcfs' },
    { name: 'Round Robin (RR)', value: 'rr' },
    { name: 'Highest Response Ratio Next (HRRN)', value: 'hrrn' },
    { name: 'Multi-Level Feedback Queue (MLFQ)', value: 'mlfq' },
    { name: 'Shortest Job First (SJF)', value: 'sjf' },
    { name: 'Shortest Remaining Time (SRT)', value: 'srt' },
];

const AlgorithmSelector: React.FC<{ onSelect: (algorithm: string) => void }> = ({ onSelect }) => {
    return (
        <div className="algorithm-selector">
            <h2>Select Scheduling Algorithm</h2>
            <select onChange={(e) => onSelect(e.target.value)} defaultValue="">
                <option value="">-- Select an Algorithm --</option>
                {algorithms.map((algorithm) => (
                    <option key={algorithm.value} value={algorithm.value}>
                        {algorithm.name}
                    </option>
                ))}
            </select>
        </div>
    );
};

export default AlgorithmSelector;