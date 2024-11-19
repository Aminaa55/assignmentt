# Patient Scheduling System

## Objective
Develop a patient scheduling system in C++ using STL and OOP to simulate healthcare queue prioritization based on urgency. This project reinforces data structures, exception handling, and collaborative coding.

## System Requirements
1. **Patient Details**:
   - **ID**: Egyptian National ID format, validated.
   - **Gender**: 'M' or 'F'.
   - **Arrival Time**: 24-hour format (e.g., 14:30).
   - **Type**: Urgent or Normal.

2. **Queueing System**:
   - Urgent Queue: Prioritized over Normal Queue.
   - Normal Queue: Served only when Urgent Queue is empty.
   - Serve Time Limit: 10 minutes per patient.

3. **Functional Requirements**:
   - **Data Setup**: Simulate different scenarios:
     - Simple: 100 patients.
     - Moderate: 300 patients.
     - Crowded: 700+ patients.
   - **Dispatching**:
     - Move patients to queues based on arrival time every minute.
   - **Serving**:
     - Serve up to `N` patients per minute (5 ≤ N ≤ 10), prioritizing Urgent patients.
     - Track average waiting times.

