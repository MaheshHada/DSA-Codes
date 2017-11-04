#include <iostream>
#include <queue>
#include <climits>
#include <utility>
#include <functional>
using namespace std;

#define f first
#define s second
typedef pair<int,int> pii;
typedef pair<int,pii> ppi;

vector<vector<int> > v;
vector<vector<bool> > visited;
vector<vector<int> > dist;
vector<pii> dir = {{-1,0},{1,0},{0,1},{0,-1}};

void ans(int n) {
	priority_queue<ppi,vector<ppi>,greater<ppi> > pq;
	dist[0][0] = v[0][0];
	pq.push(make_pair(v[0][0],make_pair(0,0)));
	while(!pq.empty()) {
		auto p = pq.top();
		pq.pop();
		int ux = p.s.f;
		int uy = p.s.s;
		int vx = ux;
		int vy = uy;
		visited[ux][uy] = true;
		for(int i=0;i<4;i++) {
			vx = ux + dir[i].f;
			vy = uy + dir[i].s;
			if(vx < 0 || vy < 0 || vx >= n || vy >= n)
				continue;
			if(!visited[vx][vy] && (dist[vx][vy] > (dist[ux][uy] + v[vx][vy]))) {
				dist[vx][vy] = dist[ux][uy] + v[vx][vy];
				pq.push(make_pair(dist[vx][vy],make_pair(vx,vy)));
			}
		}
	}
}

int main() {
	freopen("input.txt","r",stdin);
	int t;
	cin>>t;
	while(t--) {
		int n;
		cin>>n;
		v.resize(n);
		visited.resize(n);
		dist.resize(n);
		int x;
		for(int i=0;i<n;i++) {
			for(int j=0;j<n;j++) {
				cin>>x;
				v[i].push_back(x);
				visited[i].push_back(false);
				dist[i].push_back(INT_MAX);
			}
		}
		ans(n);
		// for(int i=0;i<n;i++) {
		// 	for(int j=0;j<n;j++) {
		// 		cout<<dist[i][j]<<" ";
		// 	}
		// }
		cout<<dist[n-1][n-1]<<endl;
		v.clear();
		visited.clear();
		dist.clear();
	}
	return 0;
}