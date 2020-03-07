#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
#include<cstdio>
#include<queue>
#include<map>
#include<cstring>
#include<string>
using namespace std;
typedef long  long ll;
const int N=1e5+10;
int n,m,l;
int cnt[12];
int f[N][110];
int a[N];
struct node{  //多个trie树模板
    int num[2];
    int sum;
    void init(){
        num[0]=num[1]=sum=0;
    }
}tr[12][N];
void add(int p,int x,int sign){
    int cur=1;
    tr[p][cur].sum+=sign;
    for(int i=30;i>=0;i--){
        int y = x>>i&1;
        if(!tr[p][cur].num[y])
            tr[p][cur].num[y]=++cnt[p];
        cur=tr[p][cur].num[y];
        tr[p][cur].sum+=sign;
    }
}
int find(int p,int x){//异或的经典操作，通过贪心在trie树上找相反求最大
    int cur=1,ans=0;
    for(int i=30;i>=0;i--){
        int y=x>>i&1;
        if(tr[p][tr[p][cur].num[y^1]].sum)
            ans+=1<<i,cur=tr[p][cur].num[y^1];
        else
            cur=tr[p][cur].num[y];
    }
    return ans;
}
int check(int mid){
    for(int i=0;i<=m+1;i++)//初始化不要用memset，容易超时，很难查错
        for(int j=1;j<=cnt[i];j++)
            tr[i][j].init();
    for(int i=0;i<=m+1;i++)
        cnt[i]=1;
    for(int i=0;i<=n;i++)
        for(int j=0;j<=m;j++)
        f[i][j]=0;
    f[0][0]=1;//只有这种状态是初始合法的，也就是前0个分成0组
    add(0,0,1);//刚开始是只有0这个数
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(i>l&&f[i-l-1][j-1]) //当前位置已经超过l长度了，说明不能更新，如果前面是合法转移，要从trie树中删掉
                add(j-1,a[i-l-1],-1);
            int tmp=find(j-1,a[i]);
            if(tmp>=mid){
                add(j,a[i],1);
                f[i][j]=1;
            }
        }
    }
    return f[n][m];
}
int main(){
    int t;
    cin>>t;
    int cnt=1;
    while(t--){
       cin>>n>>m>>l;
       int i;
       memset(tr,0,sizeof tr);
       for(i=1;i<=n;i++){
        scanf("%d",&a[i]);
        a[i]^=a[i-1];
       }
       int l=0,r=0x3f3f3f3f;
       while(l<r){
         int mid=l+r+1>>1;
         if(check(mid))
            l=mid;
         else
            r=mid-1;
       }
       printf("Case #%d:\n",cnt++);
       cout<<l<<endl;
    }
    return 0;
}
