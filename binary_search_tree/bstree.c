#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bstree.h"

void error(void) {
  puts("\tCannot Allocate Memory for Node");
  exit(0);
}

void insert(tn ** root, int indx, char * name, float ratio) {
  tn * tree1, * tree2; // temporary trees to traverse the tree back and forth

  if ( * root == NULL) { // empty tree so new node will be root
    * root = (tn * ) malloc(sizeof(tn));

    if ( * root == NULL)
      error();

    // populate tree
    ( * root) -> indx = indx;
    ( * root) -> ratio = ratio;
    ( * root) -> name = strdup(name);
    ( * root) -> left = ( * root) -> right = NULL; // empty children

    // non-empty tree
  } else {
    tree1 = * root; // asigning root to another value to keep track of it

    /* traverse the tree to get the pointer of the parent of the (new child) */
    while (tree1 != NULL) { // loop until the node has no children
      tree2 = tree1; // to keep track of parent node while traversing to child
      if (tree1 -> indx > indx)
        tree1 = tree1 -> left;
      else
        tree1 = tree1 -> right;
    } // this while loop will end with tree1 as null and tree2 as the parent node of the new child

    // determine whether it will be left or right child
    // left child
    if (tree2 -> indx > indx) {
      tree2 -> left = (tn * ) malloc(sizeof(tn));
      tree2 = tree2 -> left; // traverse down to check for any mem allocation errors
      if (tree2 == NULL)
        error();
      // populate
      tree2 -> indx = indx;
      tree2 -> ratio = ratio;
      tree2 -> name = strdup(name);
      tree2 -> left = tree2 -> right = NULL;

      // right child
    } else {
      tree2 -> right = (tn * ) malloc(sizeof(tn));
      tree2 = tree2 -> right;
      if (tree2 == NULL)
        error();
      tree2 -> indx = indx;
      tree2 -> ratio = ratio;
      tree2 -> name = strdup(name);
      tree2 -> left = tree2 -> right = NULL;
    }
  }
  //return root; // return the root to be able to keep track of all the tree
}

// iterative inorder traversal with a stack (non-recursive)
void inorder(tn * root) {
  tn * stack[STACK_SIZE];
  int top = -1;
  // not empty tree
  if (root != NULL) {
    ++top;
    stack[top] = root; // push the root into stack
    // check left child
    root = root -> left;
    while (top >= 0) { // to keep pushing & poping out nodes until empty stack

      while (root != NULL) { // loop through left children to push them to stack
        ++top; //
        stack[top] = root; // push into stack
        // check left side
        root = root -> left; // go to next left child
      }

      root = stack[top]; // pop
      --top;
      printf("%d -> ", root -> indx); // print path
      root = root -> right; // go right

      // pushing the right children into stack
      if (root != NULL) {
        ++top;
        stack[top] = root;
        root = root -> left;
      }
    }
  }
}

// calculate nodes count recursively
int count(tn * root) {
  if (!root) // == NULL
    return 0; // empty tree
  else {
    if (!root -> left && !root -> right)
      return 1; // only parent with no children
    else
      return 1 + (count(root -> left) + count(root -> right)); // non-empty tree with children
  }
}

tn * search(tn * root, int key) {
  tn * tree; // temporary tree to traverse the tree
  tree = root; // to keep track of the root node

  while (tree != NULL) { // loop until no chilren
    if (tree -> indx == key)
      return tree; // return the node when you find the key
    // not found yet
    else {
      if (tree -> indx > key)
        tree = tree -> left; // go left
      else
        tree = tree -> right; // go right
    }
  }
  return NULL; // not found
}

// to get the pointer to a particular node
tn * get_ptr(tn * root, int key, tn ** root_ptr) {
  tn * tree; // temporary tree
  if (root == NULL)
    return NULL; // empty tree
  tree = root;
  * root_ptr = NULL; // this like tree2 in insert function but needs to be returned here as well
  while (tree != NULL) {
    if (tree -> indx == key) // found
      return tree; // return the node
    // not found yet
    else {
      * root_ptr = tree; // store this pointer as parent root of children
      if (tree -> indx > key)
        tree = tree -> left; // go left
      else
        tree = tree -> right; // go right
    }
  }
  return NULL; // not found
}

// delete the node
tn * delete(tn * root, int key) {
  // temporary variables
  tn * to_be_deleted, * its_parent, * temp_tree; // temp_tree changes pointers in the tree
  to_be_deleted = get_ptr(root, key, & its_parent);

  if (to_be_deleted == NULL) {
    puts("\n\tThe node does not exist");
    return root;

  } else {

    // deleting a node with no child (easiest)
    if (to_be_deleted -> left == NULL && to_be_deleted -> right == NULL) {
      if (to_be_deleted == its_parent -> left)
        its_parent -> left = NULL;
      else
        its_parent -> right = NULL;
      free(to_be_deleted);
      return root;
    }

    // if the to_be_deleted is the root itself
    if (to_be_deleted == root) {
      temp_tree = to_be_deleted -> right; // go to right child
      root = temp_tree; // root will be its right child
      while (temp_tree -> left != NULL) { // loop until no more left children
        temp_tree = temp_tree -> left;
      }
      temp_tree -> left = to_be_deleted -> left; // assign the left child to temp min left child 
      free(to_be_deleted);
      return root;
    }

    // deleting node having both children
    if (to_be_deleted -> left && to_be_deleted -> right) { //!=NULL
      if (to_be_deleted == its_parent -> left) {
        temp_tree = to_be_deleted -> left;
        its_parent -> left = to_be_deleted -> left;
        while (temp_tree -> right != NULL)
          temp_tree = temp_tree -> right;
        temp_tree -> right = to_be_deleted -> right;
        to_be_deleted -> left = NULL;
        to_be_deleted -> right = NULL;
      } else {
        temp_tree = to_be_deleted -> right;
        its_parent -> right = to_be_deleted -> right;
        while (temp_tree -> left != NULL)
          temp_tree = temp_tree -> left;
        temp_tree -> left = to_be_deleted -> left;
        to_be_deleted -> left = NULL;
        to_be_deleted -> right = NULL;
      }
      free(to_be_deleted);
      return root;
    }

    // deleting a node with one child
    if (!to_be_deleted -> left && to_be_deleted -> right) { // right child
      if (to_be_deleted == its_parent -> left)
        its_parent -> left = to_be_deleted -> right;
      else
        its_parent -> right = to_be_deleted -> right;
      to_be_deleted -> right = NULL;
      free(to_be_deleted);
      return root;
    }
    if (to_be_deleted -> left && !to_be_deleted -> right) { // left child
      if (to_be_deleted == its_parent -> left)
        its_parent -> left = to_be_deleted -> left;
      else
        its_parent -> right = to_be_deleted -> left;
      to_be_deleted -> left = NULL;
      free(to_be_deleted);
      return root;
    }
  }
}
