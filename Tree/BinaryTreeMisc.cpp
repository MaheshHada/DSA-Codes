#include <bits/stdc++.h>
using namespace std;

struct Node {
	int data;
	Node *left;
	Node *right;
	Node *parent;
	Node(int key) {
		this->data = key;
		this->left = NULL;
		this->right = NULL;
		this->parent = NULL;
	}
};


//Insert In A BST
void insert(Node *root,int key) {
	if(root == NULL) {
		root = new Node(key);
		return;
	}
	queue<Node *> q;
	q.push(root);
	while(!q.empty()) {
		Node *temp = q.front();
		q.pop();
		if(temp->data >= key) {
			if(temp->left != NULL) 
				q.push(temp->left);
			else {
				Node *newNode = new Node(key);
				newNode->parent = temp;
				temp->left = newNode;
				return;
			}
		}
		else {
			if(temp->right != NULL)
				q.push(temp->right);
			else {
				Node *newNode = new Node(key);
				newNode->parent = temp;
				temp->right = newNode;
				return;
			}
		}
	}
}

//Level Order Traversal
void print(Node *root) {
	if(root == NULL)
		return;
	queue<Node*> q;
	q.push(root);
	while(!q.empty()) {
		Node *temp = q.front();
		q.pop();
		cout<<temp->data<<" ";
		if(temp->left)
			q.push(temp->left);
		if(temp->right)
			q.push(temp->right);
	}
	cout<<endl;
}

//Vertical Order Traversal
void FindMinMax(Node* root,int *imin,int *imax,int hd) {
	if(root == NULL)
		return;
	if(hd < *imin) 
		*imin = hd;
	else if(hd > *imax)
		*imax = hd;
	FindMinMax(root->left,imin,imax,hd-1);
	FindMinMax(root->right,imin,imax,hd+1);
}

//Vertical Order Traversal
void printVerticalLines(Node *root,int line_no,int hd) {
	if(root == NULL)
		return;
	if(hd == line_no)
		cout<<root->data<<" ";
	printVerticalLines(root->left,line_no,hd-1);
	printVerticalLines(root->right,line_no,hd+1);
}

//Vertical Order Traversal
void printVerticalOrder(Node *root) {
	int m1,m2;
	m1 = INT_MAX;
	m2 = INT_MIN;
	FindMinMax(root,&m1,&m2,0);
	for(int i=m1;i<=m2;i++) {
		printVerticalLines(root,i,0);
		cout<<endl;
	}
}

//Height of a Node
int height(Node *root){
	if(root == NULL)
		return -1;
	return max(height(root->left),height(root->right)) + 1;
}

//Finds if the k can be represented using the sum of two data
bool FindSum(struct Node *root,int key) {
	bool f = false;
	stack<Node*> s1,s2;
	Node *root1 = root,*root2 = root;
	bool done1,done2;
	int val1,val2;
	while(1) {
		while(!done1) {
			if(root1 != NULL) {
				s1.push(root1);
				root1->left;
			}
			else {
				if(s1.empty())
					done1=1;
				else  {
					val1 = s1.top()->data;
					root1 = s1.top();
					s1.pop();
					root1 = root1->right;
					// s1.push(root1);
					done1=1;
				}
			}
		}
		while(1) {
			while(!done2) {
				if(root2) {
					s2.push(root2);
					root2->right;
				}
				else {
					if(s2.empty())
						done2=1;
					else {
						val2 = s2.top()->data;
						root2 = s2.top();
						s2.pop();
						root2 = root2->left;
						// s2.push(root2);
						done2=1;
					}
				}
			}
		}
		if(val1!=val2 && val1+val2 == key) {
			cout<<"Found "<<val1<<" "<<val2<<endl;
			return true;
		}
		else if((val1+val2) > key) 
			done2=false;
		else if((val1+val2) < key)
			done1=false;
		if(val1>=val2)
			return false;
	}
}

//Recursive Inorder
void InOrder(struct Node *root) {
	if(root) {
		InOrder(root->left);
		cout<<root->data<<" ";
		InOrder(root->right);
	}
}

