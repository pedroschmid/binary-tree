#include <stdlib.h>
#include <stdio.h>

struct node
{
    int element;
    struct node *left;
    struct node *right;
};

typedef struct node Node;
typedef enum
{
    false,
    true
} Bool;

void FreeTree(Node *root);
void PrintPreOrder(Node *root);
void PrintInOrder(Node *root);
void PrintPostOrder(Node *root);
Node *FindMin(Node *root);
Bool FindNode(Node *root, int element);
Node *InsertNode(Node *root, int element);
Node *RemoveNode(Node *root, int element);

int main()
{
    Node *root = NULL;

    root = InsertNode(root, 10);
    root = InsertNode(root, 5);
    root = InsertNode(root, 15);
    root = InsertNode(root, 3);
    root = InsertNode(root, 7);
    root = InsertNode(root, 4);
    root = InsertNode(root, 55);
    root = InsertNode(root, 49);
    root = InsertNode(root, 28);
    root = InsertNode(root, 154);

    printf("\nTrying to find 54...");
    FindNode(root, 54);

    printf("\nTrying to find 28...");
    FindNode(root, 28);

    printf("\nRemoving 7...\n");
    RemoveNode(root, 7);

    printf("\nPre order: ");
    PrintPreOrder(root);

    printf("\nIn order: ");
    PrintInOrder(root);

    printf("\nPost order: ");
    PrintPostOrder(root);

    FreeTree(root);

    return 0;
};

void FreeTree(Node *root)
{
    if (root != NULL)
    {
        FreeTree(root->left);
        FreeTree(root->right);

        free(root);
    }
};

void PrintPreOrder(Node *root)
{
    if (root != NULL)
    {
        printf("%d, ", root->element);

        PrintPreOrder(root->left);
        PrintPreOrder(root->right);
    }
};

void PrintInOrder(Node *root)
{
    if (root != NULL)
    {
        PrintInOrder(root->left);

        printf("%d, ", root->element);

        PrintInOrder(root->right);
    }
};

void PrintPostOrder(Node *root)
{
    if (root != NULL)
    {
        PrintPostOrder(root->left);
        PrintPostOrder(root->right);

        printf("%d, ", root->element);
    }
};

Node *FindMin(Node *root)
{
    while (root->left != NULL)
        root = root->left;
    return root;
}

Bool FindNode(Node *root, int element)
{
    if (root == NULL)
    {
        printf("\nNot found =(\n");

        return false;
    }
    else
    {
        if (root->element == element)
        {
            printf("\nFound =)\n");

            return true;
        }

        if (element < root->element)
        {
            FindNode(root->left, element);
        }
        else
        {
            FindNode(root->right, element);
        }
    }
};

Node *InsertNode(Node *root, int element)
{
    if (root == NULL)
    {
        Node *newNode = (Node *)malloc(sizeof(Node));

        newNode->element = element;
        newNode->left = NULL;
        newNode->right = NULL;

        return newNode;
    }

    if (element < root->element)
    {
        root->left = InsertNode(root->left, element);
    }
    else
    {
        root->right = InsertNode(root->right, element);
    }

    return root;
};

Node *RemoveNode(Node *root, int element)
{
    if (root == NULL)
    {
        printf("\nElement not found =(\n");

        return root;
    }

    if (element < root->element)
    {
        root->left = RemoveNode(root->left, element);
    }
    else if (element > root->element)
    {
        root->right = RemoveNode(root->right, element);
    }
    else
    {
        if (root->left == NULL && root->right == NULL)
        {
            free(root);

            return NULL;
        }
        else if (root->left == NULL)
        {
            Node *temporaryNode = root->right;
            free(root);

            return temporaryNode;
        }
        else if (root->right == NULL)
        {
            Node *temporaryNode = root->left;
            free(root);

            return temporaryNode;
        }
        else
        {
            Node *temporaryNode = FindMin(root->right);

            root->element = temporaryNode->element;

            root->right = RemoveNode(root->right, temporaryNode->element);
        }
    }

    return root;
}
