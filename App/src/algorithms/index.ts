export type ProcInput = { pid: string; arrival: number; burst: number };
export type ResultEntry = { pid: string; arrival: number; burst: number; completion: number; turnaround: number; waiting: number };
export type GanttEntry = { pid: string; start: number; end: number };

function cloneProcesses(processes: ProcInput[]) {
  return processes.map(p => ({ pid: p.pid, arrival: Number(p.arrival), burst: Number(p.burst), completion: 0, turnaround: 0, waiting: 0 } as any));
}

export function fcfs(processes: ProcInput[]) {
  const ps = cloneProcesses(processes);
  ps.sort((a: any, b: any) => a.arrival - b.arrival);
  let time = 0;
  const gantt: GanttEntry[] = [];
  for (let p of ps) {
    if (p.arrival > time) time = p.arrival;
    const start = time;
    time += p.burst;
    const end = time;
    p.completion = end;
    p.turnaround = p.completion - p.arrival;
    p.waiting = p.turnaround - p.burst;
    gantt.push({ pid: p.pid, start, end });
  }
  return { results: ps as ResultEntry[], ganttChart: gantt };
}

export function sjf(processes: ProcInput[]) {
  const ps = cloneProcesses(processes);
  const n = ps.length;
  const order = ps.map((_, i) => i).sort((a, b) => ps[a].arrival - ps[b].arrival || a - b);
  const heap: number[] = []; // will store indices into ps
  let time = 0, oi = 0, completed = 0;
  const gantt: GanttEntry[] = [];

  const pushReady = () => {
    while (oi < n && ps[order[oi]].arrival <= time) {
      heap.push(order[oi++]);
    }
    heap.sort((a, b) => ps[a].burst - ps[b].burst || ps[a].arrival - ps[b].arrival);
  };

  while (completed < n) {
    pushReady();
    if (heap.length === 0) {
      if (oi < n) time = Math.max(time, ps[order[oi]].arrival);
      pushReady();
      if (heap.length === 0) break;
    }
    const idx = heap.shift()!;
    const p = ps[idx];
    const start = Math.max(time, p.arrival);
    const end = start + p.burst;
    time = end;
    p.completion = end;
    p.turnaround = p.completion - p.arrival;
    p.waiting = p.turnaround - p.burst;
    gantt.push({ pid: p.pid, start, end });
    completed++;
  }
  return { results: ps as ResultEntry[], ganttChart: gantt };
}

export function rr(processes: ProcInput[], quantum: number) {
  const ps = cloneProcesses(processes);
  ps.sort((a: any, b: any) => a.arrival - b.arrival);
  const n = ps.length;
  if (n === 0) return { results: ps as ResultEntry[], ganttChart: [] };
  const remaining = ps.map(p => p.burst);
  const ready: number[] = [];
  let time = 0, oi = 0, completed = 0;
  const gantt: GanttEntry[] = [];

  const enqueueArrived = () => {
    while (oi < n && ps[oi].arrival <= time) {
      ready.push(oi++);
    }
  };

  enqueueArrived();
  if (ready.length === 0 && oi < n) {
    time = ps[oi].arrival;
    enqueueArrived();
  }

  while (ready.length > 0) {
    const idx = ready.shift()!;
    const p = ps[idx];
    const start = Math.max(time, p.arrival);
    const slice = Math.min(quantum, remaining[idx]);
    time = start + slice;
    remaining[idx] -= slice;
    gantt.push({ pid: p.pid, start, end: time });
    enqueueArrived();
    if (remaining[idx] > 0) {
      ready.push(idx);
    } else {
      p.completion = time;
      p.turnaround = p.completion - p.arrival;
      p.waiting = p.turnaround - p.burst;
      completed++;
    }
    if (ready.length === 0 && completed < n && oi < n) {
      time = Math.max(time, ps[oi].arrival);
      enqueueArrived();
    }
  }

  return { results: ps as ResultEntry[], ganttChart: gantt };
}

export function hrrn(processes: ProcInput[]) {
  const ps = cloneProcesses(processes);
  const n = ps.length;
  let time = 0, completed = 0;
  const gantt: GanttEntry[] = [];
  const done = new Array(n).fill(false);

  while (completed < n) {
    const candidates: number[] = [];
    for (let i = 0; i < n; i++) {
      if (!done[i] && ps[i].arrival <= time) candidates.push(i);
    }
    if (candidates.length === 0) {
      time++;
      continue;
    }
    let best = candidates[0];
    let bestRatio = (time - ps[best].arrival + ps[best].burst) / ps[best].burst;
    for (let idx of candidates) {
      const ratio = (time - ps[idx].arrival + ps[idx].burst) / ps[idx].burst;
      if (ratio > bestRatio) { bestRatio = ratio; best = idx; }
    }
    const p = ps[best];
    const start = Math.max(time, p.arrival);
    const end = start + p.burst;
    time = end;
    p.completion = end;
    p.turnaround = p.completion - p.arrival;
    p.waiting = p.turnaround - p.burst;
    gantt.push({ pid: p.pid, start, end });
    done[best] = true;
    completed++;
  }
  return { results: ps as ResultEntry[], ganttChart: gantt };
}

export function srt(processes: ProcInput[]) {
  const ps = cloneProcesses(processes);
  const n = ps.length;
  if (n === 0) return { results: ps as ResultEntry[], ganttChart: [] };
  const remaining = ps.map(p => p.burst);
  const order = ps.map((_, i) => i).sort((a, b) => ps[a].arrival - ps[b].arrival || a - b);
  const heap: number[] = [];
  let oi = 0, time = 0, completed = 0;
  const gantt: GanttEntry[] = [];

  const pushArrived = () => {
    while (oi < n && ps[order[oi]].arrival <= time) {
      heap.push(order[oi++]);
    }
    heap.sort((a, b) => remaining[a] - remaining[b] || ps[a].arrival - ps[b].arrival);
  };

  while (completed < n) {
    pushArrived();
    if (heap.length === 0) {
      time = Math.max(time, ps[order[oi]].arrival);
      pushArrived();
      if (heap.length === 0) continue;
    }
    const idx = heap.shift()!;
    const p = ps[idx];
    const start = Math.max(time, p.arrival);
    const runUntil = start + 1;
    time = runUntil;
    remaining[idx] -= 1;
    gantt.push({ pid: p.pid, start, end: time });
    if (remaining[idx] === 0) {
      p.completion = time;
      p.turnaround = p.completion - p.arrival;
      p.waiting = p.turnaround - p.burst;
      completed++;
    }
    pushArrived();
    if (remaining[idx] > 0) heap.push(idx);
  }

  return { results: ps as ResultEntry[], ganttChart: gantt };
}

export function runAlgorithm(name: string, processes: ProcInput[], options?: any) {
  switch ((name || '').toLowerCase()) {
    case 'fcfs': return fcfs(processes);
    case 'sjf': return sjf(processes);
    case 'rr': return rr(processes, options?.quantum || 2);
    case 'hrrn': return hrrn(processes);
    case 'srt': return srt(processes);
    case 'mlfq':
      return rr(processes, options?.quantum || 4);
    default:
      throw new Error('Unknown algorithm: ' + name);
  }
}
