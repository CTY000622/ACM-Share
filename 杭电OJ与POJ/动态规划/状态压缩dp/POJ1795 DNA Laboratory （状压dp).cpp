分析：
我们发现字符串的个数不多，就会想到搜索或者是状态压缩
这题如果能将两个合并而且减少长度，那就意味着一个字符串的末尾和一个字符串的开头有相同之处 ，这样我们就可以先预处理一下
我们定义状态为f[i][j]表示在i集合中，当前以j开头，我们定义j开头是为了找最小字典序好找一些
我们知道最小长度可能多种，这样就需要通过dfs来构造。
==========================================
代码：
#include<iostream>
#include<vector>
#include<cstdio>
#include<string>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=17;
const int mod=1e9+7;
const int inf=0x3f3f3f3f;
int f[1<<N][N];
string s[N];
int n;
int w[N][N];
string ans;
void init(){
    int i;
    int j;
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            if(i==j)
            continue;
            if(s[i].find(s[j])!=string::npos){
                s[j]=s[i];
            }
        }
    }
    sort(s,s+n);
    n=unique(s,s+n)-s;
    memset(w,0,sizeof w);
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            if(i==j)
            continue;
            int k;
            int len=min(s[i].length(),s[j].length());
            for(k=0;k<=len;k++){
                if(s[i].substr(s[i].length()-k)==s[j].substr(0,k))
                w[i][j]=s[i].length()-k;
            }
        }
    }
}
void dfs(int id,int sum){
    if(sum==0)
    return ;
    int i,j;
    int sign=-1;
    string tmp;
    for(i=0;i<n;i++){
        if((sum>>i&1)&&i!=id){
            if(f[sum][id]==f[sum^(1<<id)][i]+w[id][i]){
                string t=s[i].substr(s[id].length()-w[id][i]);
                if(sign==-1||t<tmp){
                    tmp=t;
                    sign=i;
                }
            }
        }
    }
    ans+=tmp;
    dfs(sign,sum^(1<<id));
}
int main(){
    int t;
    cin>>t;
    int kase=0;
    while(t--){
        int i,j,k;
        cin>>n;
        for(i=0;i<n;i++){
            cin>>s[i];
        }
        if(n==1){
            init();
            cout << "Scenario #" << ++kase << ":" << endl;
            cout << s[0] << endl;
            cout << endl;
        }
        else{
            init();
            memset(f,0x3f,sizeof f);
            for(i=0;i<n;i++){
                f[1<<i][i]=s[i].length();
            }
            for(i=0;i<1<<n;i++){
                for(j=0;j<n;j++){
                    if(i>>j&1){
                        for(k=0;k<n;k++){
                            if(j==k)
                                continue;
                            if(i>>k&1){
                                f[i][j]=min(f[i][j],f[i^(1<<j)][k]+w[j][k]);
                            }
                        }
                    }
                }
            }
            int id=0;
            for(i=1;i<n;i++){
                if(f[(1<<n)-1][i]<f[(1<<n)-1][id]){
                    id=i;
                }
            }
            ans=s[id];
            dfs(id,(1<<n)-1);
            cout << "Scenario #" << ++kase << ":" << endl;
            cout << ans << endl;
            cout << endl;
        }
    }
}
