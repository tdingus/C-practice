/*
  Problem: https://www.hackerrank.com/contests/upe-hard/challenges/mommy-i-broke-math

  Input is a lot of math equations with mathematical symbols replaced with characters in
  a consistent way throughout. The problem is to output the final, solved equations with
  the original symboling.

  sample input: 
  3 f 4 S 7
  m4 J 3Z i 2 S 6 y 1 f 1
  7 d 2 f m3 i 2Z y 9 * 1 S y3 y 4

  sample output:
  3 + 4 = 7
  (4 * 3) / 2 = 6 - 1 + 1
  7 % 2 + (3 / 2) - 9 ^ 1 = -3 - 4

  explanation:
  f -> +
  S -> =
  m -> (
  J -> *
  Z -> )
  i -> /
  y -> -
  d -> %
  * -> ^

  solution: glorified, but organized brute force. tokenize all the strings, separate lines into
  equation objects. identify all possible equal sign characters, and separate these into cases (attempts)
  and see if any of them work

  SOLUTION USES UNORDERED MAP AND AUTO, COMPILE WITH -std=c++11
 */
#include <string>
#include <iostream>
#include <set>
#include <vector>
#include <unordered_map>
#include <sstream>

struct Solver;
struct Expression;
struct Attempt;

struct Solver
{
  std::vector<std::string> raw_equations;
  std::set<char> all_chars;
  std::set<char> possible_equals;
  void find_possible_equals();

  Attempt run();

  Solver(const std::vector<std::string>& _eqs) : raw_equations(_eqs), all_chars(std::set<char>()),
						 possible_equals(std::set<char>()) {}
};

void Solver::find_possible_equals() // determine what characters could be equals
{
  if (raw_equations.size() == 0) return;
  
  std::unordered_map<char, int> letter_count;

  for (int i = 0; i < raw_equations.size(); i++) {
    for (int j = 0; j < raw_equations[i].size(); j++) {
      if ((raw_equations[i][j] > '9' || raw_equations[i][j] < '0') &&
	  (raw_equations[i][j] != ' ')) {
	all_chars.insert(raw_equations[i][j]);
	if (letter_count.count(raw_equations[i][j]) > 0 && i != 0) {
	  if (letter_count.count(raw_equations[i][j]) == raw_equations.size()) 
	    letter_count.erase(raw_equations[i][j]);
	  letter_count[raw_equations[i][j]]++; // should not be seeing dups in line 0
	}
	else if (i == 0) { // should only be adding unique chars in line 0
	  letter_count[raw_equations[i][j]] = 1;
	}
      }
    }
  }

  // only insert characters that appear as many times as there are lines
  for (auto it = letter_count.begin(); it != letter_count.end(); it++) {
    if (it->second == raw_equations.size()) possible_equals.insert(it->first);
  }
}

Attempt Solver::run()
{
  find_possible_equals();
  std::vector<Attempt> attempts(possible_equals.size());
  int a_it = 0;
  for (auto it = possible_equals.begin(); it != possible_equals.end(); it++) {
    attempts[a_it] = Attempt(*it, all_chars, raw_equations);
    if (attempts[a_it].run()) return attempts[a_it];
    a_it++;
  }
  return attempts[0]; // attempt will have false in this
}

// attempt to solve the equation
struct Expression
{
  std::vector<char> operators;
  std::string expression;
  int value;
  bool correct; // true if expression can be evaluated, false otherwise (ie. mismatch paren)

  Expression(const std::string& expr) : expression(expr), value(0), correct(false) {}

  Expression(const std::string& original, const std::vector<char>& all_chars, const std::vector<char>& _operators,
	     const std::vector<int>& argswap) : operators(_operators), expression(original), value(0), correct(false) {
    for (int i = 0; i < expression.size() i++) {
      for (int j = 0; j < all_chars.size(); j++) {
	if (expression[i] == all_chars[j]) {
	  expression[i] = operators[argswap[j]];
	  break;
	}
      } 
    }
  }

  int evaluate();

private: // for internal PEMDAS functions, used by evaluate()
  bool evaluate_parens();
  bool evaluate_exponents();
  bool evaluate_mult_div();
};

// go through and evaluate pemdas, returns flag false if failed, otherwise value in value
bool Expression::evaluate() {
  // first start recursing with parentheses
  if (!evaluate_parens()) return false;
  // now in each recursed expression, tokenize and then evaluate
  std::vector<std::string> tokens;
  std::stringstream ss; ss << expression;
  std::string word;
  while (ss >> word) {
    tokens.push_back(word);
  }
  
  if (!evaluate_exponents() || !evaluate_mult_div() || ) return false;

  correct = true;
  return true;
}

bool Expression::evaluate_parens() // first check ( ... ), evaluate recursively
{
  for (int i = 0; i < expression.size(); i++) {
    if (expression[i] == '(') {
      int paren_count = 1;
      int start_index = i+1;
      while (paren_count > 0 && i < expression.size()) {
	i++;
	if (expression[i] == '(') paren_count++;
	else if (expression[i] == ')') paren_count--;
      }
      if (paren_count > 0) return false; // mismatch parens
      else {
	Expression e = Expression(expression.substr(start_index, i-start_index)); // recursively solve parens
	e.evaluate();
	if (e.correct) {
	  std::stringstream ss;
	  ss << expression.substr(start_index) << e.value << expression.substr(i+1);
	  expression = ss.str();
	  i = 0; // restart from beginning just to be safe
	}
      }
    }
  }
  return true; // after evaluating, there should be no parens left in expression
}

bool Expression::evaluate_exponents() // then check #^#
{
  int recent_number_index = -1;
  int recent_number_size = 0;

  //bool found_valid_expo_start = false; // if encounters ### ^, this is true.
  std::stringstream ss;
  for (int i = 0; i < expression.size(); i++) {
    if (expression[i] == ' ') continue;
    if (expression[i] == '-' || (expression[i] >= '0' && expression[i] <= '9')) {
      recent_number_index = i;
      recent_number_size = 1;
      found_num = true;
      i++;

      while (i < expression.size() && expression[i] >= '0' && expression[i] <= '9') {
	recent_number_size++;
	i++;
      }
    }
    else {

      if (expression[i] == '^') { 
	if (recent_number_index == -1 || recent_number_size == 0) return false; // break out, incorrect exp
	ss << expression.substr(recent_number_index, recent_number_size);
	int value;
	ss >> value; // get a in a^b
	i++;
	recent_number_index = -1; recent_number_size = 0;
	while (i < expression.size() && expression[i] == ' ') i++;
	while (
      }
      else { // encountered anything, / * +, whatever
	
      }
    }
  }
}

bool Expression::evaluate_mult_div()
{
  
}

// attempt algorithm:
// given two lists:
// {+, -, /, ... } {a, b, c, d, ... } which should definitely be the same length
// create argswap {0, 1, 4, 3, ...} which represents mapping between left and right lists
// permute through all possible argswaps until one works, if none work, attempt fails
struct Attempt
{
  bool result;
  bool run(char equals); // pass in which character is equals

  char equals_char;
  
  

};

int main()
{
  std::vector<std::string> lines;
  std::string line;
  while (std::getline(std::cin, line)) {
    lines.push_back(line);
  }
  Solver solver(lines);
  Attempt a = solver.run();
  if (a.result) {
    a.print_equations();
  }
}
