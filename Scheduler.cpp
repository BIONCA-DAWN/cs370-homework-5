#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <iomanip>
#include <algorithm>

using namespace std;

struct Process {
    int pid;
    int arrival;
    int burst;
    int remaining;
    int priority;
    int start_time = -1;
    int end_time = -1;
    bool completed = false;
};

vector<Process> readInputFile(const string& filename) {
    ifstream infile(filename);
    vector<Process> processes;
    string line;
    while (getline(infile, line)) {
        stringstream ss(line);
        string temp;
        Process p;
        getline(ss, temp, ','); p.pid = stoi(temp);
        getline(ss, temp, ','); p.arrival = stoi(temp);
        getline(ss, temp, ','); p.burst = stoi(temp);
        getline(ss, temp, ','); p.priority = stoi(temp);
        p.remaining = p.burst;
        processes.push_back(p);
    }
    return processes;
}

void runFCFS(vector<Process> processes) {
    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.arrival < b.arrival;
    });

    int time = 0;
    double total_turnaround = 0;
    double total_waiting = 0;

    for (auto& p : processes) {
        if (time < p.arrival) time = p.arrival;
        p.start_time = time;
        time += p.burst;
        p.end_time = time;

        int turnaround = p.end_time - p.arrival;
        int waiting = p.start_time - p.arrival;

        total_turnaround += turnaround;
        total_waiting += waiting;
    }

    const auto avg_turnaround = total_turnaround / processes.size();
    const auto avg_waiting = total_waiting / processes.size();
    const auto throughput = static_cast<double>(processes.size()) / (time == 0 ? 1 : time);

    cout << "--- FCFS ---\n";
    cout << fixed << setprecision(3);
    cout << "Average Turnaround Time: " << avg_turnaround << '\n';
    cout << "Average Waiting Time: " << avg_waiting << '\n';
    cout << "Throughput: " << throughput << "\n\n";
}

void runSJFP(vector<Process> processes) {
    int time = 0, completed = 0;
    const int n = static_cast<int>(processes.size());
    double total_turnaround = 0, total_waiting = 0;

    while (completed < n) {
        auto it = min_element(processes.begin(), processes.end(), [&](const auto& a, const auto& b) {
            return (!a.completed && a.arrival <= time && a.remaining > 0 &&
                    (b.completed || b.arrival > time || b.remaining <= 0 || a.remaining < b.remaining));
        });

        if (it == processes.end() || it->completed || it->arrival > time || it->remaining <= 0) {
            ++time;
            continue;
        }

        if (it->start_time == -1)
            it->start_time = time;

        --it->remaining;
        ++time;

        if (it->remaining == 0) {
            it->end_time = time;
            it->completed = true;
            ++completed;

            const int turnaround = it->end_time - it->arrival;
            const int waiting = turnaround - it->burst;
            total_turnaround += turnaround;
            total_waiting += waiting;
        }
    }

    const auto avg_turnaround = total_turnaround / n;
    const auto avg_waiting = total_waiting / n;
    const auto throughput = static_cast<double>(n) / time;

    cout << "--- SJFP ---\n";
    cout << fixed << setprecision(3);
    cout << "Average Turnaround Time: " << avg_turnaround << '\n';
    cout << "Average Waiting Time: " << avg_waiting << '\n';
    cout << "Throughput: " << throughput << "\n\n";
}

void runPriority(vector<Process> processes) {
    int time = 0, completed = 0;
    const int n = static_cast<int>(processes.size());
    double total_turnaround = 0, total_waiting = 0;

    while (completed < n) {
        auto it = min_element(processes.begin(), processes.end(), [&](const auto& a, const auto& b) {
            return (!a.completed && a.arrival <= time && a.remaining > 0 &&
                    (b.completed || b.arrival > time || b.remaining <= 0 || a.priority < b.priority));
        });

        if (it == processes.end() || it->completed || it->arrival > time || it->remaining <= 0) {
            ++time;
            continue;
        }

        if (it->start_time == -1)
            it->start_time = time;

        --it->remaining;
        ++time;

        if (it->remaining == 0) {
            it->end_time = time;
            it->completed = true;
            ++completed;

            const int turnaround = it->end_time - it->arrival;
            const int waiting = turnaround - it->burst;
            total_turnaround += turnaround;
            total_waiting += waiting;
        }
    }

    const auto avg_turnaround = total_turnaround / n;
    const auto avg_waiting = total_waiting / n;
    const auto throughput = static_cast<double>(n) / time;

    cout << "--- Priority ---\n";
    cout << fixed << setprecision(3);
    cout << "Average Turnaround Time: " << avg_turnaround << '\n';
    cout << "Average Waiting Time: " << avg_waiting << '\n';
    cout << "Throughput: " << throughput << "\n\n";
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: ./Scheduler <input_filename>" << endl;
        return 1;
    }

    const auto filename = string(argv[1]);
    const auto processes = readInputFile(filename);

    runFCFS(processes);
    runSJFP(processes);
    runPriority(processes);

    return 0;
}
