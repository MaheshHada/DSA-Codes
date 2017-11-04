o#include <iostream>
#include <cstdio>
using namespace std;

template <class T> class Deque {
	class Node {
	public:
		T data;
		Node *next;
		Node *prev;
		Node() {
			this->data = NULL;
			next = NULL;
			prev = NULL;
		}
		Node(T dat) {
			this->data = dat;
			this->next = NULL;
			this->prev = NULL;
		}
	};
	Node *head;
	Node *tail;
	int siz;
public:
	Deque() {
		head = NULL;
		tail = NULL;
		siz = 0;
	} 
	Deque(T dat1) {
		Node *newNode = new Node(dat1);
		head = newNode;
		tail = newNode;
		siz = 1;
	}
	~Deque() { //destructor
		Node *n = head;
		while(n != NULL) {
			Node *temp = n;
			n = n->next;
			delete temp;
		}
		siz = 0;
	}
	void enqueue(T dat1) {
		Node *n = new Node(dat1);
		if(siz == 0) {
			head = tail = n;
			siz++;
			return ;
		}
		head->prev = n;
		n->next = head;
		siz++;
		head = n;
	}
	void dequeue() {
		if(siz == 0){
			cout<<"Deque Empty"<<endl;
			return;
		}
		if(siz == 1) 
		{
			head = NULL;
			tail = NULL;
			siz=0;
		}
		else
		{
			tail = tail->prev;
			tail->next = NULL;
			siz--;
		}
	}
	int size() {
		return siz;
	}
	void print(){
		Node *n = head;
		cout<<"Print the Deque: ";
		while(n != NULL) {
			cout<<n->data<<" ";
			n = n->next;
		}
		cout << endl;
	}
};

int main() {
	Deque<char> *q = new Deque<char>();
	q->enqueue('q');
	q->enqueue('a');
	q->print();
	q->dequeue();
	q->print();
	q->dequeue();
	q->print();
	q->dequeue();
	delete q;
	return 0;
}
