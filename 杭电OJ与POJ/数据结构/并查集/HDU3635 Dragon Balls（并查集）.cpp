分析：
一道并查集水题，我们只需控制根节点移动次数，之后递归更新就可以了
我们定义size为集合大小，d[]为该点到父节点的距离，那么递归的时候只需要跟新到父节点的距离即可。
====================================================
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
int p[N];
int size[N];
int d[N];
int find(int x){
	if(p[x]!=x){
		int t=p[x];
		p[x]=find(p[x]);
		d[x]+=d[t];
	}
	return p[x];
}
int main(){
   int i;
   int t;
   cin>>t;
   int q=1;
   while(t--){
   	int n,m;
   	scanf("%d%d",&n,&m);
   	for(i=1;i<=n;i++){
   		p[i]=i;
   		size[i]=1;
   		d[i]=0;
	}
	printf("Case %d:\n",q++);
	for(i=1;i<=m;i++){
		string s;
		cin>>s;
		if(s=="T"){
			int a,b;
			scanf("%d%d",&a,&b);
			int pa=find(a),pb=find(b);
			if(pa!=pb){
				
				size[pb]+=size[pa];
				size[pa]=0;
				p[pa]=pb;
				d[pa]=1;
			}
		}
		else{
			int a;
			cin>>a;
			int pa=find(a);
			printf("%d %d %d\n",pa,size[pa],d[a]);
		}
	}
   }
}
