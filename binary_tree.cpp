#include "binary_tree.h"
#include <algorithm>

BinaryTree::BinaryTree() { root = nullptr; }

BinaryTree::BinaryTree(std::string root_data) {
  root = new Node;
  root->data = root_data;
  root->left = nullptr;
  root->right = nullptr;
}

BinaryTree::BinaryTree(std::string root_data, BinaryTree left,
                       BinaryTree right) {
  root = new Node;
  root->data = root_data;
  root->left = left.root;
  root->right = right.root;
}



void BinaryTree::del_tree() {
  del_tree(this->root);
}

void BinaryTree::del_tree(Node *root) {
  if (root == nullptr) {
      return ;
  }
  else {
      Node* del = root;
      Node* left = root->left;
      Node* right = root->right;
      delete del;
      del_tree(left);
      del_tree(right);
  }
}



int BinaryTree::height(const Node *n) const {
  if (n == nullptr) {
    return 0;
  } else {
    return 1 + std::max(height(n->left), height(n->right));
  }
}

int BinaryTree::height() const { return height(root); }

bool BinaryTree::empty() const { return root == nullptr; }

std::string BinaryTree::data() const { return root->data; }

BinaryTree* BinaryTree::left() const {
  BinaryTree* result = new BinaryTree;
  result->root = this->root->left;
  return result;
}

BinaryTree* BinaryTree::right() const {
  BinaryTree* result = new BinaryTree;
  result->root = this->root->right;
  return result;
}

void BinaryTree::create_subtree(std::string new_animal, std::string question) {
  BinaryTree right(root->data); // Create new right subtree with question that
                                // is currently held within this node
  BinaryTree left(new_animal);  // Create new left subtree with new question
                                // asking if it is the new animal
  root->right = right.root;     // point right pointer to right subtree
  root->left = left.root;       // point left pointer to left subtree
  root->data = question; // set the question within this node to a new question
}

void BinaryTree::save() const {
  std::ofstream file("questions.txt");
  save(root, file);
}

void BinaryTree::save(Node *parent, std::ofstream &file) const {
  if (parent == nullptr) {
    file << "NULL" << std::endl;
    return;
  }
  
  file << parent->data << std::endl;
  save(parent->left, file);
  save(parent->right, file);
}

void BinaryTree::read() {
  std::ifstream file("questions.txt");
  read(root, file);
}

/**
  * Reads the questions from the file and constructs the tree
  * Note to team: was segfaulting earlier, changed the function slightly
  * both read functions originally const, had to change to non-const
  * parent node changed to pass by reference
  * also when doing y/n, don't use capital Y/N
*/
void BinaryTree::read(Node *&parent, std::ifstream &file) {
  std::string question;
  getline(file, question);
  if (question == "NULL") {
    return;
  }
  if (parent == nullptr) {
    parent = new Node;
  }
  parent->data = question;
  read(parent->left, file);
  read(parent->right, file);
}