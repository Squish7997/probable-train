// ProjectTwoAssignment.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <filesystem>

using namespace std;

int main()
{

    while (true) {
        displayMenu();
    }
    return 0;
}


// define a structure to hold bid information
struct Course {
    string courseID; // unique identifier
    string courseName;
    vector<string> prerequisites;
};


// Internal structure for tree node
struct Node {
    Course course;
    Node* left;
    Node* right;

    // default constructor
    Node() {
        left = nullptr;
        right = nullptr;
    }

    // initialize with a bid
    Node(Course courseID) :
        Node() {
        course = courseID;
    }
};

//============================================================================
// Binary Search Tree class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a binary search tree
 */
class BinarySearchTree {

private:
    Node* root;

    void addNode(Node* node, Course course);
    void inOrder(Node* node);
    void postOrder(Node* node);
    void preOrder(Node* node);
    Node* removeNode(Node* node, string courseID);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void InOrder();
    void PostOrder();
    void PreOrder();
    void Insert(Course course);
    void Remove(string courseID);
    Course Search(string courseID);
};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
    // FixMe (1): initialize housekeeping variables
    //root is equal to nullptr
    root = nullptr;

}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {
    //FixMe (2)
    // recurse from root deleting every node
    while (root != nullptr) {
        removeNode(root, root->course.courseID);
    }
}

/**
 * Traverse the tree in order
 */
void BinarySearchTree::InOrder() {
    // FixMe (3a): In order root
    // call inOrder fuction and pass root 
    inOrder(root);
}

/**
 * Traverse the tree in post-order
 */
void BinarySearchTree::PostOrder() {
    // FixMe (4a): Post order root
    // postOrder root
    postOrder(root);

}

/**
 * Traverse the tree in pre-order
 */
void BinarySearchTree::PreOrder() {
    // FixMe (5a): Pre order root
    // preOrder root
    preOrder(root);
}





/**
 * Insert a bid
 */
void BinarySearchTree::Insert(Course course) {
    // FIXME (6a) Implement inserting a bid into the tree
    // if root equarl to null ptr
      // root is equal to new node
    // else
      // add Node root
    Node* current = root;

    //If root is empty, inserts bid at root index
    if (root == nullptr) {
        root = new Node(course);
        return;
    }
    else {
        //adds a new node and inserts into bst
        addNode(new Node(course),course);
    }
}

/**
 * Remove a bid
 */
void BinarySearchTree::Remove(string courseID) {
    // FIXME (7a) Implement removing a bid from the tree
    // remove node root bidID
    removeNode(root, courseID);
    
    
}

/**
 * Search for a bid
 */
Course BinarySearchTree::Search(string courseID) {
    // FIXME (8) Implement searching the tree for a bid
    // set current node equal to root
    Node* current = root;

    // keep looping downwards until bottom reached or matching bidId found
    while (current != NULL) {
        // if match found, return current bid
        if (current->course.courseID == courseID) {
            return current->course;
        }
        // if bid is smaller than current node then traverse left
        if (courseID < current->course.courseID) {
            current = current->left;
        }
        // else larger so traverse right
        else {
            current = current->right;
        }
    }
    //sends empty course if not found
    return {};
}

/**
 * Add a bid to some node (recursive)
 *
 * @param node Current node in tree
 * @param bid Bid to be added
 */
void BinarySearchTree::addNode(Node* node, Course course) {
    // FIXME (6b) Implement inserting a bid into the tree
    // if node is larger then add to left
    if (course.courseID < node->course.courseID)
        // if no left node
        if (node->left == nullptr) {
            node->left = new Node(course);
        }
    // this node becomes left
// else recurse down the left node
        else {
            addNode(node->left, course);
        }
    // else
    else {
        //if no right child exists
        if (node->right == nullptr) {
            //inserts bid into right child index
            node->right = new Node(course);
        }
        else {
            //recurses right side
            addNode(node->right, course);
        }
    }
}
void BinarySearchTree::inOrder(Node* node) {
    //if node has nullptr
    if (node == nullptr) {
        return;
    }

    //if node is not equal to null ptr
    else {
        //traverses left subtress
        inOrder(node->left);

        //prints bid data(ID, TITLE, AMOUNT, FUND)
        cout << "Course ID: " << node->course.courseID << "\n"
            << "Course Name: " << node->course.courseName << "\n";
        for (string prerequisites : node->course.prerequisites) {
            cout << prerequisites << " ";
        }

        //travers right subtree
        inOrder(node->right);
    }

}
void BinarySearchTree::postOrder(Node* node) {
    //if node hass nullptr
    if (node == nullptr) {
        return;        
    }

    //traverses through right child nodes if not null
    postOrder(node->right);

    //prints node information
    cout << "Course ID: " << node->course.courseID << "\n"
        << "Course Name: " << node->course.courseName << "\n";

    /*
    * checks if prerequisite vector is empty, 
    * if false, not empty, prerequisite information is printed
    */
    if (!node->course.prerequisites.empty()) {
        //illerates through prerequisites vector
        for (string prerequisite : node->course.prerequisites) {
            cout << prerequisite << " ";
        }
    }
    
    //traverses through left children nodes
    postOrder(node->left);

}

