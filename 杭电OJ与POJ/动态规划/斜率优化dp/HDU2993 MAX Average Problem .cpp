本题的做法是斜率优化dp，但是这题杭电经过数据加强后即使算法正确也很难通过
必须要用读入加速，但这个其实在acm中并不要求，所以不建议做，同题可做poj 2018

#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cmath>
#include<vector>
#include<string>
#include<cstring>
#include<map>
using namespace std;
typedef long long ll;
const int N=1e5+10;
const int BUF=25000000;
char Buf[BUF],*buf=Buf;
inline void read(int &a){
    for(a=0;*buf<48;buf++);
    while(*buf>47) a=a*10+*buf++-48;
}
int a[N];
int q[N];
double f[N];
int n,k;
int tot;
int s[N];
double check(int j,int i){
    return  1.0*(s[i]-s[j])/(i-j);
} 
int main(){
    int i;
    tot=fread(Buf,1,BUF,stdin);
    while(1){
    if(buf-Buf+1>=tot) break;

        read(n),read(k);
    for(i=1;i<=n;i++){
        read(a[i]);
        s[i]=s[i-1]+a[i];
    }
    int tt=0;
    int hh=0;
    q[0]=0;
    double ans=0;
    for(i=k;i<=n;i++){
      while(hh+1<=tt&&check(q[hh],i)<check(q[hh+1],i))
      hh++;
      ans=max(ans,check(q[hh],i));
      int j=i-k+1; 
      while(hh+1<=tt&&check(q[tt],j)<check(q[tt-1],q[tt]))
      tt--;
      q[++tt]=j;
    }
    printf("%.2f\n",ans); }
    
    
}
