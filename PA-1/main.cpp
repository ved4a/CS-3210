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

int main(void){
    // Input output, reading writing respectively
    ifstream input("input.txt");
    ofstream output("output.txt");

    // Store # of points in 'n'
    int n;
    input >> n;

    // Store ALL points in a vector
    vector<Point> points(n);

    // Read points from input.txt [.first is x, .second is y]
    for (int i = 0; i < n; i++){
        input >> points[i].first >> points[i].second;
    }

    // Sort points
    // Best: descending x
    // If x's are same: ascending y
    sort(points.begin(), points.end(), CompareX());

    // Each layer is a VECTOR of vectors (aka vector of POINTS)
    vector<vector<Point>> layer;



    return 0;
}