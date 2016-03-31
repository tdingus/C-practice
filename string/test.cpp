/*
  KMP implementation of substring

  note for compiling, use command -std=c++11 for the test cases
  if you don't want to compile with this, instead comment out test cases
*/
#include <algorithm>
#include <iostream>
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
int main()
{
  std::string text;
  std::string check;
  std::getline(std::cin,text);
  std::getline(std::cin,check);
  int max = 0;
  for (int i = 0; i < check.size()-max; i++) {
    //std::cout << check.substr(0,i) << " + " << check.substr(check.size()-i) << std::endl;
    for (int j = max; i+j <= check.size(); j++) {
      if (KMP::check_substr(text,check.substr(i,j)) == true && j > max) {
	max = j;    
	if (check.size() - i <= max) break;
      }
    }
  }
  std::cout << max;  
}
