#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bstree.h"

void error(void) {
  puts("\tCannot Allocate Memory for Node");
  exit(0);
}

int compare(tn * x, tn * y, Type type) {
  switch (type) {
  case INT:
    if (x -> value._int > y -> value._int)
      return 1;
  case FLOAT:
    if (x -> value._float > y -> value._float)
      return 1;
  case STR:
    if (strcmp(x -> value._str, y -> value._str) > 0)
      return 1;
  }
  return 0;
}

int compare2(tn * x, Tuple y, Type type, char op) {
  switch (type) {
  case INT:
    if (op == '>') {
      if (x -> value._int > y.val._int)
        return 1;
    } else if (op == '=') {
      if (x -> value._int == y.val._int)
        return 1;
    } else {
      if (x -> value._int < y.val._int)
        return 1;
    }
    case FLOAT:
      if (op == '>') {
        if (x -> value._float > y.val._float)
          return 1;
      } else if (op == '=') {
        if (x -> value._float == y.val._float)
          return 1;
      } else {
        if (x -> value._float < y.val._float)
          return 1;
      }
      case STR:
        if (op == '>') {
          if (strcmp(x -> value._str, y.val._str) > 0)
            return 1;
        } else if (op == '=') {
          if (strcmp(x -> value._str, y.val._str) == 0)
            return 1;
        } else {
          if (strcmp(x -> value._str, y.val._str) < 0)
            return 1;
        }
  }
  return 0;
}

void insert_node(tn ** root, tn * _new, Type type) {
  tn * tree1, * tree2; // temporary trees to traverse the tree back and forth

  if ( * root == NULL) { // empty tree so new node will be root
    ( * root) = _new;
    ( * root) -> left = ( * root) -> right = NULL; // empty children

    // non-empty tree
  } else {
    tree1 = * root; // asigning root to another value to keep track of it

    /* traverse the tree to get the pointer of the parent of the (new child) */
    while (tree1 != NULL) { // loop until the node has no children
      tree2 = tree1; // to keep track of parent node while traversing to child
      if (compare(tree1, _new, type))
        tree1 = tree1 -> left;
      else
        tree1 = tree1 -> right;
    } // this while loop will end with tree1 as null and tree2 as the parent node of the new child

    // determine whether it will be left or right child
    // left child
    if (compare(tree2, _new, type)) {
      tree2 -> left = _new;
      tree2 = tree2 -> left; // traverse down to check for any mem allocation errors
      tree2 -> left = tree2 -> right = NULL;

      // right child
    } else {
      tree2 -> right = _new;
      tree2 = tree2 -> right;
      tree2 -> left = tree2 -> right = NULL;
    }
  }
}
// iterative inorder traversal with a stack (non-recursive)
void pinorder(tn * root, Type type) {
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
      switch (type) {
      case INT:
        printf("%d -> ", root -> value._int); // print path
        break;
      case FLOAT:
        printf("%.2f -> ", root -> value._float); // print path
        break;
      case STR:
        printf("%s -> ", root -> value._str); // print path
        break;
      }
      root = root -> right; // go right

      // pushing the right children into stack
      if (root != NULL) {
        ++top;
        stack[top] = root;
        root = root -> left;
      }
    }
  }
  //puts("");
}

tn * searchtree(tn * root, Tuple value, Type type) {
  tn * tree; // temporary tree to traverse the tree
  tree = root; // to keep track of the root node

  while (tree != NULL) { // loop until no chilren
    if (compare2(tree, value, type, '='))
      return tree; // return the node when you find the key
    // not found yet
    else {
      if (compare2(tree, value, type, '>'))
        tree = tree -> left; // go left
      else
        tree = tree -> right; // go right
    }
  }
  return NULL; // not found
}

// to get the pointer to a particular node
tn * get_ptr(tn * root, Tuple key, tn ** root_ptr, Type type) {
  tn * tree; // temporary tree
  if (root == NULL)
    return NULL; // empty tree
  tree = root;
  * root_ptr = NULL; // this like tree2 in insert function but needs to be returned here as well
  while (tree != NULL) {
    if (compare2(tree, key, type, '='))
      return tree; // return the node
    // not found yet
    else {
      * root_ptr = tree; // store this pointer as parent root of children
      if (compare2(tree, key, type, '>'))
        tree = tree -> left; // go left
      else
        tree = tree -> right; // go right
    }
  }
  return NULL; // not found
}

// delete the node
void deletenode(tn ** root, Tuple key, Type type, int * filled) {
  // temporary variables
  tn * to_be_deleted, * its_parent, * temp_tree; // temp_tree changes pointers in the tree
  to_be_deleted = get_ptr( * root, key, & its_parent, type);

  if (to_be_deleted == NULL) {
    puts("The value does not exist");
    return;

  } else {

    // deleting a node with no children (easiest)
    if (to_be_deleted -> left == NULL && to_be_deleted -> right == NULL) {
      if (its_parent) { // it has a parent meaning not root
        if (to_be_deleted == its_parent -> left)
          its_parent -> left = NULL;
        else
          its_parent -> right = NULL;
        free(to_be_deleted);
        return;
      } else {
        // it is the root
        free(to_be_deleted);
        return;
      }
    }

    // if the to_be_deleted is the root itself
    if (to_be_deleted == * root) {
      temp_tree = to_be_deleted -> right; // go to right child

      if (temp_tree) {
        * root = temp_tree; // root will be its right child
        while (temp_tree -> left != NULL) { // loop until no more left children
          temp_tree = temp_tree -> left;
        }
        // assign the left child to temp min left child
        temp_tree -> left = to_be_deleted -> left;
      } else {
        temp_tree = to_be_deleted -> left;
        * root = temp_tree; // root will be its right child
      }
      // tree will be empty
      free(to_be_deleted);
      * filled = * filled - 1;
      return;

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
      return;
    }

    // deleting a node with one child
    if (!to_be_deleted -> left && to_be_deleted -> right) { // right child
      if (to_be_deleted == its_parent -> left)
        its_parent -> left = to_be_deleted -> right;
      else
        its_parent -> right = to_be_deleted -> right;
      to_be_deleted -> right = NULL;
      free(to_be_deleted);
      return;
    }
    if (to_be_deleted -> left && !to_be_deleted -> right) { // left child
      if (to_be_deleted == its_parent -> left)
        its_parent -> left = to_be_deleted -> left;
      else
        its_parent -> right = to_be_deleted -> left;
      to_be_deleted -> left = NULL;
      free(to_be_deleted);
      return;
    }
  }
}
