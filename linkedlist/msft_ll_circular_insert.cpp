/*
  MSFT question

  given a circular linked list, sorted in ascending order, insert a new node

  solution: given the entry node, create a new one right after (as the old entry) and then float the node 
  left/right accordingly.

  new node x is in the right position if:
  a <= x <= b
  a <= x > b, where b < a (this means that it's new max).
  a > x < b, where b < a (this means that it's new min).
  if x would float into its original position, quit out (we've come full circle).
 */

#include <iostream>
#include <vector>

struct Node {
  int value;
  Node* next;

  Node() {}
  Node(int _value) : value(_value) {}
  Node(int values[], int size) {
    Node* tmp = this;
    for (int i = 0; i < size; i++) {
      tmp->value = values[i];
      if (i != size-1) {
	tmp->next = new Node();
	tmp = tmp->next;
      }
    }
    tmp->next = this;
  }

  void print_list();
  Node* insert_node(int value);
  void delete_list();
};

void Node::print_list() {
  std::cout << "starting print" << std::endl << "this: " << value << std::endl;
  Node* tmp = next;
  while (tmp != this) {
    std::cout << tmp->value << std::endl;
    tmp = tmp->next;
  }
}

void Node::delete_list() {
  Node* tmp = next;
  std::vector<Node*> death_row;
  death_row.push_back(this);
  while (tmp != this) {
    death_row.push_back(tmp);
    tmp = tmp->next;
  }
  for (int i = 0; i < death_row.size(); i++) {
    delete death_row[i];
  }
}

Node* Node::insert_node(int new_v) {
  // create new node to store current value
  Node* new_node = new Node(new_v);
  new_node->next = next;
  next = new_node;
  // start floating
  Node* prev_tmp = this;
  Node* tmp = new_node;
  bool not_first = false;
  while (tmp != next || !not_first) { // breaks if we came full circle 
    if (tmp->value >= prev_tmp->value && // check if fits or new max
	(tmp->value <= tmp->next->value ||
	 (tmp->value > tmp->next->value && prev_tmp->value > tmp->next->value)))
      return tmp;
    else if (prev_tmp->value > tmp->value && tmp->value <= tmp->next->value)
      return tmp; // for new min
    // if it doesn't fit, swap
    int tmp_int = tmp->value;
    tmp->value = tmp->next->value;
    tmp->next->value = tmp_int;
    prev_tmp = tmp;
    tmp = tmp->next;
    not_first = true;
  }
  return tmp;
}

int main() {
  int tmp_list[] = {5,5,5,5,5};
  Node* tmp = new Node(tmp_list,5);
  Node* tmp_1 = tmp->insert_node(6);
  //  std::cout << tmp_1->value << std::endl;
  tmp->print_list();
  tmp->delete_list();
}

