#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;
ll N;
vector<vector<pair<ll,ll> > > graph;

void djikstra(ll src) {
	priority_queue<pii,vector<pii>,greater<pii> > pq;
	vector<ll> dist(N,INT_MAX);
	pq.push(make_pair(0,src));
	dist[src] = 0;
	vector<bool> visited(N,false);
	while(!pq.empty()) {
		ll u = pq.top().second;
		pq.pop();
		if(visited[u])
			continue;
		visited[u] = true;
		for(ll i=0;i<graph[u].size();i++) {
			ll v = graph[u][i].first;
			ll w = graph[u][i].second;
			if(!visited[v] && dist[v] > dist[u] + w) {
				dist[v] = dist[u] + w;
				pq.push(make_pair(dist[v],v));
			}
		}
	}
	for(ll i=0;i<N;i++) {
		if(dist[i] == INT_MAX) {
			cout<<"-1"<<" ";
			continue;
		}
		else if(i == src)
			continue;
		else
			cout<<dist[i]<<" ";
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	freopen("input.txt","r",stdin);
	ll t;
	cin>>t;
	while(t--) {
		cin>>N;
		ll m;
		cin>>m;
		graph.resize(N);
		for(ll i=0;i<m;i++) {
			ll u,v,w;
			cin>>u>>v>>w;
			graph[u-1].push_back(make_pair(v-1,w));
			graph[v-1].push_back(make_pair(u-1,w));
		}
		ll x;
		cin>>x;
		djikstra(x-1);
		cout<<endl;
		graph.clear();
	}
	return 0;
}