import React from 'react';

interface ResultDisplayProps {
    results: any[];
    ganttChart: any[];
}

const ResultDisplay: React.FC<ResultDisplayProps> = ({ results, ganttChart }) => {
    if (!results || results.length === 0) {
        return <div className="result-display"><p>No results to display</p></div>;
    }

    return (
        <div className="result-display">
            <h2>Scheduling Results</h2>
            <table>
                <thead>
                    <tr>
                        <th>Process ID</th>
                        <th>Completion Time</th>
                        <th>Turnaround Time</th>
                        <th>Waiting Time</th>
                    </tr>
                </thead>
                <tbody>
                    {results && results.map((result: any, index: number) => (
                        <tr key={index}>
                            <td>{result.pid}</td>
                            <td>{result.completion}</td>
                            <td>{result.turnaround}</td>
                            <td>{result.waiting}</td>
                        </tr>
                    ))}
                </tbody>
            </table>
            {ganttChart && ganttChart.length > 0 && (
                <>
                    <h2>Gantt Chart</h2>
                    <div className="gantt-chart">
                        {ganttChart.map((entry: any, index: number) => (
                            <div key={index} className="gantt-entry">
                                <span>Process {entry.pid}: {entry.start} → {entry.end}</span>
                            </div>
                        ))}
                    </div>
                </>
            )}
        </div>
    );
};

export default ResultDisplay;