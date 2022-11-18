#include <bits/stdc++.h>

using namespace std;

struct Process
{
    int id; // -1 represents dummp Processes / blank spaces
    int start;
    int size;
    int end;
};

// These four are global and is not secured. Should use a getter and setter method in a class to make it secure. But for simplicity, it's made global
int job_profile;
int replacement_policy;
int time_steps;
bool start_sim = false;




typedef struct Process Process;

struct Memory
{
    int size = 1024; // If we ever change size of memory. By default it is 1024
    vector<Process> p;
    float average_fragmentation = 0.0; // Done
    float average_hole = 0.0;          // Done
    float average_number_of_holes_reqd = 0.0;
    float highest_fragmentation = -1;               // Done
    float lowest_fragmentation = (float)size + 1.0; // Done
    float average_number_of_jobs = 0.0;             // Done
    int highest_number_of_jobs = -1;                // Done
    int lowest_number_of_jobs = INT_MAX;            // Done
    float average_job_size = 0.0;                   // Done
    float average_number_of_holes = 0.0;            // Done
    int highest_number_of_holes = -1;               // Done
    int lowest_number_of_holes = INT_MAX;           // Done

    int largest_number_of_partitions_in_a_row = 0;
    int largest_number_of_evictions = 0;

    // The largest number of partitions created in a row without any intervening evictions
    // The largest number of evictions required in satisfying a single new partition request
};

typedef struct Memory Memory;

Process create_process(int id)
{
    int size = 0;
    // srand(time(0));
    switch (job_profile)
    {
    case 1:
        size = rand() % (1023 - 1 + 1) + 1;
        break;
    case 2:
        size = rand() % (100 - 1 + 1) + 1;
        break;
    case 3:
        size = rand() % (1000 - 500 + 1) + 500;
        break;
    default:
        size = 0;
    }
    // cin >> size;
    Process p;
    p.id = id;
    p.size = size;
    return p;
}

Process create_blank(int start, int size)
{
    Process blank;
    blank.id = -1;
    blank.start = start;
    blank.size = size;
    blank.end = blank.start + blank.size - 1;
    return blank;
}

// Printing The memory after each time step
void print(Memory memory)
{
    for (auto p : memory.p)
    {
        cout << p.start << " --- " << p.id << " --- " << p.end;
        cout << "    ";
    }
    cout << endl;
}

void print_stats(Memory memory)
{
    cout << "Average Fragementation (as a fraction of total memory): " << (memory.average_fragmentation / time_steps) / memory.size << endl;
    cout << "Average Hole : " << (memory.average_hole / memory.average_number_of_holes) << endl;

    cout << "Average Number of Holes reqd. : " << memory.average_number_of_holes_reqd / time_steps << endl;

    cout << "Highest Fragmentation Measured (as a fraction of total memory): " << memory.highest_fragmentation / memory.size << endl;
    cout << "Lowest Fragmentation Measured (as a fraction of total memory): " << memory.lowest_fragmentation / memory.size << endl;
    cout << "Average number of jobs : " << memory.average_number_of_jobs / time_steps << endl;
    cout << "Highest number of jobs : " << memory.highest_number_of_jobs << endl;
    cout << "Lowest number of jobs : " << memory.lowest_number_of_jobs << endl;
    cout << "Average Size of a job : " << memory.average_job_size / memory.average_number_of_jobs << endl;
    cout << "Average number of holes : " << memory.average_number_of_holes / time_steps << endl;
    cout << "Highest number of holes : " << memory.highest_number_of_holes << endl;
    cout << "Lowest number of holes : " << memory.lowest_number_of_holes << endl;

    cout << "I DON'T KNOW" << endl;
    cout << "I DON'T KNOW" << endl;
}

void fix_blanks(Memory *memory)
{
    for (int i = 0; i < memory->p.size() - 1; i++)
    {
        if (memory->p[i].id == memory->p[i + 1].id && memory->p[i].id == -1)
        {
            memory->p[i].end = memory->p[i + 1].end;
            memory->p[i].size = memory->p[i].end - memory->p[i].start + 1;
            memory->p.erase(memory->p.begin() + i + 1);
        }
    }
    // print(*memory);
}

