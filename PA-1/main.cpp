#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include <algorithm>
using namespace std;

// Read coordinates from input.txt
vector<pair<int, int>> readInput(const string& filename) {
    ifstream infile(filename);

     // Read the first line to get # of points
    int n;
    infile >> n;

    // Declare a vector pair of size n to store coordinates post-reading
    vector<pair<int, int>> points(n);
    for(int i = 0; i < n; i++){
        infile >> points[i].first >> points[i].second;
    }

    infile.close();
    return points;
}

vector<deque<pair<int, int>>> findMaximalLayers(vector<pair<int, int>>& points){
    // Sort the points in descending order (x-coordinate)
    sort(points.begin(), points.end(), [](const pair<int, int> &a, const pair<int, int> &b) {
        // If 2 points have the same x-coordinate, then sort by descending y-coordinate
        return (a.first > b.first) || (a.first == b.first && a.second > b.second);
    });

    // Make each layer a queue to easily add/remove
    vector<deque<pair<int, int>>> layers;
};