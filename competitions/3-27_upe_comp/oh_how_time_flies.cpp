/*
  Problem: https://www.hackerrank.com/contests/upe-hard/challenges/oh-how-time-flies
  <solution incomplete>
  In essence, you're given a board that represents your room (an 8x8 square),
  and there's 5 objects you need to grab in order (represented by chars 1-5).
  Your starting position is labelled s, exit (after grabbing the 5th) is x.
  
  There are also walls in the room, and you can obviously not cross through those.

  Solution: This can be broken up into subproblems: this is equal to the shortest path
  from s to 1, 1 to 2, 2 to 3, 3 to 4, etc. Each of these subproblems can be solved with an
  adaptation of Dijkstra's algorithm.

  SOLN USES UNORDERED MAP, WHICH REQUIRES -std=c++11
 */

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <unordered_map>

struct Point // used for dijkstras
{
  // usually, I would use underscore for member data to make it special. 
  // also, conceptually, a point has no distance. I wonder if it is possible to remove distance from this struct.
  int x, y, distance;
  Point() : x(0), y(0), distance(999) {}
  Point(const Point& other) : x(other.x), y(other.y), distance(other.distance) {}
  Point(int _x, int _y) : x(_x), y(_y), distance(999) {}
  Point(int _x, int _y, int _d) : x(_x), y(_y), distance(_d) {}
  bool operator<(const Point& other) const {return distance < other.distance;} // implemented for the pq
};

// a little descripton what PathFinder does
struct PathFinder
{
  // you may use a const referenced map if you are not changing it and do not need a copy
  const std::vector<std::string>& map; // oh. it is not a map, how about locations?
  std::vector<std::vector<std::string> > pathMap; // values here are valid paths ie. d\nd\nu
  std::vector<std::vector<bool> > completeMap; // used for the dijkstra's algo
  Point start, end;
  PathFinder(const std::vector<std::string >& _map, Point _s, Point _e) :
    map(_map), start(_s), end(_e) 
  {
    pathMap = std::vector<std::vector<std::string> >(map.size(), std::vector<std::string>(map[0].size(), "-1"));  
    completeMap = std::vector<std::vector<bool> >(map.size(), std::vector<bool>(map[0].size(), false));
  }

  bool checkWall(char in);
  std::string run();
};

bool PathFinder::checkWall(char in)
{
  if (in == '+' || in == '-' || in == '|' || in == '=') return true;
  return false;
}

std::string PathFinder::run()
{
  std::priority_queue<Point> pt_pq;
  pathMap[start.x][start.y] = "";
  start.distance = 0;
  pt_pq.push(start);
  //std::cout << start.x << "," << start.y << "," << end.x << "," << end.y << std::endl;
  while (!completeMap[end.x][end.y] && !pt_pq.empty()) { 
    Point next = pt_pq.top();
    pt_pq.pop();
    //std::cout << "next: " << next.x << "," << next.y << std::endl;
    if (completeMap[next.x][next.y]) continue;
    else completeMap[next.x][next.y] = true;
    // the next four if section is very similar if not the same consider using a function to 
    // replace them, so it becomes four lines, instead.
    if (!completeMap[next.x+1][next.y] && !checkWall(map[next.x+1][next.y]) &&
	(pathMap[next.x+1][next.y].size() > (pathMap[next.x][next.y] + "d\n").size() || pathMap[next.x+1][next.y] == "-1")) {
      pathMap[next.x+1][next.y] = pathMap[next.x][next.y] + "d\n";
      pt_pq.push(Point(next.x+1, next.y, next.distance + 1));
    }
    if (!completeMap[next.x-1][next.y] && !checkWall(map[next.x-1][next.y]) &&
	(pathMap[next.x-1][next.y].size() > (pathMap[next.x][next.y] + "u\n").size() || pathMap[next.x-1][next.y] == "-1")) {
      pathMap[next.x-1][next.y] = pathMap[next.x][next.y] + "u\n";
      pt_pq.push(Point(next.x-1, next.y, next.distance + 1));
    }
    if (!completeMap[next.x][next.y+1] && !checkWall(map[next.x][next.y+1]) &&
	(pathMap[next.x][next.y+1].size() > (pathMap[next.x][next.y] + "r\n").size() || pathMap[next.x][next.y+1] == "-1")) {
      pathMap[next.x][next.y+1] = pathMap[next.x][next.y] + "r\n";
      pt_pq.push(Point(next.x, next.y+1, next.distance + 1));
    }
    if (!completeMap[next.x][next.y-1] && !checkWall(map[next.x][next.y-1]) &&
	(pathMap[next.x][next.y-1].size() > (pathMap[next.x][next.y] + "l\n").size() || pathMap[next.x][next.y-1] == "-1")) {
      pathMap[next.x][next.y-1] = pathMap[next.x][next.y] + "l\n";
      pt_pq.push(Point(next.x, next.y-1, next.distance + 1));
    }
  }
  return pathMap[end.x][end.y];
}

int main() {
  int size = 10;
  std::string line;
  std::vector<std::string> map;
  
  std::unordered_map<char, Point> points;
  std::vector<char> special_pts = {'s', '1', '2', '3', '4', '5', 'x'};

  for (int a = 0; a < size; a++) {
    std::getline(std::cin, line);
    map.push_back(line);
    for (unsigned int x = 0; x < line.size(); x++) {
      for (unsigned int y = 0; y < special_pts.size(); y++) {
	if (line[x] == special_pts[y]) {
	  points[special_pts[y]] = Point(map.size()-1, x);
	}
      }
    }
  }

  std::string final_solution = "";
  for (unsigned int i = 0; i < special_pts.size()-1; i++) {
    //    std::cout << points[special_pts[i]].x << std::endl;
    PathFinder pt(map, points[special_pts[i]], points[special_pts[i+1]]);
    final_solution += pt.run();
  }

  std::cout << final_solution << std::endl;
  return 0;
}
