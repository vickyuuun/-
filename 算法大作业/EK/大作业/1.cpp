#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <functional>
#include <queue>
#include <stdio.h>  
#include <windows.h>  
#include <iostream>  
using namespace std;
int cnt = 1, nd, price, m, f, n, s, ans;
bool inq[2005];
const int INF = 0x3f3f3f3f;
const int MAXN = 80003;
const int MAXE = 160003;
struct Edge {
    int from, to, nxt, cap, flow, cost;
    Edge() {}
    Edge(int from, int to, int nxt, int cap, int flow, int cost) :from(from), to(to), nxt(nxt), cap(cap), flow(flow), cost(cost) {}
}e[MAXE];
int h[MAXN], p;
int source, sink;
int cur[MAXN];
int d[MAXN];
queue<int> q;
bool exist[MAXN];
void add_edge(int x, int y, int cap, int cost) {
    e[p] = Edge(x, y, h[x], cap, 0, cost); h[x] = p++;
    e[p] = Edge(y, x, h[y], 0, 0, -cost); h[y] = p++;
}
bool SPFA() {
    memset(d, 0x3f, sizeof(d));
    memset(exist, 0, sizeof(exist));
    memset(cur, -1, sizeof(cur));
    q.push(source);
    d[source] = 0;
    exist[source] = 1;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        exist[u] = 0;
        for (int i = h[u]; ~i; i = e[i].nxt) {
            int v = e[i].to;
            if (e[i].cap > e[i].flow && d[v] > d[u] + e[i].cost) {
                d[v] = d[u] + e[i].cost;
                cur[v] = i;
                if (!exist[v]) {
                    q.push(v);
                    exist[v] = 1;
                }
            }
        }
    }
    return d[sink] != INF;
}
long long MCMF() {
    long long cost = 0;
    while (SPFA()) {
        int flow = INF;
        for (int i = sink; i != source; i = e[cur[i]].from)
            flow = min(flow, e[cur[i]].cap - e[cur[i]].flow);
        for (int i = sink; i != source; i = e[cur[i]].from) {
            e[cur[i]].flow += flow;
            e[cur[i] ^ 1].flow -= flow;
        }
        cost += flow * d[sink];
    }
    return cost;
}
int main()
{
    memset(h, -1, sizeof(h));
    cin>>nd;
    int x; source = 0; sink = 8000;
    for (int i = 1; i <= nd; i++)
    {
        cin>>x;
        add_edge(source, i, x, 0);//连源点汇点
        add_edge(nd + i, sink, x, 0);
    }
    cin>>price>>m>>f>>n>>s;
    for (int i = 1; i <= nd; i++)
    {
        if (i + 1 <= nd)add_edge(i, i + 1, INF, 0);//留到明天
        if (i + m <= nd)add_edge(i, nd + i + m, INF, f);//快洗
        if (i + n <= nd)add_edge(i, nd + i + n, INF, s);//慢洗
        add_edge(source, nd + i, INF, price);//新买
    }

    LARGE_INTEGER timeStart;    //开始时间  
    LARGE_INTEGER timeEnd;      //结束时间  

    LARGE_INTEGER frequency;    //计时器频率  
    QueryPerformanceFrequency(&frequency);
    double quadpart = (double)frequency.QuadPart;//计时器频率  

    QueryPerformanceCounter(&timeStart);
    cout<<MCMF()<<endl;

    QueryPerformanceCounter(&timeEnd);

    //得到两个时间的耗时  
    double elapsed = (timeEnd.QuadPart - timeStart.QuadPart) / quadpart;
    std::cout << elapsed << "s" << std::endl;//单位为秒，精度为微秒(1000000/cpu主频)  
    return 0;
}
