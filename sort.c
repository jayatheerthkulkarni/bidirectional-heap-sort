#include <stdio.h>
#include <stdlib.h>

// AVL Tree node
typedef struct AVLNode {
    int key;
    struct AVLNode *left, *right;
    int height;
} AVLNode;

// Function to get the height of the tree
int height(AVLNode *N) {
    return N ? N->height : 0;
}

// Function to create a new AVL node
AVLNode* newNode(int key) {
    AVLNode* node = (AVLNode*)malloc(sizeof(AVLNode));
    node->key   = key;
    node->left  = NULL;
    node->right = NULL;
    node->height = 1;  // New node is initially at leaf
    return(node);
}

// Right rotate
AVLNode *rightRotate(AVLNode *y) {
    AVLNode *x = y->left;
    AVLNode *T2 = x->right;
    // Perform rotation
    x->right = y;
    y->left = T2;
    // Update heights
    y->height = 1 + (height(y->left) > height(y->right) ? height(y->left) : height(y->right));
    x->height = 1 + (height(x->left) > height(x->right) ? height(x->left) : height(x->right));
    // Return new root
    return x;
}

// Left rotate
AVLNode *leftRotate(AVLNode *x) {
    AVLNode *y = x->right;
    AVLNode *T2 = y->left;
    // Perform rotation
    y->left = x;
    x->right = T2;
    // Update heights
    x->height = 1 + (height(x->left) > height(x->right) ? height(x->left) : height(x->right));
    y->height = 1 + (height(y->left) > height(y->right) ? height(y->left) : height(y->right));
    // Return new root
    return y;
}

// Get balance factor
int getBalance(AVLNode *N) {
    return N ? height(N->left) - height(N->right) : 0;
}

// Insert a key into the AVL tree
AVLNode* insert(AVLNode* node, int key) {
    if (!node)
        return(newNode(key));
    if (key < node->key)
        node->left  = insert(node->left, key);
    else
        node->right = insert(node->right, key);
    // Update height
    node->height = 1 + (height(node->left) > height(node->right) ? height(node->left) : height(node->right));
    // Get balance factor
    int balance = getBalance(node);
    // Left Left Case
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);
    // Right Right Case
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);
    // Left Right Case
    if (balance > 1 && key > node->left->key) {
        node->left =  leftRotate(node->left);
        return rightRotate(node);
    }
    // Right Left Case
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

// Find the node with minimum key value
AVLNode *minValueNode(AVLNode* node) {
    AVLNode* current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

// Find the node with maximum key value
AVLNode *maxValueNode(AVLNode* node) {
    AVLNode* current = node;
    while (current->right != NULL)
        current = current->right;
    return current;
}

// Delete a node from the AVL tree
AVLNode* deleteNode(AVLNode* root, int key) {
    if (!root)
        return root;
    if ( key < root->key )
        root->left = deleteNode(root->left, key);
    else if( key > root->key )
        root->right = deleteNode(root->right, key);
    else {
        if( (root->left == NULL) || (root->right == NULL) ) {
            AVLNode *temp = root->left ? root->left : root->right;
            if (!temp) {
                temp = root;
                root = NULL;
            }
            else
             *root = *temp; // Copy the contents of the non-empty child
            free(temp);
        }
        else {
            AVLNode* temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
    }
    if (!root)
      return root;
    // Update height
    root->height = 1 + (height(root->left) > height(root->right) ? height(root->left) : height(root->right));
    // Get balance factor
    int balance = getBalance(root);
    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);
    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left =  leftRotate(root->left);
        return rightRotate(root);
    }
    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);
    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

// Custom sort function using AVL tree
void customSort(int arr[], int n) {
    AVLNode* root = NULL;
    for (int i = 0; i < n; i++)
        root = insert(root, arr[i]);

    int start = 0, end = n - 1;
    while (start <= end) {
        // Find and remove the smallest element
        AVLNode* minNode = minValueNode(root);
        arr[start++] = minNode->key;
        root = deleteNode(root, minNode->key);

        if (start > end)
            break;

        // Find and remove the largest element
        AVLNode* maxNode = maxValueNode(root);
        arr[end--] = maxNode->key;
        root = deleteNode(root, maxNode->key);
    }
}

// Main function remains the same
int main() {
    int n;
    printf("Enter the size of the array: ");
    scanf("%d", &n);
    int arr[n];

    printf("Enter the elements of the array: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    customSort(arr, n);

    printf("Sorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}
