#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <iostream>
#include <string>
#include <fstream>

class Node
{
  private:
  std::string data;
  Node* left;
  Node* right;
  friend class BinaryTree;
};

// A binary tree in which each node has two children
class BinaryTree
{
  public:
  BinaryTree(); // Constructs an empty tree
  BinaryTree(std::string root_data); // Constructs a tree with one node and no children
  BinaryTree(std::string root_data, BinaryTree left, BinaryTree right); // Constructs a binary tree
  //~BinaryTree(); //destructor
  //void del_tree(Node* root);
  int height() const; // Returns the height of this tree
  bool empty() const; // Checks whether this tree is empty
  std::string data() const; // Gets the data at the root of this tree
  BinaryTree left() const; // Gets the left subtree of this tree
  BinaryTree right() const; // Gets the right subtree of this tree
  void create_subtree(std::string new_animal, std::string question); // Creates new question branch
  void save() const;
  void save(Node* root, std::ofstream& file) const;
  void read() ;
  void read(Node*& parent, std::ifstream& file);
  
  private:
  int height(const Node* n) const; // Returns the height of the subtree whose root is the given node
  Node* root;
};

#endif
