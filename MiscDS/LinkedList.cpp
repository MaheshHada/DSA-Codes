// #include <bits/stdc++.h>
#include <bits/stdc++.h>
using namespace std;


struct Node {
	int data;
	Node *next;
	Node(int data) {
		this->data = data;
		next = NULL;
	}
};



Node* insert(Node *head,int data) {
	if(head == NULL) 
		return new Node(data);
	Node* curr = head;
	while(curr->next != NULL) {
		curr = curr->next;
	}
	curr->next = new Node(data);
	return head;
}

Node* deleteNode(Node *head,int data) {
	if(head == NULL)
		return NULL;
	Node *curr = head;
	if(head->data == data) {
		head = head->next;
		return head;
	}
	while(curr->next != NULL && curr->next->data != data) {
		curr = curr->next;
	}
	if(curr->next == NULL)
		return NULL;
	if(curr->next->next == NULL) {
		delete(curr->next);
		curr->next = NULL;
		return head;
	}
	else {
		Node *pls = curr->next->next;
		delete(curr->next);
		curr->next  = pls;
		return head;
	}
}

void print(Node* head) {
	if(head == NULL) {
		cout<<"List is Null"<<endl;
		return;
	}
	Node* curr = head;
	while(curr != NULL) {
		cout<<curr->data<<"-->";
		curr = curr->next;
	}
	cout<<"NULL"<<endl;
}

