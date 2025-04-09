# Dining Philosophers Problem - Simulation

This project is a C++ implementation of the classic **Dining Philosophers Problem**, demonstrating multi-threading synchronization with real-time visualization.

## Table of Contents
1. [Problem Description](#problem-description)
2. [Solution Approach](#solution-approach)
3. [Implementation Details](#implementation-details)
4. [Features](#features)
5. [Usage](#usage)
6. [Example Output](#example-output)

---

## Problem Description

The Dining Philosophers Problem illustrates key challenges in concurrent programming:

- **Circular Wait Condition**: Philosophers waiting indefinitely for forks
- **Resource Contention**: Limited forks shared between multiple threads
- **Starvation Risk**: Some philosophers might never get to eat

**Classic Scenario:**
- N philosophers seated at a round table
- N forks placed between them
- Each philosopher needs 2 forks to eat
- Can only use adjacent forks

---

## Solution Approach

This implementation guarantees deadlock-free operation through:

1. **Strict Fork Ordering**:
    - Always acquire lower-numbered fork first
    - Breaks potential circular wait

2. **Bounded Execution**:
    - Fixed meal count per philosopher
    - Time-limited simulation

3. **Visual Monitoring**:
    - Color-coded state indicators
    - Real-time meal counters

---

## Implementation Details

### Core Architecture

| Component          | Description                          | Key Technologies        |
|--------------------|--------------------------------------|-------------------------|
| Philosopher Thread | Independent execution unit           | std::thread             |
| Fork Management    | Shared resource control              | std::mutex              |
| State Visualization| Real-time console display            | Windows.h/ncurses       |
| Timing Control     | Simulation duration management       | std::chrono             |

### Synchronization Flow
1. Philosopher begins thinking
2. Attempts to acquire forks in fixed order
3. Eats for randomized duration
4. Releases forks
5. Repeats until meal limit reached

---

## Features

### Core Functionality
- Adjustable philosopher count (3-15 recommended)
- Configurable meal limits
- Time-bound simulation

### Visualization
- **State Colors**:
    - 🟢 Thinking (green)
    - 🔴 Eating (red)
    - 🟡 Full (yellow)
- Real-time status updates
- Clean console rendering

### Technical
- Deadlock prevention
- Thread-safe console output
- Cross-platform compatibility

---

## Usage

### Compilation
```bash
g++ -std=c++11 -o philosophers philosophers.cpp

