/*
  Min-max heap practice:
  elements on odd rows (top node is level 1) are smaller than all nodes below
  elements on even rows are larger than all nodes below
  insertion (log n), access (O(1))

  requires -std=c++11 for initializer_list
*/
#include <math.h>
#include <iostream>
#include <initializer_list>
#include <vector>

struct MinMaxHeap
{
  /*
    for sanities' sake:
    for a list in this program: 3, 5, 8, 9, -2
    an index is defined as its array index, so list[0] = 3
    but an iterator is defined as its heap index, so list[1] = 3, list[2] = 5, etc.
    iterator{elem} = index{elem} + 1 for all elem in list, essentially

    this is important because the traditional heap in array definitions assume iterators, but
    that needs to be converted between index and iterator. 
  */

  std::vector<int> values;
  
  static int level(int iterator); // root is on level 1, its children are level 2.

  int getMax();
  int getMin();
  void insert(int value);
  int removeMax();
  int removeMin();

  void printHeap();

  MinMaxHeap(const std::initializer_list<int>& input) : values(input) {}
};

void MinMaxHeap::printHeap()
{
  for (auto i:values)
    std::cout << i << ", ";
  std::cout << std::endl;
}

int MinMaxHeap::level(int iterator)
{
  return (int) (log(iterator)/log(2)) + 1; // using bayes' theorem to get log_2 of (index + 1), important because index 0 should return 1
}

int MinMaxHeap::getMin()
{
  if (values.size() == 0) return -1;
  return values[0];
}

int MinMaxHeap::getMax()
{
  if (values.size() == 0) return -1;
  if (values.size() == 1) return values[0];
  int max = values[1];
  if (values.size() >= 3) {
    if (values[2] > max)
      max = values[2];
  }
  return max;
}

// parent = 

void MinMaxHeap::insert(int value)
{
  values.push_back(value); // first insert at the end, then 
  if (values.size() == 1) return;
  int iterator = values.size();
  int tmp_iterator = iterator/2;
  if (values[iterator-1] > values[iterator/2-1]) { // check versus parent, if greater, value is > all min levels on way to root, so check max levels
    if (level(tmp_iterator)%2 == 1) tmp_iterator /= 2; // ensure what we're checking is a max level
    while (values[iterator-1] > values[tmp_iterator-1] && tmp_iterator > 0) { // tmp_iterator is 2 levels ahead
      int tmp = values[iterator-1];
      values[iterator-1] = values[tmp_iterator-1];
      values[tmp_iterator-1] = tmp;
      iterator = tmp_iterator;
      tmp_iterator /= 4;
    }
  }
  else if (values[iterator-1] < values[iterator/2-1]) { // if smaller, value is < all max levels on way to root, so check min levels
    if (level(tmp_iterator)%2 == 0) tmp_iterator /= 2;
    while (values[iterator-1] < values[tmp_iterator-1] && tmp_iterator > 0) { // tmp_iterator is 2 levels ahead
      int tmp = values[iterator-1];
      values[iterator-1] = values[tmp_iterator-1];
      values[tmp_iterator-1] = tmp;
      iterator = tmp_iterator;
      tmp_iterator /= 4;
    }
  }
}

int main()
{

  //  std::cout << MinMaxHeap::level(1) << " " << MinMaxHeap::level(2) << " " << MinMaxHeap::level(12) << std::endl;
  MinMaxHeap mmh({8,71,41,31,10,11,16,46,51,31,21,13});
  mmh.insert(61);
  mmh.printHeap();
};
