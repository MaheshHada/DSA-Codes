#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <functional>
#include <climits>
#include <cstring>
using namespace std;

#define f first
#define s second
#define MAX 10
typedef pair<int,int> pii;
vector<pii> graph[10];

void MST(int n) {
	bool visited[10];
	int dist[10];
	int parent [10];
	// memset(visited,false,sizeof(visited));
	// memset(dist,INT_MAX,sizeof(dist));
	// memset(parent,-1,sizeof(parent));
	for(int i=0;i<n;i++) {
		parent[i] = -1;
		visited[i] = false;
		dist[i] = INT_MAX;
	}
	dist[0] = 0;
	priority_queue<pii,vector<pii>,greater<pii> > pq;
	pq.push(make_pair(dist[0],0));
	while(!pq.empty()) {
		pii p = pq.top();
		pq.pop();
		int u = p.s;
		if(visited[u])
			continue;
		visited[u] = true;
		for(int i=0;i<graph[u].size();i++) {
			int v = graph[u][i].f;
			int w = graph[u][i].s;
			if(!visited[v] && dist[v] > dist[u] + w) {
				dist[v] = dist[u] + w;
				parent[v] = u;
				pq.push(make_pair(dist[v],v));
			}
		}
	}
	for(int i=1;i<n;i++) {
		cout<<parent[i]<<"-->"<<i<<" "<<dist[i]<<endl;
	}
}

int main() {
	freopen("input.txt","r",stdin);
	int n,e;
	cin>>n>>e;
	int u,v,w;
	for(int i=0;i<e;i++) {
		cin>>u>>v>>w;
		graph[u].push_back(make_pair(v,w));
		graph[v].push_back(make_pair(u,w));
	}
	for(int i=0;i<n;i++) {
		cout<<i<<":";
		for(int j=0;j<graph[i].size();j++) {
			cout<<"("<<graph[i][j].f<<" "<<graph[i][j].s<<") ";
		}
		cout<<endl;
	}
	MST(n);
	return 0;
}

