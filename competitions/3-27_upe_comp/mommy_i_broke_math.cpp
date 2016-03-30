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

  solution: glorified, but organized guess in check. tokenize all the strings, separate lines into
  equation objects that come up with mappings that work. go through all the mappings that work and
  
 */
