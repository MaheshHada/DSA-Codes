#include <bits/stdc++.h>
using namespace std;

void RevStack(stack<int> &st) {
	if(!st.empty()) {
		int u = st.top();
		// cout<<u<<" ";
		st.pop();
		RevStack(st);
		cout<<u<<" ";
		st.push(u);
	} 
}

void inserAtBottom(stack<int> &st,int u) {
	if(st.empty()) {
		st.push(u);
	}
	else {
		int v = st.top();
		st.pop();
		inserAtBottom(st,u);
		st.push(v);
	}
}

//rverses the stack in place
void Reverse(stack<int> &st) {
	if(!st.empty()) {
		int u = st.top();
		st.pop();
		Reverse(st);
		inserAtBottom(st,u);
	}
}

int main() {
	cout<<"vsv"<<endl;
	//freopen("inpu.txt","r",stdin);
	stack<int> st;
	cout<<"vsv"<<endl;
	st.push(1);
	st.push(5);
	st.push(8);
	
	// RevStack(st);
	cout<<st.size()<<endl;
	Reverse(st);
	cout<<st.top();

	return 0;
}