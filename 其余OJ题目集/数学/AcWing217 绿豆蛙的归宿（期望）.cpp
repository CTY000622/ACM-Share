#include<iostream>
#include<cstring>
using namespace std;
const int N=3e5+10;
int h[N],e[N],ne[N],idx;
int w[N];
double f[N];
int in[N];
void add(int a,int b,int c){
    e[idx]=b,ne[idx]=h[a],w[idx]=c,h[a]=idx++;
}
double dfs(int u){
    if(f[u]>=0)
    return f[u];
    f[u]=0;
    int i;
    for (int i = h[u]; ~i; i = ne[i])
    {
        int j = e[i];
        f[u] += (w[i] + dfs(j)) / in[u];
    }
    return f[u];
}
int main(){
    int i;
    int n;
    int m;
    cin>>n>>m;
    memset(h,-1,sizeof h);
    memset(f,-1,sizeof f);
    for(i=1;i<=m;i++){
        int u,v;
        int c;
        scanf("%d%d%d",&u,&v,&c);
        add(u,v,c);
        in[u]++;
    }
    printf("%.2f\n",dfs(1));
    return 0;
}
