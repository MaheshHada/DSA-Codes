#include <iostream>
using namespace std;

#define MAX  20
int G[MAX][MAX];
int N;

//finds the shortest path between all pairs of vertices

void floydwarshall() {
	for(int k=0;k<N;k++) {
		for(int i=0;i<N;i++) {
			for(int j=0;j<N;j++) {
				if(G[i][k] + G[k][j] < G[i][j]) {
					G[i][j] = G[i][k] + G[k][j];
				}
			}
		}
	}
} 

int main() {
	freopen("input.txt","r",stdin);
	int t;
	cin>>t;
	while(t--) {
		cin>>N;
		for(int i=0;i<N;i++) {
			for(int j=0;j<N;j++) {
				cin>>G[i][j];
			}
		}
		floydwarshall();
		for(int i=0;i<N;i++) {
			for(int j=0;j<N;j++) {
				cout<<G[i][j]<<" ";
			}
		}
		cout<<endl;
	}
	return 0;
}