void BinarySearchTree::preOrder(Node* node) {
    if (node == nullptr) {
        return;
    }
    //if node is not equal to null ptr prints out bid information
    cout << "Course ID: " << node->course.courseID << "\n"
        << "Course Name: " << node->course.courseName << "\n";

    /*
    * Checks if the prerequiste vector is empty, 
    * if false, not empty, prerequisite information is printed.
    */
    if (!node->course.prerequisites.empty()) {
        
        //illerates through prerequisites vector
        for (string prerequisite : node->course.prerequisites) {
            cout << prerequisite << " ";
        }
    }

    // traverses through left subtree of children
    preOrder(node->left);

    //traveses through right subtree of children
    preOrder(node->right);
}

/**
 * Remove a bid from some node (recursive)
 */
Node* BinarySearchTree::removeNode(Node* node, string courseID) {
    //Figure 6.6.1: BST remove algorithm ZYBOOKS CS 300: Data Structures and Algortihtms
    
    while (node != nullptr) {

        //if node is found
        if (node->course.courseID == courseID) {

            //check to see if there is no children
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                return nullptr;
            }

            //if node has left child ONLY
            else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            //if node has right child only
            else if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            }

            //if node has two children
            else {
                Node* successorNode = node->right;

                while (successorNode->left != nullptr) {
                    successorNode = successorNode->left;
                }
                //replaces node's data with successor node's data.
                node->course = successorNode->course;

                //remove the successor node
                removeNode(successorNode, successorNode->course.courseID);

                return node;
            }
        }

        //if node is not found
        else {
            
            //checks left children
            if (node->course.courseID > courseID) {
                removeNode(node->left, node->left->course.courseID);
            }

            //checks right children
            else {
                removeNode(node->right, node->right->course.courseID);
            }

        }
    }
}
    // check for match and if so, remove left node using recursive call 
    // (otherwise recurse down the right subtree)
    // check for match and if so, remove right node using recursive call
    // (otherwise no children so node is a leaf node)
    // if left node = nullptr && right node = nullptr delete node 
    // (otherwise check one child to the left)
    // if left node != nullptr && right node = nullptr delete node 
    // (otherwise check one child to the right)
    // if left node = nullptr && right node != nullptr delete node
    // (otherwise more than one child so find the minimum)
    // create temp node to right
    // while left node is not nullptr keep moving temp left
    // make node bid (right) equal to temp bid (left)
    // remove right node using recursive call
    // return node

//BST COMPLETE, OPEN AND READ THE FILE FUNCTION
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//creates a binary searchtree (bst = binary search tree)
    BinarySearchTree bst;
/*
Opens the file and reads the file as input,
creates newCourse with input and inserts course
into the binary search tree
*/
void openReadFile(string fileName) {
    ifstream file(fileName);
    
    //if the file did not open
    if (!file.is_open()) {
        //prints out error message and returns
        cerr << "Error: File did not open.\n";
        return;
    }
    //declares a line for file input
    string line;

    //reads file as input
    while (getline(file, line)) {

        //allows a string input
        stringstream fileData(line);
        string courseID, courseName, prerequisite;
        vector<string> prerequisites;

        //checks to see if there is a ID
        if (!getline(fileData, courseID, ',')) {
            //prints out error message if id exists
            cerr << "Error: No ID.\n" << endl;
            continue;
        }
        //checks to see if there is a name
        if (!getline(fileData, courseName)) {
            //prints out error message if no name exists.
            cerr << "Error: No Name.\n" << endl;
            continue;
        }

        //intakes one or more prerequisites if any exist.
        while (getline(fileData, prerequisite, ',')) {
            prerequisites.push_back(prerequisite);
        }

        //creates a new course with course information from input file.
        Course newCourse = { courseID, courseName, prerequisites };

        //inserts newCourse into the binary search tree.
        bst.Insert(newCourse);

    }

    file.close();
}

// gets the file input
void getFileName() {
    string fileName;

    //gets user input on file
    cout << "Enter the file you want to open: \n";
    cin >> fileName;

    //opens and reads file
    openReadFile(fileName);

    return;
}
void menuOption() {
    //get user input on menu option and do functions
    int menuOption;
    cin >> menuOption;
    


    switch (menuOption) {
    case 1:
        getFileName();
        fileOpened = true;
        break;

    case 2:
        if (!fileOpened) {
            getFileName();
            fileOpened = true;
        }
        bst.InOrder();
        break;
    case 3:
        if (!fileOpened) {
            getFileName();
            bst.PreOrder();
            break;
        }
    case 9:
        exit(0);
    }

    return;
}
void displayMenu() {
    //print out menu display
    cout << "Welcome to the course planner.\n";
    cout << "1. Load Data Structure.\n";
    cout << "2. Print Course list.\n";
    cout << "3. Print Course.\n";
    cout << "9. Exit Program.\n";

    menuOption();
}

//keeps track if file has been opened
bool fileOpened = false;

