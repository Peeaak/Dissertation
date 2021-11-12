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
const int N = 1000000+7;
const int dx[] = {-1,1,0,0,-1,-1,1,1};
const int dy[] = {0,0,-1,1,-1,1,-1,1};
using namespace std;
 
struct Edge {
    int to,next;
    Edge() {}
    Edge(int to,int next):to(to),next(next) {}
};
struct MCS{
    Edge edge[N<<1];
    int head[N],tot;
    int n,m;
    bool vis[N];
    int id[N];//编号
    int label[N];//与多少标号点相邻
    int order[N];//完美消除序列
    vector<int> V[N];
    vector<int> X[N];
    int S[N];
    int W[N];
    int temp_w[N];	
	int book[N];
    vector<int> weight;
 	vector<int> red;
    vector<int> blue;
    
    void init(int n,int m) {
        this->n=n;
        this->m=m;
        for(int i=1; i<=n; i++)
            V[i].clear();
        for(int i=1; i<=n; i++)
            X[i].clear();
        memset(head,-1,sizeof(head));
        memset(order,0,sizeof(order));
        memset(label,0,sizeof(label));
        memset(vis,0,sizeof(vis));
        memset(id,0,sizeof(id));
        memset(S,0,sizeof(S));
        memset(W,0,sizeof(W));
        tot=0;
    }
 
    void addEdge(int x,int y) {
        edge[tot].to=y;
        edge[tot].next=head[x];
        head[x]=tot++;
    }
 
    void mcs() {
        for(int i=1; i<=n; i++)
            V[0].push_back(i);
        int maxx=0;
        int now=0;
        for(int i=1; i<=n; i++) { //从前往后
            bool flag=false;
            while(!flag) {
                for(int j=V[maxx].size()-1; j>=0; j--) { //从后往前
                    if(vis[V[maxx][j]])
                        V[maxx].pop_back();
                    else {
                        flag=true;
                        now=V[maxx][j];
                        break;
                    }
                }
                if(!flag)
                    maxx--;
            }
            vis[now]=true;
            //逆序存放
            order[n-i+1]=now;
            id[now]=n-i+1;
 
            for(int j=head[now]; j!=-1; j=edge[j].next) {
                int to=edge[j].to;
                if(!vis[to]) {
                    label[to]++;
                    V[label[to]].push_back(to);
                    maxx=max(maxx,label[to]);
                }
            }
        }
    }
    int bucket[N];//桶
    int judge() { //判断是否是弦图
        memset(vis,0,sizeof(vis));
        memset(bucket,0,sizeof(bucket));
        for(int i=n; i>0; i--) {
            int cnt=0;
 
            int ret=1;
            for(int j=head[order[i]]; j!=-1; j=edge[j].next)
                if(id[edge[j].to]>i)
                    vis[bucket[++cnt]=edge[j].to]=1;
 
            for(int j=head[bucket[1]]; j!=-1; j=edge[j].next) {
                int to=edge[j].to;
                if(to!=bucket[1]&&vis[to]) {
                    if(vis[to]) {
                        ret++;
                        vis[to]++;
                    }
                }
            }
            for(int j=1; j<=cnt; j++)
                vis[bucket[j]]=0;
            if(cnt&&ret!=cnt)
                return false;
        }
        return true;
    }
    
    void MaximalClique(){
    	printf("\n\n\n");
    
    	for(int i = 0 ; i <= n ; i ++ )
    		S[i] = 0;
    	
    	for(int i = 1 ; i <= n ; i ++){
    		//printf("%d-----\n",i);
    		int temp = head[order[i]];
    		if(temp == -1){
    				printf("Maximal clique %d\n",order[i]);
			}
    		
    		else{
    			for(int j = head[order[i]]; j != -1 ; j = edge[j].next){
    				int now = order[i];
    				int nt = edge[j].to;
    				//printf("-%d %d\n",now,nt);
    				if(id[now] < id[nt]){
    					
    					X[now].push_back(nt);
					}
					//printf("--%d %d",id[X[now][0] ],id[X[now][X[now].size()]]);
					if(X[now].size()){
						if(id[X[now][0] ] > id[X[now][X[now].size()-1]] ){
							swap(X[now][0],X[now][X[now].size()-1]);
						}
					}
				}
				int now = order[i];
				//printf("X.size :%d \n",X[now].size());
				if(X[now].size() == 0) continue;
				int nowu = X[now][0];
				if(S[nowu] < X[now].size()-1)
				S[nowu] = X[now].size()-1;
				if(S[now] < X[now].size()){
					printf("Maximal clique : %d ", now);
					for(int j = 0 ; j < X[now].size(); j ++){
						printf("%d ",X[now][j]);
					} 	
					printf("\n");
				}
				
			}
		}	
	}
	
