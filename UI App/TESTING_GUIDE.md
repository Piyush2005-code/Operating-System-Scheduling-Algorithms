# Scheduling Algorithms Simulator - Testing Guide

## ✅ What Was Fixed

### Issue 1: Empty Window
**Problem**: Window opened but showed no content
**Solution**: 
- Fixed React rendering with proper element detection
- Updated CSS to ensure proper layout and visibility
- Added error handling in renderer

### Issue 2: Algorithm Execution Error
**Problem**: "Error invoking remote method 'run-algorithm': Type error: cannot read property 'map' of undefined"
**Solution**:
- Fixed preload script to pass arguments as an object to ipcRenderer.invoke
- Updated IPC handler to properly destructure and validate payload
- Added comprehensive error handling and logging

## 🚀 How to Test the App

### Step 1: Build the Project
```bash
cd /home/piyush/Documents/VS_Code_Workspace/DSA_Project/App/scheduling-algorithms-app
npx webpack --mode production
```

### Step 2: Start the App
```bash
npm start
```

### Step 3: Test the UI

1. **Select an Algorithm**
   - Click the "Select Scheduling Algorithm" dropdown
   - Choose one of the available algorithms:
     - First-Come, First-Served (FCFS)
     - Round Robin (RR)
     - Highest Response Ratio Next (HRRN)
     - Multi-Level Feedback Queue (MLFQ)
     - Shortest Job First (SJF)
     - Shortest Remaining Time (SRT)

2. **Add Processes**
   - Enter Process ID (e.g., "P1")
   - Enter Arrival Time (e.g., 0)
   - Enter Burst Time (e.g., 5)
   - Click "Add Process"
   - Repeat to add more processes

3. **Run Algorithm**
   - Once you've selected an algorithm and added at least one process
   - Click the "Run Algorithm" button
   - Results should appear showing:
     - **Results Table**: Process ID, Completion Time, Turnaround Time, Waiting Time
     - **Gantt Chart**: Visual representation of process execution

## 📊 Expected Output Example

When you add processes like:
- P1: Arrival=0, Burst=5
- P2: Arrival=1, Burst=3
- P3: Arrival=2, Burst=2

And run an algorithm, you should see:
- A table with calculated scheduling metrics
- A Gantt chart showing the process timeline

## 🔧 Console Debugging

If you encounter issues:
1. Open DevTools (should open automatically)
2. Check the Console tab for error messages
3. Look for logs starting with "IPC Handler" or "Error in IPC handler"

## 📝 Test Cases

### Test Case 1: Basic FCFS
- Add 3 processes with different burst times
- Select FCFS algorithm
- Click Run Algorithm
- Verify results are displayed

### Test Case 2: Multiple Algorithms
- Add same processes
- Try different algorithms
- Verify results change appropriately

### Test Case 3: Edge Cases
- Try with only 1 process
- Try with 0 burst time
- Verify error handling works

## 🐛 Troubleshooting

**Issue**: Window still empty
- Solution: Check DevTools console for React errors
- Make sure dist/index.html exists

**Issue**: Algorithm not running
- Solution: Check that algorithm is selected and at least one process is added
- Button should be enabled (not grayed out)

**Issue**: Results not displaying
- Solution: Check DevTools console for errors
- Verify preload script is loaded (check Network tab)

## ✨ Next Steps

For production use:
1. Replace mock results with actual C++ algorithm calls
2. Add process validation
3. Add more algorithm types
4. Add export/save functionality
5. Add historical results tracking
