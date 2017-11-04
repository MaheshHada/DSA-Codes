#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <climits>
#include <utility>
using namespace std;

#define MAX 501
#define f first
#define s second
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<int,int> ppi;
int graph[MAX][MAX];
ll dist[MAX][MAX];
bool visited[MAX][MAX];
int n,m;
vector<pii> dir = {{1,0},{0,1}};

int minDist(int x,int y,int w) {
	priority_queue<ppi,vector<ppi>,greater<ppi> > pq;
	pq.push(make_pair(w,make_pair(x,y)));
	while(!pq.empty()) {
		int x = pq.top().s.f;
		int y = pq.top().s.s;
		int d = pq.top().f;
		pq.pop();
		if(vx == n-1 && vy == m-1) {
			return d;
		}
		if(d <= 0) {
			return d;
		}
		if(visited[x][y])
			continue;
		visited[x][y] = true;
		for(int i=0;i<2;i++) {
			int vx = x + dir[i].f;
			int vy = y + dir[i].s;
			if(vx < n && vy < m && !visited[vx][vy] && dist[vx][vy] > dist[x][y] + arr[vx][vy]) {
				pq.push(make_pair(dist[vx][vy],make_pair(vx,vy)));
			}
		}
	}
	return 0;
}

int bindex(vector<int> val,int l,int r) {
	if(l < r) {
		int mid = (l+r)/2;
		if(val[mid] == INT_MAX) {
			int d = minDist(,);
		}
	}
}

int main() {
	for(int i=0;i<n;i++) {
		for(int j=0;j<m;j++) {
			cin>>arr[i][j];
			dist[i][j] = INT_MAX;
			visited[i][j] = false;
		}
	}
	for(int )
	for(int i=0;i<n;i++) {
		for(int j=0;j<m;j++) {
			dist[i][j] = INT_MAX;
			visited[i][j] = false;
		}
	}
	return 0;
}