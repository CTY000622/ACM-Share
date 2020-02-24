并查集+拓扑排序
分析：
这道理重要的想法就是利用并查集缩点，将所有相等的点缩成同一个点
因为如果不缩点，那么如果两个数相等，其他的数与他们中任意一个数有关系，就需要把相等的数的关系也都连上，也就是加边。这样十分复杂
我们又可以发现，如果缩点，因为每个点本身有rp值，所以缩成的点能排序的话，原先也可以。就是基于这个原理证明的缩点的正确性
缩完点后进行拓扑排序，我们发现，如果最后拓扑完的点并不是所有点，说明有环，则conflict，如果可以拓扑，说明是信息不完全，因为会有至少两个点是并列的
如果能全排列，说明ok，代码中一些注意点注释。
===================================================================
代码：
#include<algorithm>
#include<iostream>
#include<cstdio>
#include<vector>
#include<cstring>
#include<string> 
#include<set>
#include<map>
#include<queue>
using namespace std;
typedef long long ll;
const int N=1e5+10;
int in[N];
int x[N],y[N];
int p[N];
string s[N];
int n,m;
int h[N],e[N],ne[N],idx;
int sum;
void add(int a,int b){ //前向星 
    e[idx]=b,ne[idx]=h[a],h[a]=idx++;
}
void init(){
    memset(h,-1,sizeof h);
    idx=0;
    memset(in,0,sizeof in);
}
int find(int x){
    if(p[x]!=x){
        p[x]=find(p[x]);
    }
    return p[x];
}
void topo(){
    int i;
    queue<int> q;
    for(i=0;i<n;i++){
        if(!in[i]&&p[i]==i)//一定要找根节点且入度为0，不然多加了点 
        q.push(i);
    }
    if(q.size()==0){
        cout<<"CONFLICT"<<endl;
        return  ;
    }
    int top=0;
    while(q.size()){
        if(q.size()>1){
            top=1; //不能直接break，因为如果冲突加不完全则输出冲突 
        }
        int u=q.front();
        q.pop();
        sum--;
        for(i=h[u];i!=-1;i=ne[i]){
            int j=e[i];
            in[j]--;
            if(!in[j])
            q.push(j);
        }
    }
    if(sum>0)
    cout<<"CONFLICT"<<endl;
    else{
        if(top==1)
        cout<<"UNCERTAIN"<<endl;
        else
        cout<<"OK"<<endl;
    }
}
int main(){
    int i;
    while(cin>>n>>m){
        for(i=0;i<n;i++)
        p[i]=i;
        init();
        sum=n;
        for(i=1;i<=m;i++){
            cin>>x[i]>>s[i]>>y[i];
            if(s[i]=="="){
                int pa=find(x[i]),pb=find(y[i]);
                if(pa!=pb){
                    p[pa]=pb;
                    sum--;//记得缩完点后个数变少 
                }
            }
        }
        int sign=0;
        for(i=1;i<=m;i++){
            int pa=find(x[i]),pb=find(y[i]);
            if(pa==pb&&s[i]!="="){//这个地方说明两个相等的点存在相等又存在不等关系，则矛盾，例如a=b,b=c,a>c,这在之前是检查不出来的 
                sign=1;
                break;
            }
            if(s[i]==">"){
                add(pa,pb);
                in[pb]++;
            }
            else if(s[i]=="<"){
                add(pb,pa);
                in[pa]++;
            }
        }
        if(sign)
        cout<<"CONFLICT"<<endl;
        else
        topo();
    }
}