//NonRecursive InOrder
void InorderNonRecursive(Node *root) {
	stack<Node *> s;
	while(1) {
		while(root!=NULL) {
			s.push(root);
			root = root->left;
		}
		if(s.empty()) 
			break;
		root = s.top();
		s.pop();
		cout<<root->data<<" ";
		root = root->right;
	}
}

//Searching Tree for a key returns a Node to that key
Node*  search(Node *root,int key) {
	if(root == NULL)
		return NULL;
	else if(root->data > key) {
		return search(root->left,key);
	}else if(root->data < key) {
		return search(root->right,key);
	}else
		return root;
}

//Returns a Pointer to the minimum node in tree
Node* FindMin(Node *root) {
	if(root == NULL)
		return NULL;
	else if(root->left == NULL) {
		return root;
	}
	else {
		return FindMin(root->left);
	}
}

// Node* PrintLeftView(Node *root,int h) {
// 	if(root!=NULL) {
// 		if()
// 		PrintLeftView(root->left,h);
// 		PrintLeftView(root->right,h);
// 	}
// }

//Returns pointer to max node int he tree
Node* FindMax(Node *root) {
	if(root == NULL)
		return NULL;
	else if(root->right == NULL)
		return root;
	else  
		return FindMax(root->right);
}

//Returns Predeccessor of the node, if the node is minimum of tree it returns itself
Node* Predecessor(Node *root,int key) {
	if(root == NULL)
		return NULL;
	Node *temp = search(root,key);
	if(temp->left!=NULL) {
		temp = temp->left;
		while(temp->right != NULL) {
			temp = temp->right;
		}
		return temp;
	}else {
		if(FindMin(root)->data == key) {
			return temp;
		}
		temp = temp->parent;
		while(temp->data > key) {
			temp = temp->parent;
		}
		return temp;
	}
}

//Returns the pointer to the successor of the node, if the node is maximum it returns itself
Node* Successor(Node *root,int key) {
	if(root == NULL)
		return NULL;
	Node *temp = search(root,key);
	if(temp->right != NULL) {
		temp = temp->right;
		while(temp->left != NULL) {
			temp = temp->left;
		}
		return temp;
	}else {
		if(FindMax(root)->data == key) {
			return temp;
		}
		temp = temp->parent;
		while(temp->data < key) {
			temp = temp->parent;
		}
		return temp;
	}
}

void PreOrderItr(Node *root) {
	stack<Node*> s;
	Node *curr = root;
	bool flag = false;
	while(!flag) {
		if(curr) {
			cout<<curr->data<<" ";
			s.push(curr);
			curr = curr->left;
		}else {
			if(!s.empty()) {
				curr = s.top();
				s.pop();
				curr = curr->right;
			}else {
				flag = true;
			}
		}
	}
}

void InOrderItr(Node* root) {
	stack<Node*> s;
	bool flag = false;
	Node* curr = root;
	while(!flag) {
		if(curr) {
			s.push(curr);
			curr = curr->left;
		}else {
			if(!s.empty()) {
				curr = s.top();
				s.pop();
				cout<<curr->data<<" ";
				curr = curr->right;
			}else {
				flag = true;
			}
		}
	}
}

void postOrderItr(Node *root) {
	if(root == NULL)
		return;
	stack<Node*> s1,s2;
	s1.push(root);
	Node *curr = root;
	while(!s1.empty()) {
		auto p = s1.top();
		s1.pop();
		s2.push(p);
		if(p->left)
			s1.push(p->left);
		if(p->right)
			s1.push(p->right);
	}
	while(!s2.empty()) {
		cout<<s2.top()->data<<" ";
		s2.pop();
	}
}

int maxPathSumUtil(Node* root,int &res) {
	if(root == NULL)
		return 0;
	int l = maxPathSumUtil(root->left,res);
	int r = maxPathSumUtil(root->right,res);
	int max_single = max(max(l,r)+root->data,root->data);
	res = max(res,max(max_single,l+r+root->data));
	return max_single;
}

