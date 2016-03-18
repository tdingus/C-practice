/*
  KMP implementation of substring

  note for compiling, use command -std=c++11 for the test cases
  if you don't want to compile with this, instead comment out test cases
 */
#include <algorithm>
#include <iostream>
#include <initializer_list>
#include <string>
#include <vector>

struct KMP
{
  static std::vector<int> populate_overlap(const std::string &pattern); // first step in substr
  static bool check_substr(const std::string &test, const std::string &pattern);
};

/*
  preprocessing step:
  overlap list for substr[0:n] = longest prefix of substr that is also a suffix
  used to save iterations on final step

  ie. for "abcde", overlap list is {0, 0, 0, 0, 0}
  for "aaabaaa", overlap list is {0, 1, 2, 0, 1, 2, 3};
 */
std::vector<int> KMP::populate_overlap(const std::string &pattern)
{ // O(n^2) over substr length (improvable?)
  std::vector<int> overlap_list(pattern.size());
  overlap_list[0] = 0; // first value is always 0
  unsigned int match = 0; // how much of the prefix matches the suffix
  unsigned int it = 1; // position in string
  while (it < pattern.size()) {
    while (pattern[match] == pattern[it]) { // if you spot a match, go ham
      match++;
      overlap_list[it] = match;
      it++; // keep iterating until it doesn't work
    }
    if (match > 0) match = overlap_list[match-1]; // when it doesnt work, try again from beginning
    if (match == 0) it++; // otherwise its a lost cause
  }
  return overlap_list;
}

/*
  actual substr step O(n)
 */
bool KMP::check_substr(const std::string& text, const std::string& pattern) 
{
  std::vector<int> overlap_list = KMP::populate_overlap(pattern); //O(m)
  unsigned int match = 0;
  unsigned int it = 0; // position in text
  while (it < text.size()) {
    while (pattern[match] == text[it] && it < text.size()) {
      match++;
      it++;
      if (match == pattern.size()) return true;
    }
    if (match > 0) match = overlap_list[match-1];
    else if (match == 0) it++;
  }
  return false;
}

struct KMP_overlap_test_case 
{
  std::string input;
  std::vector<int> exp_output;
  std::string id;
  KMP_overlap_test_case(const std::string& _input,
			const std::initializer_list<int>& _output,
			const std::string& _id) : input(_input), exp_output(_output), id(_id) {}
  void run() 
  {
    std::vector<int> output = KMP::populate_overlap(input);
    //bool pass = std::equal(exp_output.begin(), exp_output.end(), output.end());
    std::cout << id;
    if (/*pass*/ output == exp_output) std::cout << " pass" << std::endl;
    else {
      std::cout << " fail" << std::endl;
      for(unsigned int i = 0; i < output.size(); i++) {
	std::cout << output[i];
      }
      std::cout << std::endl;
      for(unsigned int i = 0; i < exp_output.size(); i++) {
	std::cout << exp_output[i];
      }
      std::cout << std::endl;
    }
  }
};

struct KMP_substr_test_case
{
  std::string text;
  std::string pattern;
  bool exp_output;
  KMP_substr_test_case(const std::string& _text, 
		       const std::string& _pattern,
		       bool  _output) :
    text(_text), pattern(_pattern), exp_output(_output) {}
  void run() 
  {
    bool test = KMP::check_substr(text, pattern);
    std::cout << text << "," << pattern;
    if (test == exp_output) std::cout << " pass";
    else std::cout << " fail";
    std::cout << std::endl;
  }
};

int main()
{
  std::vector<KMP_overlap_test_case> tests = {
    KMP_overlap_test_case(std::string("cocacola"),{0,0,1,0,1,2,0,0},std::string("cocacola")), 
    KMP_overlap_test_case(std::string("aaabaaa"), {0,1,2,0,1,2,3},std::string("aaabaaa")), 
    KMP_overlap_test_case(std::string("abcde"), {0,0,0,0,0}, std::string("abcde")),
    KMP_overlap_test_case(std::string("nabnatnabnab"), {0,0,0,1,2,0,1,2,3,4,5,3}, std::string("nabnatnabnab"))
  };
  std::cout << "testing overlap:" << std::endl;
  for (unsigned int i = 0; i < tests.size(); i++) {
    tests[i].run();
  }
  std::cout << std::endl << "testing substr:" << std::endl;
  std::vector<KMP_substr_test_case> tests2 = {
    KMP_substr_test_case(std::string("easy"), std::string("easy"), true), 
    KMP_substr_test_case(std::string("medmedium"), std::string("medium"), true),
    KMP_substr_test_case(std::string("harharharhar"), std::string("hard"), false),
    KMP_substr_test_case(std::string("bananano"), std::string("nano"), true),
    KMP_substr_test_case(std::string("abcde"), std::string("fghi"), false)
  };
  for (unsigned int i = 0; i < tests2.size(); i++) {
    tests2[i].run();
  }
}
