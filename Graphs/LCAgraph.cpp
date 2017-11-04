#include <bits/stdc++.h>
using namespace std;

//Zero indexing the vector array
vector<vector<int> > graph(112345);
bool visited[112345];

void dfs(int u,vector<int> &v1) {
	visited[u] = true;
	v1.push_back(u);
	for(int i=0;i<graph[u].size();i++) {
		int v = graph[u][i];
		if(!visited[v]) {
			dfs(v,v1);
		}
	}
}

int LCA(int u,int v) {
	vector<int> v1,v2;
	memset(visited,false,sizeof(visited));
	dfs(u,v1);
	memset(visited,false,sizeof(visited));
	dfs(v,v2);
	for(int i=0;i<v1.size();i++)
		cout<<v1[i]<<" ";
	cout<<endl;
	for(int i=0;i<v2.size();i++)
		cout<<v2[i]<<" ";
	cout<<endl;
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
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	memset(visited,false,sizeof(visited));
	LCA(3,4);
	return 0;
}