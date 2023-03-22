#include <bits/stdc++.h>
using namespace std;
void Merge(vector<int> &vec, int left, int mid, int right);
void MergeSort(vector<int> &vec, int left, int right)
{
    if (left < right)
    {
        int mid = (left + right) / 2;
        MergeSort(vec, left, mid);
        MergeSort(vec, mid + 1, right);
        Merge(vec, left, mid, right);
    }
}
void Merge(vector<int> &vec, int left, int mid, int right)
{
    vector<int> LeftSub(vec.begin()+left, vec.begin()+mid+1);
    vector<int> RightSub(vec.begin()+mid+1,vec.begin()+right+1);
    LeftSub.insert(LeftSub.end(),INT_MAX);
    RightSub.insert(RightSub.end(),INT_MAX);
    int iLeft = 0, iRight = 0;
    for(int i = left;i <= right; ++i){
        if(LeftSub[iLeft] <= RightSub[iRight]){
            vec[i] = LeftSub[iLeft];
            ++iLeft;
        }
        else{
            vec[i] = RightSub[iRight];
            ++iRight;
        }
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
    MergeSort(vec, 0, vec.size() - 1);
    for (auto i : vec)
        cout << i << ' ';
    return 0;
}
