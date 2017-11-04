#include <iostream>
#include <climits>
#include <map>
#include <deque>
#include <queue>
using namespace std;

struct Node {
	int data;
	Node *left,*right;
	Node() {

	}
	Node(int key) {
		this->data = key;
		left = right = NULL;
	}
};

Node* insert(Node *root,int x) {
	if(root == NULL) {
		return new Node(x);
	}else if(root->data  >= x) {
		root->left = insert(root->left,x);
	}else {
		root->right = insert(root->right,x);
	}
	return root;
}

Node* searchKey(Node *root,int key) {
	if(root == NULL) {
		return NULL;
	}
	else if(root->data == key) {
		return root;
	}else if(root->data > key) {
		searchKey(root->left,key);
	}else {
		searchKey(root->right,key);
	}
}

void InOrder(Node *root) {
	if(root != NULL) {
		InOrder(root->left);
		cout<<root->data<<" ";
		InOrder(root->right);
	}
}

//here the max_value has to be a pointer since it has to be updated when the LeftViewUtil is called for the root->left node
// before it is called for the right->Node

void printLeftViewUtil(Node *root,int level,int *max_level) {
	if(root == NULL) 
		return ;
	if(*max_level < level) {
		cout<<root->data<<" ";
		*max_level = level;
	}
	printLeftViewUtil(root->left,level+1,max_level);
	printLeftViewUtil(root->right,level+1,max_level);
}

void printLeftView(Node *root) {
	int max_level = 0;
	printLeftViewUtil(root,1,&max_level);
}

int maxValue(Node *root) {
    if(root == NULL)
        return 0;
    return max(max(maxValue(root->left),maxValue(root->right)),root->data);
}

int minValue(Node *root) {
    if(root == NULL)
        return INT_MAX;
    return min(min(minValue(root->left),minValue(root->right)),root->data);
}

void printBottomView(Node *root) {
	queue<pair<Node*,int> > q;
	map<int,Node*> treemap;
	q.push(make_pair(root,0));
	treemap.insert(make_pair(0,root));
	while(!q.empty()) {
		pair<Node*,int> p = q.front();
		Node *node = p.first;
		q.pop();
		if(treemap.find(p.second) != treemap.end()) {
			treemap[p.second] = node;
		}
		else {
			treemap.insert(make_pair(p.second,node));
		}
			if(node->left) {
				q.push(make_pair(node->left,p.second-1));
			}
			if(node->right) {
				q.push(make_pair(node->right,p.second+1));
			}
	}
	for(auto p : treemap) {
		cout<<p.second->data<<" ";
	}
}

void printVerticalOrder(Node *root) {
	queue<pair<Node*,int> > q;
	map<int,vector<Node*> > treemap;
	q.push(make_pair(root,0));
	while(!q.empty()) {
		pair<Node*,int> p = q.front();
		q.pop();
		Node *node = p.first;
		int hd = p.second;
		treemap[hd].push_back(node);
		if(node->left)
			q.push(make_pair(node->left,hd-1));
		if(node->right)
			q.push(make_pair(node->right,hd+1));
	}
	map<int,vector<Node*> > :: iterator it;
	for(it=treemap.begin();it!=treemap.end();it++) {
		vector<Node*> v = (*it).second;
		for(int i=0;i<v.size();i++) {
			cout<<v[i]->data<<" ";
		}
		cout<<"$";
	}
}

int height(Node *root) {
	if(root == NULL) {
		return 0;
	}
	return max(height(root->left),height(root->right)) + 1;
}

int diameter(Node *root) {
	if(root == NULL) {
		return 0;
	}
	return max(max(diameter(root->left),diameter(root->right)),height(root->left)+height(root->right)+1);
}

void LevelOrderTraversal(Node *root) {
	if(root == NULL)
		return;
	queue<Node *> q;
	q.push(root);
	while(!q.empty()) {
		Node *temp = q.front();
		cout<<temp->data<<" ";
		q.pop();
		if(temp->left)
			q.push(temp->left);
		if(temp->right)
			q.push(temp->right);
	}
}

void LevelOrderTraversalSpiral(Node *root) {
	if(root == NULL)
		return;
	deque<Node*> q1;
	deque<Node*> q2;
	q2.push_back(root);
	int dummy = 1;
	Node *temp;
	while(!q1.empty() || !q2.empty()) {
		while(!q1.empty() && dummy == 0) {
			temp = q1.front();
			cout<<temp->data<<" ";
			q1.pop_front();
			if(temp->left)
				q2.push_back(temp->left);
			if(temp->right)
				q2.push_back(temp->right);
		}
		while(!q2.empty() && dummy == 1) {
			temp = q2.back();
			cout<<temp->data<<" ";

			q2.pop_back();
			if(temp->right)
				q1.push_front(temp->right);
			if(temp->left)
				q1.push_front(temp->left);
		}
		dummy = 1 - dummy;
	}
}

