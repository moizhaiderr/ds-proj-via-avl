# Data-Structure-Project-via-avl-Tree
PROJECT: - Inventory Management System


DOCUMENTATION


Overview:
The code implements an inventory management system using an AVL (Adelson-Velsky and Landis) tree data structure. The system allows users to perform various operations such as adding, updating, and deleting products in the inventory. The inventory is stored in an AVL tree, ensuring that the tree remains balanced for efficient searching, insertion, and deletion operations.

Components:

AVLNode Structure:

Represents a node in the AVL tree.
Contains information about the product, including key (Product ID), product name, quantity, left and right child pointers, and the height of the node in the tree.
Height, Balance, and Rotation Functions:

getHeight: 
Calculates the height of a given node in the AVL tree.
getBalance:
 Calculates the balance factor of a given node.
createNode:
 Creates a new AVL node with the provided key, product name, and quantity.

rightRotate and leftRotate: 
Perform right and left rotations, respectively, to maintain the balance of the AVL tree during insertion and deletion.

Insertion and Deletion Functions:

insertNode:
 Inserts a new product node into the AVL tree while maintaining balance.

deleteNode:
 Deletes a product node with a given key from the AVL tree while ensuring the tree remains balanced.
Traversal Functions:

inOrderTraversal: 
Performs an in-order traversal of the AVL tree, printing product information in sorted order based on the Product ID.

Search Function:

searchProduct: 
Searches for a product node with a given key in the AVL tree.
Menu and User Interface:

displayMenu: 
Displays a simple menu for users to choose operations.
The main function contains the main program logic, utilizing the AVL tree functions to manage the inventory based on user input.
Operations:

1)Add Product 
Takes input for Product ID, name, and quantity.
Inserts a new product node into the AVL tree.
2)Update Product Quantity 
Takes input for Product ID and the new quantity.
Searches for the product and updates its quantity.
3)Delete Product 
Takes input for Product ID.
Deletes the product node with the specified ID from the AVL tree.
4)Display Inventory 
Prints the inventory in sorted order (based on Product ID) using in-order traversal.
5)Search for a Product
Takes input for Product ID.
Searches for the product and prints its information if found.
6)Exit 
Exits the program.

Usage:
Users can interact with the system through the console menu.
Products are managed and stored in the AVL tree, ensuring efficient searching and maintenance of balance.

Notes:
The AVL tree structure helps in maintaining a balanced tree, optimizing search, insertion, and deletion operations.
The code uses templates to allow storing products with different data types for the product name.
Conclusion:

The provided C++ code offers a simple and efficient inventory management system utilizing AVL trees, providing a balanced and organized data structure for product storage and retrieval. 

