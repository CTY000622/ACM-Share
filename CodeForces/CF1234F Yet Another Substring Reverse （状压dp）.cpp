分析：
首先我们发现，因为可以在任意地方翻转，所以最后的答案就是一个合法子串和他的补集的子集中个数和最大的那个
因此我们先枚举每一个合法状态，记录他的合法个数有几个。
然后我们从头枚举每一个状态，计算状态的子集中的最大个数。
这样我们最后只要枚举状态和补集，就能计算出真正的答案了
========================================
代码：
#include<iostream>
#include<vector>
#include<cstdio>
#include<string>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=21;
int f[1<<21];
int n;
string s;
int st[N];
int main(){
	cin>>s;
	int i,j;
	for(i=0;i<s.size();i++){
		int tmp=0;
		int cnt=0;
		memset(st,0,sizeof st);
		for(j=i;j<s.size();j++){ //枚举每一个合法状态 
			if(st[s[j]-'a'])
			break;
			tmp+=1<<(s[j]-'a');
			st[s[j]-'a']=1;
			cnt++;
			f[tmp]=cnt;
		}
		
	} 
	for(i=0;i<1<<20;i++){ //dp思想由子集的最大数来判断当前状态的最大个数 
		for(j=0;j<20;j++){
			if(i>>j&1){
				f[i]=max(f[i],f[i^(1<<j)]);
			}
		}
	}
	int res=0;
	for(i=0;i<1<<20;i++){//枚举状态和补集就行，因为现在补集中的个数就是补集和他子集中的最大个数 
		res=max(res,f[i]+f[i^((1<<20)-1)]);
	}
	cout<<res<<endl;
} 
