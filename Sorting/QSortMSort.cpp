#include <bits/stdc++.h>
using namespace std;

int partition(int A[],int p,int r) {
	int x = A[r];
	int i = p-1;
	for(int j=p;j<r;j++) {
		if(A[j] <= x) {
			i++;
			int temp = A[j];
			A[j] = A[i];
			A[i] = temp;
		}
	}
	A[r] = A[i+1];
	A[i+1] = x;
	return i+1;
}

void QuickSort(int A[],int p,int r) {
	if(p < r) {
		int q = partition(A,p,r);
		QuickSort(A,p,q-1);
		QuickSort(A,q+1,r);
	}
}

void Merge(vector<int> A,int low,int mid,int high) {
	vector<int> l,r;
	vector<int> mer;-
	for(int p=low;p<=mid;p++) {
		l.push_back(A[p]);
	}
	for(int q=mid+1;q<=high;q++) {
		r.push_back(A[q]);
	}
	int i=0,j=0,k=0;
	while(i < l.size() && j < r.size()) {
		if(A[i] > A[j]) {
			mer[k] = A[j];
			j++;
		}
		else {
			mer[k] = A[i];
			i++;
		}
		k++;
	}
	while(i < l.size()) {
		mer[k++] = A[i++];
	}
	while(j < r.size()) {
		mer[k++] = A[j++];
	}
}

void MergeSort(vector<int> A,int low,int high) {
	int mid;
	if( low < high) {
		mid = (low+high)/2;
		MergeSort(A,low,mid);
		MergeSort(A,mid+1,high);
		Merge(A,low,mid,high);
	}
}


int main() {
	int a[] = {1,4,5,3,2,6,8,7};
	vector<int> aa;
	for(int i=0;i<8;i++) {
		aa.push_back(a[i]);
	}
	MergeSort(aa,0,7);
	for(int i=0;i<8;i++) {
		cout<<aa[i]<<" ";
	}
	return 0;
}