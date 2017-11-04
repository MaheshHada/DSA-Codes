#include <bits/stdc++.h>
using namespace std;

vector<int> graph[112345];

void dfs(int u,vector<int> &dist,vector<bool> &visited) {
	if(visited[u])
		return;
	visited[u] = true;
	for(int i=0;i<graph[u].size();i++)  {
		int v = graph[u][i];
		if(visited[v])
			continue;
		dist[v]  = dist[u] + 1;
		dfs(v,dist,visited);
	}
}

void bfs(vector<int> &dist,vector<bool> &visited,queue<int> &q) {
	if(!q.empty()) {
		int u = q.front();
		q.pop();
		if(visited[u])
			return bfs(dist,visited,q);
		visited[u] = true;
		for(int i=0;i<graph[u].size();i++) {
			int v = graph[u][i];
			if(visited[v])
				return bfs(dist,visited,q);
			dist[v] = dist[u] + 1;
			q.push(v);
		}
		return bfs(dist,visited,q);
	}
}

int main() {
	freopen("input.txt","r",stdin);
	int n;
	cin>>n;
	int m;
	cin>>m;
	int u,v;
	for(int i=0;i<m;i++) {
		cin>>u>>v;
		u--;
		v--;
		graph[u].push_back(v);
	}
	vector<int> dist(n,0);
	vector<bool> visited(n,false);
	// dfs(0,dist,visited);
	queue<int> q;
	q.push(0);
	bfs(dist,visited,q);
	for(auto i : dist) {
		cout<<i<<endl;
	}
	return 0;
}