	void MaximalWeightClique(){
    	printf("\n");
    	int ans = 0;
    	for(int i = 0 ; i <= n ; i ++ )
    		S[i] = 0;
    	
    	for(int i = 1 ; i <= n ; i ++){
    		//printf("%d-----\n",i);
    		
    		int temp = head[order[i]];
    		if(temp == -1){
    			printf("Maximal clique %d\n",order[i]);
    			if(ans < W[order[i]]){
    				ans = W[order[i]];
    				weight.clear();
    				weight.push_back(order[i]);
				} 
			}
    			
    		else{
    			for(int j = head[order[i]]; j != -1 ; j = edge[j].next){
    				int now = order[i];
    				int nt = edge[j].to;
    				//printf("-%d %d\n",now,nt);
    				if(id[now] < id[nt]){
    					
    					X[now].push_back(nt);
					}
					//printf("--%d %d",id[X[now][0] ],id[X[now][X[now].size()]]);
					if(X[now].size()){
						if(id[X[now][0] ] > id[X[now][X[now].size()-1]] ){
							swap(X[now][0],X[now][X[now].size()-1]);
						}
					}
				}
				int now = order[i];
				//printf("X.size :%d \n",X[now].size());
				if(X[now].size() == 0) continue;
				int nowu = X[now][0];
				if(S[nowu] < X[now].size()-1)
				S[nowu] = X[now].size()-1;
				if(S[now] < X[now].size()){
					int tempweight = 0;
					printf("Maximal clique : %d ", now);
					for(int j = 0 ; j < X[now].size(); j ++){
						printf("%d ",X[now][j]);
						tempweight += W[X[now][j]]; 
					}
 					tempweight += W[now];
					printf("\n");
					
					printf("the weight of current maximal clique :%d\n",tempweight);
					if(tempweight > ans ){
						ans = tempweight;
						weight.clear();
						weight.push_back(now);
						for(int j = 0 ; j < X[now].size(); j ++){
							weight.push_back(X[now][j]);
						}
					}
				}
				
			}
		}
		printf("the maximal weight clique is : ");
		for(int i = 0 ; i < weight.size() ; i++){
			printf("%d ",weight[i]);
		}
		printf("\n");
		printf("the sum of weight of the maximal weight clique is : %d", ans );
	}
    int getMaximumClique() { //计算最大团、最小着色
        //printf("!!!");
		int res=0;
        for(int i=1; i<=n; i++)
            res=max(res,label[i]+1);
        
        return res;
    }
    int getMaximumIndependentSet() { //计算最大独立集、最小团覆盖
        memset(vis,0,sizeof(vis));
        int res=0;
        for(int i=1; i<=n; i++) {
            if(!vis[order[i]]) {
                res++;
                vis[order[i]]=true;
                for(int j=head[order[i]]; j!=-1; j=edge[j].next)
                    vis[edge[j].to]=true;
            }
        }
        return res;
    }
  
    void getMaximumWeightedIndependentSet(){    	
    	for(int i = 0 ; i < N ; i++)
    		temp_w[i] = W[i];
    	memset(vis,0,sizeof(vis));
    	memset(book,0,sizeof(book));
    	red.clear();
    	blue.clear();
    	for(int i = 1 ; i <= n ; i++){
    		int now = order[i];
    		vis[now] = 1;
    		if(temp_w[now] <= 0)
    			continue;
    		else{
    			red.push_back(now);
    			for(int j = head[now] ; j != -1 ; j = edge[j].next){
    				int v = edge[j].to;
    				if(vis[v])
    					continue;
    				temp_w[v] -= temp_w[now];
    				temp_w[v] = max(temp_w[v],0);
				}
			}
			temp_w[now] = 0;
		}
		for(int i = red.size() - 1; i >= 0  ; i --){
			int now = red[i];
			int flag = 0;
			for(int j = head[now]; j != -1 ; j = edge[j].next){
				int v = edge[j].to;
				if (book[v]){
					flag = 1;
					break;
				}
			}
			if(flag == 0){
				book[now] = 1;
				blue.push_back(now);
			}
			
		}
		int ans = 0;
//		for(int i = 0 ; i < red.size() ; i ++){
//			printf("%d \n",red[i]);
//		
//		}
		printf("the maximum weighted independent set is :");
		for(int i = 0 ; i < blue.size() ; i ++){
			printf("%d ",blue[i]);
			ans += W[blue[i]];
		}
		printf("\n");
		printf("the sum of weight is %d\n",ans);
		return ;
	}
}mcs;
int main() {
    int n,m;
    while(scanf("%d%d",&n,&m)!=EOF&&(n+m)) {
        mcs.init(n,m); 
//		for(int i = 1 ; i <= n ; i ++){
//        	scanf("%d",&mcs.W[i]);
//		}
        for(int i=1; i<=m; i++) {
            int x,y;
            scanf("%d%d",&x,&y);
            mcs.addEdge(x,y);
            mcs.addEdge(y,x);
        }
       	clock_t start_time,end_time;
		start_time = clock();
        mcs.mcs();
		int c = mcs.getMaximumIndependentSet();
		printf("%d\n",c);
		end_time = clock();
		printf("%lf \n",(double)(end_time-start_time));
		
    }
    return 0;
}
/*
6 10
2 3
3 4
4 5
5 6
6 2
1 2
1 3
1 4
1 5
1 6

4 5
1 2
2 3
3 4
4 1
2 4

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

9 14
2 1 2 3 1 3 1 2 3
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
9 10
1 2
1 3
1 4
1 5
1 6
1 7
1 8
1 9
1 10

6 9
1 2 4 2 2 2
1 2
1 3
2 3
2 4
2 5
3 5
4 5
4 6
5 6
*/
