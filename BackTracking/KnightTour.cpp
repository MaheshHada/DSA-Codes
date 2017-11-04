#include <iostream>
#include <vector>
#include <utility>
#include <cstring>
#include <functional>
using namespace std;

typedef pair<int,int> pii;
#define N 8
#define f first
#define s second

vector<pii> dir = {{1,2},{1,-2},{-2,1},{-2,-1},{2,1},{2,-1},{-1,2},{-1,-2}};

void printSol(int sol[N][N]) {
	for(int i=0;i<N;i++) {
		for(int j=0;j<N;j++) {
			cout<<sol[i][j]<<" ";
		}
		cout<<endl;
	}
}

bool SolveKnight(int sol[N][N],int x,int y,int moves) {
	if(moves == 62) {
		return true;
	}
	for(int i=0;i<8;i++) {
		int vx = x + dir[i].f;
		int vy = y + dir[i].s;
		if(vx >= 0 && vy >= 0 && vx < N && vy < N && sol[vx][vy] == -1) {
			sol[vx][vy] = moves;
			if(SolveKnight(sol,vx,vy,moves+1) == true) {
				return true;
			}
			sol[x][y]= -1;
		}
	}
	return false;
}

int main() {
	int sol[N][N];
	memset(sol,-1,sizeof(sol[0][0])*N*N);
	sol[0][0] = 0;
	// printSol(sol);
	sol[0][0] = 0;
	SolveKnight(sol,0,0,0);
	printSol(sol);
	return 0;
}