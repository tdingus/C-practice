/*
  problem from Tim Q. (HW assignment)

  sort an input linked list with random integers using constant space in
  worst case n log n time.

  attempt 1:
  merge sort, should be n log n

  tried doing this with recursion, but recursion is not constant space (disregard this file)

 */

#include <iostream>

class Node {
public:
  int value;
  Node* next;

  Node(int v_) : value(v_) {}
};
Node* merge_sort(Node* root);
Node* recursive_break(Node* root, int size);
Node* merge(Node* left_half, Node* right_half);


Node* merge_sort(Node* root){
  Node* tmp = root;
  int size = 0;
  while (tmp) {
    tmp = tmp->next;
    size++;
  }
  return recursive_break(root, size);
}

Node* recursive_break(Node* root, int size) {
  if (size == 0 || size == 1) return root;
  else if (size == 2) {
    if (root->value > root->next->value) {
      int tmp = root->value;
      root->value = root->next->value;
      root->next->value = tmp;
    }
    return root;
  }
  
  Node* tmp = root;
  int i = 1;
  for (i; i < size/2; i++) tmp = tmp->next; // break into half
  Node* right_half = tmp->next;
  tmp->next = NULL;
  return merge(recursive_break(root, i),
	       recursive_break(right_half, size-i));

}

Node* merge(Node* left_half, Node* right_half){
  Node* root = NULL;
  Node* tmp = NULL;
  while (left_half || right_half) {
    if (!right_half || (left_half && left_half->value <= right_half->value)) {
      if (root == NULL) {
	root = left_half;
	tmp = root;
      }
      else {
	tmp->next = left_half;
	tmp = tmp->next;
      }
      left_half = left_half->next;
    }
    else {
      if (root == NULL) {
	root = right_half;
	tmp = root;
      }
      else {
	tmp->next = right_half;
	tmp = tmp->next;
      }
      right_half = right_half->next;
    }
  }
  return root;
}

void print_ll(Node* root) {
  while (root != NULL) {
    std::cout << root->value << std::endl;
    root = root->next;
  }
}

int main() {
  Node* n1 = new Node(8);
  Node* n2 = new Node(5);
  Node* n3 = new Node(4);
  Node* n4 = new Node(6);
  Node* n5 = new Node(1);
  //n1.next = &n2;
  //n3.next = &n4;
  //  print_ll(merge(&n1,&n3));
  n1->next = n2;
  n2->next = n3;
  n3->next = n4;
  n4->next = n5;
  print_ll(recursive_break(n1, 5));

  delete n1; delete n2; delete n3; delete n4; delete n5;
}
