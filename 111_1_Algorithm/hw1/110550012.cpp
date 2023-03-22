#include <iostream>
#include <vector>
using namespace std;
// n/3
long long findFakeCoin(vector<long long> &vec, long long low, long long high, long long n)
{
    long long num1, num2, num3, i;
    long long sum1 = 0, sum2 = 0, sum3 = 0;
    long long rest = 0;
    if (n == 1)
        return low;
    if (n == 2){
        if(vec[high+1]){
            if(vec[low] != vec[high+1])
                return low;
            else return high;
        }
        else
            if(vec[low] != vec[low-1])
                return low;
            else return high;
    }
    num1 = num2 = num3 = n / 3;
    rest = n - 3 * num1; // <3

    for (i = 0; i < num1; ++i)
        sum1 += vec[low + i];
    for (i = num1; i < num1 + num2; ++i)
        sum2 += vec[low + i];
    for (i = num1 + num2; i < num1 + num2 + num3; ++i)
        sum3 += vec[low + i];
    if (sum1 == sum2 && sum2 == sum3)
        return findFakeCoin(vec, low+num1+num2+num3, high, rest);
    else if (sum2 == sum3)
        return findFakeCoin(vec, low, low + num1 - 1, num1);
    else if (sum1 == sum3)
        return findFakeCoin(vec, low + num1, low + num1 + num2 - 1, num2);
    else if (sum1 == sum2)
        return findFakeCoin(vec, low + num1 + num2, low + num1 + num2 + num3 -1, num3);
    return 0; //avoid compile warning
}
int main()
{
    long long n, low, high, res;
    vector<long long> vec;
    while (cin >> n)
    {
        low = 0;
        high = n - 1;
        vec.resize(n);
        for (long long i = 0; i < n; ++i)
            cin >> vec[i];
        res = findFakeCoin(vec, low, high, n);
        cout << res << '\n';
    }
    return 0;
}