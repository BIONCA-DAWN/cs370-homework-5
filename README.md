# cs370-homework-5

Homework 5 - CPU Scheduling Algorithms
Student: Bionca Coleman


DESCRIPTION:

This project shows three CPU scheduling algorithms

1. First Come First Serve (FCFS) - Non-preemptive
2. Shortest Job First (SJFP) - Preemptive
3. Priority Scheduling - Preemptive

Each algorithm shows and reports:
- Average Turnaround Time
- Average Waiting Time
- Throughput

---

FILES INCLUDED:

- Scheduler.cpp    : Main C++
- Makefile         : Compiles the project using g++
- README.txt       : This file

---

HOW TO COMPILE:

Make sure you're in the project directory, then run:
    make
    make clean for restart


HOW TO RUN:

To run the scheduler with the CSV input file, use:
    ./Scheduler CS370-HW5-Input.csv

The input file must be formatted with one process per line.
Example:
    1,0,3,5
    2,2,4,2
    3,3,1,3



OUTPUT:

For each algorithm, the program prints:
- Average Turnaround Time
- Average Waiting Time
- Throughput

This is what a sample output looks like:
    --- FCFS ---
        Average Turnaround Time: 4.200
    Average Waiting Time: 1.200
    Throughput: 0.333