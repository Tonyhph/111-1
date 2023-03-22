#include <iostream>
using namespace std;

int main()
{
    long long m, n; // m resources n projects
    cin >> n >> m;
    long long table[n + 1][m + 1];
    for (long long i = 1; i <= n; ++i)
        for (long long j = 0; j <= m; ++j)
            cin >> table[i][j];

    long long dp[1000][1000]= {0};
    for(long long i = 1; i <= n; ++i){
        for(long long j = 1; j <= m; ++j){
            for(long long k = 0; k <= j; ++k){
                dp[i][j] = max(dp[i][j], dp[i-1][j-k] + table[i][k]);
            }
        }
    }
    cout<<dp[n][m]<<'\n';
    return 0;
}

