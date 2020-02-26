The same as the poj1182
Only need to enum every person as judge
=======================================
code:
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
int p[N];
int d[N];
int x[N],y[N];
char s[N];
int n;
void init(){
	for(int i=0;i<=n;i++){
		p[i]=i;
		d[i]=0;
	}
}
int find(int x){
	if(p[x]!=x){
		int t=p[x];
		p[x]=find(p[x]);
		d[x]=(d[x]+d[t])%3;
	}
	return p[x];
}
int main(){
    int m;
	while(cin>>n>>m){
		int i;
		for(i=1;i<=m;i++){
			cin>>x[i]>>s[i]>>y[i];
		}
		int sign;
		int ans=-1;
		int pos=0;
		int tot=0;
		for(i=0;i<n;i++){
			int flag=1;
			init();
			for(int j=1;j<=m;j++){
				if(x[j]==i||y[j]==i)
				continue;
				if(s[j]=='=')
				sign=0;
				if(s[j]=='>')
				sign=1;
				if(s[j]=='<')
				sign=2;
				int pa=find(x[j]),pb=find(y[j]);
				if(pa==pb){
					if((d[x[j]]+3-d[y[j]])%3!=sign){
						flag=0;
						pos=max(pos,j);
						break;
					}
				}
				else{
					p[pa]=pb;
					d[pa]=(-d[x[j]]+sign+3+d[y[j]])%3;
				}
			}
			if(flag){
				tot++;
				ans=i;
			}
		}
		if(tot==0)
		cout<<"Impossible"<<endl;
		else if(tot>=2){
			cout<<"Can not determine"<<endl;
		}
		else{
			printf("Player %d can be determined to be the judge after %d lines\n",ans,pos);
		}
	} 
}
