/*
  UPE-hard (easy problem)
  
  Problem: Stock optimization, given an input of stock prices, determine the maximum profit one can obtain
  For instance given 3.5, 2, 4, 100, 90, 6, 18, 2
  The output should be: buy in at 2, sell at 100 (although the exact output here is buy: 1, sell: 3, the 
  problem wanted index outputs).

  Solution:
  O(n) - simply store the smallest number up until now for each value, return the largest difference at the end.
  init at 0, so you can check if no profit can be obtained.
 */
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
  float x;
  std::vector<float> values;
  unsigned int smallest_index = 0;
    
  unsigned int greatest_profit_s_index = 0;
  unsigned int greatest_profit_b_index = 0;
    
  while (cin >> x) {
    values.push_back(x);
    if (values[values.size()-1] - values[smallest_index] > values[greatest_profit_s_index] - values[greatest_profit_b_index])         {
      greatest_profit_s_index = values.size()-1;
      greatest_profit_b_index = smallest_index;
    }
    if (values[smallest_index] > values[values.size()-1]) smallest_index = values.size() - 1;
  }
    
  float result = values[greatest_profit_s_index] - values[greatest_profit_b_index];
  if (result > 0) {
    std::cout << "Buy: " << greatest_profit_b_index << std::endl <<
      "Sell: " << greatest_profit_s_index;
  }
  else { 
    std::cout << "No Profit" << std::endl;
  }
    
  return 0;
}