void Reverse(Node **head) {
	if(*head == NULL)
		return;
	Node *next,*prev = NULL,*current = *head;
	while(current != NULL) {
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	*head = prev;
}
Node* RecursiveRverse(Node **head) {
	Node *first,*rest;
	if(*head == NULL)
		return NULL;
	first = *head;
	rest = (*head)->next;
	if(rest == NULL)
		return NULL;
	RecursiveRverse(&rest);
	first->next->next = first;
	first->next = NULL;
	*head = rest;
}

void SingleToCircular(Node **head) {
	if(head == NULL)
		return;
	Node *curr = *head;
	if(curr->next == NULL)
		return;
	Node *first = *head;
	while(curr->next != NULL) {
		curr = curr->next;
	}
	curr->next = first;
}

void TraverseCircular(Node **head) {
	if(head == NULL)
		return;
	Node *first = *head;
	Node *curr = *head;
	if(curr->next == NULL) {
		cout<<curr->data<<endl;
		return;
	}
	do {
		cout<<curr->data<<"--->";
		curr = curr->next;
	}while(curr != first);
	cout<<curr->data<<"--->continues"<<endl;
}

// void deleteList(Node **head) {
// 	if(*head == NULL)
// 		return;
// 	Node *head;
// 	while(curr != NULL) {
// 		next = curr->next;
// 		free(curr);
// 	}
// }

Node* ReverseK(Node *head,int k,int n) {
	Node *curr = head,*prev = NULL,*next;
	stack<Node*> s;
	int count = 0;
	for(int i=0;i<n/k;i++) {
		count = 0;
		if(curr == NULL)
			break;
		if(curr->next == NULL) {
			s.push(curr);
			break;
		}
		while(curr != NULL && count < k) {
			next = curr->next;
			curr->next = prev;
			prev = curr;
			curr = next;
			count++;
		}
		if(curr == NULL)
			break;
		s.push(curr);
		cout<<curr->data<<endl;
		curr = curr->next;
	}
	if(n%k != 0) {
		if(curr != NULL)
			if(curr->next == NULL) {
				s.push(curr);
		}
		else 
		{
			while(curr != NULL) {
				next = curr->next;
				curr->next = prev;
				prev = curr;
				curr = next;
			}
			if(curr == NULL)
				s.push(prev);
		}
	}
	Node *temp;
	if(!s.empty()) {
		head = s.top();
	}
	while(!s.empty()) {
		temp = s.top();
		s.pop();
		temp->next->next = temp;
	}
	return head;
}


int getCount(Node *head) {
	if(head == NULL)
		return 0;
	return 1 + getCount(head->next);
}

bool isPallindromeStack(Node *head) {
	Node *curr = head;
	stack<Node*> s;
	if(curr == NULL)
		return false;
	if(curr->next == NULL)
		return true;
	while(curr != NULL) {
		s.push(curr);
		curr = curr->next;
	}
	Node *temp;
	curr = head;
	while(curr != NULL && !s.empty()) {
		temp = s.top();
		s.pop();
		if(temp->data != curr->data)
			return false;
		curr = curr->next;
	}
	return true;
}

bool removeLoop(Node *head) {
	unordered_set<Node*> uset;
	Node *curr = head,*prev = head;
	while(curr != NULL) {
		if(uset.find(curr) == uset.end()) {
			uset.insert(curr);
			prev = curr;
			curr = curr->next;
		}
		else {
			prev = NULL;
			break;
		}
	}
	return head;
}

Node* SortedMerge(Node* head1,   Node* head2)
{
    Node *curr1 = head1,*curr2 = head2;
    Node *ans = NULL,*fans = NULL;
    while(curr1 != NULL && curr2 != NULL) {
        if(curr1->data <= curr2->data) {
            if(ans == NULL) {
                ans = curr1;
                fans = ans;
                curr1 = curr1->next;
            }
            else {
                ans->next = curr1;
                curr1 = curr1->next;  
                ans = ans->next;  
            }
        }
        else {
            if(ans == NULL) {
                ans = curr2;
                fans = ans;
                curr2 = curr2->next;
            }
            else {
                ans->next = curr2;
                curr2 = curr2->next;
                ans = ans->next;   
            }
        }
    }
    while(curr1 != NULL) {
        ans->next = curr1;
        curr1 = curr1->next;
        ans = ans->next;
    }
    while(curr2 != NULL) {
        ans->next = curr2;
        curr2 = curr2->next;
        ans = ans->next;
    }
    return fans;
}

Node* RecursiveMerge(Node *h1,Node* h2) {
	if(!h1) 
		return h2;
	if(!h2)
		return h1;
	if(h1->data < h2->data) {
		h1->next = RecursiveMerge(h1->next,h2);
		return h1;
	}
	else {
		h2->next  =RecursiveMerge(h1,h2->next);
		return h2;
	}
}

// bool intersectPointhelper(Node *head1,Node* head2,set<pair<int,Node*> > &visited,int l,bool &flag) {
//     if(head1 == NULL || head2 == NULL) {
//         return false;
//     }
//     if(head1->next && head2->next && head1->next == head2->next) {
//     	if(!flag) {
//         	visited.insert(make_pair(l,head1));
//  			flag = true;
//     	}
//         return true;
//     }
// 	return intersectPointhelper(head1->next,head2,visited,l+1,flag) || intersectPointhelper(head1,head2->next,visited,l+1,flag);
//     // return false
// }

// int intersectPoint(Node* head1, Node* head2)
// {
//     int l = 0;
//     bool flag = false;
//     set<pair<int,Node*> > visited;
//     if(intersectPointhelper(head1,head2,visited,l,flag)) {
//         for(auto p : visited) {
//             auto x  = p;
//             return p.second->data;
//         }   
//     }
//     return -1;
// }

// void pairwiseSwap(Node* head) {
// 	if(head == NULL)
// 		return;
// 	if(head->next == NULL)
// 		return;
// 	if(head->next->next == NULL) {
// 		head->next->next = head;
// 		head = head->next;
// 		head->next->next = NULL:
// 		return;
// 	}
// 	Node *temp = head,*temp1 = head->next->next;
// 	while(temp != NULL && temp->next != NULL) {
// 		Node *curr = temp->next->next;
// 		temp->next->next = temp;
		
// 	}
// }

int main() {
	// freopen("input.txt","r",stdin);
	// int t;
	// cin>>t;
	// while(t--) {
	// int n1,n2,x;
	// cin>>n1>>n2;
	// Node* head1 = NULL;
	// for(int i=0;i<n1;i++) {
	// 	cin>>x;
	// 	head1 = insert(head1,x);
	// }
	// print(head1);
	// Node* head2 = NULL;
	// for(int i=0;i<n2;i++) {
	// 	cin>>x;
	// 	head2 = insert(head2,x);
	// }
	// print(head2);
	// // cout<<detectLoop(head)<<endl;
	// Node *temp = SortedMerge(head1,head2);
	// print(temp);

	// }

	Node *temp1 = new Node(2);
	Node *temp2 = new Node(3);
	temp1->next = new Node(5);
	temp1->next->next = new Node(6);
	temp1->next->next->next = new Node(7);
	temp2->next = new Node(8);
	temp2->next->next = temp1->next->next->next;
	temp2->next->next->next = new Node(9);
	print(temp1);
	cout<<endl;
	print(temp2);
	cout<<endl;
	// cout<<
	cout<<intersectPoint(temp1,temp2);
	// <<endl;
	return 0;
}