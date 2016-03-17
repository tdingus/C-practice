/*
  question from reddit

  given two int arrays, determine if they are rotations of each other
  ie. 1,2,3,4,5 and 4,5,1,2,3 are rotations

  solution 1:
  this can be done in nlogn time by sorting both arrays, keeping track of orig position
  and then iterating and determining "rotation factor" and making all the rotation factors
  are consistent. this may run into a little trouble with duplicates

  solution 2:
  first check that both arrays are the same size

  if you double the original array, then check for second as substring, should be linear?
  interesting caveat: when you remove the substring you should always get the original if they
  are truly cyclic permutations

  this is best case O(n), worst case O(n^2) i.e. lots of duplicates:
  {3,3,3,3,3,5} vs {3,3,3,3,5,3}
 */

struct Soln1
{
  static struct SortedNumber
  {
    int value;
    int count;
    int index;

    SortedNumber(int _value, int _index) : value(_value), index(_index), count(1) {}
    
  };

};


