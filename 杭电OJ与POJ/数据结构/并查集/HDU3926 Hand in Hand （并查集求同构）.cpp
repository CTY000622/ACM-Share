分析：
本题可以用并查集求同构的原因是，每个点只能和两个点相连，因此只有环和链两种情况，没有其他的种类。
首先我们知道同构就是有相同个数长度的的链和相同个数长度的环。这样我们在并查集只需要维护两个信息。
一个是集合大小，一个是有没有环。因为环只可能在头尾节点，所以只需要把环记录在我们并查集的根节点就行了。就能代表这个集合是不是环
===================================================
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
const int mod=1e9+7;
int p[N];
int d[N];
int sign[N];
int n,m;
struct node{
    int cnt;
    int st;
    bool operator <(const node &t){
        if(cnt==t.cnt)
        return st<t.st;
        return cnt<t.cnt;
    }
}s1[N],s2[N];
void init(){
    int i;
    for(i=1;i<=n;i++){
        p[i]=i;
        d[i]=1;
        sign[i]=0;
    }
}
int find(int x){
    if(p[x]!=x){
        p[x]=find(p[x]);
    }
    return p[x];
}
int main(){
      int t;
      cin>>t;
      int q=1;
      while(t--){
        cin>>n>>m;
        int n1=n,m1=m;
        init();
        int i;
        for(i=1;i<=m;i++){
            int a,b;
            cin>>a>>b;
            int pa=find(a),pb=find(b);
            if(pa==pb){
                sign[pa]=1;    
            }
            else{
                p[pa]=pb;
                d[pb]+=d[pa];
            }
        }
        int idx=0;
        for(i=1;i<=n;i++){
            if(p[i]==i){
                s1[idx++]={d[i],sign[i]};
            }
        }
        sort(s1,s1+idx);
        cin>>n>>m;
        init();
        for(i=1;i<=m;i++){
            int a,b;
            cin>>a>>b;
            int pa=find(a),pb=find(b);
            if(pa==pb){
                sign[pa]=1;    
            }
            else{
                p[pa]=pb;
                d[pb]+=d[pa];
            }
        }
        idx=0;
        for(i=1;i<=n;i++){
            if(p[i]==i){
                s2[idx++]={d[i],sign[i]};
            }
        }
        sort(s2,s2+idx);
        int flag=0;
        for(i=0;i<idx;i++){
            if(s1[i].cnt!=s2[i].cnt||s1[i].st!=s2[i].st){
                flag=1;
                break;
            }
        }
        if(n1!=n||m1!=m){
            printf("Case #%d: NO\n",q++);
            continue;
        }
        if(!flag)
        printf("Case #%d: YES\n",q++);
        else
        printf("Case #%d: NO\n",q++);
    }
}
