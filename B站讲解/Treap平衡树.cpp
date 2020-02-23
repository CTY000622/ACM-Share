AcWing 253
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<map> 
#include<vector> 
using namespace std;
typedef  long long ll;
const int N=5e5+10;
const int inf=0x3f3f3f3f;
int root;
int idx;
struct node{
    int l,r;
    int key;
    int val;
    int cnt;
    int size;
}tr[N];
void pushup(int u){ //总个数等于两边加自身 
    tr[u].size=tr[tr[u].l].size+tr[tr[u].r].size+tr[u].cnt;  
}
int get(int key){
    tr[++idx].key=key;    //创建辛店赋值key 
    tr[idx].val=rand();  //为val创建一个随机值，便于大根堆 
    tr[idx].size=tr[idx].cnt=1; 
    return idx;    
}
void build(){ //初始化，重点是两个哨兵以及别忘了更新 
    get(-inf);
    get(inf);
    root=1;
    tr[1].r=2;
    pushup(1);
}
void zig(int &p){ //右旋操作 
    int q=tr[p].l;
    tr[p].l=tr[q].r;
    tr[q].r=p;
    p=q;
    pushup(tr[p].r);
    pushup(p);
}
void zag(int &p){ //左旋操作 
    int q=tr[p].r;
      tr[p].r=tr[q].l;
      tr[q].l=p;
      p=q;
      pushup(tr[p].l);
      pushup(p);
}
void insert(int &p,int key){  //没有就创造 
    if(!p){
        p=get(key);
        return ;
    }
    if(tr[p].key==key)
    tr[p].cnt++;
    else if(tr[p].key>key){
        insert(tr[p].l,key);  //插左边很可能导致左边的val大于根节点 
        if(tr[tr[p].l].val>tr[p].val)
        zig(p);
    }
    else{
        insert(tr[p].r,key);  //插右边很可能导致右边的val大于根节点 
        if(tr[tr[p].r].val>tr[p].val)
        zag(p);
    }
    pushup(p);  //一定要更新 
}
void remove(int &p,int key){
    if(!p)
    return ;
    if(tr[p].key==key){ //分三类 
        if(tr[p].cnt>1)
        tr[p].cnt--;
        else if(tr[p].l||tr[p].r){   
            if(!tr[p].r||tr[tr[p].l].val>tr[tr[p].r].val){ //没有右节点，或者左节点的val大于右节点 
                zig(p);
                remove(tr[p].r,key);
            }
            else{
                zag(p);  //其他情况，左旋 
                remove(tr[p].l,key);
            }
        }
        else
        p=0; //叶节点直接删除 
    }
    else if(tr[p].key>key)
    remove(tr[p].l,key);
    else 
    remove(tr[p].r,key);
    pushup(p);
}
int get_rank_by_key(int p, int key){//通过值找排名 
    if(!p)
    return 0;
    if(tr[p].key==key)
    return tr[tr[p].l].size+1;
    else if(key<tr[p].key)
    return  get_rank_by_key(tr[p].l,key);
    else
    return tr[tr[p].l].size+tr[p].cnt+get_rank_by_key(tr[p].r,key);
    
}
int get_key_by_rank(int p, int rank){ //通过排名找值
    if(!p)
    return inf;
    if(tr[tr[p].l].size>=rank)
    return get_key_by_rank(tr[p].l,rank);
    else if(tr[tr[p].l].size+tr[p].cnt>=rank)
    return tr[p].key;
    else
    return get_key_by_rank(tr[p].r,rank-tr[p].cnt-tr[tr[p].l].size);
}
int get_prev(int p, int key){//查询比他小的最大值 
    if(!p) return -inf;
    if(tr[p].key>=key)     
    return get_prev(tr[p].l,key);
    return max(tr[p].key,get_prev(tr[p].r,key));
}
int get_next(int p, int key){ //查找比他大的最小值 
    if(!p) return inf;
    if(tr[p].key<=key)
    return get_next(tr[p].r,key);
    return min(tr[p].key,get_next(tr[p].l,key)); 
}
int main(){
    build();
    int n;
    scanf("%d", &n);
    while (n -- ){
        int opt, x;
        scanf("%d%d", &opt, &x);
        if (opt == 1) insert(root, x);
        else if (opt == 2) remove(root, x);
        else if (opt == 3) printf("%d\n", get_rank_by_key(root, x) - 1);
        else if (opt == 4) printf("%d\n", get_key_by_rank(root, x + 1));
        else if (opt == 5) printf("%d\n", get_prev(root, x));
        else printf("%d\n", get_next(root, x));
    }
    return 0;
}