void terminate_process(Memory *memory)
{
    int index_termination = 0;
    // srand(time(0));
    fix_blanks(memory);
    // print(*memory);
    while (memory->p.size() != 1)
    {
        index_termination = rand() % (memory->p.size());
        // cout << "Problem Here !!";
        if (memory->p[index_termination].id != -1)
        {
            // cout << "Terminating process : " << memory->p[index_termination].id << endl;
            memory->p[index_termination].id = -1;
            break;
        }
        // fix_blanks(memory);
    }
    // cin >> index_termination;
    fix_blanks(memory);
}

void best_fit(Memory *memory, Process p)
{
    int min_frag = memory->size + 1;
    int min_frag_index = memory->size + 1;
    for (int i = 0; i < memory->p.size(); i++)
    {
        Process process = memory->p[i];

        if (process.id == -1)
        {
            if (start_sim)
                memory->average_number_of_holes_reqd++;
            if (process.size >= p.size)
            {
                min_frag = (process.size <= min_frag) ? process.size : min_frag;
                min_frag_index = (process.size <= min_frag) ? i : min_frag_index;
            }
        }
    }

    if (min_frag_index == memory->size + 1)
    {
        // cout << "h" << endl;
        terminate_process(memory);
        best_fit(memory, p);
    }
    else
    {
        memory->p[min_frag_index].id = p.id;
        memory->p[min_frag_index].size = p.size;
        memory->p[min_frag_index].end = memory->p[min_frag_index].start + memory->p[min_frag_index].size - 1;
        memory->p.insert(memory->p.begin() + min_frag_index + 1, create_blank(memory->p[min_frag_index].end + 1, min_frag - p.size));
        if (start_sim)
        {
            memory->average_fragmentation += min_frag - p.size;
            memory->highest_fragmentation = (memory->highest_fragmentation < (min_frag - p.size)) ? (min_frag - p.size) : memory->highest_fragmentation;
            memory->lowest_fragmentation = (memory->lowest_fragmentation > (min_frag - p.size)) ? (min_frag - p.size) : memory->lowest_fragmentation;
        }
    }
}

void worst_fit(Memory *memory, Process p)
{
    int max_frag = -1;
    int max_frag_index = -1;
    for (int i = 0; i < memory->p.size(); i++)
    {
        Process process = memory->p[i];

        if (process.id == -1)
        {
            if (start_sim)
                memory->average_number_of_holes_reqd++;
            if (process.size >= p.size)
            {
                max_frag = (process.size >= max_frag) ? process.size : max_frag;
                max_frag_index = (process.size >= max_frag) ? i : max_frag_index;
            }
        }
    }

    if (max_frag_index == -1)
    {
        terminate_process(memory);
        // cout << "h" << endl;
        worst_fit(memory, p);
    }
    else
    {
        memory->p[max_frag_index].id = p.id;
        memory->p[max_frag_index].size = p.size;
        memory->p[max_frag_index].end = memory->p[max_frag_index].start + memory->p[max_frag_index].size - 1;
        memory->p.insert(memory->p.begin() + max_frag_index + 1, create_blank(memory->p[max_frag_index].end + 1, max_frag - p.size));
        if (start_sim)
        {
            memory->average_fragmentation += max_frag - p.size;
            memory->highest_fragmentation = (memory->highest_fragmentation < (max_frag - p.size)) ? (max_frag - p.size) : memory->highest_fragmentation;
            memory->lowest_fragmentation = (memory->lowest_fragmentation > (max_frag - p.size)) ? (max_frag - p.size) : memory->lowest_fragmentation;
        }
    }
}

