import React, { useState } from 'react';

const ProcessInput = ({ onSubmit }) => {
    const [pid, setPid] = useState('');
    const [arrival, setArrival] = useState('');
    const [burst, setBurst] = useState('');
    const [error, setError] = useState('');

    const handleSubmit = (e) => {
        e.preventDefault();
        if (!pid || !arrival || !burst) {
            setError('All fields are required.');
            return;
        }
        setError('');
        onSubmit({ pid, arrival: parseInt(arrival), burst: parseInt(burst) });
        setPid('');
        setArrival('');
        setBurst('');
    };

    return (
        <div className="process-input">
            <h2>Process Input</h2>
            <form onSubmit={handleSubmit}>
                <div>
                    <label>Process ID:</label>
                    <input
                        type="text"
                        value={pid}
                        onChange={(e) => setPid(e.target.value)}
                    />
                </div>
                <div>
                    <label>Arrival Time:</label>
                    <input
                        type="number"
                        value={arrival}
                        onChange={(e) => setArrival(e.target.value)}
                    />
                </div>
                <div>
                    <label>Burst Time:</label>
                    <input
                        type="number"
                        value={burst}
                        onChange={(e) => setBurst(e.target.value)}
                    />
                </div>
                {error && <p style={{ color: 'red' }}>{error}</p>}
                <button type="submit">Add Process</button>
            </form>
        </div>
    );
};

export default ProcessInput;