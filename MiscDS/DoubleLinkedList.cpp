#include <iostream>
using namespace std;

struct DoubleNode {
	int data;
	DoubleNode *next,*previous;
	DoubleNode(int data) {
		this->data = data;
		next = previous = NULL;
	}
};

DoubleNode* insertDouble(DoubleNode* head,int data) {
	if(head == NULL) {
		return new DoubleNode(data);
	}
	DoubleNode* curr = head;
	while(curr->next != NULL) {
		curr = curr->next;
	}
	DoubleNode* newNode = new DoubleNode(data);
	curr->next = newNode;
	newNode->previous = curr;
	return head;
}

DoubleNode *deleteDouble(DoubleNode *head,int data) {
	if(head == NULL)
		return NULL;
	DoubleNode *curr = head;
	if(head->data == data) {
		head = head->next;
		head->previous = NULL;
		delete(curr);
		return head;
	}
	while(curr != NULL && curr->data!=data) {
		curr = curr->next;
	}
	if(curr == NULL)
		return NULL;
	DoubleNode *pls = curr->next;
	if(pls != NULL) {
		curr->previous->next  = pls;
		pls->previous = curr->previous;
		delete(curr);
		return head;
	}
	curr->previous->next = NULL;
	delete(curr);
	return head;
}

void printDouble(DoubleNode* head) {
	if(head == NULL) {
		cout<<"List is empty!"<<endl;
		return;
	}
	DoubleNode* curr = head;
	while(curr != NULL) {
		cout<<curr->data<<"-->";
		curr = curr->next;
	}
	cout<<"NULL"<<endl;
}


int main() {
	freopen("input.txt","r",stdin);
	int n,x;
	cin>>n;
	DoubleNode* head = NULL;
	for(int i=0;i<n;i++) {
		cin>>x;
		head = insertDouble(head,x);
	}
	DoubleNode* rhead = deleteDouble(head,5);
	if(rhead != NULL)
		head = rhead;
	// cout<<head->data<<endl;
	printDouble(head);
	return 0;
}
