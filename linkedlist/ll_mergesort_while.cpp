/*
  Sort linked list in worst case nlogn time, constant space
  Second attempt - use while loop merge sort (recursion is not constant space)
 */

#include <iostream>

struct Node
{
  int value;
  Node* next;
  
  Node() {}
  Node(int _value) : value(_value) {}
  Node(int* values, int size) { // assumes size of list is correct
    Node* tmp = this;
    for (int i = 0; i < size; ++i) {
      tmp->value = *values;
      //std::cout << "values = " << *values << std::endl;
      if (i != size-1) {
	tmp->next = new Node();
	tmp = tmp->next;
	values++;
      }
    }
  }

  static int get_list_size(Node* root); // finds size of a linked list
  static Node* sort_list(Node* root); // does a merge sort on a linked list
  static Node* merge_lists(Node* left, Node* right); // merges two merge sort pieces
  static void print_list(Node* root); // prints a linked list
  static void delete_tree(Node* root); // cleanup
};

int Node::get_list_size(Node* root)
{
  int size = 0;
  while (root != NULL) {
    size++;
    root = root->next;
  }
  return size;
}

void Node::print_list(Node* root)
{
  std::cout << "starting print of linked_list" << std::endl;
  while (root != NULL) {
    std::cout << root->value << std::endl;
    root = root->next;
  }
}

Node* Node::sort_list(Node* root)
{
  Node* prev_tmp = NULL; // tmp iterator that follows tmp
  Node* tmp = root; // tmp iterator that will run through list multiple times
  int size = get_list_size(root);
  int piece_size = 2; // starts at two, doubles every iteration
  int piece_it = 0; // counts the piece number, resets every iter
  while (piece_size < size*2) { // should iterate log n times
    Node* pre_piece = NULL; // represents node right before piece
    Node* left = NULL; Node* right = NULL;      
    for (int i = 0; i < size; i++) {

      if (i % (piece_size/2) == 0 && i % piece_size != 0) { // start of next piece 
	prev_tmp->next = NULL; // disconnect left tree from right
	right = tmp; // start right tree of new piece
      }

      if (i % piece_size == 0 || (i+1 == size)) { // start of new piece, merge old
        if (i > 0) {
	  if (prev_tmp != NULL) prev_tmp->next = NULL; // detach right tree
	  Node* new_tree = merge_lists(left, right); // merge left/right trees
	  if (piece_it == 0) root = new_tree; // root may change
	  if (pre_piece != NULL) pre_piece->next = new_tree; // rebuild tree connections
	  ++piece_it;
	  
	  if (i % piece_size == 0) { // reattach if necessary
	    while (new_tree != NULL && new_tree->next != NULL)
	      new_tree = new_tree->next;
	    new_tree->next = tmp;
	    pre_piece = new_tree;
	  }
	}
	left = tmp; // start left tree of new piece	
      }
      prev_tmp = tmp;
      tmp = tmp->next;
    }
    tmp = root; // reset for next iter
    piece_size *= 2;
    piece_it = 0;
  }

  return root;
}

Node* Node::merge_lists(Node* left, Node* right) // merges two sorted ll in O(n)
{
  Node* root = NULL;
  Node* tmp = NULL;

  if (right == NULL) {
    return left;
  }

  if (left->value <= right->value) {
    root = left;
    left = left->next;
  }
  else {
    root = right;
    right = right->next;
  }
  tmp = root;

  while ((left != NULL) || (right != NULL)) {
    if ((right == NULL) || (left != NULL && left->value <= right->value)) {
      tmp->next = left;
      tmp = tmp->next;
      left = left->next;
    }
    else {
      tmp->next = right;
      tmp = tmp->next;
      right = right->next;
    }
  }
  
  return root;
}

void Node::delete_tree(Node* root)
{
  while (root != NULL) {
    Node* tmp = root;
    root = root->next;
    delete tmp;
  }
}

int main() {
  //testing constructors
  int list1[] = {3,5};
  int list2[] = {4,6};
  int list3[] = {12,6,5,4,9};
  //testing merge
  Node* root1 = new Node(list1, 2);
  Node* root2 = new Node(list2, 2);
  Node* root = Node::merge_lists(root1, root2);
  Node::print_list(root);
  
  //testing full sort
  Node* root3 = new Node(list3, 5);
  root3 = Node::sort_list(root3);
  Node::print_list(root3);
  //testing merge
  //  delete[] list1; delete[] list2;
  Node::delete_tree(root);
  Node::delete_tree(root3);
}
