#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <functional>
using namespace std;

#define f first
#define s second
typedef pair<int,int> pii;
typedef pair<int,pii> ppi;


int find(pii subsets[],int i) {
	if(subsets[i].f != i) 
		return find(subsets,subsets[i].f);
	return subsets[i].f;
}

void Union(pii subsets[],int x,int y) {
	int xroot = find(subsets,x);
	int yroot = find(subsets,y);
	if(subsets[xroot].s > subsets[yroot].s) {
		subsets[yroot].f = xroot;
	}else if(subsets[xroot].s < subsets[yroot].s){
		subsets[xroot].f = yroot;
	}else {
		subsets[yroot].f = xroot;
		subsets[xroot].s++;
	}
}

int main() {
	freopen("input.txt","r",stdin);
	int t;
	cin>>t;
	while(t--) {
		int n,e;
		cin>>n>>e;
		int u,v,w;
		priority_queue<ppi,vector<ppi>,greater<ppi> > edg; 
		for(int i=0;i<e;i++) {
			cin>>u>>v>>w;
			u--;v--;
			edg.push(make_pair(w,make_pair(u,v)));
		}
		pii subsets[n];
		for(int i=0;i<n;i++) {
			subsets[i].f = i;
			subsets[i].s = 0;
		}
		int in = 0;
		int ans = 0;
		// vector<pii> res;
		while(in < n) {
			if(!edg.empty()) {
				auto p = edg.top();
				edg.pop();
				int x = p.s.f;
				int y = p.s.s;
				int w = p.f;
				if(find(subsets,x) != find(subsets,y)) {
					Union(subsets,x,y);
					// res.push_back(make_pair(x,y));
					ans += w;
					in++;
				}
			}
			else {
				break;
			}
		}
		// for(int i=0;i<res.size();i++) {
		// 	cout<<res[i].f<<"-->"<<res[i].s<<endl;
		// }
		// edg.clear();
		// res.clear();
		while(!edg.empty()) {
			edg.pop();
		}
		cout<<ans<<endl;
	}
	return 0;
}