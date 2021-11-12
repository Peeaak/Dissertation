#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<string>
#include<cstring>
#include<cmath>
#include<ctime>
#include<algorithm>
#include<utility>
#include<stack>
#include<queue>
#include<vector>
#include<set>
#include<map>
#include<bitset>
#define PI acos(-1.0)
#define INF 0x3f3f3f3f
#define LL long long
#define Pair pair<int,int>
LL quickPow(LL a,LL b){ LL res=1; while(b){if(b&1)res*=a; a*=a; b>>=1;} return res; }
LL quickModPow(LL a,LL b,LL mod){ LL res=1; a=a%mod; while(b){if(b&1)res=(a*res)%mod; a=(a*a)%mod; b>>=1;} return res; }
LL getInv(LL a,LL mod){ return quickModPow(a,mod-2,mod); }
const double EPS = 1E-10;
const int MOD = 1E9+7;
const int N = 22000;
const int dx[] = {-1,1,0,0,-1,-1,1,1};
const int dy[] = {0,0,-1,1,-1,1,-1,1};
using namespace std;
 
struct Edge{
    int to;
    Edge(){}
    Edge(int to):to(to){}
};
struct Node{
    int id,num;
    Node(){}
    Node(int id,int num):id(id),num(num){}
    friend bool operator<(Node a,Node b) {
        return a.num<b.num;
    }
};
int n,m;
int G[N][N];
vector<Edge>edge[N];
int link[N],tot;//标号序列
int order[N];//完美消除序列
int num[N];//点编号
int bucket[N];//更新一个点的标号序列时的桶
bool vis[N];
clock_t start_time,end_time;
 
void bfs(int x){//维护标号序列
    memset(num,0,sizeof(num));
    memset(link,0,sizeof(link));
    memset(vis,0,sizeof(vis));
    tot=n;
 
    priority_queue<Node> Q;
    Q.push(Node(x,1));
    while(!Q.empty()) {
        Node now=Q.top();
        Q.pop();
        if(!vis[now.id]){
            vis[now.id]=true;
            link[tot]=now.id;
            order[now.id]=tot;
            tot--;
            if(tot==0)
                break;
        }
        for(int i=0;i<edge[now.id].size();i++) {
            int to=edge[now.id][i].to;
            if (vis[to]) continue;
            num[to]++;
            if(!vis[to])
               Q.push(Node(to,num[to]));
        }
    }
}
bool check() {
    bfs(1);//维护标号序列
 	end_time = clock();
	printf("%lf \n",(double)(end_time-start_time));
    for(int i=1;i<=n;i++){
        int minn=n+1;
        int tail=0;//桶的指针
        int value;
        
        for(int j=0;j<edge[link[i]].size();j++) {
            int to=edge[link[i]][j].to;
            if(order[to]>i) {
                if(minn>order[to]) {
                    minn=order[to];
                    value=to;
                }
                bucket[tail++]=to;//入桶
            }
        }
        for(int j=0;j<tail;j++) {
            if(bucket[j]!=value&&G[value][bucket[j]]==0)
                return false;
        }
    }
    return true;
}
int main() {
    while(scanf("%d%d",&n,&m)!=EOF&&(n+m)){
    	clock_t start_time,end_time;
		
    	
        for(int i=1;i<=n;i++)
            edge[i].clear();
        memset(G,0,sizeof(G));
        for(int i=0;i<m;i++){
            int x,y;
            scanf("%d%d",&x,&y);
            edge[x].push_back(y);
            edge[y].push_back(x);
            G[x][y]=1;
            G[y][x]=1;
        }
		start_time = clock();
        if(check())
            printf("Perfect\n\n");
        else
            printf("Imperfect\n\n");		
		end_time = clock();
		printf("%lf \n",(double)(end_time-start_time));
//        for(int i = 0 ; i <=n ; i ++){
//        	printf("%d ",order[i]);
//		}
		printf("\n");

		

		
    }
    return 0;
}
/*
9
14
1 2
1 3
1 4
2 3
2 4
2 5
3 5
3 4
3 6
3 7
5 6
6 7
6 8
8 9

10 18
2 3
3 4
4 5
5 6
6 7
7 8
8 9
9 10
10 2
1 2
1 3
1 4
1 5
1 6
1 7
1 8
1 9
1 10

10 17
2 3
3 4
4 5
5 6
6 7
7 8
8 9
10 2
1 2
1 3
1 4
1 5
1 6
1 7
1 8
1 9
1 10
*/
