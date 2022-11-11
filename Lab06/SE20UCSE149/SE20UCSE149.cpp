// Author : Rounak Das
// Banker's Algorithm

#include <bits/stdc++.h>

using namespace std;

struct Process
{
    int id;
    vector<int> requirements;
    vector<int> alloted;
    vector<int> need;
};

int total_sequences = 0;
vector<vector<struct Process>> safe_sequences;

bool isResourceAvailable(struct Process process, vector<int> available)
{
    // cout << available[0];
    for (int i = 0; i < process.need.size(); i++)
    {
        if (process.need[i] > available[i])
        {
            return false;
        }
    }
    return true;
}

void safe_sequence(vector<struct Process> processes, vector<int> available, vector<bool> marked, vector<struct Process> sequence)
{
    // Creating a tree data structure in a depth first search manner and checking for sequences.
    for (int i = 0; i < processes.size(); i++)
    {
        // cout << processes[i].need.size() << "\n";
        if (!marked[i] && isResourceAvailable(processes[i], available))
        {
            // total_sequences++;
            marked[i] = true;
            // cout << processes[i].id << "\n";
            sequence.push_back(processes[i]);
            for (int j = 0; j < processes[i].need.size(); j++)
            {
                available[j] += processes[i].alloted[j];
            }

            // cout << endl;

            safe_sequence(processes, available, marked, sequence);
            // cout << "false\n";
            marked[i] = false;
            sequence.pop_back();
            for (int j = 0; j < processes[i].need.size(); j++)
            {
                available[j] -= processes[i].alloted[j];
            }
        }
    }

    // for (int j = 0; j < sequence.size(); j++)
    // {
    //     cout << sequence[j].id << "->";
    // }
    // cout << endl;

    if (sequence.size() == processes.size())
    {
        total_sequences++;
        safe_sequences.push_back(sequence);
    }
}

void print_sequences()
{
    cout << total_sequences << endl;
    for (int i = 0; i < total_sequences; i++)
    {
        for (int j = 0; j < safe_sequences[i].size(); j++)
        {
            cout << safe_sequences[i][j].id << " ";
        }
        cout << endl;
    }
}

int main()
{
    freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    int m;
    cin >> m; // Resources
    int n;
    cin >> n; // Processes
    vector<struct Process> process(n);

    for (int i = 0; i < n; i++)
    {
        process[i].id = i;
        process[i].requirements.assign(m, 0);
        process[i].alloted.assign(m, 0);
        process[i].need.assign(m, 0);
    }

    int instances[m]; //Instances

    for (int i = 0; i < m; i++)
    {
        cin >> instances[i];
    }

    ;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> process[i].requirements[j];
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> process[i].alloted[j];
        }
    }

    // return 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            process[i].need[j] = process[i].requirements[j] - process[i].alloted[j];
        }
    }

    vector<int> available(m);

    for (int i = 0; i < m; i++)
    {
        available[i] = 0;
        for (int j = 0; j < n; j++)
        {
            available[i] += process[j].alloted[i];
        }
        available[i] = instances[i] - available[i];
    }

    // for (int i = 0; i < n; i++)
    // {
    //     for (int j = 0; j < m; j++)
    //     {
    //         cout << process[i].requirements[j] << " ";
    //     }
    //     cout << "\t";
    //     for (int j = 0; j < m; j++)
    //     {
    //         cout << process[i].alloted[j] << " ";
    //     }
    //     cout << "\t";
    //     for (int j = 0; j < m; j++)
    //     {
    //         cout << process[i].need[j] << " ";
    //     }
    //     cout << "\n";
    // }

    // for (int i = 0; i < m; i++)
    // {
    //     cout << available[i] << " ";
    // }

    vector<bool> marked(n, false);

    vector<struct Process> sequence;

    safe_sequence(process, available, marked, sequence);
    print_sequences();

    return 0;
}