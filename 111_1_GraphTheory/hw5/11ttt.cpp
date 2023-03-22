#include <bits/stdc++.h>
using namespace std;

double mat[21][21];
int deg[21];
int c[7];
int n, m;

int main()
{
    int i, j, x, y;
    int temp;
    while (cin>>n>>m)
    {
        memset(mat, 0, sizeof(mat));
        memset(deg, 0, sizeof(deg));
        for (j = 1; j <= m; j++)
        {
            cin>>x>>y;
            if (!mat[x][y])
            {
                ++deg[x];
                ++deg[y];
                mat[x][y] = mat[y][x] = 1;
            }
        }
        for (i = 1; i <= n; i++)
        {
            if (deg[i] == 1)
                for (j = 1; j <= n; j++)
                    if (mat[i][j])
                    {
                        mat[i][j] = mat[j][i] = 0;
                        deg[i] = 0;
                        deg[j]--;
                    }
            if (deg[i] == 2)
            {
                for (j = 1; j <= n; j++)
                    if (mat[i][j])
                    {
                        temp = j;
                        break;
                    }
                for (j = temp + 1; j <= n; j++)
                    if (mat[i][j])
                    {
                        mat[i][j] = mat[j][i] = 0;
                        mat[i][temp] = mat[temp][i] = 0;
                        deg[i] = 0;
                        if (mat[j][temp])
                        {
                            deg[j]--;
                            deg[temp]--;
                        }
                        else
                        {
                            mat[j][temp] = mat[temp][j] = 1;
                        }
                    }
            }
        }
        temp = 1;
        for (c[1] = 1; c[1] <= n - 4; c[1]++)
            if (deg[c[1]])
                for (c[2] = c[1] + 1; c[2] <= n - 3; c[2]++)
                    if (deg[c[2]])
                        for (c[3] = c[2] + 1; c[3] <= n - 2; c[3]++)
                            if (deg[c[3]])
                                for (c[4] = c[3] + 1; c[4] <= n - 1; c[4]++)
                                    if (deg[c[4]])
                                        for (c[5] = c[4] + 1; c[5] <= n; c[5]++)
                                            if (deg[c[5]])
                                            {
                                                x = 1;
                                                for (i = 1; i <= 5; i++)
                                                    if (x)
                                                        for (j = 1; j <= 5; j++)
                                                            if (!mat[c[i]][c[j]])
                                                            {
                                                                x = 0;
                                                                break;
                                                            }
                                                if (x)
                                                {
                                                    temp = 0;
                                                    goto ff1;
                                                }
                                            }
        for (c[1] = 1; c[1] <= n - 2; c[1]++)
            if (deg[c[1]])
                for (c[2] = c[1] + 1; c[2] <= n - 1; c[2]++)
                    if (deg[c[2]])
                        for (c[3] = c[2] + 1; c[3] <= n; c[3]++)
                            if (deg[c[3]])
                                for (c[4] = c[1] + 1; c[4] <= n - 2; c[4]++)
                                    if ((deg[c[4]]) && (c[4] != c[2]) && (c[4] != c[3]))
                                        for (c[5] = c[4] + 1; c[5] <= n - 1; c[5]++)
                                            if (deg[c[5]] && (c[5] != c[2]) && (c[5] != c[3]))
                                                for (c[6] = c[5] + 1; c[6] <= n; c[6]++)
                                                    if (deg[c[6]] && (c[6] != c[2]) && (c[6] != c[3]))
                                                    {
                                                        x = 1;
                                                        for (i = 1; i <= 3; i++)
                                                            if (x)
                                                                for (j = 4; j <= 6; j++)
                                                                    if (!mat[c[i]][c[j]])
                                                                    {
                                                                        x = 0;
                                                                        break;
                                                                    }
                                                        if (x)
                                                        {
                                                            temp = 0;
                                                            goto ff1;
                                                        }
                                                    }
    ff1:;
        if (temp)
            printf("YES\n");
        else
            printf("NO\n");
    }
    return 0;
}
