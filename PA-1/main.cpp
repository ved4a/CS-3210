#include <iostream>
#include <fstream> // File handling
#include <vector> // Vectors to store points
#include <algorithm> // Sorting

using namespace std;

// A point is a pair of integers
typedef pair<int, int> Point;

// Comparator for sorting points
// Sort by descending x-coordinate first
// If x-coordinates are equal, sort by ascending y-coordinate
struct CompareX {
    bool operator()(const Point &a, const Point &b) const {
        return a.first > b.first || (a.first == b.first && a.second < b.second);
    }
};