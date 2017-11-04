#include <bits/stdc++.h>
using namespace std;

class AVL {
	class Node {
	public:
		int data;
		int height;
		Node *left;
		Node *right;
		Node(int data) {
			this->data = data;
			this->height = 1;
			this->left = NULL;
			this->right = NULL;
		}
	};
	public:
		Node *root;

	int height(Node *root) {
		if(root  == NULL)
			return -1;
		else
			return root->height;
	}
	Node* RotateLeft(Node *root) {
		Node *temp = root->right;
		root->right = temp->left;
		temp->left = root;
		root->height = max(height(root->left),height(root->right)) + 1;
		temp->height = max(height(temp->left),height(temp->right)) + 1;
		return temp;
	}
	Node* RotateRight(Node *root) {
		Node *temp = root->left;
		root->left = temp->right;
		temp->right = root;
		root->height = max(height(root->left),height(root->right)) + 1;
		temp->height = max(height(temp->left),height(temp->right)) + 1;
		return temp; //temp is the new root
	}
	Node* RotateLeftRight(Node *root) {
		RotateLeft(root->left);
		return RotateRight(root);
	}
	Node* RotateRightLeft(Node *root) {
		RotateRight(root->right);
		return RotateLeft(root);
	}
public:
	void insert(Node *&root,int data) {
		if(!root) {
			root = new Node(data);
			return;
		}
		if(data <= root->data) {
			insert(root->left,data);
			root->height = max(height(root->left),height(root->right)) + 1;
			if(height(root->left) - height(root->right) == 2) {
				if(data <= root->left->data) {
					root = RotateRight(root);
				}else {
					root = RotateLeftRight(root);
				}
			}
		}else if(data > root->data){
			insert(root->right,data);
			root->height = max(height(root->left),height(root->right)) + 1;
			if(height(root->right) - height(root->left) == 2) {
				if(data <= root->right->data) {
					root = RotateLeft(root);
				}
				else  {
					root = RotateRightLeft(root);
				}
			}
		}
	}
	AVL() {
		this->root = NULL;
	}
public:
	void printInorder(Node *root) {
		if(root) {
			printInorder(root->left);
			cout<<root->data<<" "<<root->height<<endl;
			printInorder(root->right);

		}
	}
};

int main() {
	AVL *a = new AVL();
	a->insert(a->root,13);
	a->insert(a->root,23);
	a->insert(a->root,34);
	a->insert(a->root,12);
	a->insert(a->root,10);
	a->insert(a->root,19);
	a->insert(a->root,26);
	a->printInorder(a->root);
	cout<<"*"<<a->root->data<<endl;
	return 0;
}