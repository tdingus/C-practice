/*
  taken from: https://github.com/kensterz/interview-questions-in-javascript
  
  given an input array, output the largest 3-number product

  solutions:
  O(n logn) - sort the array (merge sort, heap sort, whatever), take top 3 and multiply
  O(n + log n) - create max heap from array 3 times, each time removing the max element
  O(n) - iterate through array three times, remove max each time (not as interesting :P)

  note this solution uses initializer list, so compile with -std=c++11
 */
#include <iostream>
#include <vector>
#include <initializer_list>

struct ProductGenerator
{
  static int maxProduct(const std::initializer_list<int>& input);
private:
  static void maxHeapify(std::vector<int>& input);
  static void heapify(std::vector<int>& input, unsigned int i); // children of i must be max heaps
};

void ProductGenerator::maxHeapify(std::vector<int>& input) //O(n);
{
  for (int i = input.size()/2; i >= 0; i--) { // i > input.size()/2 are all leaves
    heapify(input, i);
  }
}

void ProductGenerator::heapify(std::vector<int>& input, unsigned int i) // 0's children are 1 and 2
{
  if (i >= input.size()) return;
   std::cout << "i = " << i << std::endl;
 
  int max = input[i];
  if (2*i+1 < input.size() && input[2*i+1] > max) {
    max = input[2*i+1];
  }
  if (2*i+2 < input.size() && input[2*i+2] > max) {
    max = input[2*i+2];
  }
  if (max != input[i]) {
    int tmp = input[i];
    if (max == input[2*i+1]) {
      input[i] = input[2*i+1];
      input[2*i+1] = tmp;
      ProductGenerator::heapify(input, 2*i+1);
    }
    else {
      input[i] = input[2*i+2];
      input[2*i+2] = tmp;
      ProductGenerator::heapify(input, 2*i+2);
    }
    
  }
}

int ProductGenerator::maxProduct(const std::initializer_list<int>& _input)
{
  std::vector<int> input(_input);
  int product = 1;
  for (unsigned int i = 0; i < 3; i++) {
    ProductGenerator::maxHeapify(input);
    product *= input[0];
    input.erase(input.begin());
  }
  return product;
};

int main()
{
  std::cout << ProductGenerator::maxProduct({1,8,6,4,1,2,10,9,9}) << std::endl;
}
