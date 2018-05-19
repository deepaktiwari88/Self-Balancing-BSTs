#include<bits/stdc++.h>

using namespace std;

struct node                 // Structure of a node
{
    int data;
    node* left;
    node* right;
    int height;
};

class AVL_Tree              // Class implementing AVL Tree
{
    public:

    node* root;

    AVL_Tree()              // Constructor
    {
        root = NULL;
    }

    int height(node* root)      // Method returning height of a node
    {
        if(root==NULL)
            return 0;
        else
            return root->height;
    }

    int balance_factor(node* root)         // Method calculating balance factor
    {
        if(root==NULL)
            return 0;

        return (height(root->left) - height(root->right));
    }

    node* getnode(int value)                // Creation of new node
    {
        node* temp = new node;
        temp->data = value;
        temp->left = NULL;
        temp->right = NULL;
        temp->height = 1;

        return temp;
    }

    node* rightRotate(node* root)                 // Right Rotation
    {
        node* leftchild = root->left;               // Left child of current node
        node* left_right = leftchild->right;        // Right child of left child of current node

        leftchild->right = root;                    // Make current node the right child of leftchild
        root->left = left_right;                    // Make left_right the left child of root

        root->height = 1+max(height(root->left), height(root->right));                          // Find new height of both nodes
        leftchild->height = 1+max(height(leftchild->left), height(leftchild->right));

        return leftchild;                   // Return new root
    }

    node* leftRotate(node* root)            // Left Rotation
    {
        node* rightchild = root->right;             // Right child of current node
        node* right_left = rightchild->left;        // Left child of right child of current node

        rightchild->left = root;                    // Make current node the left child of rightchild
        root->right = right_left;                   // Make right_left th right child of root

        root->height = 1+max(height(root->left), height(root->right));                          // Find new height of both nodes
        rightchild->height = 1+max(height(rightchild->left), height(rightchild->right));

        return rightchild;                  // Return new root
    }

    node* insert(node* root, int value)        // Recursive Insert
    {
        if(root==NULL)
            return getnode(value);

        if(value==root->data)
            return root;

        if(value < root->data)
            root->left = insert(root->left, value);
        else
            root->right = insert(root->right, value);

        root->height = 1 + max(height(root->left), height(root->right));

        int balance = balance_factor(root);

        if((balance > 1) && (value < root->left->data))             // Case 1 : Left Left
            return rightRotate(root);

        if((balance > 1) && (value > root->left->data)){            // Case 2 : Left Right
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        if((balance < -1) && (value > root->right->data))             // Case 3 : Right Right
            return leftRotate(root);

        if((balance < -1) && (value < root->right->data)){            // Case 4 : Right Left
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;                // Return current root
    }


    int findheight(node* root, int value)       // Finding height of any node (Search Operation)
    {
        if(root==NULL)
            return -1;

        if(value==root->data)
            return root->height;

        if(value > root->data)
            return findheight(root->right, value);
        else
            return findheight(root->left, value);
    }
};

int main()
{
    AVL_Tree tree1;         // AVL_Tree Object

    int choice,value;

    while(1)
    {
        cout<<"1. Insert.\n2. Find Height.\n3. Exit.\n---------------------------\n";

        cin>>choice;

        if(choice==1)
        {
            cout<<"Enter value.\n"<<endl;
            cin>>value;

            tree1.root = tree1.insert(tree1.root, value);
        }

        if(choice==2)
        {
            cout<<"Enter value.\n"<<endl;
            cin>>value;

            value = tree1.findheight(tree1.root, value);

            if(value==-1)
                cout<<"Value doesn't exist\n"<<endl;
            else
                cout<<"Height "<<value<<endl<<endl;

        }

        if(choice==3)
            break;
    }
}
