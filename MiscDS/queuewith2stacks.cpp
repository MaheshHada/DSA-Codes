#include<bits/stdc++.h>
using namespace std;

class QueueusingStacks {
	stack<int> inputstack;
	stack<int> outputstack;
	private: int size = 0;
	public:
		void enqueue(int i) {
			inputstack.push(i);
			size++;
		}
		int dequeue() {
			if(outputstack.empty()) {
				while(!inputstack.empty()) {
					outputstack.push(inputstack.top());
					inputstack.pop();
				}
			}
			int t=0;
			if(!outputstack.empty()) {
				t = outputstack.top();
				outputstack.pop();
				size--;
			}
			return t;
		}

		bool empty() {
			return size == 0;
		}
};

int main() {
	 QueueusingStacks q;
	 for(int i=1;i<=3;i++)
	 	q.enqueue(i);
	 cout<<q.dequeue()<<" ";
	 cout<<q.dequeue()<<" ";
	 cout<<q.dequeue()<<" ";
	 q.enqueue(4);
	 cout<<q.dequeue()<<" ";
}