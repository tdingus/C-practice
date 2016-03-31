/*
  first part to a spell checker algorithm

  generate all possible similar words in linear time on the size of an input word
 */
#include <iostream>
#include <vector>
#include <string>

class SpellChecker
{
private:
  static void loadDictionary(const std::vector<std::string>& dictionary); // to be implemented

public:
  static bool checkWord(const std::string& word);
  static void checkSimilarWords(const std::string& word); 
};

bool SpellChecker::checkWord(const std::string& word)
{
  std::cout << ", " << word;
  return true;
}

void SpellChecker::checkSimilarWords(const std::string& word)
{
  std::string tmp;
  std::cout << "word: " << word << std::endl;
  for (unsigned int it = 1; it < 2*(word.size()+1); it++) {
    //std::cout << "it: " << it << std::endl;
    tmp = word;
    if (it%2 == 0) {
      for (char letter = 'a'; letter <= 'z'; letter++) { // constant time
	tmp[it/2-1] = letter;
	checkWord(tmp);
      }
    }
    else {
      // insert character, then iterate on that character
      int new_it = (it + 1)/2 - 1;
      tmp = tmp.substr(0,new_it) + "a" + tmp.substr(new_it);
      for (char letter = 'a'; letter <= 'z'; letter++) { // constant time
	tmp[new_it] = letter;
	checkWord(tmp);
      }
    }
  }
}

int main() {
  SpellChecker::checkSimilarWords(std::string("spel"));
}
