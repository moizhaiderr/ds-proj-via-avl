#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

// AVL Node structure
template <typename T>
struct AVLNode
{
    int key;
    T productName;
    int quantity;
    AVLNode *left;
    AVLNode *right;
    int height;
};

// Function to get the height of a node
template <typename T>
int getHeight(AVLNode<T> *node)
{
    if (node == NULL)
        return 0;
    return node->height;
}

// Function to get the balance factor of a node
template <typename T>
int getBalance(AVLNode<T> *node)
{
    if (node == NULL)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

// Function to create a new AVL node
template <typename T>
AVLNode<T> *createNode(int key, T productName, int quantity)
{
    AVLNode<T> *newNode = new AVLNode<T>;
    newNode->key = key;
    newNode->productName = productName;
    newNode->quantity = quantity;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1;
    return newNode;
}

// Function to perform right rotation
template <typename T>
AVLNode<T> *rightRotate(AVLNode<T> *y)
{
    AVLNode<T> *x = y->left;
    AVLNode<T> *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = 1 + max(getHeight(y->left), getHeight(y->right));
    x->height = 1 + max(getHeight(x->left), getHeight(x->right));

    return x;
}

// Function to perform left rotation
template <typename T>
AVLNode<T> *leftRotate(AVLNode<T> *x)
{
    AVLNode<T> *y = x->right;
    AVLNode<T> *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = 1 + max(getHeight(x->left), getHeight(x->right));
    y->height = 1 + max(getHeight(y->left), getHeight(y->right));

    return y;
}

// Function to insert a key into the AVL tree
template <typename T>
AVLNode<T> *insertNode(AVLNode<T> *root, int key, T productName, int quantity)
{
    // Perform standard BST insertion
    if (root == NULL)
        return createNode(key, productName, quantity);

    if (key < root->key)
        root->left = insertNode(root->left, key, productName, quantity);
    else if (key > root->key)
        root->right = insertNode(root->right, key, productName, quantity);
    else
        return root; // Duplicate keys are not allowed

    // Update height of the current node
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    // Get the balance factor to check if the node became unbalanced
    int balance = getBalance(root);

    // Left Left Case
    if (balance > 1 && key < root->left->key)
        return rightRotate(root);

    // Right Right Case
    if (balance < -1 && key > root->right->key)
        return leftRotate(root);

    // Left Right Case
    if (balance > 1 && key > root->left->key)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Left Case
    if (balance < -1 && key < root->right->key)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Function to find the node with the minimum key value
template <typename T>
AVLNode<T> *findMinNode(AVLNode<T> *root)
{
    AVLNode<T> *current = root;
    while (current->left != NULL)
        current = current->left;
    return current;
}

// Function to delete a node with a given key from the AVL tree
template <typename T>
AVLNode<T> *deleteNode(AVLNode<T> *root, int key)
{
    if (root == NULL)
        return root;

    // Perform standard BST delete
    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else
    {
        // Node with only one child or no child
        if (root->left == NULL || root->right == NULL)
        {
            AVLNode<T> *temp = root->left ? root->left : root->right;

            // No child case
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else // One child case
                *root = *temp;

            delete temp;
        }
        else
        {
            // Node with two children, get the inorder successor
            AVLNode<T> *temp = findMinNode(root->right);

            // Copy the inorder successor's data to this node
            root->key = temp->key;
            root->productName = temp->productName;
            root->quantity = temp->quantity;

            // Delete the inorder successor
            root->right = deleteNode(root->right, temp->key);
        }
    }

    // If the tree had only one node, then return
    if (root == NULL)
        return root;

    // Update height of the current node
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    // Get the balance factor to check if the node became unbalanced
    int balance = getBalance(root);

    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Function to print AVL tree in-order
template <typename T>
void inOrderTraversal(AVLNode<T> *root)
{
    if (root != NULL)
    {
        inOrderTraversal(root->left);
        cout << "Product ID: " << root->key << ", Name: " << root->productName << ", Quantity: " << root->quantity << endl;
        inOrderTraversal(root->right);
    }
}

// Function to search for a product by its key
template <typename T>
AVLNode<T> *searchProduct(AVLNode<T> *root, int key)
{
    if (root == NULL || root->key == key)
        return root;

    if (key < root->key)
        return searchProduct(root->left, key);

    return searchProduct(root->right, key);
}

// Function to display the menu and get user input
char displayMenu()
{
    cout << "\nMenu:\n";
    cout << "1. Add Product\n";
    cout << "2. Update Product Quantity\n";
    cout << "3. Delete Product\n";
    cout << "4. Display Inventory\n";
    cout << "5. Search for a Product\n";
    cout << "6. Exit\n";
    cout << "Enter your choice: ";

    char choice;
    cin >> choice;
    return choice;
}

int main()
{
    AVLNode<string> *root = NULL;

    char choice;
    do
    {
        choice = displayMenu();

        switch (choice)
        {
        case '1':
        {
            int productId, quantity;
            string productName;
            cout << "Enter Product ID: ";
            cin >> productId;
            cout << "Enter Product Name: ";
            cin.ignore();
            getline(cin, productName);
            cout << "Enter Quantity: ";
            cin >> quantity;

            root = insertNode(root, productId, productName, quantity);
            cout << "Product added successfully.\n";
            break;
        }
        case '2':
        {
            int productId, newQuantity;
            cout << "Enter Product ID to update quantity: ";
            cin >> productId;

            AVLNode<string> *productNode = searchProduct(root, productId);
            if (productNode != NULL)
            {
                cout << "Enter new quantity: ";
                cin >> newQuantity;
                productNode->quantity = newQuantity;
                cout << "Quantity updated successfully.\n";
            }
            else
            {
                cout << "Product not found.\n";
            }
            break;
        }
        case '3':
        {
            int productId;
            cout << "Enter Product ID to delete: ";
            cin >> productId;

            root = deleteNode(root, productId);
            cout << "Product deleted successfully.\n";
            break;
        }
        case '4':
        {
            cout << "Inventory:\n";
            inOrderTraversal(root);
            break;
        }
        case '5':
        {
            int productId;
            cout << "Enter Product ID to search: ";
            cin >> productId;

            AVLNode<string> *productNode = searchProduct(root, productId);
            if (productNode != NULL)
            {
                cout << "Product found - ";
                cout << "Product ID: " << productNode->key << ", Name: " << productNode->productName << ", Quantity: " << productNode->quantity << endl;
            }
            else
            {
                cout << "Product not found.\n";
            }
            break;
        }
        case '6':
            cout << "Exiting program.\n";
            break;
        default:
            cout << "Invalid choice. Please enter a valid option.\n";
        }
    } while (choice != '6');

    return 0;
}
