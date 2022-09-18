#include <bits/stdc++.h>

using namespace std;

struct process
{
    int pid = -1;
    int burst_time = 0;
    int arrival_time = 0;
    int wait_time = 0;
    int turn_around_time = 0;
    int completion_time = 0;
    int response_time = -1;
    int priority = -1;
};

vector<process> p;

// Helper functions

bool compareByBurst(process &a, process &b)
{
    if (a.burst_time == b.burst_time)
    {
        if (a.arrival_time == b.arrival_time)
            return a.pid - b.pid;
        return a.arrival_time - b.arrival_time;
    }
    return a.burst_time < b.burst_time;
}
bool compareByPriority(process &a, process &b)
{
    if (a.priority == b.priority)
    {
        if (a.arrival_time == b.arrival_time)
            return a.pid - b.pid;
        return a.arrival_time - b.arrival_time;
    }
    return a.priority < b.priority;
}

bool compareByArrival(process &a, process &b)
{
    if (a.arrival_time == b.arrival_time)
        return a.pid - b.pid;
    return a.arrival_time - b.arrival_time;
}

void printOutput(vector<process> gantt)
{
    for (int i = 0; i < (int)p.size(); i++)
    {
        cout << p[i].wait_time << " ";
    }
    cout << endl;

    for (int i = 0; i < (int)p.size(); i++)
    {
        cout << p[i].response_time << " ";
    }
    cout << endl;

    for (int i = 0; i < (int)p.size(); i++)
    {
        cout << p[i].turn_around_time << " ";
    }
    cout << endl;
    cout << setprecision(4) << (float)(p.size()) / gantt.size() << endl;
}

void FCFS()
{
    vector<process> ready_queue;
    int time = 0;
    vector<process> gantt;
    int k = 0;
    // sort(p.begin(), p.end(), compareByArrival);

    int flag = 0;
    while (flag != (int)p.size())
    {
        if (time < p[k].arrival_time && ready_queue.empty())
        {
            time++;
            gantt.push_back(process());
            continue;
        }
        while (k != (int)p.size() && time >= p[k].arrival_time)
        {
            ready_queue.push_back(p[k]);
            k++;
        }
        while (ready_queue[0].burst_time != 0)
        {
            ready_queue[0].burst_time--;
            time++;
            gantt.push_back(ready_queue[0]);
        }
        p[ready_queue[0].pid - 1].completion_time = time;
        ready_queue.erase(ready_queue.begin());
        flag++;
    }

    for (int i = 0; i < p.size(); i++)
    {
        p[i].turn_around_time = p[i].completion_time - p[i].arrival_time;
        p[i].response_time = p[i].wait_time = p[i].turn_around_time - p[i].burst_time;
    }

    printOutput(gantt);
}

void SJF()
{
    vector<process> ready_queue;
    int time = 0;
    vector<process> gantt;
    int k = 0;

    int flag = 0;
    while (flag != (int)p.size())
    {
        if (time < p[k].arrival_time && ready_queue.empty())
        {
            time++;
            gantt.push_back(process());
            continue;
        }
        while (k != (int)p.size() && time >= p[k].arrival_time)
        {
            ready_queue.push_back(p[k]);
            k++;
        }
        // below part gets redundant because sorting takes place even when all the processes are in ready_queue. Can be optimised :)
        sort(ready_queue.begin(), ready_queue.end(), compareByBurst);

        while (ready_queue[0].burst_time != 0)
        {
            ready_queue[0].burst_time--;
            time++;
            gantt.push_back(ready_queue[0]);
        }
        p[ready_queue[0].pid - 1].completion_time = time;
        ready_queue.erase(ready_queue.begin());
        flag++;
    }

    for (int i = 0; i < p.size(); i++)
    {
        p[i].turn_around_time = p[i].completion_time - p[i].arrival_time;
        p[i].response_time = p[i].wait_time = p[i].turn_around_time - p[i].burst_time;
    }

    printOutput(gantt);
}

void SRTF()
{
    // sort(p.begin(), p.end(), compareByBurst);
    // for (int i = 0; i < (int)p.size(); i++)
    // {
    //     cout << p[i].arrival_time << " " << p[i].burst_time << endl;
    // }
    // return;

    vector<process> ready_queue;
    // ready_queue.push_back(p[0]);
    // ready_queue[0].arrival_time -= 1;
    // cout << ready_queue[0].arrival_time;
    // return;

    int time = 0;
    vector<process> gantt;
    int k = 0;

    int flag = 0;
    while (flag != (int)p.size())
    {
        if (time < p[k].arrival_time && ready_queue.empty())
        {
            time++;
            gantt.push_back(process());
            continue;
        }
        while (k != (int)p.size() && time == p[k].arrival_time)
        {
            ready_queue.push_back(p[k]);
            k++;
        }
        // below part gets redundant because sorting takes place even when all the processes are in ready_queue. Can be optimised :)
        sort(ready_queue.begin(), ready_queue.end(), compareByBurst);
        ready_queue[0].burst_time -= 1;
        if (p[ready_queue[0].pid - 1].response_time == -1)
            p[ready_queue[0].pid - 1].response_time = time;
        gantt.push_back(ready_queue[0]);
        time++;
        if (ready_queue[0].burst_time == 0)
        {
            p[ready_queue[0].pid - 1].completion_time = time;
            ready_queue.erase(ready_queue.begin());
            flag++;
        }
    }

    // for (int i = 0; i < gantt.size(); i++)
    //     cout << gantt[i].pid << " ";
    // cout << endl;

    for (int i = 0; i < (int)p.size(); i++)
    {
        p[i].turn_around_time = p[i].completion_time - p[i].arrival_time;
        p[i].wait_time = p[i].turn_around_time - p[i].burst_time;
        p[i].response_time = p[i].response_time - p[i].arrival_time;
    }

    printOutput(gantt);
}

