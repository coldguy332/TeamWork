#include <iostream>
#include <fstream>

using namespace std;

// Define the binary tree node structure
struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

// Function to perform preorder traversal and save the data to a text file
void savePreorder(TreeNode* root, ofstream& outFile) {
    if (root == nullptr) {
        outFile << "null ";  // Use a marker for null nodes
        return;
    }

    outFile << root->data << " ";
    savePreorder(root->left, outFile);
    savePreorder(root->right, outFile);
}

// Function to read data from a text file and reconstruct the binary tree
TreeNode* buildTree(ifstream& inFile) {
    string val;
    inFile >> val;

    if (val == "null") {
        return nullptr;
    }

    int data = stoi(val);
    TreeNode* root = new TreeNode(data);

    root->left = buildTree(inFile);
    root->right = buildTree(inFile);

    return root;
}

// Function to save a binary tree to a text file
void saveBinaryTreeToFile(TreeNode* root, const char* filename) {
    ofstream outFile(filename);
    if (!outFile.is_open()) {
        cerr << "Error opening file." << endl;
        return;
    }

    savePreorder(root, outFile);

    outFile.close();
}

// Function to read a binary tree from a text file
TreeNode* readBinaryTreeFromFile(const char* filename) {
    ifstream inFile(filename);
    if (!inFile.is_open()) {
        cerr << "Error opening file." << endl;
        return nullptr;
    }

    TreeNode* root = buildTree(inFile);

    inFile.close();

    return root;
}

int main() {
    // Example: Creating a binary tree
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);

    // Save the binary tree to a text file
    saveBinaryTreeToFile(root, "binary_tree.txt");

    // Read the binary tree from the text file
    TreeNode* reconstructedRoot = readBinaryTreeFromFile("binary_tree.txt");

    // Now, 'reconstructedRoot' should point to the reconstructed binary tree.

    // Clean up memory (not necessary in this simple example, but important in a real program)
    // ...

    return 0;
}
