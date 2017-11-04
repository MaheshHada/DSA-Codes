#include <iostream>
#include <queue>
#include <vector>
#include <utility>
using namespace std;


typedef pair<int,int> pii;

struct Node {
	int data;
	Node *next;
	Node(int key) {
		data = key;
		next = NULL;
	}
};

int main() {
	freopen("input.txt","r",stdin);
	int n;
	cin>>n;
	vector<deque<int> > v(n); 
	for(int i=0;i<n;i++) {
		int x,y;
		cin>>x;
		for(int j=0;j<x;j++) {
			cin>>y;
			v[i].push_back(y);
		}
	}
	Node *temp = NULL;
	Node *reff = NULL;
	priority_queue<pii,vector<pii>,greater<pii> > pq;
	for(int i=0;i<n;i++) {
		pq.push(make_pair(v[i].front(),i));
		v[i].pop_front();
	}
	bool flag = false;
	while(!pq.empty()) {
		pii px = pq.top();
		pq.pop();
		int val = px.first;
		int arr_idx = px.second;
		if(!temp) {
			temp = (Node*)malloc(sizeof(Node));
			temp->data = val;
			temp->next = NULL;
			reff = temp;
		}else {
			reff->next = (Node*)malloc(sizeof(Node));
			reff->next->data = val;
			reff->next->next = NULL;
			reff = reff->next;
		}
		if(!v[arr_idx].empty()) {
			pq.push(make_pair(v[arr_idx].front(),arr_idx));
			v[arr_idx].pop_front();
		}
	}
	Node *temp2 = temp;
	while(temp2 != NULL) {
		cout<<temp2->data<<endl;
		temp2 = temp2->next;
	}
	return 0;
}