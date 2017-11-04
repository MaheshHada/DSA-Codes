#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
#include <utility>
using namespace std;

#define f first
#define s second
typedef pair<int,int> pii;

vector<vector<int> > graph;
bool visited[10];

void printAllPathsUtil(int u,int dest,vector<int> &path,vector<vector<int> > &big) {
	visited[u] = true;
	path.push_back(u);
	if(u == dest){
		big.push_back(path);
	}
	else {
		for(int i=0;i<graph[u].size();i++) {
			int v = graph[u][i];
			if(!visited[v])
				printAllPathsUtil(v,dest,path,big);
		}
	}
	path.pop_back();
	visited[u] = false;
}

void printAllPaths(int src,int dest) {
	memset(visited,false,sizeof(visited));
	vector<int> path;
	vector<vector<int> > big;
	printAllPathsUtil(src,dest,path,big);
	for(int i=0;i<big.size();i++) {
		for(auto p : big[i])
			cout<<p<<" ";
		cout<<endl;
	}
	cout<<endl;
}

int countPathWithMedge(int src,int dest,int m) {
	queue<pii> q;
	q.push(make_pair(src,0));
	int count = 0;
	while(!q.empty()) {
		auto p = q.front();
		q.pop();
		int u = p.f;
		int d = p.s;
		if(d > m)
			break;
		if(u == dest && d == m)
			count++;
		for(int i=0;i<graph[u].size();i++) {
			int v = graph[u][i];
			q.push(make_pair(v,d+1));
		}
	}
	return count;
}

bool is_safe(int graph[MAX][MAX],vector<int> path,int v,int N) {
	if(graph[path.back()][v] != 1) {
		return false;
	}
	for(int i=0;i<path[i].size();i++) {
		if(path[i] == v) 
			return false;
	}
	return true;
}

bool hamCycle(int graph[MAX][MAX],vector<int> path,int u,int N) {
	if(is_safe(graph,path,u,N)) {
		path.push_back(u);
		if(hamCycle(graph,path,))
	}
}

int main() {
	freopen("input.txt","r",stdin);
	int V,e;
	cin>>V>>e;
	int u,v;
	graph.resize(V);
	for(int i=0;i<e;i++) {
		cin>>u>>v;
		graph[u].push_back(v);
	}
	int src,dest;
	cin>>src>>dest;
	int m;
	cin>>m;
	// printAllPaths(src,dest);
	cout<<countPathWithMedge(src,dest,m)<<endl;
	graph.clear();
	return 0;
}