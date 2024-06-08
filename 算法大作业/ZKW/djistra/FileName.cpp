#include<iostream>
#include<deque>
#include<cstring>
#include <time.h>    
#include <stdio.h>  
#include <windows.h>  
#include <iostream>  
#define int long long
using namespace std;

const int N = 2e5 + 5;
const int inf = 1e18;
int n, m, s, t, dis[N], head[N], cur[N], num = 1, ans, cost;
bool vis[N];
struct edge
{
    int nxt, v, w, cost;
} e[N << 1];

void add(int u, int v, int w, int cost)
{
    e[++num].nxt = head[u];
    e[num].v = v;
    e[num].w = w;
    e[num].cost = cost;
    head[u] = num;
}

bool spfa()
{
    for (int i = s; i <= t; i++)
        cur[i] = head[i], vis[i] = 0, dis[i] = 1e18;
    dis[s] = 0, vis[s] = 1;
    deque<int> q;
    q.push_back(s);
    while (!q.empty())
    {
        int u = q.front();
        q.pop_front();
        vis[u] = 0;
        for (int i = head[u]; i; i = e[i].nxt)
        {
            int v = e[i].v, w = e[i].w;
            if (dis[v] > dis[u] + e[i].cost && w)
            {
                dis[v] = dis[u] + e[i].cost;
                if (!vis[v]) {
                    vis[v] = 1;

                    if (!q.empty() && dis[v] < dis[q.front()]) {//优化点：路径短的优先进行
                        q.push_front(v);
                    }
                    else {
                        q.push_back(v);
                    }
                
                }
             
            }
        }
    }
    return dis[t] != 1e18;
}

int dfs(int u, int in)
{
    if (u == t)
    {
        vis[t] = 1;
        return in;
    }
    int out = 0, res;
    vis[u] = 1;
    for (int i = cur[u]; i && in; i = e[i].nxt)
    {
        cur[u] = i;
        int v = e[i].v, w = e[i].w;
        if ((!vis[v] || v == t) && w && dis[v] == dis[u] + e[i].cost)
        {
            res = dfs(v, min(in - out, e[i].w));
            cost += e[i].cost * res;
            e[i].w -= res, e[i ^ 1].w += res;
            out += res, in -= res;
            if (out == in)
                break;
        }
    }
    return out;
}

void zkw() {
    while (spfa())
    {
        vis[t] = 1;
        while (vis[t])
        {
            memset(vis, 0, sizeof(vis));
            ans += dfs(s, 1e9);
        }
    }
}

signed main()
{
    cin >> n;
    s = 0, t = 2 * n + 1;
    for (int i = 1, x; i <= n; i++)
    {
        cin >> x;
        add(s, i * 2, x, 0);
        add(i * 2, s, 0, 0);
        add(i * 2 - 1, t, x, 0);
        add(t, i * 2 - 1, 0, 0);
    }
    int p, t1, t2, f1, f2;
    cin>> p >>t1 >>f1 >>t2 >>f2;
    for (int i = 1; i <= n; i++)
    {
        add(s, i * 2 - 1, inf, p);
        add(i * 2 - 1, s, 0, -p);
        if (i + t1 <= n)
        {
            add(i * 2, (i + t1) * 2 - 1, inf, f1);
            add((i + t1) * 2 - 1, i * 2, 0, -f1);
        }
        if (i + t2 <= n)
        {
            add(i * 2, (i + t2) * 2 - 1, inf, f2);
            add((i + t2) * 2 - 1, i * 2, 0, -f2);
        }
        if (i + 1 <= n)
        {
            add(i * 2, (i + 1) * 2, inf, 0);
            add((i + 1) * 2, i * 2, 0, 0);
        }
    }
    LARGE_INTEGER timeStart;    //开始时间  
    LARGE_INTEGER timeEnd;      //结束时间  

    LARGE_INTEGER frequency;    //计时器频率  
    QueryPerformanceFrequency(&frequency);
    double quadpart = (double)frequency.QuadPart;//计时器频率  

    QueryPerformanceCounter(&timeStart);
    zkw();
    cout << cost<<endl;
    QueryPerformanceCounter(&timeEnd);

    //得到两个时间的耗时  
    double elapsed = (timeEnd.QuadPart - timeStart.QuadPart) / quadpart;
    std::cout << elapsed <<"s" << std::endl;//单位为秒，精度为微秒(1000000/cpu主频)  
    
    

  
}