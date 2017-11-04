#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <functional>
using namespace std;

#define MAX 50
#define f first
#define s second
typedef pair<int,int> pii;
typedef pair<int,pii> ppi;
int n,m;
bool visited[MAX][MAX];
vector<string> graph;

vector<pii> dir = {{-1,0},{0,-1},{0,1},{1,0}};

void bfs(int x,int y) {
	queue<pii> q;
	q.push(make_pair(x,y));
	while(!q.empty()) {
		auto p = q.front();
		q.pop();
		int ux = p.f;
		int uy = p.s;
		if(visited[ux][uy]) 
			continue;
		visited[ux][uy] =  true;
		for(int i=0;i<4;i++) {
			int vx = ux + dir[i].f;
			int vy = uy + dir[i].s;
			if(vx >= 0 && vy >=0 && vx < n && vy < m && !visited[vx][vy] && graph[vx][vy] == 'X') {
				q.push(make_pair(vx,vy));
			}
		}
	}
}

int traverse() {
	// bool visited[n][m];
	for(int i=0;i<n;i++) {
		for(int j=0;j<m;j++) {
			visited[i][j] = false;
		}
	}
	int count = 0;
	for(int i=0;i<n;i++) {
		for(int j=0;j<m;j++) {
			if(visited[i][j] == false && graph[i][j] == 'X') {
					bfs(i,j);
					count++;
			}
		}
	}
	return count;
}

int main() {
	freopen("input.txt","r",stdin);
	int t;
	cin>>t;
	while(t--) {
		cin>>n>>m;
		string x;
		for(int i=0;i<n;i++) {
			cin>>x;
			graph.push_back(x);
		}
		cout<<traverse()<<endl;
		graph.clear();
	}
	return 0;
}