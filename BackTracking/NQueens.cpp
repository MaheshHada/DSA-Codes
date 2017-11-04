//printing all the n queens possible solutions for n*n
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define MAX 10
int N;

bool isSafeBoard(int board[MAX][MAX],int row,int col) {
	for(int i=0;i<col;i++) {
		if(board[row][i] == 1)
			return false;
	}
	for(int i=row,j=col;i>=0 && j>=0;i--,j--) {
		if(board[i][j] == 1)
			return false;
	}
	for(int i=row,j=col;i<N && j >=0;i++,j--) {
		if(board[i][j] == 1)
			return false;
	}
	return true;
}

void findSol(int board[MAX][MAX],vector<vector<int> > &ans) {
	vector<int> v;
	for(int j=0;j<N;j++) {
		for(int i=0;i<N;i++) {
			if(board[j][i] == 1) {
				v.push_back(i+1);
    			break;
		   	}
	 	}
	}
	ans.push_back(v);
}

void printSol(vector<vector<int> > ans) {
	sort(ans.begin(),ans.end());
	for(int i=0;i<ans.size();i++) {
		cout<<"[";
		for(int j=0;j<N;j++) {
			cout<<ans[i][j]<<" ";
		}
		cout<<"] ";
	}
	cout<<endl;
}

void solveNQueenUtil(int board[MAX][MAX],int col,vector<vector<int> > &ans) {
	if(col == N) {
		findSol(board,ans);
	}
	for(int i=0;i<N;i++) {
		if(isSafeBoard(board,i,col)) {
			board[i][col] = 1;
			solveNQueenUtil(board,col+1,ans);
			board[i][col] = 0;
		}
	}
}

int main() {
	freopen("input.txt","r",stdin);
	int t;
	cin>>t;
	while(t--) {
	    cin>>N;
	    int board[MAX][MAX];
	    for(int i=0;i<N;i++) {
	    	for(int j=0;j<N;j++) {
	    		board[i][j] = 0;
	    	}
	    }
	    vector<vector<int> > ans;
	    solveNQueenUtil(board,0,ans);
		printSol(ans);
	}
	return 0;
}