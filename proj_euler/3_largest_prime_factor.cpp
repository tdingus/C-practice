/*
  The prime factors of 13195 are 5, 7, 13 and 29.

  What is the largest prime factor of the number 600851475143 ?

  (Complete)
 */
#include <iostream>
#include <vector>

bool check_prime(const unsigned long n) // only check up to sqrt(n)
{
  if (n <= 1) return false;
  for (unsigned long i = 2; i < n && i*i <= n; i++) {
    if (n % i == 0) return false;
  }
  return true;
}

unsigned long largest_prime_factor(const unsigned long n) // O(n), runs sqrt(n) times and each can have sqrt(n) for check_prime
{
  unsigned long largest_factor = 0;
  for (unsigned long i = 1; i < n && i*i <= n; i++) {
    if (n % i == 0 && check_prime(i)) largest_factor = i;
  }
  return largest_factor;
}

int main()
{
  std::cout << largest_prime_factor(600851475143) << std::endl;
}
