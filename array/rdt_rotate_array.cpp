/*
  question from reddit

  given two int arrays, determine if they are rotations of each other
  ie. 1,2,3,4,5 and 4,5,1,2,3 are rotations

  solution:
  double one of the arrays, and then check if one is a substring of the other
  this can be done in O(2n) = O(n) time with KMP
  
  compile with -std=c++11 for this solution
 */

#include <iostream>
#include <vector>
#include <initializer_list>

class RotationCheck
{
public:
  static bool checkRotation(const std::initializer_list<int>& array1, const std::initializer_list<int>& array2);
private:
  static std::vector<int> KMPpreprocess(const std::vector<int>& pattern);
  static bool KMPcheckSubstr(const std::vector<int>& text, const std::vector<int>& pattern);
};

// preprocessing step consists of checking for internal overlap in pattern
// to save time when checking the main text, done in O(m), m is size of pattern
std::vector<int> RotationCheck::KMPpreprocess(const std::vector<int>& pattern)
{
  std::vector<int> overlap(pattern.size());
  unsigned int match = 0;
  unsigned int it = 1;
  overlap[0] = 0;
  while (it < pattern.size()) {
    if (pattern[match] == pattern[it]) { // found internal pattern
      match++;
      overlap[it] = match;
      it++;
      continue;
    }
    if (match > 0) match = overlap[match-1]; // break out from other while, try last overlap
    else if (match == 0) it++; // if not, give up
  }
  return overlap;
}

// main step consists of using the overlap from above to find substring in text
// overlap allows you to not have to always check from beginning
// done in O(n), size of text meaning full check = O(m+n)
bool RotationCheck::KMPcheckSubstr(const std::vector<int>& text, const std::vector<int>& pattern)
{
  std::vector<int> overlap = RotationCheck::KMPpreprocess(pattern);
  unsigned int match = 0;
  unsigned int it = 0;
  while (it < text.size()) {
    if (pattern[match] == text[it]) {
      if (match+1 == pattern.size()) return true; // complete match
      match++; it++; continue;
    }
    if (match > 0) match = overlap[match-1];
    else if (match == 0) it++;
  }
  return false;
}

bool RotationCheck::checkRotation(const std::initializer_list<int>& array1, const std::initializer_list<int>& array2)
{
  std::vector<int> vector1(array1);
  std::vector<int> vector2(array2); // pattern
  if (vector1.size() != vector2.size()) return false;
  unsigned int orig_size = vector1.size(); // double vector 1, which is now text
  for (unsigned int i = 0; i < orig_size; i++)
    vector1.push_back(vector1[i]);
  return RotationCheck::KMPcheckSubstr(vector1, vector2); // check substr
}

struct RotationTestCase
{
  bool test;
  bool exp_output;
  RotationTestCase(const std::initializer_list<int>& _input1,
		   const std::initializer_list<int>& _input2,
		   bool _exp_output) :
    test(RotationCheck::checkRotation(_input1,_input2)), 
    exp_output(_exp_output) {}

  void run()
  {
    if (test == exp_output) std::cout << "PASS" << std::endl;
    else std::cout << "FAIL" << std::endl;
  }
};

int main()
{
  std::vector<RotationTestCase> cases = {
    RotationTestCase({1,2,3,4,5}, {1,2,3,4,5}, true),
    RotationTestCase({4,5,1,2,3}, {1,2,3,4,5}, true),
    RotationTestCase({1,2,3,4,5}, {4,5,1,3,2}, false),
    RotationTestCase({1,1,1,1,1,1}, {1,1,1,1,1}, false),
    RotationTestCase({5,4,4,3,2}, {3,2,5,4,4}, true)
  };
  for (auto i : cases)
    i.run();
}
