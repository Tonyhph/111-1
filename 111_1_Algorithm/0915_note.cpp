#include <bits/stdc++.h>
using namespace std;

void InsertionSort(vector<int> &vec)
{
    int size = vec.size();
    int key;
    for (int i = 1; i < size; ++i)
    {
        key = vec[i];
        int j = i - 1;
        while (key < vec[j] && j >= 0)
        {
            vec[j + 1] = vec[j];
            --j;
        }
        vec[j+1] = key;
    }
}

int main()
{
    vector<int> vec;
    vec.push_back(3);
    vec.push_back(1);
    vec.push_back(7);
    vec.push_back(6);
    vec.push_back(0);
    vec.push_back(-1);
    InsertionSort(vec);
    for (auto i : vec)
        cout << i << ' ';
    return 0;
}