Node* LCA(Node *root,int n1,int n2) {
	if(root == NULL)
		return NULL;
	if(n1 <= root->data && n2 >= root->data)
		return root;
	if(n1 <= root->data && n2 <= root->data)
		return LCA(root->left,n1,n2);
	if(n1 >= root->data && n2 >= root->data)
		return LCA(root->right,n1,n2);
}

Node* minValueNode(Node *root) {
	if(root == NULL)
		return NULL;
	while(root->left != NULL) {
		root = root->left;
	}
	return root;
}

Node* InOrderToDLLUtil(Node *root) {
	if(root != NULL) {
		if(root->left) {
			Node *temp = root->left;
			while(temp->right != NULL) {
				temp = temp->right;
			}
			Node* l = InOrderToDLLUtil(root->left);
			if(l) {
				temp->right = root;
			    root->left = temp;
			}
			else {
				root->left = NULL;
			}
		}
		if(root->right) {
			Node *temp1 = root->right;
			while(temp1->left != NULL) {
				temp1 = temp1->left;
			}
			Node *r = InOrderToDLLUtil(root->right);
			if(r) {
				temp1->left = root;
				root->right = temp1;
			}
			else {
				root->right = NULL;
			}
		}
	}
	return root;
}

Node *InOrderToDLL(Node* root) {
	Node *temp = minValueNode(root);
	InOrderToDLLUtil(root);
	return temp;
}

Node* maxValueNode(Node *root) {
	if(root == NULL) 
		return NULL;
	while(root->right != NULL) {
		root = root->right;
	}
	return root;
}

bool isIdentical(Node *r1,Node *r2) {
    if(r1 == NULL && r2 == NULL)
        return true;
    if(r1 != NULL && r2 != NULL) {
        return (r1->data == r2->data) && isIdentical(r1->left,r2->left) && isIdentical(r1->right,r2->right);
    }
    return false;
}


int maxPathfromRootToLeaf(Node *root) {
    if(root == NULL) 
        return 0;
    if(root->left == NULL && root->right == NULL)
        return root->data;
    return max(maxPathfromRootToLeaf(root->left),maxPathfromRootToLeaf(root->right)) + root->data;
}

int maxPathSum(struct Node *root)
{
    if(root == NULL)
        return 0;
    if(root->left == NULL && root->right == NULL) 
        return root->data;
    return max(max(maxPathSum(root->left),maxPathSum(root->right)),(maxPathfromRootToLeaf(root->left) + maxPathfromRootToLeaf(root->right) + root->data));
}

int countLeaves(Node* root)
{
  if(root == NULL)
    return 0;
  if(root->left == NULL && root->right == NULL)
    return 1;
  return countLeaves(root->left) + countLeaves(root->right);
}

bool isBalanced(Node *root)
{
    if(root == NULL)
        return true;
    if(abs(height(root->left) - height(root->right)) > 1)
        return false;
    return isBalanced(root->left) && isBalanced(root->right);
}


int main() {
	Node *root = NULL;
	// Node n;
	//  n.data = 9;
	// cout<<n.data<<endl;
	root = insert(root,10);
	root = insert(root,6);
	root = insert(root,15);
	root = insert(root,7);
	root = insert(root,1);
	InOrder(root);
	cout<<endl;
	// cout<<searchKey(root,7)->data<<endl;
	// printLeftView(root);
	// cout<<maxValue(root)<<endl;
	// cout<<minValue(root)<<endl;
	// printBottomView(root);
	// printVerticalOrder(root);
	// cout<<diameter(root)<<endl;
	// LevelOrderTraversal(root);
	// cout<<endl;
	// LevelOrderTraversalSpiral(root);
	// cout<<LCA(root,1,7)->data<<endl;
	// cout<<LCA(root,6,10)->data<<endl;
	// cout<<LCA(root,10,10)->data<<endl;
	// Node *temp = InOrderToDLL(root);
	// while(temp != NULL) {
	// 	cout<<temp->data<<" ";
	// 	temp = temp->right;
	// }
	// cout<<maxValueNode(root)->data<<endl;
	// Node *temp = maxValueNode(root);
	// fixPrevPointer(root);
	// while(temp != NULL) {
	// 	cout<<temp->data<<" ";
	// 	temp = temp->left;
	// }
	// TreetoDoubll(root);
	Node *t1 = new Node(3);
	t1->left = new Node(4);
	t1->right = new Node(4);
	// Node *t2 = new Node(3);
	// cout<<"**"<<isIdentical(t1,t2);
	cout<<isSymmetric(root)<<endl;
	cout<<isSymmetric(t1)<<endl;
	return 0;
}
