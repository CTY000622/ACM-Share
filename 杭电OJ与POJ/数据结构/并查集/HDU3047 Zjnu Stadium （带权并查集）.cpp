分析：
经典向量法
====================
#include<iostream>
#include<algorithm>
#include<string>
#include<cstring>
#include<vector>
#include<cstdio>
#include<map>
using namespace std;
const int N=1e5+10;
int n,m;
int p[N];
int d[N];
int find(int x){
    if(x!=p[x]){
        int t=p[x];
        p[x]=find(p[x]);
        d[x]=(d[x]+d[t])%300;
    }
    return p[x];
}
int main(){
    while(cin>>n>>m){
        int i;
        memset(d,0,sizeof d);
        int num=0;
        for(i=1;i<=n;i++)
            p[i]=i;
        for(i=1;i<=m;i++){
            int x,a,b;
            scanf("%d%d%d",&a,&b,&x);
            int pa=find(a),pb=find(b);
            if(pa==pb){
                if(((d[a]-d[b])%300+300)%300!=(-x+300)%300)
                    num++;
            }
            else{
                p[pa]=pb;
                d[pa]=((-d[a]-x+d[b])%300+300)%300;
            }
        }
        cout<<num<<endl;
    }
}