void first_fit(Memory *memory, Process p)
{
    for (int i = 0; i < memory->p.size(); i++)
    {
        Process process = memory->p[i];

        // print(*memory);
        // cout << p.size << endl;
        if (process.id == -1) // If it is blank
        {
            if (start_sim)
                memory->average_number_of_holes_reqd++;
            if (process.size > p.size)
            {
                // cout << process.size << " " << p.size << endl;
                memory->p[i].id = p.id;
                memory->p[i].size = p.size;
                memory->p[i].end = memory->p[i].start + memory->p[i].size - 1;
                memory->p.insert(memory->p.begin() + i + 1, create_blank(memory->p[i].end + 1, process.size - p.size));
                // print(*memory);
                if (start_sim)
                {
                    memory->average_fragmentation += process.size - p.size;
                    memory->highest_fragmentation = (memory->highest_fragmentation < (process.size - p.size)) ? (process.size - p.size) : memory->highest_fragmentation;
                    memory->lowest_fragmentation = (memory->lowest_fragmentation > (process.size - p.size)) ? (process.size - p.size) : memory->lowest_fragmentation;
                }
                return;
            }
            else if (process.size == p.size)
            {
                memory->p[i].id = p.id;
                if (start_sim)
                {
                    memory->highest_fragmentation = (memory->highest_fragmentation < (process.size - p.size)) ? (process.size - p.size) : memory->highest_fragmentation;
                    memory->lowest_fragmentation = (memory->lowest_fragmentation > (process.size - p.size)) ? (process.size - p.size) : memory->lowest_fragmentation;
                    memory->average_fragmentation += 0;
                }
                // print(*memory);
                return;
            }
        }
    }

    terminate_process(memory);
    first_fit(memory, p);
}

void update_memory(Memory *memory, Process p)
{
    switch (replacement_policy)
    {
    case 1:
        best_fit(memory, p);
        break;
    case 2:
        worst_fit(memory, p);
        break;
    case 3:
        first_fit(memory, p);
        break;
    default:
        cout << "Incorrect replacement policy";
        exit(0);
    }

    for (int i = 0; i < memory->p.size(); i++)
    {
        Process process = memory->p[i];
        if (process.size <= 0 || process.start > process.end)
        {
            memory->p.erase(memory->p.begin() + i);
        }
    }
}

void update_holes_stats(Memory *memory)
{
    int num_holes = 0;
    int num_jobs = 0;
    for (auto process : memory->p)
    {
        if (process.id == -1)
        {
            // cout << process.size << endl;
            memory->average_hole += process.size;
            num_holes++;
        }
        else
        {
            memory->average_job_size += process.size;
            num_jobs++;
        }
    }
    memory->average_number_of_jobs += num_jobs;
    memory->highest_number_of_jobs = (memory->highest_number_of_jobs < num_jobs) ? num_jobs : memory->highest_number_of_jobs; // Updating number of Holes
    memory->lowest_number_of_jobs = (memory->lowest_number_of_jobs > num_jobs) ? num_jobs : memory->lowest_number_of_jobs;    // Updating number of Holes

    memory->average_number_of_holes += num_holes;
    memory->highest_number_of_holes = (memory->highest_number_of_holes < num_holes) ? num_holes : memory->highest_number_of_holes; // Updating number of Holes
    memory->lowest_number_of_holes = (memory->lowest_number_of_holes > num_holes) ? num_holes : memory->lowest_number_of_holes;    // Updating number of Holes
}

void simulate()
{
    Memory memory;
    int id = 0;

    Process blank = create_blank(0, memory.size);

    memory.p.push_back(blank); // Pushed a dummy job profile;

    for (int i = 0; i < time_steps; i++)
    {
        Process p = create_process(id);
        // cout << "Process created of size " << p.size << endl;
        update_memory(&memory, p);
        id++;
        fix_blanks(&memory);
        // print(memory);
    }

    // Simulation Complete !
    // Starting to record now here !
    cout << "-------------" << endl;

    start_sim = true;

    for (int i = 0; i < time_steps; i++)
    {
        update_holes_stats(&memory);
        Process p = create_process(id);
        // cout << "Process created of size " << p.size << endl;
        update_memory(&memory, p);
        id++;
        fix_blanks(&memory);
    }

    fix_blanks(&memory);
    print_stats(memory);
}

// int main(int argc, char **argv)
int main()
{
    // freopen("input.txt", "r", stdin);
    // if(argc != 2){
    //     cout << "Incorrect input, try again" <<endl;
    //      return 0;
    // }

    // job_profile = (int)argv[1] - '0'; Job Profile
    // replacement_policy = (int)argv[2] - '0'; Replacement Policy

    time_steps = 1000; // Time Steps
    job_profile = 3;
    replacement_policy = 1;
    simulate();
    return 0;
}