#include <iostream>
#include <queue>
#include <cmath>
#include <ctime>
using namespace std;

class AVL {
    class Node {
    public:
        int data;
        int height;
        Node* parent;
        Node* left;
        Node* right;
        int size;
        Node()
            : Node(0)
        {
        }
        Node(int data)
            : data(data)
            , height(0)
            , parent(nullptr)
            , left(nullptr)
            , right(nullptr)
            , size(1)
        {
        }
        void print(Node* root)
        {
            if (root) {
                print(root->left);
                cout << root->data << " " << flush;
                print(root->right);
            }
        }
        void update()
        {
            if (left && right) {
                height = 1 + max(left->height, right->height);
                size = 1 + left->size + right->size;
                return;
            }
            if (left) {
                height = 1 + left->height;
                size = 1 + left->size;
            }
            else if (right) {
                height = 1 + right->height;
                size = 1 + right->size;
            }
            else {
                height = 0;
                size = 1;
            }
        }
        // balance = height(left) - height(right)
        int getBalance()
        {
            if (left && right)
                return (left->height - right->height);
            else if (left)
                return left->height;
            else if (right)
                return -right->height;
            else
                return 0;
        }
        void setLeftChild(Node* newLeft)
        {
            if (newLeft)
                newLeft->parent = this;
            left = newLeft;
            update();
        }
        void setRightChild(Node* newRight)
        {
            if (newRight)
                newRight->parent = this;
            right = newRight;
            update();
        }
    };
    void setRoot(Node* n)
    {
        root = n;
        if (root)
            root->parent = nullptr;
    }
    Node* findNode(int data)
    {
        Node* tmp = root;
        while (tmp) {
            if (data == tmp->data)
                return tmp;
            else if (data < tmp->data)
                tmp = tmp->left;
            else
                tmp = tmp->right;
        }
        return nullptr;
    }
    void rotateLeft(Node*& n)
    {
        int side; //0 -> left, 1 -> right
        Node* p = n->parent;
        if (p) {
            if (p->left == n)
                side = 0;
            else
                side = 1;
        }
        Node* tmp = n->right;
        n->setRightChild(tmp->left);
        tmp->setLeftChild(n);
        if (p) {
            if (!side)
                p->setLeftChild(tmp);
            else
                p->setRightChild(tmp);
        }
        else
            setRoot(tmp);
    }
    void rotateRight(Node*& n)
    {
        int side; //0 -> left, 1 -> right
        Node* p = n->parent;
        if (p) {
            if (p->left == n)
                side = 0;
            else
                side = 1;
        }
        Node* tmp = n->left;
        n->setLeftChild(tmp->right);
        tmp->setRightChild(n);
        if (p) {
            if (!side)
                p->setLeftChild(tmp);
            else
                p->setRightChild(tmp);
        }
        else
            setRoot(tmp);
    }
    void balanceAtNode(Node*& n)
    {
        int bal = n->getBalance();
        if (bal > 1) {
            if (n->left->getBalance() < 0)
                rotateLeft(n->left);
            rotateRight(n);
        }
        else if (bal < -1) {
            if (n->right->getBalance() > 0)
                rotateRight(n->right);
            rotateLeft(n);
        }
    }

public:
    Node* root;
    AVL()
        : root(nullptr)
    {
    }
    AVL(int data)
        : root(new Node(data))
    {
    }
    void print()
    {
        root->print(root);
    }
    void printLevelOrder()
    {
        if (!root)
            return;
        queue<Node*> q;
        q.push(root);
        q.push(nullptr);
        while (!q.empty()) {
            Node* u = q.front();
            q.pop();
            if (u) {
                cout << u->data << " " << flush;
                if (u->left)
                    q.push(u->left);
                if (u->right)
                    q.push(u->right);
            }
            else {
                cout << endl;
                if (!q.empty())
                    q.push(nullptr);
            }
        }
        cout << endl;
    }
    AVL* findSubtree(int data)
    {
        Node* target = findNode(data);
        if (!target)
            return nullptr;
        AVL* subtree = new AVL();
        subtree->root = target;
        return subtree;
    }
    // return false if data already present --> avl_set
    bool insert(int data)
    {
        if (!root) {
            root = new Node(data);
            return true;
        }
        Node* newnode;
        Node* tmp = root;
        while (true) {
            if (data < tmp->data) {
                if (!tmp->left) {
                    newnode = new Node(data);
                    tmp->setLeftChild(newnode);
                    break;
                }
                else
                    tmp = tmp->left;
            }
            else if (data > tmp->data) {
                if (!tmp->right) {
                    newnode = new Node(data);
                    tmp->setRightChild(newnode);
                    break;
                }
                else
                    tmp = tmp->right;
            }
            else // value found in tree, dont add
                return false;
        }
        tmp = newnode;
        // balance newly added node
        // and traverse up towards root
        while (tmp) {
            tmp->update();
            balanceAtNode(tmp);
            tmp = tmp->parent;
        }
    }
    // return true if data found and deleted
    bool remove(int data)
    {
        if (!root)
            return false;
        Node* toRemove = findNode(data);
        // data doesn't exist
        if (!toRemove)
            return false;
        int side; //0 -> left, 1 -> right
        Node* p = toRemove->parent;
        if (p) {
            if (p->left == toRemove)
                side = 0;
            else
                side = 1;
        }
        int bal = toRemove->getBalance();
        // leaf node
        if (!toRemove->left && !toRemove->right) {
            if (p) {
                if (!side)
                    p->setLeftChild(nullptr);
                else
                    p->setRightChild(nullptr);
                delete toRemove;
                p->update();
                balanceAtNode(p);
            }
            else {
                setRoot(nullptr);
                delete toRemove;
            }
        }
        // no right child; only left child
        else if (!toRemove->right) {
            if (p) {
                if (!side)
                    p->setLeftChild(toRemove->left);
                else
                    p->setRightChild(toRemove->left);
                delete toRemove;
                p->update();
                balanceAtNode(p);
            }
            else {
                setRoot(toRemove->left);
                delete toRemove;
            }
        }
        // no left child; only right child
        else if (!toRemove->left) {
            if (p) {
                if (!side)
                    p->setLeftChild(toRemove->right);
                else
                    p->setRightChild(toRemove->right);
                delete toRemove;
                p->update();
                balanceAtNode(p);
            }
            else {
                setRoot(toRemove->right);
                delete toRemove;
            }
        }
        // both children present
        else {
            Node *tmp, *r, *rp;
            // left subtree > right subtree
            if (bal > 0) {
                if (!toRemove->left->right) {
                    r = toRemove->left;
                    r->setRightChild(toRemove->right);
                    tmp = r;
                }
                else {
                    r = toRemove->left->right;
                    while (r->right)
                        r = r->right;
                    rp = r->parent;
                    rp->setRightChild(r->left);
                    tmp = rp;
                    r->setLeftChild(toRemove->left);
                    r->setRightChild(toRemove->right);
                }
            }
            // right subtree, left subtree
            else {
                if (!toRemove->right->left) {
                    r = toRemove->right;
                    r->setLeftChild(toRemove->left);
                    tmp = r;
                }
                else {
                    r = toRemove->right->left;
                    while (r->left)
                        r = r->left;
                    rp = r->parent;
                    rp->setLeftChild(r->left);
                    tmp = rp;
                    r->setLeftChild(toRemove->left);
                    r->setRightChild(toRemove->right);
                }
            }
            if (p) {
                if (!side)
                    p->setLeftChild(r);
                else
                    p->setRightChild(r);
                delete toRemove;
            }
            else {
                setRoot(r);
                delete toRemove;
            }
            balanceAtNode(tmp);
        }
        return true;
    }
    Node* kthSmallest(Node* root, int k)
    {
        int r = 1;
        if (root->left)
            r += root->left->size;
        if (k == r)
            return root;
        if (k < r)
            return kthSmallest(root->left, k);
        else
            return kthSmallest(root->right, k - r);
    }
    int getHeight()
    {
        return root->height;
    }
};

