#include<bits/stdc++.h>
using namespace std;
/*
<aside>
💡 Question-1

You are given a binary tree. The binary tree is represented using the TreeNode class. Each TreeNode has an integer value and left and right children, represented using the TreeNode class itself. Convert this binary tree into a binary search tree.

</aside>
*/
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
 
void inorder(TreeNode* root, vector<TreeNode*>& nodes) {
    if (root == NULL) {
        return;
    }
    inorder(root->left, nodes);
    nodes.push_back(root);
    inorder(root->right, nodes);
}
TreeNode* constructBST(vector<TreeNode*>& nodes, int start, int end) {
    if (start > end) {
        return NULL;
    }
    int mid = (start + end) / 2;
    TreeNode* root = nodes[mid];
    root->left = constructBST(nodes, start, mid - 1);
    root->right = constructBST(nodes, mid + 1, end);
    return root;
}
TreeNode* convertToBST(TreeNode* root) {
    vector<TreeNode*> nodes;
    inorder(root, nodes);
    sort(nodes.begin(), nodes.end(), [](const TreeNode* a, const TreeNode* b) {
        return a->val < b->val;
    });
    return constructBST(nodes, 0, nodes.size() - 1);
}

/*
<aside>
💡 Question-2:

Given a Binary Search Tree with all unique values and two keys. Find the distance between two nodes in BST. The given keys always exist in BST.

</aside>
*/

#include <iostream>
using namespace std;
 
// A Binary Tree Node
struct Node {
    struct Node *left, *right;
    int key;
};
 
Node* newNode(int key)
{
    Node* temp = new Node;
    temp->key = key;
    temp->left = temp->right = NULL;
    return temp;
}
Node* LCA(Node* root, int n1, int n2)
{
    
    if (root == NULL)
        return root;
    if (root->key == n1 || root->key == n2)
        return root;
 
    Node* left = LCA(root->left, n1, n2);
    Node* right = LCA(root->right, n1, n2);
 
    if (left != NULL && right != NULL)
        return root;
    if (left == NULL && right == NULL)
        return NULL;
    if (left != NULL)
        return LCA(root->left, n1, n2);
 
    return LCA(root->right, n1, n2);
}

int findLevel(Node* root, int k, int level)
{
    if (root == NULL)
        return -1;
    if (root->key == k)
        return level;
 
    int left = findLevel(root->left, k, level + 1);
    if (left == -1)
        return findLevel(root->right, k, level + 1);
    return left;
}
 
int findDistance(Node* root, int a, int b)
{
   
    Node* lca = LCA(root, a, b);
 
    int d1 = findLevel(lca, a, 0);
    int d2 = findLevel(lca, b, 0);
 
    return d1 + d2;
}


/*
Question 3
Write a program to convert a binary tree to a doubly linked list.
*/


#include <iostream>
using namespace std;
 
// Data structure to store a binary tree node
struct Node
{
    int data;
    Node *left, *right;
 
    Node(int data)
    {
        this->data = data;
        this->left = this->right = nullptr;
    }
};
void printDLL(Node* &head)
{
    Node* curr = head;
    while (curr != nullptr)
    {
        cout << curr->data << " ";
        curr = curr->right;
    }
}
void convert(Node* root, Node* &head)
{
    
    if (root == nullptr) {
        return;
    }
 
     
    convert(root->left, head);
    root->left = nullptr;
 

    Node* right = root->right;
 
  
    root->right = head;
    if (head != nullptr) {
        head->left = root;
    }
 
    head = root;
 
    
    convert(right, head);
}
void reverse(Node*& head)
{
    Node* prev = nullptr;
    Node* current = head;
 
    while (current)
    {
        swap(current->left, current->right);
        prev = current;
        current = current->left;
    }
 
    if (prev != nullptr) {
        head = prev;
    }
}
void convert(Node* root)
{
    Node* head = nullptr;
    convert(root, head);
    reverse(head);
    printDLL(head);
}


/*
<aside>
💡 Question-4:

Write a program to connect nodes at the same level.

</aside>
*/
class node
{
    public:
    int data;
    node* left;
    node* right;
    node *nextRight;

    node(int data)
    {
        this->data = data;
        this->left = NULL;
        this->right = NULL;
        this->nextRight = NULL;
    }
};
node *getNextRight(node *p)
{
    node *temp = p->nextRight;
    while (temp != NULL)
    {
        if (temp->left != NULL)
            return temp->left;
        if (temp->right != NULL)
            return temp->right;
        temp = temp->nextRight;
    }
    return NULL;
}
void connectRecur(node* p)
{
    node *temp;
 
    if (!p)
    return;
    p->nextRight = NULL;
    while (p != NULL)
    {
        node *q = p;
        while (q != NULL)
        {
            if (q->left)
            {
                if (q->right)
                    q->left->nextRight = q->right;
                else
                    q->left->nextRight = getNextRight(q);
            }
 
            if (q->right)
                q->right->nextRight = getNextRight(q);
            q = q->nextRight;
        }
        if (p->left)
            p = p->left;
        else if (p->right)
            p = p->right;
        else
            p = getNextRight(p);
    }
}