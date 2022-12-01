#include <bits/stdc++.h>

using namespace std;

int no_of_frames = 0;
int n = 0;
vector<int> ar;
int page_faults = 0;

void demand_paging_FIFO() // Done !
{
    vector<int> frames(no_of_frames, -1); // Initial Test Case is wrong in the pdf document.

    for (int i = 0; i < ar.size(); i++)
    {
        for (int item : frames)
        {
            if (item == ar[i])
            {
                goto label;
            }
        }
        page_faults++;
        frames.erase(frames.begin());
        frames.push_back(ar[i]);
    label:
        continue;
    }
    cout << page_faults << endl;
}

int change(vector<int> ar, vector<int> frames, int index)
{
    int res = -1, far = index;
    for (int i = 0; i < frames.size(); i++)
    {
        int j;
        for (j = index; j < ar.size(); j++)
        {
            if (frames[i] == ar[j])
            {
                if (j > far)
                {
                    far = j;
                    res = i;
                }
                break;
            }
        }
        if (j == ar.size())
        {
            return i;
        }
    }
    if (res == -1)
        return 0;
    else
        return res;
}
void demand_paging_OPTIMAL()
{
    vector<int> frames(no_of_frames, -1);

    for (int i = 0; i < ar.size(); i++)
    {
        for (int item : frames)
        {
            if (item == ar[i])
                goto label;
        }
        page_faults++;
        if (*frames.end() == -1)
        {
            frames.pop_back();
            frames.insert(frames.begin(), ar[i]);
        }
        else
        {
            // Replacing
            int j = change(ar, frames, i + 1);
            frames[j] = ar[i];
        }

    label:
        continue;
    }
    cout << page_faults << endl;
}

int change_2(vector<int> ar, vector<int> frames, int index)
{
    int res = -1, far = ar.size() - index;

    reverse(ar.begin(), ar.end());

    // cout << far << endl;

    for (int i = 0; i < frames.size(); i++)
    {
        int j;
        for (j = ar.size() - index; j < ar.size(); j++)
        {
            // cout << j << " ";
            if (frames[i] == ar[j])
            {
                if (j > far)
                {
                    far = j;
                    res = i;
                }
                break;
            }
        }
        // cout << endl;
        if (j == ar.size())
        {
            reverse(ar.begin(), ar.end());
            // cout << i << endl;
            return i;
        }
    }
    reverse(ar.begin(), ar.end());
    if (res == -1)
        return 0;
    else
    {
        // cout << res << endl;
        return res;
    }
}

void demand_paging_LRU()
{
    vector<int> frames(no_of_frames, -1);

    for (int i = 0; i < ar.size(); i++)
    {
        for (int item : frames)
        {
            if (item == ar[i])
                goto label;
        }
        page_faults++;

        if (frames.back() == -1)
        {
            frames.pop_back();
            frames.insert(frames.begin(), ar[i]);
        }
        else
        {
            // Replacing
            int j = change_2(ar, frames, i);
            frames[j] = ar[i];
            // return;
        }

    label:
        continue;
    }
    cout << page_faults << endl;
}

int main()
{
    // freopen("input.txt", "r", stdin);
    cin >> no_of_frames;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int input;
        cin >> input;
        ar.push_back(input);
    }
    char *OPTION;
    cin.getline(OPTION, 10);

    if (OPTION[1] == 'F')
    {
        demand_paging_FIFO();
    }
    else if (OPTION[1] == 'O')
    {
        demand_paging_OPTIMAL();
    }
    else
    {
        demand_paging_LRU();
    }
    return 0;
}