// Program by Danny, Mohammed, Amal, AnthonyR
// Much of BinaryTree code taken from zyBooks

//ALL OF PROGRAM IS FINISHED EXCEPT WRITING QUESTION TREE TO FILE
// YOU ARE AN ACTUAL LEGEND MY GUY -Mohammed

// This program demonstrates a decision tree for an animal guessing game.

#include <iostream>
#include <string>
#include <fstream>

#include "binary_tree.h"

int main()
{
  // INITIAL QUESTION TREE
  BinaryTree question_tree(
  "Is it a mammal?",
    BinaryTree("Does it have stripes?",
      BinaryTree("Is it a carnivore?",
        BinaryTree("Is it a tiger?"),
        BinaryTree("Is it a zebra?")),
      BinaryTree("Is it a pig?")),
    BinaryTree("Does it fly?",
      BinaryTree("Is it an eagle?"),
      BinaryTree("Does it swim?",
        BinaryTree("Is it a penguin?"),
        BinaryTree("Is it an ostrich?"))));
  // SAVE ROOT OF ENTIRE TREE
  BinaryTree head;
  head.read();
  // LOOP FOR REPEATING THE GUESSING GAME
  bool repeat = true;
  while (repeat)
  {
    // RESET QUESTION TREE BACK TO THE START
    question_tree = head;
    // LOOP FOR GUESSING GAME
    bool done = false;
    while (!done)
    {
      BinaryTree left = question_tree.left();
      BinaryTree right = question_tree.right();
      // IF LEFT OR RIGHT SUBTREE IS EMPTY (leaf node = last question)
      if (left.empty() && right.empty())
      {
        done = true; // end looping as this is the last question
        // Receive response from user
        std::string response;
        do
        {
          std::cout << question_tree.data() << " (y/n): ";
          std::cin >> response;
        } 
        while (response != "y" && response != "n");
        if (response == "y") // Animal has been guessed
        {
          // EXTRACTING ANIMAL NAME FROM THE LAST QUESTION TO BE DISPLAYED TO THE USER
          int i = question_tree.data().length() - 2; // last character of string, besides the '?'
          while (i != 0 && !isspace(question_tree.data()[i])) // while last space is not reached, count letters backwards
          { --i; }
          std::string animalname = question_tree.data().substr(i+1); // take last word from last question
          animalname.pop_back(); // remove question mark from string
          std::cout << "The animal has been guessed! The animal is " << animalname << std::endl;
          done = true;
        } 
        else // Animal has not been guessed, create new subtree
        {
          std::cout << "What animal was it? (Animal must exist, enter as single word): ";  
          std::string animal;
          std::cin >> animal;
          std::cout << "Please give a question that is true for the new animal but false for the last guessed animal: ";
          std::string question;
          std::cin.ignore();
          getline(std::cin, question);
          question_tree.create_subtree("Is it a " + animal + "?", question);
        }
      }
      // IF LEFT AND RIGHT SUBTREE ARE NOT EMPTY (Traverse through tree)
      else
      {
        // Receive response from user
        std::string response;
        do
        {
          std::cout << question_tree.data() << " (y/n): ";
          std::cin >> response;
        } 
        while (response != "y" && response != "n");
        
        if (response == "y") // if yes, traverse left subtree
        { question_tree = left; }
        else // if no, traverse right subtree
        { question_tree = right; }         
      }
    }
    // ASK USER FOR PROGRAM REPETITION
    std::cout << "Do you want to play the game again? (y/n): ";
    std::string input;
    std::cin >> input;
    if (input == "n" || input == "N")
    { repeat = false; }
  }
  head.save(); // saving file
  std::cout << "Thank you for playing our game!" << std::endl;
}
