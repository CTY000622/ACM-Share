分析：
模拟题
=============================
#include<iostream>
#include<queue>
#include<map>
#include<vector>
#include<cstdio>
#include<algorithm>
#include<stack>
#include<cstring>
using namespace std;
typedef long long ll;
const int N=1100;
map<string,int> m1;
struct node{
    int pidx;
    int eidx;
    string firstname;
    string lastname;
    string pnum[N];
    string email[N];
}s[N];
bool cmp(string a,string b){
    return a<b;
}
int main(){
    int n;
    int cnt=1;
    while(cin>>n){
        int i;
        if(n==0)
            break;
        int idx=1;
        m1.clear();
        for(i=0;i<N;i++)
            s[i].eidx=s[i].pidx=0;
        for(i=1;i<=n;i++){
            string tmp1,tmp2,tmp3;
            cin>>tmp1>>tmp2>>tmp3;
            string res=tmp2+tmp1;
            if(!m1[res]){
                m1[res]=idx;
                s[idx].firstname=tmp1;
                s[idx].lastname=tmp2;
                int hh=tmp3.find('@');
                if(hh==string::npos){
                    s[idx].pnum[s[idx].pidx++]='('+tmp3.substr(0,3)+')'+tmp3.substr(3,3)+'-'+tmp3.substr(6);
                }
                else{
                    s[idx].email[s[idx].eidx++]=tmp3;
                }
                idx++;
            }
            else{
                int sign=m1[res];
                int hh=tmp3.find('@');
                if(hh==string::npos){
                    s[sign].pnum[s[sign].pidx++]='('+tmp3.substr(0,3)+')'+tmp3.substr(3,3)+'-'+tmp3.substr(6);
                }
                else{
                    s[sign].email[s[sign].eidx++]=tmp3;
                }
            }
        }
        printf("Contact list #%d:\n",cnt++);
        map<string,int>::iterator it;
        for(it=m1.begin();it!=m1.end();it++){
            int sign=it->second;
            cout<<s[sign].firstname<<" "<<s[sign].lastname<<endl;
            cout<<"Phone:"<<endl;
            int j;
            sort(s[sign].pnum,s[sign].pnum+s[sign].pidx,cmp);
            for(j=0;j<s[sign].pidx;j++)
                cout<<s[sign].pnum[j]<<endl;
            cout<<"E-Mail:"<<endl;
            sort(s[sign].email,s[sign].email+s[sign].eidx,cmp);
            for(j=0;j<s[sign].eidx;j++)
                cout<<s[sign].email[j]<<endl;
            cout<<"###"<<endl;
        }
        cout<<endl;
    }
    return 0;
}
