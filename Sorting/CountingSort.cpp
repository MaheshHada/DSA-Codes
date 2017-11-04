#include <iostream>
#include <cstring>
using namespace std;

int main() {
	int arr[] = {1,2,4,2,7,5,6,6,8,4};
	int n = 10;
	int count[10];
	memset(count,0,sizeof(count));
	//hashing
	for(int i=0;i<10;i++) {
		count[arr[i]]++;
	}
	//converting to the cumulative count array
	int output[10];
	for(int i=1;i<10;i++) {
			count[i] += count[i-1];
	}
	//assigning the output indexes the correct sorted elements
	for(int i=0;i<10;i++) {
		output[count[arr[i]]-1] = arr[i];
		count[arr[i]]--;
	}
	//printing answer
	for(int i=0;i<10;i++) {
		cout<<output[i]<<" ";
	}
	return 0;
}