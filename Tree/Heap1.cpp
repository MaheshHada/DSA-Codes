#include <bits/stdc++.h>
using namespace std;


struct Heap {
	int *array;
	int count;
	int capacity;
	Heap() {
		array = NULL;
		capacity = count = 0;
	}
};

Heap* CreateHeap(int capacity) {
	// struct Heap* h = (Heap*)malloc(sizeof(struct Heap));
	Heap *h = new Heap();
	if(h == NULL) {
		cout<<"Memory Error"<<endl;
		return NULL;
	}
	h->capacity = capacity;
	h->count = 0;
	h->array = (int*)malloc(sizeof(int)*h->capacity);
	// h->array = new int[capacity];
	// cout<<"height " <<sizeof(h->array) / sizeof(h->array[0])<<endl;
	if(h->array == NULL) {
		cout<<"Memory Error";
		return NULL;
	}
	return h;
}

int Parent(struct Heap *h,int i)  {
	if(i<=0 || i>=h->count)
		return -1;
	return (i-1)/2;
}

int LeftChild(struct Heap *h,int i) {
	int left = 2*i+1;
	if(left<0 || left>=h->count)
		return -1;
	return left;
}

int RightChild(struct Heap *h,int i) {
	int right = 2*i+2;
	if(right<0 || right>=h->count) 
		return -1;
	return right;
}

void Heapify(struct Heap* h,int i) {
	int l,r,max1,temp;
	l = LeftChild(h,i);
	r = RightChild(h,i);
	if(l != -1 && h->array[l] > h->array[i])
		max1 = l;
	else
		max1 = i;
	if(r != -1 && h->array[r] > h->array[max1])
		max1 = r;
	if(max1 != i) {
		temp = h->array[max1];
		h->array[max1] = h->array[i];
		h->array[i] = temp;
		Heapify(h,max1);
	}
	// cout<<max1<<endl;
}

int ExtractMax(struct Heap *h) {
	if(h->count == 0)
		return -1;
	int data = h->array[0];
	h->array[0] = h->array[h->count-1];
	h->count = h->count -1;
	Heapify(h,0);
	return data;
}

void ResizeHeap(struct Heap *h) {
	int *array_old = h->array;
	h->array = (int*)malloc(sizeof(int)*h->capacity*2);
	if(h->array == NULL) {
		cout<<"Memory Error";
		return;
	}
	for(int i=0;i<h->capacity;i++) {
		h->array[i] = array_old[i];
	}
	h->capacity *= 2;
	free(array_old);
}

void InsertHeap(struct Heap *h,int key) {
	if(h->count == h->capacity) {
		ResizeHeap(h);
	}
	h->count++;
	int i = h->count-1;
	while(i>=0 && key > h->array[(i-1)/2]) {
		h->array[i] = h->array[(i-1)/2];
		i = (i-1)/2;
	}
	h->array[i] = key;
}

void DestroyHeap(struct Heap *h) {
	if(h == NULL)
		return;
	free(h->array);
	free(h);
	h = NULL;
}

void BuildHeap(struct Heap *h,int A[] ,int n) {
	if(h == NULL)
		return;
	// cout<<h->capacity<<endl;
	while(n > h->capacity)
		ResizeHeap(h);
	for(int i=0;i<n;i++) {
		h->array[i] = A[i];
	}
	// for(int i=0;i<n;i++)
	// 	cout<<h->array[i]<<" ";
	h->count = n;
	for(int i=(n-1)/2;i>=0;i--)
		Heapify(h,i);
}

void HeapSort(int A[],int n) {
	struct  Heap *h = CreateHeap(n);
	BuildHeap(h,A,n);
	int temp,old_size = n;
	for(int i=n-1;i>0;i--) {
		temp = h->array[i];
		h->array[i] = h->array[0];
		h->array[0] = temp;
		h->count--;
		Heapify(h,0);
	}
	h->count = old_size;
	// for(int i=n-1;i>=0;i--) {
	// 	A[i] = ExtractMax(h);
	// }
	for(int i=0;i<n;i++)
		cout<<A[i]<<" ";
	cout<<endl;
}

void PrintHeap(struct Heap *h) {
	cout<<"count "<<h->count<<endl;
	for(int i=0;i<h->count;i++)
		cout<<h->array[i]<<" ";
	cout<<endl;
}

void PrintGthanK(Heap *h,int k) {
	if(h->count == 0)
		return;
	if( > k) {
		cout<<root->data;
		PrintGthanK(root->left,k);
		PrintGthanK(root->right,k);
	}else {
		return;
	}
}

int main() {
	struct Heap *h = CreateHeap(5);
	// cout<<h->capacity<<endl;
	int A[] = {31,10,36,1,8};
	BuildHeap(h,A,5);
	// for(int i=0;i<h->count;i++)
	// 	cout<<h->array[i]<<" ";
	PrintHeap(h);
	// cout<<h->array[0];
	// HeapSort(A,5);
	PrintGthanK(h,7);
	return 0;
}