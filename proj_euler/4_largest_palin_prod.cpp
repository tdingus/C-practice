/*
  A palindromic number reads the same both ways. The largest palindrome made from the product of two 2-digit numbers is 9009 = 91 × 99.

  Find the largest palindrome made from the product of two 3-digit numbers.
 */

bool check_palindrome(int n)
{
  std::vector<int> digits;
  while (n > 0) {
    digits.push_back(n%10);
    n -= n%10;
    n /= 10;
  }
  for (int i = 0; i < digits.size() - 1 - i && i < digits.size(); i++) {
    if (digits[i] != digits[digits.size() - 1 - i]) return false;
  }
  return true;
}

int main()
{
  int first[] = {1,0,0};
  int second[] = {1
}
