#include <cstdlib>
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

struct Point {
    int x;
    int y;
    Point() : x(0), y(0) {}
    Point(int a, int b) : x(a), y(b) {}
};
 

class Solution {
private:
    class EqualFn {
    public:
        bool operator() (double const& t1, double const& t2) const
        {
            return (abs(t1 - t2) < 1e-9);
        }
    };

public:
    int maxPoints(vector<Point> &points) {
        int maxCount;
        if (points.size() > 0) {
            maxCount = 1;
        } else {
            return 0;
        }

        // key = gradient
        // value = count
        unordered_map<double, int, hash<double>, EqualFn> countMap;
        for (int i = 0; i < points.size(); ++i) {
            Point basePoint = points[i];

            // treat repeated basePoint separately
            int repeats = 1;
            for (int j = i + 1; j < points.size(); ++j) {
                Point nextPoint = points[j];
                double m;
                if (abs(nextPoint.x - basePoint.x) < 1e-9) {
                    if (abs(nextPoint.y - basePoint.y) < 1e-9) {
                        // repeats increase the count to every line through this basePoint
                        repeats += 1;
                        continue;
                    } else {
                        // vertical line
                        m = numeric_limits<double>::max();
                    }
                } else {
                    m = 1.0*(nextPoint.y - basePoint.y) / (nextPoint.x - basePoint.x);
                }
                unordered_map<double, int, hash<double>, EqualFn>::iterator it = countMap.find(m);
                if (it == countMap.end()) {
                    countMap.insert(pair<double, int>(m, 1));
                } else {
                   // increment count
                    it->second += 1;
                }
            }
            // find maxCount of this round
            
            // if only repeated basePoints and no other points
            if (countMap.size() == 0) {
                if (repeats > maxCount) {
                    maxCount = repeats;
                }
                continue;
            }

            for (unordered_map<double, int, hash<double>, EqualFn>::iterator it = countMap.begin(); it != countMap.end(); ++it) {
                // increase by number of repeats to all lines
                if (it->second + repeats > maxCount) {
                    maxCount = it->second + repeats;
                }
            }
            // each round is independent
            countMap.clear();
        }

        return maxCount;
    }
};


int main() {
    Solution s;
    vector<Point> pts;
    pts.push_back(Point(84,250));
    pts.push_back(Point(0,0));
    pts.push_back(Point(1,0));
    pts.push_back(Point(0,-70));
    pts.push_back(Point(0,-70));
    pts.push_back(Point(1,-1));
    pts.push_back(Point(21,10));
    pts.push_back(Point(42,90));
    pts.push_back(Point(-42,-230));

    cout << s.maxPoints(pts) << endl;
}