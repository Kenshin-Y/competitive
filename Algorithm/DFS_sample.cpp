/*
 ICPC
 maze[nx][ny]=0;
 dfs(n+1,nx-dx[i],ny-dy[i]);
 maze[nx][ny]=1;
 が本質
 */

void dfs(int n,int x,int y){
    if(n>=ans) return;
    rep(i,4){
        int nx=x+dx[i],ny=y+dy[i];
        if(nx<0||h<=nx||ny<0||w<=ny) continue;
        if(maze[nx][ny]==1) continue;
        for(;;){
            if(maze[nx][ny]==3){
                chmin(ans,n);
                return;
            }
            nx+=dx[i]; ny+=dy[i];
            if(nx<0||h<=nx||ny<0||w<=ny) break;
            if(maze[nx][ny]==1){
                maze[nx][ny]=0;
                dfs(n+1,nx-dx[i],ny-dy[i]);
                maze[nx][ny]=1;
                break;
            }
        }
    }
}
