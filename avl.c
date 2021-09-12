#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    int height;
    struct node *left;
    struct node *right;
};

typedef struct node AVLTREE;

int max(int a, int b);

int height(AVLTREE *root)
{
    if (root == NULL)
        return -1;
    else
    {
        int lheight, rheight;
        rheight = (height(root->right));
        lheight = (height(root->left));
        if (rheight > lheight)
            return rheight + 1;
        else
            return lheight + 1;
    }
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}


AVLTREE *new_node(int data)
{
    AVLTREE *root = (AVLTREE *) malloc(sizeof(AVLTREE));
    root->data = data;
    root->left = NULL;
    root->right = NULL;
    root->height = 1;
    return (root);
}

AVLTREE *rightRotate(AVLTREE *y)
{
    AVLTREE *x = y->left;
    AVLTREE *z = x->right;

    x->right = y;
    y->left = z;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

AVLTREE *leftRotate(AVLTREE *x)
{
    AVLTREE *y = x->right;
    AVLTREE *z = y->left;
    y->left = x;
    x->right = z;
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    return y;
}

int balance_tree(AVLTREE *b)
{
    if (b == NULL)
        return 0;
    return height(b->left) - height(b->right);
}

AVLTREE *insert(AVLTREE *root, int data)
{
    if (root == NULL)
        return (new_node(data));
    if (data < root->data)
        root->left = insert(root->left, data);
    else if (data > root->data)
        root->right = insert(root->right, data);
    else
        return root;

    root->height = 1 + max(height(root->left), height(root->right));
    int balance = balance_tree(root);

    if (balance > 1 && data < root->left->data)
        return rightRotate(root);

    if (balance < -1 && data > root->right->data)
        return leftRotate(root);

    if (balance > 1 && data > root->left->data)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && data < root->right->data)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

void inorder(AVLTREE *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

int size (AVLTREE *root) {
    if (root == NULL)
        return 0;
    else
        return 1+size(root->left)+size(root->right);
}

int edge(AVLTREE *root)
{
    if (root == NULL)
        return 0;
    else
        return size(root->left) + size(root->right);
}

int leaves (AVLTREE *root) {
    if (root == NULL)
        return 0;
    if (root->left == root->right)
        return 1;
    else
        return leaves(root->left)+leaves(root->right);
}


int main() {
    AVLTREE *customroot = NULL;
    int i = 0;
    printf("\nPlease enter numbers to add data to the tree.\n");
    do {
        scanf("%d", &i);
        if (i != -1)
            customroot = insert(customroot, i);
    } while (i != -1);
    if (customroot != NULL) {
        printf("Inorder value: ");
        inorder(customroot);
        printf("\n");
        printf("Tree size: ");
        printf("%d", size(customroot));
        printf("\n");
        printf("Edge size: ");
        printf("%d", edge(customroot));
        printf("\n");
        printf("Number of leaves: ");
        printf("%d", leaves(customroot));
        printf("\n");
        printf("Height = %d", height(customroot));
        printf("\n");
    }
    getchar();
    return 0;
}
