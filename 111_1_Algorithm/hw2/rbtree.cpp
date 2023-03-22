#include <iostream>
#include <vector>
using namespace std;
class TreeNode
{
public:
    TreeNode *rightChild;
    TreeNode *leftChild;
    TreeNode *parent;
    int key;
    bool color; // 1: black 0: red
    friend class rbTree;
    TreeNode() : leftChild(0), rightChild(0), parent(0), key(0), color(0) {}
    TreeNode(int key) : leftChild(0), rightChild(0), parent(0), key(key), color(0) {}
};
class rbTree
{
private:
    TreeNode *NIL;
    void leftRotation(TreeNode *x)
    {
        TreeNode *y = x->rightChild;
        x->rightChild = y->leftChild;
        if (y->leftChild != NIL)
            y->leftChild->parent = x;
        y->parent = x->parent;
        if (x->parent == NIL)
            root = y;
        else if (x == x->parent->leftChild)
            x->parent->leftChild = y;
        else
            x->parent->rightChild = y;
        y->leftChild = x;
        x->parent = y;
    }
    void rightRotation(TreeNode *x)
    {
        TreeNode *y = x->leftChild;
        x->leftChild = y->rightChild;
        if (y->rightChild != NIL)
            y->rightChild->parent = x;
        y->parent = x->parent;
        if (x->parent == NIL)
            root = y;
        else if (x == x->parent->leftChild)
            x->parent->leftChild = y;
        else
            x->parent->rightChild = y;
        y->rightChild = x;
        x->parent = y;
    }

public:
    TreeNode *root;
    rbTree()
    {
        NIL = new TreeNode;
        NIL->color = 1;
        root = NIL;
        root->parent = NIL;
    };
    void IOT(TreeNode *node, vector<TreeNode *> &vec)
    {
        if (node == NIL)
            return;
        IOT(node->leftChild, vec);
        vec.push_back(node);
        IOT(node->rightChild, vec);
    };
    void Insert(int key);
    void insertFix(TreeNode *node);
    void Delete(int key);
    void deleteFix(TreeNode *node);
    TreeNode *searchKey(int target)
    {
        TreeNode *cur = root;
        while (target != cur->key)
        {
            if (target < cur->key)
                cur = cur->leftChild;
            else
                cur = cur->rightChild;
        }
        return cur;
    };
};
void rbTree::Insert(int key)
{
    TreeNode *p = NIL; //parent of s
    TreeNode *s = root;
    TreeNode *insertedNode = new TreeNode(key);
    while (s != NIL)
    {
        p = s;
        if (insertedNode->key < s->key)
            s = s->leftChild;
        else
            s = s->rightChild;
    }
    insertedNode->parent = p;
    if (p == NIL)
        this->root = insertedNode;
    else if (insertedNode->key < p->key)
        p->leftChild = insertedNode;
    else
        p->rightChild = insertedNode;
    insertedNode->leftChild = NIL;
    insertedNode->rightChild = NIL;
    insertedNode->color = 0;
    insertFix(insertedNode);
}
void rbTree::insertFix(TreeNode *node)
{
    while (node->parent->color == 0) // parent is red
    {
        if (node->parent == node->parent->parent->leftChild) // parent is leftChild of grandparent
        {
            TreeNode *uncle = node->parent->parent->rightChild;
            if (uncle->color == 0) // uncle is red
            {
                node->parent->color = 1;
                uncle->color = 1;
                node->parent->parent->color = 0;
                node = node->parent->parent;
            }
            else // uncle is black
            {
                if (node == node->parent->rightChild) // > parent
                {
                    node = node->parent;
                    leftRotation(node);
                }
                node->parent->color = 1;
                node->parent->parent->color = 0;
                rightRotation(node->parent->parent);
            }
        }
        else // parent is rightChild of grandparent
        {
            TreeNode *uncle = node->parent->parent->leftChild;
            if (uncle->color == 0)
            {
                node->parent->color = 1;
                uncle->color = 1;
                node->parent->parent->color = 0;
                node = node->parent->parent;
            }
            else
            {
                if (node == node->parent->leftChild)
                {
                    node = node->parent;
                    rightRotation(node);
                }
                node->parent->color = 1;
                node->parent->parent->color = 0;
                leftRotation(node->parent->parent);
            }
        }
    }
    root->color = 1;
}
void rbTree::Delete(int key)
{
    TreeNode *deletedNode = searchKey(key);
    TreeNode *s; // target
    TreeNode *c; // child of s
    if (deletedNode->leftChild == NIL || deletedNode->rightChild == NIL)
        s = deletedNode;
    else
    {
        TreeNode *temp = deletedNode;
        if (temp->rightChild != NULL)
        {
            temp = temp->rightChild;
            while (temp->leftChild != NULL)
                temp = temp->leftChild;
            s = temp;
        }
        else
        {
            TreeNode *newNode = temp->parent;
            while (newNode != NULL && temp == newNode->rightChild)
            {
                temp = newNode;
                newNode = newNode->parent;
            }
            s = newNode;
        }
    }
    if (s->leftChild != NIL)
        c = s->leftChild;
    else
        c = s->rightChild;
    c->parent = s->parent;
    if (s->parent == NIL)
        this->root = c;
    else if (s == s->parent->leftChild)
        s->parent->leftChild = c;
    else
        s->parent->rightChild = c;
    if (s != deletedNode)
        deletedNode->key = s->key;
    if (s->color) // black
        deleteFix(c);
}
void rbTree::deleteFix(TreeNode *node)
{
    while (node != root && node->color)
    {
        if (node == node->parent->leftChild)
        {
            TreeNode *sib = node->parent->rightChild;
            if (sib->color == 0) // sib is red
            {
                sib->color = 1;
                node->parent->color = 0;
                leftRotation(node->parent);
                sib = node->parent->rightChild;
            }
            // sib is black
            if (sib->leftChild->color && sib->rightChild->color) //both children of sib black
            {
                sib->color = 0;
                node = node->parent;
            }
            else //either one
            {
                if (sib->rightChild->color) //right black && left red
                {
                    sib->leftChild->color = 1;
                    sib->color = 0;
                    rightRotation(sib);
                    sib = node->parent->rightChild;
                }
                //right red left black
                sib->color = node->parent->color;
                node->parent->color = 1;
                sib->rightChild->color = 1;
                leftRotation(node->parent);
                node = root;
            }
        }
        else
        { // node is right
            TreeNode *sib = node->parent->leftChild;
            if (sib->color == 0)
            {
                sib->color = 1;
                node->parent->color = 0;
                rightRotation(node->parent);
                sib = node->parent->leftChild;
            }
            if (sib->leftChild->color && sib->rightChild->color)
            {
                sib->color = 0;
                node = node->parent;
            }
            else
            {
                if (sib->leftChild->color) // right red left black
                {
                    sib->rightChild->color = 1;
                    sib->color = 0;
                    leftRotation(sib);
                    sib = node->parent->leftChild;
                }
                // left red right black
                sib->color = node->parent->color;
                node->parent->color = 1;
                sib->leftChild->color = 1;
                rightRotation(node->parent);
                node = root;
            }
        }
    }
    node->color = 1;
}
int main()
{
    int t;
    int op, n;
    cin >> t;
    rbTree RBT;
    for (int i = 0; i < t; ++i)
    {
        cin >> op >> n;
        vector<int> vec(n);
        if (op == 1)
        { // Insert
            for (int j = 0; j < n; ++j)
            {
                cin >> vec[j];
                RBT.Insert(vec[j]);
            }

            cout << "Insert: ";
            for (int j = 0; j < n; ++j)
                cout << vec[j] << ", ";
            cout << '\n';
            vector<TreeNode *> inorder;
            RBT.IOT(RBT.root, inorder);
            for (auto i : inorder)
            {
                cout << "key: " << i->key << ' ' << "parent: ";
                if (i->parent->key != 0)
                    cout << i->parent->key;
                cout << ' ' << "color: ";
                if (i->color)
                    cout << "black";
                else
                    cout << "red";
                cout << '\n';
            }
        }
        else
        { // Delete
            for (int j = 0; j < n; ++j)
            {
                cin >> vec[j];
                RBT.Delete(vec[j]);
            }

            cout << "Delete: ";
            for (int j = 0; j < n; ++j)
                cout << vec[j] << ", ";
            cout << '\n';
            vector<TreeNode *> inorder;
            RBT.IOT(RBT.root, inorder);
            for (auto i : inorder)
            {
                cout << "key: " << i->key << ' ' << "parent: ";
                if (i->parent->key != 0)
                    cout << i->parent->key;
                cout << ' ' << "color: ";
                if (i->color)
                    cout << "black";
                else
                    cout << "red";
                cout << '\n';
            }
        }
    }

    return 0;
}