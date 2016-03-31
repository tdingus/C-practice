/*
  given a circular linked list, sorted in ascending order, insert a new node

  the test-cases i wrote require a new version of g++ (use -std=c++11 as one of the
  compiler options)

  solution: given the entry node, create a new one right after representing the new node and then float the node right until it reaches the right spot (with checking for infinite).

  new node x is in the right position if:
  a <= x <= b
  a <= x > b, where b < a (this means that it's new max).
  a > x < b, where b < a (this means that it's new min).
  if x would float into its original position, quit out (we've come full circle).
 */

#include <iostream>
#include <string>
#include <initializer_list>
#include <vector>

struct Node 
{
  int value;
  Node* next;

  Node() : value(0), next(NULL) {}
  Node(int _value) : value(_value), next(NULL) {}
  Node(int values[], int size) : value(0), next(NULL)
  {
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
  
  Node(std::vector<int> values)  : value(0), next(NULL)
  {
    Node* tmp = this;
    for (unsigned int i = 0; i < values.size(); i++) {
      tmp->value = values[i];
      if (i != values.size()-1) {
	tmp->next = new Node();
	tmp = tmp->next;
      }
    }
    tmp->next = this;
  }

  void print_list() const;
  Node* insert_node(int value);
  void delete_list();
};

void Node::print_list() const
{
  std::cout << "output: " << value << ", ";
  Node* tmp = next;
  while (tmp != this) {
    std::cout << tmp->value << ",";
    tmp = tmp->next;
  }
  std::cout << std::endl;
}

void Node::delete_list() 
{
  Node* tmp = this;
  Node* this_ptr = this;
  while (tmp != this_ptr) {
    Node* next = tmp->next;
    delete tmp;
    tmp = next;
  }
}

Node* Node::insert_node(int new_v) 
{
  // create new node to store current value
  Node* new_node = new Node(new_v);
  new_node->next = next;
  next = new_node;
  // start floating
  Node* prev_tmp = this;
  Node* tmp = new_node;
  bool not_first = false;
  while (tmp != next || !not_first) { // breaks if we came full circle 
    if ((tmp->value >= prev_tmp->value) && // check if fits or new max
	(tmp->value <= tmp->next->value ||
	 (tmp->value > tmp->next->value && prev_tmp->value > tmp->next->value)))
      return tmp;
    else if (prev_tmp->value > tmp->value && tmp->value <= tmp->next->value
	     && prev_tmp->value > tmp->next->value)
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

struct Test_case 
{
  std::vector<int> input;
  int insert;
  std::vector<int> output;
  std::string id;

  Test_case(std::initializer_list<int> _input, int _insert, 
	    std::initializer_list<int> _output, std::string _id) : input(_input), insert(_insert), output(_output), id(_id) {}
};

int main() 
{
  std::vector<Test_case> cases = {Test_case({5,5,5}, 6, {5,5,5,6},std::string("all same test")),
		       Test_case({2,4,6,8,10}, 6, {2,4,6,6,8,10}, std::string("normal add")),
		       Test_case({2,4,6,8,10}, 1, {1,2,4,6,8,10}, std::string("wrap around add + min")),
		       Test_case({2,4,6,8,10}, 12, {2,4,6,8,10,12}, std::string("normal add + max"))};
  for (unsigned int i = 0; i < cases.size(); i++) {
    std::cout << "doing test: " << cases[i].id << std::endl;
    Node* tmp = new Node(cases[i].input);
    tmp->insert_node(cases[i].insert);
    tmp->print_list();
    std::cout << "expected output: ";
    for (unsigned int x = 0; x < cases[i].output.size(); x++)
      std::cout << (cases[i].output)[x] << ", ";
    std::cout << std::endl;
    tmp->delete_list();
  }
}

