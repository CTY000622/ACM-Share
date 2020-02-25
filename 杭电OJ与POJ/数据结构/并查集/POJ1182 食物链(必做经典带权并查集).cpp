分析：
本题最重要的是通过向量的想法来解决这一类关系，这样思维难度大大降低，首先我们明白一点
根据传递性的定义（也就是离散数学中的传递性），x->y =x->z+z>y
我们要知道的一点是，并查集中的题目都是有传递性的，而传递性的题目并不一定能通过并查集解决
我们知道我们要将两个不同的集合合并，就是将他们的头结点合并，所以我们需要知道d[pa]的大小是多少
那么我们定义pa->pb的关系就等于 pa->x+x->y+y->pb，其中x->y是题目中提供了的，所以这道题的难点就迎刃而解。
在find函数中，这个d[x]的关系也可以通过这样的方法解决，我们知道d[x]就是x到合并前的父节点和合并前的父节点与他的父节点的向量和
也就是d[x]=(d[x]+d[p[x]])%3;
虽然我可以将他说的更详细一些，但我并不打算这样做，因为这是核心部分，而其余细节需要自己来敲才能掌握的更牢
注意要对3取模，因为我们这个是在模3意义下的相等，比如x对y是2，y对z是2，那么x对z其实1，也就是x吃z，所以4%3==1
我在很多地方都加了3，是因为我不确定通过操作后是否会出现负数溢出，当然你可以自行判断是否溢出，如果没有溢出，那就不需要+3
==========================================================================
代码:
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
int n,k; 
int d[N];
int find(int x){
	if(p[x]!=x){
		int t=p[x];
		p[x]=find(p[x]);
		d[x]=(d[x]+d[t])%3;
	}
	return p[x];
}
int main(){
	cin>>n>>k;
	int i;
	for(i=1;i<=n;i++)
	p[i]=i;
	int flag=0;
	int x,y;
	int opt;
	while(k--){
		scanf("%d%d%d",&opt,&x,&y);
		if(x>n||y>n){
			flag++;
			continue;
		}
		if(opt==1){
			int pa=find(x),pb=find(y);
			if(pa==pb){
				if(d[x]!=d[y]){
					flag++;
					continue;
				}
			}
			else{
				p[pa]=pb;
				d[pa]=((-d[x]+0+3+d[y])%3+3)%3;
			}
		}
		else{
			if(x==y){
				flag++;
				continue;
			}
			int pa=find(x),pb=find(y);
			if(pa==pb){
				if((d[x]+3-d[y])%3!=1){
					flag++;
					continue;
				}
			}
			else{
				p[pa]=pb;
				d[pa]=((-d[x]+1+3+d[y])%3+3)%3;
			}
		}
	}
	cout<<flag<<endl;
}