void priority_scheduling()
{
    for (int i = 0; i < (int)p.size(); i++)
    {
        int input;
        cin >> input;
        p[i].priority = input;
    }

    vector<process> ready_queue;
    int time = 0;
    vector<process> gantt;
    int k = 0;

    int flag = 0;
    while (flag != (int)p.size())
    {
        if (time < p[k].arrival_time && ready_queue.empty())
        {
            time++;
            gantt.push_back(process());
            continue;
        }
        while (k != (int)p.size() && time == p[k].arrival_time)
        {
            ready_queue.push_back(p[k]);
            k++;
        }
        // below part gets redundant because sorting takes place even when all the processes are in ready_queue. Can be optimised :)
        sort(ready_queue.begin(), ready_queue.end(), compareByPriority);
        ready_queue[0].burst_time -= 1;
        if (p[ready_queue[0].pid - 1].response_time == -1)
            p[ready_queue[0].pid - 1].response_time = time;
        gantt.push_back(ready_queue[0]);
        time++;
        if (ready_queue[0].burst_time == 0)
        {
            p[ready_queue[0].pid - 1].completion_time = time;
            ready_queue.erase(ready_queue.begin());
            flag++;
        }
    }

    // for (int i = 0; i < gantt.size(); i++)
    //     cout << gantt[i].pid << " ";
    // cout << endl;

    for (int i = 0; i < (int)(int)p.size(); i++)
    {
        p[i].turn_around_time = p[i].completion_time - p[i].arrival_time;
        p[i].wait_time = p[i].turn_around_time - p[i].burst_time;
        p[i].response_time = p[i].response_time - p[i].arrival_time;
    }

    printOutput(gantt);
}

void round_robin()
{
    int time_q;
    cin >> time_q;

    vector<process> ready_queue;

    int time = 0;
    vector<process> gantt;
    int k = 0;

    int flag = 0;
    while (flag != (int)p.size())
    {
        if (time < p[k].arrival_time && ready_queue.empty())
        {
            time++;
            gantt.push_back(process());
            continue;
        }
        while (k != (int)p.size() && time >= p[k].arrival_time)
        {
            ready_queue.push_back(p[k]);
            k++;
        }
        if (ready_queue[0].burst_time != 0)

            ready_queue.push_back(ready_queue[0]);
        ready_queue.erase(ready_queue.begin());

        if (p[ready_queue[0].pid - 1].response_time == -1)
            p[ready_queue[0].pid - 1].response_time = time;
        gantt.push_back(ready_queue[0]);

        ready_queue[0].burst_time -= time_q;

        if (ready_queue[0].burst_time <= 0)
        {
            time += ready_queue[0].burst_time + time_q;
            p[ready_queue[0].pid - 1].completion_time = time;
            ready_queue[0].burst_time = 0;
            flag++;
            continue;
        }
        time += time_q;
    }

    for (int i = 0; i < (int)p.size(); i++)
    {
        p[i].turn_around_time = p[i].completion_time - p[i].arrival_time;
        p[i].wait_time = p[i].turn_around_time - p[i].burst_time;
        p[i].response_time = p[i].response_time - p[i].arrival_time;
    }
    for (int i = 0; i < gantt.size(); i++)
        cout << gantt[i].pid << " ";
    cout << endl;

    printOutput(gantt);
}

int main()
{
    freopen("input.txt", "r", stdin);
    int choice, n;
    cin >> choice >> n;
    // process p[n];

    for (int i = 0; i < n; i++)
    {
        process input;
        input.pid = i + 1;
        // int input;
        cin >> input.arrival_time;
        p.push_back(input);
    }

    for (int i = 0; i < n; i++)
    {
        int input;
        cin >> input;
        p[i].burst_time = input;
    }
    switch (choice)
    {
    case 1:
        FCFS();
        break;
    case 2:
        SJF();
        break;
    case 3:
        SRTF();
        break;
    case 4:
        priority_scheduling();
        break;
    case 5:
        round_robin();
        break;
    default:
        cout << -1 << endl;
    }
    return 0;
}