int maxPathSum(Node *root) {
	int res = INT_MIN;
	res = maxPathSumUtil(root,res);
	return res;
}

Node* insertR(Node *root,int key) {
	if(root == NULL)
		return new Node(key);
	if(root->data > key) {
		root->left = insertR(root->left,key);
	} 
	else {
		root->right = insertR(root->right,key);
	}
	return root;
}

Node* SortedOrderToTree(int arr[],int l,int r,Node *root) {
	if(l <= r) {
		int mid = (l+r)/2;
		root = new Node(arr[mid]);
		root->left = SortedOrderToTree(arr,l,mid-1,root);
		root->right = SortedOrderToTree(arr,mid+1,r,root);
		return root;
	}
	return NULL;
}

Node* createTree(int arr[],int n) {
	Node* root = NULL;
	// int n = sizeof(*arr)/sizeof(arr[0]);
	// cout<<n<<endl;
	root = SortedOrderToTree(arr,0,n-1,root);
	return root;
}

Node* PreIntoTree(vector<int> pre,vector<int> in,int start,int end) {
	int static index = 0;
	if(start > end)
		return NULL;
	Node* temp = new Node(pre[index++]);
	if(start == end)
		return temp;
	int nodeInd = lower_bound(in.begin() + start,in.begin()+end,temp->data) - in.begin();
	temp->left = PreIntoTree(pre,in,start,nodeInd-1);
	temp->right = PreIntoTree(pre,in,nodeInd+1,end);
	return temp;
}

Node* PostInToTree(vector<int> post,vector<int> in,int start,int end,int *pindex) {
	if(start > end)
		return NULL;
	Node *temp = new Node(post[*pindex]);
	(*pindex)--;
	if(start == end)
		return temp;
	int nodeInd = lower_bound(in.begin()+start,in.begin()+end,temp->data) - in.begin();
	temp->right = PostInToTree(post,in,nodeInd+1,end,pindex);
	temp->left = PostInToTree(post,in,start,nodeInd-1,pindex);
	return temp;
}


int main() {
	// Node *root = NULL;
	// root = insertR(root,10);
	// insertR(root,8);
	// insertR(root,11);
	// root = insertR(root,6);
	// root = insertR(root,9);
	// root = insertR(root,4);
	// root = insertR(root,7);
	// // print(root);
	// printVerticalOrder(root);
	// cout<<"height: "<<height(root);
	// InorderNonRecursive(root);
	// cout<<endl;
	// InOrder(root);
	// cout<<endl;
	// cout<<FindSum(root,99);
	// cout<<search(root,4)->data;
	// cout<<FindMin(root)->data;
	// cout<<FindMax(root)->data;
	// cout<<Successor(root,10)->data;
	// cout<<Successor(root,8)->data;
	// cout<<Successor(root,6)->data;
	// PreOrderItr(root);
	// cout<<endl;
	// InOrderItr(root);
	// cout<<endl;
	// postOrderItr(root);
	// cout<<maxPathSum(root)<<endl;
	// int arr[] = {1,2,3,4,5,6,7,9,10,11};
	// int n = sizeof(arr)/sizeof(arr[0]);
	///very important information the sizeof() is resolved at compile time and not on the runtime.
	//so after passing it to the function if we do sizeof(arr)/sizeof(arr[0]) it will not give the crrect value
	// Node *temp = createTree(arr,n);
	// InOrderItr(temp);
	// cout<<endl;
	// PreOrderItr(temp);
	vector<int> pre(5),in(5);
	pre[0] = 4;
	pre[1] = 13;
	pre[2] = 12;
	pre[3]= 19;
	pre[4] = 15;
	in[0] = 4;
	in[1] = 12;
	in[2] = 13;
	in[3]= 15;
	in[4] = 19;
	Node *tempp  = NULL;
	int *k;
	*k = 4;
	tempp = PostInToTree(pre,in,0,4,k);
	InOrderItr(tempp);
	cout<<endl;
	postOrderItr(tempp);
	return 0;
}