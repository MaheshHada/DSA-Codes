#include <iostream>
#include <vector>
#include <map>
using namespace std;

vector<vector<int> > v;
vector<vector<bool> > visited;
int n;
typedef pair<int,int> pii;

map<char,pii> dmap = {{'D',{1,0}},{'L',{0,-1}},{'R',{0,1}},{'U',{-1,0}}};

void dfs(int x,int y,string path,vector<string> &big,char c) {
	visited[x][y] = true;
	path.push_back(c);
	if(x == n-1 && y == n-1) {
		big.push_back(path.substr(1));
		path.pop_back();
		visited[x][y] = false;
		return;
	}
	for(auto &p : dmap) {
		char c = p.first;
		int xx = x + p.second.first;
		int yy = y + p.second.second;
		if(xx >= 0 && yy >= 0 && xx < n && yy < n && v[xx][yy] && !visited[xx][yy]) {
			dfs(xx,yy,path,big,c);
		}
	}
	visited[x][y] = false;
	path.pop_back();
}

int main() {
	freopen("input.txt","r",stdin);
	int t;
	cin>>t;
	while(t--) {
		cin>>n;
		v.clear();
		v.resize(n);
		int x;
		visited.clear();
		visited.resize(n);
		for(int i=0;i<n;i++) {
			for(int j=0;j<n;j++) {
				cin>>x;
				v[i].push_back(x);
				visited[i].push_back(false);
			}
		}
		vector<string> big;
		string path;
		dfs(0,0,path,big,'\0');
		for(auto p : big) {
			cout<<p<<" ";
		}
		cout<<endl;
		big.clear();
	}
	return 0;
}