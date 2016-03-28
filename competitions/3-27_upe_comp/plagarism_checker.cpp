/*
  Problem: Given two text strings, find the largest common substring

  The solution I implemented during the competition was an adaptation of KMP, which is O(nm^2), where m is the
  pattern string size, and n is the text string size

  Dynamic programming:
  OPT(i, j) = longest suffix of string1[0,i] and suffix of string2[0,i] that matches
  OPT(i, j) = OPT(i-1,j-1) + 1 if string2[j] == string1[i], 0 otherwise
*/
#include <string>
#include <iostream>
#include <vector>

struct OverlapCheck
{
  static int getMaxOverlap(const std::string& str1, const std::string& str2);
};

int OverlapCheck::getMaxOverlap(const std::string& str1, const std::string& str2)
{
  int max = 0;
  std::vector<std::vector<int> > overlapTable(str1.size(), std::vector<int>(str2.size(), 0));
  for (unsigned int i = 0; i < str1.size(); i++) {
    for (unsigned int j = 0; j < str2.size(); j++) {
      unsigned int current_overlap = 0;
      if (i + current_overlap >= str1.size()) break;
      if (str1[i+current_overlap] == str2[j]) {
	if (i > 0 && j > 0) {
	  overlapTable[i+current_overlap][j] = overlapTable[i+current_overlap-1][j-1] + 1;
	  if (overlapTable[i+current_overlap][j] > max) max = overlapTable[i+current_overlap][j];
	}
	else overlapTable[i][j] = 1;
	current_overlap++;
      }
      else current_overlap = 0;
    }
  }
  return max;
}

int main()
{
  std::string str1, str2;
  std::getline(std::cin, str1);
  std::getline(std::cin, str2);
  std::cout << OverlapCheck::getMaxOverlap(str1, str2) << std::endl;
}