void testAVL()
{
    int arr[] = { 5, 2, 3, 1, 4, 6, 7, 8 };
    int n = 8;
    AVL* tree = new AVL();
    for (int i = 0; i < 10; i++)
        tree->insert(arr[i % 8]);
    tree->print();
    cout << endl;
    tree->printLevelOrder();
    // tree->remove(3);
    // tree->printLevelOrder();
    cout << tree->getHeight() << endl;
    delete tree;
}

void testKthSmallest()
{
    int arr[] = { 13, 17, 21, 12, 10, 19, 26, 28 };
    int n = 8;
    AVL* tree = new AVL();
    for (int i = 0; i < 10; i++)
        tree->insert(arr[i % 8]);
    tree->printLevelOrder();
    for (int i = 0; i < 8; i++)
        cout << tree->kthSmallest(tree->root, i + 1)->data << " " << flush;
    cout << endl;
    delete tree;
}


void test()
{
    int arr[] = { 13, 17, 21, 12, 10, 19, 26, 28 };
    int n = 8;
    AVL* tree = new AVL();
    for (int i = 0; i < 10; i++)
        tree->insert(arr[i % 8]);
    tree->printLevelOrder();
    delete tree;
}

void testHeight()
{
    AVL avl;
    for(int i = 0; i < 2030; i++) {
        int x = 1 + rand() % 10923;
        avl.insert(x);
    }
    // avl.printLevelOrder();
    cout << log2(2030) << " " << avl.getHeight() << endl;
}

int main()
{
    // testKthSmallest();
    //freopen("out.txt", "w", stdout);
    srand(time(0));
    // test();
    AVL avl;
    int N = 119298;
    for(int i = 0; i < N; i++) {
        int x = 1 + rand() % N;
        avl.insert(x);
    }
    // avl.printLevelOrder();
    cout << log2(avl.root->size + 1) << " " << avl.getHeight() << endl;
    return 0;
}