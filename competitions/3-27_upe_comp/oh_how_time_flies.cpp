/*
 Problem: https://www.hackerrank.com/contests/upe-hard/challenges/oh-how-time-flies

 In essence, you're given a board that represents your room (an 8x8 square),
 and there's 5 objects you need to grab in order (represented by chars 1-5).
 Your starting position is labelled s, exit (after grabbing the 5th) is x.

 There are also walls in the room, and you can obviously not cross through those.

 Sample input:
 +--------+
 |s|4     |
 | |  ==  |
 | |  ==5 |
 | |  =x  |
 | |  ====|
 | |3     |
 | |===== |
 |1     2 |
 +--------+
 Sample output:
 d
 d
 d
 d
 d
 d
 d
 r
 r
 r
 r
 r
 r
 r
 u
 u
 l
 l
 l
 l
 l
 u
 u
 u
 u
 u
 r
 r
 r
 r
 d
 d
 d
 l
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

struct Point
{
    unsigned int x, y;
    Point() :
            x(0),
            y(0)
    {
    }
    Point(const Point& other) :
            x(other.x),
            y(other.y)
    {
    }
    Point(unsigned int _x, int _y) :
            x(_x),
            y(_y)
    {
    }
};

struct DijkstraPoint: public Point
{
    unsigned int distance; // distance from start (in terms of moves)
    std::string shortestPath; // should be of length distance, contents will be in form d\nr\nl etc
    bool completed; // in the algorithm, if it is popped from the queue
    DijkstraPoint() :
            Point(),
            distance(999),
            shortestPath(""),
            completed(false)
    {
    }
    DijkstraPoint(unsigned int _x, unsigned int _y) :
            Point(_x, _y),
            distance(999),
            shortestPath(""),
            completed(false)
    {
    }
    DijkstraPoint(unsigned int _x, unsigned int _y, unsigned int _d) :
            Point(_x, _y),
            distance(_d),
            shortestPath(""),
            completed(false)
    {
    }
};

struct PathFinder
{

    struct Comparator
    {
        bool operator()(const DijkstraPoint* one, const DijkstraPoint* other)
        {
            return one->distance > other->distance;
        }
    };

    const std::vector<std::string>& room;
    const unsigned int room_width;
    const unsigned int room_length;

    std::priority_queue<DijkstraPoint*, std::vector<DijkstraPoint*>, Comparator> pt_pq;
    Point start, end;
    std::vector<std::vector<DijkstraPoint> > roomPts; // represents points in room

    PathFinder(const std::vector<std::string>& _room, unsigned int width, unsigned int length, const Point& _s,
               const Point& _e) :
            room(_room),
            room_width(width),
            room_length(length),
            pt_pq(std::priority_queue<DijkstraPoint*, std::vector<DijkstraPoint*>, Comparator>()),
            start(_s),
            end(_e),
            roomPts(std::vector<std::vector<DijkstraPoint> >(_room.size(), std::vector<DijkstraPoint>(_room[0].size())))
    {
        for(unsigned int i = 0; i < roomPts.size(); i++)
        {
            for(unsigned int j = 0; j < roomPts.size(); j++)
            {
                if(i == start.x && j == start.y)
                {
                    roomPts[i][j] = DijkstraPoint(i, j, 0);
                }
                else
                {
                    roomPts[i][j] = DijkstraPoint(i, j);
                }
            }
        }
    }

    bool checkWall(char in);
    std::string run();
};

// checkWall to isWall

bool PathFinder::checkWall(char in)
{
    if(in == '+' || in == '-' || in == '|' || in == '=') return true;
    return false;
}

std::string PathFinder::run() // use dijkstra's algorithm
{
    DijkstraPoint* next;
    pt_pq.push(&roomPts[start.x][start.y]);
    while(!(roomPts[end.x][end.y].completed) && !pt_pq.empty() && ((next = pt_pq.top())->distance != 999))
    {
        pt_pq.pop(); // pop current shortest path (at start will be 0)

        // then check paths
        std::vector<std::string> paths =
            { "d\n", "u\n", "l\n", "r\n" };
        std::vector<int> modifiers =
            { 1, -1, 0, 0 };
        for(unsigned int i = 0; i < paths.size(); i++)
        {
            int child_x = next->x + modifiers[i];
            int child_y = next->y + modifiers[paths.size() - 1 - i];
            if((child_x >= room_width) || (child_y >= room_length))
            {
                continue;
            }
            if(!(roomPts[child_x][child_y].completed) && (roomPts[child_x][child_y].distance > next->distance + 1)
                    && !(checkWall(room[child_x][child_y])))
            {
                roomPts[child_x][child_y].distance = next->distance + 1;
                roomPts[child_x][child_y].shortestPath = next->shortestPath + paths[i];
                pt_pq.push(&roomPts[child_x][child_y]);
            }
        }
    }
    return roomPts[end.x][end.y].shortestPath;
}

int do_main(const std::vector<std::string>& room)
{
    std::unordered_map<char, Point> points;
    std::vector<char> special_pts =
        { 's', '1', '2', '3', '4', '5', 'x' };
    unsigned int room_width = 0;
    for(int a = 0; a < room.size(); a++)
    {
        std::string line = room[a];
        if(room_width == 0) room_width = line.size();
        for(unsigned int x = 0; x < line.size(); x++)
        {
            for(unsigned int y = 0; y < special_pts.size(); y++)
            {
                if(line[x] == special_pts[y])
                {
                    points[line[x]] = Point(a, x);
                }
            }
        }
    }

    std::string final_solution = "";
    for(unsigned int i = 0; i < special_pts.size() - 1; i++)
    {
        PathFinder pt(room, room_width, room.size(), points[special_pts[i]], points[special_pts[i + 1]]);
        std::string output = pt.run();
        if(output == "")
        {
            std::cout << special_pts[i + 1] << " cannot be reached with this setup, aborting" << std::endl;
            break;
        }
        final_solution += pt.run();
    }
    std::cout << final_solution << std::endl;
    return 0;
}

int main()
{
    const std::vector<std::string> rooms[] =
        {
            { "s 4     ",
              "        ",
              "      5 ",
              "     x  ",
              "        ",
              "  3     ",
              "        ",
              "1     2 "
            },
            { "s|4     ",
              " |  ==  ",
              " |  ==5 ",
              " |  =x  ",
              " |  ====",
              " |3     ",
              " |===== ",
              "1     2 "
            },
            {
                // empty one is important.
            }
        };
    unsigned int i = 0;
    while(rooms[i].size() > 0)
    {
        do_main(rooms[i]);
        i++;
    }
}
