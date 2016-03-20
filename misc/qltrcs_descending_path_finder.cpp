/*
  problem from some phone screen question blog

  given a 2d array of values and an input index and output index, return true iff
  there is a path from the input to output index given that you can only move to
  smaller values and can only move up/down/left/right

  solution: recursive find, but you can make small optimizations on the search
  such as ignoring points that are dead ends. also in any given path there is the
  caveat that you should never return to a point that you've been to, simply because
  that makes no sense logically (if a path exists to the output which has a duplicate
  there must be a path to the output that doesn't have a duplicate).

  NOTE: this solution uses unordered map, which requires -std=c++11
 */
#include <unordered_map>
#include <vector>
#include <functional>

struct Point
{
  int x;
  int y;
  bool operator==(const Point& other)
  {
    return (other.x == x && other.y == y);
  }
  static size_t point_hash(const Point& pt) // used for unordered_map
  {
    return pt.x + 100*pt.y;
  }
  Point(int _x, int _y) : x(_x), y(_y) {}
};

size_t point_hash(const Point& pt)
{
  return std::hash<int>()(pt.x) ^ std::hash<int>()(pt.y);
}

struct PathFinder
{
  static std::unordered_map<Point, int> countChildren(const int** array);
};

std::unordered_map<Point, int> PathFinder::countChildren(const int** _array)
{
  std::unordered_map<Point, int, decltype(&point_hash)> 
    childrenMap(100, point_hash);
  std::vector<std::vector<int> > array(_array);
  return childrenMap;
}

int main()
{

}
