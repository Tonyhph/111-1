#include <iostream>
#include <vector>
using namespace std;
// n/2
void findFakeCoin(vector<int> &vec, int low, int high, int n)
{
    int num1, num2, i;
    int sum1 = 0, sum2 = 0;
    int rest = 0;
    if (n == 1)
        return low;
    num1 = num2 = n / 2;
    rest = n - 2 * num1; // ==1

    for (i = 0; i < num1; ++i)
        sum1 += vec[low + i];
    for (i = num1; i < num1 + num2; ++i)
        sum2 += vec[low + i];
    if (sum1 == sum2)
    {
        if(n%2 == 0){
            return;
        }
        else ans = high;
        return;
    }
    else
    {
        return findFakeCoin(vec, low, low + num1 - 1, num1);
        return findFakeCoin(vec, low + num1, low + num1 + num2 -1, num2);
    }
}
int main()
{
    int n, low, high, res;
    vector<int> vec;
    while (cin >> n)
    {
        low = 0;
        high = n - 1;
        vec.resize(n);
        for (int i = 0; i < n; ++i)
            cin >> vec[i];
        res = findFakeCoin(vec, low, high, n);
        cout << res << '\n';
    }
    return 0;
}