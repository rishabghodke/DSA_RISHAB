//Generate a c code using avl trees concept to perform following:
//1.Generate random numbers and store it in a file
//2.Read element by element and insert as a node
//3.deletion of a node
//(Insert and delete should follow rules of avl)
//4.display the tree structure
//for all these, inputs to be provided by the user.

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
    int height;
};

// Function to get the maximum of two integers
int max(int a, int b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}


// Function to get the height of a node
int getHeight(struct Node *node) {
    if (node == NULL)
        return 0;
    return node->height;
}

// Function to create a new AVL tree node
struct Node *createNode(int data) {
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

// Function to right rotate a subtree rooted with y
struct Node *rightRotate(struct Node *y) {
    struct Node *x = y->left;
    struct Node *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    // Return new root
    return x;
}

// Function to left rotate a subtree rooted with x
struct Node *leftRotate(struct Node *x) {
    struct Node *y = x->right;
    struct Node *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    // Return new root
    return y;
}

// Function to get the balance factor of a node
int getBalanceFactor(struct Node *node) {
    if (node == NULL)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

// Function to insert a node into the AVL tree
struct Node *insertNode(struct Node *node, int data) {
    // Perform the normal BST insertion
    if (node == NULL)
        return createNode(data);

    if (data < node->data)
        node->left = insertNode(node->left, data);
    else if (data > node->data)
        node->right = insertNode(node->right, data);
    else // Duplicate keys are not allowed
        return node;

    // Update the height of the ancestor node
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    // Get the balance factor of the ancestor node to check if it became unbalanced
    int balance = getBalanceFactor(node);

    // Left Left Case
    if (balance > 1 && data < node->left->data)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && data > node->right->data)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && data > node->left->data) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && data < node->right->data) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // Return the balanced node
    return node;
}

// Function to find the minimum value node in a given AVL tree
struct Node *findMinValueNode(struct Node *node) {
    struct Node *current = node;

    while (current->left != NULL)
        current = current->left;

    return current;
}

// Function to delete a node from the AVL tree
struct Node *deleteNode(struct Node *root, int data) {
    // Perform the normal BST delete
    if (root == NULL)
        return root;

    if (data < root->data)
        root->left = deleteNode(root->left, data);
    else if (data > root->data)
        root->right = deleteNode(root->right, data);
    else {
        // Node with only one child or no child
        if (root->left == NULL || root->right == NULL) {
            struct Node *temp = root->left ? root->left : root->right;

            // No child case
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else // One child case
                *root = *temp;

            free(temp);
        } else {
            // Node with two children
            struct Node *temp = findMinValueNode(root->right);

            // Copy the inorder successor's data to this node
            root->data = temp->data;

            // Delete the inorder successor
            root->right = deleteNode(root->right, temp->data);
        }
    }

    // If the tree had only one node, return
    if (root == NULL)
        return root;

    // Update the height of the current node
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    // Get the balance factor of the current node to check if it became unbalanced
    int balance = getBalanceFactor(root);

    // Left Left Case
    if (balance > 1 && getBalanceFactor(root->left) >= 0)
        return rightRotate(root);

    // Left Right Case
    if (balance > 1 && getBalanceFactor(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 && getBalanceFactor(root->right) <= 0)
        return leftRotate(root);

    // Right Left Case
    if (balance < -1 && getBalanceFactor(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    // Return the balanced node
    return root;
}

// Function to display the AVL tree using inorder traversal
void displayTree(struct Node *root) {
    if (root != NULL) {
        displayTree(root->left);
        printf("%d ", root->data);
        displayTree(root->right);
    }
}

int main() {
    struct Node *root = NULL;
    int choice, data;
    FILE *file;

    printf("1. Generate random numbers and store them in a file\n");
    printf("2. Read element by element and insert as a node\n");
    printf("3. Delete a node\n");
    printf("4. Display the tree structure\n");
    printf("0. Exit\n");

    while (1) {
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                file = fopen("numbers.txt", "w");
                if (file == NULL) {
                    printf("Error opening the file.\n");
                    return 1;
                }

                int numCount;
                printf("Enter the number of random numbers to generate: ");
                scanf("%d", &numCount);

                printf("Generated numbers: ");
                for (int i = 0; i < numCount; i++) {
                    int num = rand() % 100;  // Generate a random number between 0 and 99
                    printf("%d ", num);
                    fprintf(file, "%d\n", num);
                }

                fclose(file);
                printf("\nNumbers successfully stored in the file.\n");
                break;

            case 2:
                file = fopen("numbers.txt", "r");
                if (file == NULL) {
                    printf("Error opening the file.\n");
                    return 1;
                }

                while (fscanf(file, "%d", &data) != EOF)
                    root = insertNode(root, data);

                fclose(file);
                printf("Numbers successfully inserted as nodes in the AVL tree.\n");
                break;

            case 3:
                printf("Enter the node to delete: ");
                scanf("%d", &data);
                root = deleteNode(root, data);
                printf("Node successfully deleted from the AVL tree.\n");
                break;

            case 4:
                printf("Tree structure:\n");
                displayTree(root);
                printf("\n");
                break;

            case 0:
                printf("Exiting the program.\n");
                return 0;

            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }

    return 0;
}
