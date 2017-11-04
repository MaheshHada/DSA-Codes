#include <iostream>
#include <queue>
#include <vector>
#include <functional>
using namespace std;

int left(int i,int n) {
    if(2*i + 1 < n) {
        return 2*i+1;
    }
    return -1;
}
int right(int i,int n) {
    if(2*i+2 < n)
        return 2*i+2;
    return -1;
}
void swap(int *a,int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
void heapify(int arr[], int n, int i)  {
    int l = left(i,n);
    int r = right(i,n);
    int largest = i;
    if(l != -1 && arr[largest] < arr[l])
        largest = l;
    if(r != -1 && arr[largest] < arr[r])
        largest = r;
    if(largest != i) {
        swap(arr[largest],arr[i]);
        heapify(arr,n,largest);
    }
}
void buildHeap(int arr[], int n)  { 
    for(int i=(n-1)/2;i>=0;i++) {
        heapify(arr,n,i);
    }
}


int main() {
	freopen("input.txt","r",stdin);
	int n;
	cin>>n;
	priority_queue<int> q1;
	priority_queue<int,vector<int>,greater<int> > q2;
	int x;
	cin>>x;
	q1.push(x);
	cout<<x<<endl;
	for(int i=1;i<n;i++) {
	    cin>>x;
	    if(!q1.empty() && q1.top() >= x)
	        q1.push(x);
	    else
	        q2.push(x);
	   int d = q1.size() - q2.size();
	   if(abs(d) > 1) {
	       if(d == -2) {
	           q1.push(q2.top());
	           q2.pop();
	       }else{
	           q2.push(q1.top());
	           q1.pop();
	       }
	   }
	   int ds = q1.size() - q2.size();
	   if(ds == 0) {
	       cout<<(q1.top()+q2.top())/2<<endl;
	   }
	   else if(ds == 1) {
	       cout<<q1.top()<<endl;
	   }
	   else {
	        cout<<q2.top()<<endl;    
	   }
	}
	return 0;
}