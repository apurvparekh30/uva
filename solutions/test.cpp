// Apurv Parekh
// 4th Aug 2018

#include <algorithm>
#include <cstdio>
#include <queue>

using namespace std;

const int MAX = 10;
const int mod = 20437;

struct cell{
    int x,y,w;
    char to;
    cell(){}
    cell(int x,int y,int w,char to):x(x),y(y),w(w),to(to){}
};
int n;
char grid[MAX][MAX];
bool visited[11][11][100];
cell s;

char last;

int dp[11][11][100][130];
int dr[]={1,0,-1,0};
int dc[]={0,-1,0,1};
int tc=0;

void bfs(){
    queue<cell> q;
    q.push(s);
    while(!q.empty()){
        cell u=q.front(); q.pop();
        int x=u.x; int y=u.y; int w=u.w; char to=u.to;
        if(visited[x][y][to]) continue;
        visited[x][y][to]=true;
        if(grid[x][y] == last){
            printf("%d %d\n",w,dp[x][y][to][w]%mod);
            return;
        }
        int paths=dp[x][y][to][w];
        if(grid[x][y]==to){
            grid[x][y]='.';
            to++;
        }
        for(int i=0;i<4;i++){
            int nx=x+dr[i]; int ny=y+dc[i];
            if(nx<0||nx>=n||ny<0||ny>=n) continue;
            if(visited[nx][ny][to]) continue;
            char next = grid[nx][ny];
            if(next!='.' && next!=to) continue;
            int &ref=dp[nx][ny][to][w+1];
            ref=(ref+(paths%mod))%mod;
            q.push(cell(nx,ny,w+1,to));
        }
    }
    printf("Impossible\n");
}

int main(){
   
    while(scanf("%d",&n),n){
        tc++;
        last='A';
        fill(&dp[0][0][0][0],&dp[11][0][0][0],0);
        fill(&visited[0][0][0],&visited[11][0][0],false);
        for(int i=0;i<n;i++){
            scanf("% ");
            for(int j=0;j<n;j++){
                scanf("%c",&grid[i][j]);
                if(grid[i][j]=='A'){
                    dp[i][j]['A'][0]=1;
                    s=cell(i,j,0,'A');
                }
                if(grid[i][j]>last){
                    last=grid[i][j];
                }
            }
        }
        printf("Case %d: ",tc);
        bfs();
    }
    return 0;
}
