#include <bits/stdc++.h>
using namespace std;

void insertionSort(int a[],int n) {
	int temp;
	for(int i=1;i<n;i++) {
		temp = a[i];
		for(int j=i-1;j>=0;j--) {
			if(a[j] > temp) {
				a[j+1] = a[j];
				a[j] = temp;
			}
		}
	}
}

int main() {
	int a[] = {13,47,74,12,89,74,18,38};
	int n = 8;
	insertionSort(a,n);
	for(int i=0;i<n;i++) {
		cout<<a[i]<<" ";
	}
	return 0;
}