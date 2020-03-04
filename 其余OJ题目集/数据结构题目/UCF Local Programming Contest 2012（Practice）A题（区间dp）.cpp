分析：
经典区间dp的模型，也就是合并石子问题。
只需要预处理消费数组即可，就是长度和最大的深度
==============================================
代码：
#include<iostream>
#include<algorithm>
#include<string>
#include<cstring>
#include<vector>
#include<cstdio>
#include<map>
using namespace std;
const int N=1e5+10;
struct node{
    int l;
    int d;
    int v;
}s[N],w[25][25];
int f[25][25];
int main(){
    int t;
    cin>>t;
    int cnt=1;
    while(t--){
        int n;
        int i,j;
        cin>>n;
        for(i=1;i<=n;i++){
            int a,b;
            cin>>a>>b;
            s[i].l=a;
            s[i].d=b;
        }
        memset(f,0x3f,sizeof f);
        for(i=1;i<=n;i++){
            f[i][i]=0;
        }
        for(i=1;i<=n;i++){
            for(j=i;j<=n;j++){
                    if(i==j){
                        w[i][j].l=s[i].l;
                        w[i][j].d=s[i].d;
                        continue;
                    }
                    int k;
                    int sum=0;
                    for(k=i;k<=j;k++){
                        sum+=s[k].l;
                    }
                w[i][j].l=sum;
                w[i][j].d=max(s[j].d,w[i][j-1].d);

            }
        }
        int len,l,r;
        for(len=2;len<=n;len++){
            for(l=1;l+len-1<=n;l++){
                r=l+len-1;
                int k;
                for(k=l;k<r;k++){
                    int s1=min(w[l][k].l,w[l][k].d);
                    int s2=min(w[k+1][r].l,w[k+1][r].d);
                    f[l][r]=min(f[l][r],f[l][k]+f[k+1][r]+s1*s2*100);
                }
            }
        }
        printf("The minimum cost for lot #%d is $%d.\n",cnt++,f[1][n]);
        cout<<endl;

    }
}
