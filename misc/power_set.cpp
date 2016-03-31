/*
  question: given an input set, output its power set
  i.e. {1,2,3} --> {{}, {1}, {2}, {3}, {1,2}, {2,3}, {1,3}, {1,2,3}}

  algorithm:

  mathematically there will always be 2^n sets
  we can associate each element with a piece size of size 2^i, where i is the index
  elements will show up in sets within a piece, then be not present for a piece, then 
  present then not present etc.

  this makes more sense with an example:
  {1,2,3}, piece sizes {1,2,4}
  
  by this algorithm, 1 appears in sets 0, 2, 4, 6 (notice 1,3,5,7 skipped)
  2 appears in sets 0,1 , 4,5 (notice 2,3 , 6,7 skipped)
  3 appears in sets 0,1,2,3 (notice 4,5,6,7 skipped)

  the first step is to generate the powers of two, then do the main step
 */
#include <iostream>
#include <initializer_list> // req c++11
#include <vector>

class PowerSetGenerator
{
public:
  static std::vector<std::vector<int> > generatePowerSet(const std::initializer_list<int>& input);

private:
  static std::vector<int> generatePowersOf2(unsigned int size);
};

std::vector<int> PowerSetGenerator::generatePowersOf2(unsigned int size) // linear time
{
  std::vector<int> output(size);
  output[0] = 1;
  for (unsigned int i = 1; i < size; i++) {
    output[i] = output[i-1] * 2;
  }
  return output; // largest power will be 2^(n-1)
}

std::vector<std::vector<int> > PowerSetGenerator::generatePowerSet(const std::initializer_list<int>& _input) // n * 2^n
{
  std::vector<int> input(_input); // load input
  std::vector<int> pieceSizes = PowerSetGenerator::generatePowersOf2(input.size());
  std::vector<int> iterators(pieceSizes); // this will keep track of where in each set we are
  std::vector<std::vector<int> > powerSet(pieceSizes[input.size()-1] * 2); // 2^n sets
  for (unsigned int i = 0; i < powerSet.size(); i++) {
    for (unsigned int j = 0; j < iterators.size(); j++) {
      if (iterators[j] > 0) {
	powerSet[i].push_back(input[j]);
      }
      iterators[j]--;
      if (iterators[j] == -1 * pieceSizes[j]) {
	iterators[j] = pieceSizes[j];
      }
    }
  }

  return powerSet;
}

int main()
{
  std::vector<std::vector<int> > powerSet = PowerSetGenerator::generatePowerSet({1,2,3});
  for (unsigned int i = 0; i < powerSet.size(); i++) {
    std::cout << "set " << i << ":";
    for (unsigned int j = 0; j < powerSet[i].size(); j++) {
      std::cout << powerSet[i][j] << ",";
    }
    std::cout << std::endl;
  }
}
