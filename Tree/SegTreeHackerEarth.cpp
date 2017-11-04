#include <iostream>
using namespace std;

struct Node {
	int ceven,codd;
	Node() {
		ceven = 0;
		codd = 0;
	}
};

int N;
Node tree[112345];
long long a[112345];

void buildUtil(int node,int l,int r) {
	if(l == r) {
		if(a[l] %2 == 0)
			tree[node].ceven = 1;
		else
			tree[node].codd = 1;
	}
	else {
		int mid = (l+r)/2;
		buildUtil(2*node,l,mid);
		buildUtil(2*node+1,mid+1,r);
		tree[node].ceven = tree[2*node].ceven + tree[2*node+1].ceven;
		tree[node].codd = tree[2*node].codd + tree[2*node+1].codd;
	}
}

void buildSegTree() {
	buildUtil(1,0,N-1);
}

void updateUtil(int node,int l,int r,int idx,long long val) {
	if(l == r) {
		long long p = a[idx];
		// cout<<"********"<<p<<endl;
		a[idx] = val;
		// cout<<"++++++++"<<a[idx]<<endl;
		if(p%2 == 0) {
			if(val%2 != 0) {
				tree[node].ceven--;
				tree[node].codd++;
			} 
		}else {
			if(val%2 == 0) {
				tree[node].ceven++;
				tree[node].codd--;
			}
		}
	}
	else {
		int mid = (l+r)/2;
		if(idx >= l && idx <= mid) {
			updateUtil(2*node,l,mid,idx,val);
		}
		else {
			updateUtil(2*node+1,mid+1,r,idx,val);
		}
		tree[node].ceven = tree[2*node].ceven + tree[2*node+1].ceven;
		tree[node].codd = tree[2*node].codd + tree[2*node+1].codd;
	}
}

void updateSegTree(int idx,long long val) {
	updateUtil(1,0,N-1,idx-1,val);
}

int query1(int node,int start,int end,int l,int r) {
	if(r < start || l > end) {
		return 0;
	}
	if(l <= start && end <= r) {
		return tree[node].codd;
	}
	int mid = (start+end)/2;
	int p1 = query1(2*node,start,mid,l,r);
	int p2 = query1(2*node+1,mid+1,end,l,r);
	return (p1+p2);
}

int query0(int node,int start,int end,int l,int r) {
	if(r < start || l > end) {
		return 0;
	}
	if(l <= start && end <= r) {
		return tree[node].ceven;
	}
	int mid = (start+end)/2;
	int p1 = query0(2*node,start,mid,l,r);
	int p2 = query0(2*node+1,mid+1,end,l,r);
	return (p1+p2);
}

void printSegTree() {
	for(int i=1;i<2*N+2;i++) {
		cout<<"tree["<<i<<"]="<<tree[i].codd<<","<<tree[i].ceven<<" ;";
	}
	cout<<endl;
}

int main() {
	freopen("input.txt","r",stdin);
	cin>>N;
	for(int i=0;i<N;i++) {
		cin>>a[i];
	}
	buildSegTree();
	printSegTree();
	// cout<<endl<<endl;
	// updateSegTree(0,6);
	// cout<<query(1,0,N-1,3,4);
	// printSegTree();
	int q;
	cin>>q;
	while(q--) {
		int x,y;
		long long z;
		cin>>x>>y>>z;
		switch(x) {
			case 0: updateSegTree(y,z);
					printSegTree();
					break;
			case 1: cout<<query0(1,0,N-1,y,z)<<endl;
					break;
			case 2: cout<<query1(1,0,N-1,y,z)<<endl;
					break;
		}
	}
	return 0;
}