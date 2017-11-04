#include <iostream>
#include <vector>
using namespace std;


void flodfill(vector<vector<int> > &arr,int n,int m,int x,int y,int prevC,int newC) {
	if(x < 0 || x >= m || y < 0 || y >= n)
		return;
	if(arr[x][y] != prevC)
		return;
	arr[x][y] = newC;
	flodfill(arr,n,m,x-1,y,prevC,newC);
	flodfill(arr,n,m,x+1,y,prevC,newC);
	flodfill(arr,n,m,x,y-1,prevC,newC);
	flodfill(arr,n,m,x,y+1,prevC,newC);
}

int main() {
	freopen("input.txt","r",stdin);
	int t;
	cin>>t;
	while(t--) {
		int n,m;
		cin>>n>>m;
		vector<vector<int> > arr(n);
		int in;
		for(int i=0;i<n;i++) {
			for(int j=0;j<m;j++) {
				cin>>in;
				arr[i].push_back(in);
			}
		}
		int x,y,K;
		cin>>x>>y>>K;
		flodfill(arr,n,n,x,y,arr[x][y],K);
		for(int i=0;i<n;i++) {
			for(int j=0;j<m;j++) {
				cout<<arr[i][j]<<" ";
			}
		}
		cout<<endl;
		arr.clear();
	}
	return 0;
}