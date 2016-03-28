/*
  Problem: Word Search algorithm
  
  given an input like:
  15

  MHDFVIFOTFPEQNW
  XWLKSRXLSAGUKBW
  XKHBFEDLEEPFDPP
  SMLNRPFEIFFDMGF
  FMAQUJSHYCWBNOD
  RNJRGQTJBUVYZEJ
  QLJFAUFLEUBOBPJ
  UGSJYPKDHSEYTZS
  PKMWHEVDAQVDSYA
  QKQWENLFSFWAZVF
  QHGZNRFIOMPQJYV
  MQCVOHCLQGEQCGH
  GSAWHKZMNZRKTMU
  INDIORBKVJVBRYC
  MMHYLOPTCNZZSBP

  HELLO
  WORLD
  
  where the first line is the word search board size, the next size lines is the board,
  and the words after that are the words to find,

  output:
  HELLO(8,5,N)
  WORLD(4,13,NE)

  solution: not sure if there's a nicer way of doing this, currently doing an O(mn) algo where
  m = size of search words input, n = size of board
 */

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

bool searchWord(const std::string& input, unsigned int size, const std::vector<std::vector<char> >& array, int x, int y, const std::string& direction) {
  if (x < 0 || x >= size || y < 0 || y >= size) return false;
  if (array[x][y] == input[0]) {
    if (input.size() == 1) return true;
    std::string new_input = input.substr(1);
    if (direction == "N") {return searchWord(new_input, size, array, x-1, y, direction);}
    else if (direction == "E") {return searchWord(new_input, size, array, x, y+1, direction);}
    else if (direction == "W") {return searchWord(new_input, size, array, x, y-1, direction);}
    else if (direction == "S") {return searchWord(new_input, size, array, x+1, y, direction);}
    else if (direction == "NE") {return searchWord(new_input, size, array, x-1, y+1, direction);}
    else if (direction == "NW") {return searchWord(new_input, size, array, x-1, y-1, direction);}
    else if (direction == "SE") {return searchWord(new_input, size, array, x+1, y+1, direction);}
    else if (direction == "SW") {return searchWord(new_input, size, array, x+1, y-1, direction);}
  }
  return false;
}

struct Solution {
  unsigned int x;
  unsigned int y;
  std::string direction;
  bool correct;
  Solution() : correct(false) {}
  Solution(int _x, int _y, std::string _direction) : x(_x), y(_y), direction(_direction), correct(true) {}
};

int main() {
  unsigned int size;
  cin >> size;
  std::vector<std::vector<char> > array(size);
  std::vector<std::string> words;
  for (unsigned int i = 0; i < size; i++) { // load array
    std::string line;
    cin >> line;
    for (unsigned int j = 0; j < line.size(); j++) {
      array[i].push_back(line[j]);
    }
  }
  std::string word;
  while (cin >> word) { // load search words
    words.push_back(word);
  }
  std::vector<Solution> solutions(words.size());
  std::string directions[] = {"N", "S", "E", "W", "NE", "NW", "SE", "SW"};
  for (unsigned int i = 0; i < size; i++) {
    for (unsigned int j = 0; j < size; j++) {
      for (unsigned int k = 0; k < words.size(); k++) {
	if (words[k][0] == array[i][j]) {
	  for (int l = 0; l < 8; l++) {
	    bool output = searchWord(words[k], size, array, i, j, directions[l]);
	    if (output == true) solutions[k] = Solution(i+1,j+1,directions[l]);
	  }
	}
      }
    }
  }
  for (int m = 0; m < solutions.size(); m++) {
    if (solutions[m].correct) std::cout << words[m] << "(" << solutions[m].y << "," << solutions[m].x << "," << solutions[m].direction << ")" << std::endl;
  }
  return 0;
}
