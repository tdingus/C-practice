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
  

  struct PointHash
  {
    std::size_t operator()(const Point& pt) const
    {
      return std::hash<int>()(pt.x) ^ std::hash<int>()(pt.y);
    }
  };
  
  struct PointEqual
  {
    bool operator()(const Point& lhs, const Point& rhs) const
    {
      return (lhs.x == rhs.x) && (lhs.y == rhs.y);
    }
  };

  Point() : x(0), y(0) {}
  Point(int _x, int _y) : x(_x), y(_y) {}
};

struct PathFinder
{
  static std::unordered_map<Point, int,Point::PointHash, Point::PointEqual> 
  countChildren(const std::initializer_list<std::initializer_list<int>>& input);
};

std::unordered_map<Point, int, Point::PointHash, Point::PointEqual>
PathFinder::countChildren(const std::initializer_list<std::initializer_list<int>>& input)
{
  std::unordered_map<Point, int, Point::PointHash, Point::PointEqual> childrenMap(100);
  return childrenMap;
}

int main()
{
  PathFinder::countChildren({{1,2,3},{2,3,4},{5,6,7}});
}
