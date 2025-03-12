#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

// Read coordinates from input.txt
vector<pair<int, int>> readCoordinates(const string& filename) {
    ifstream infile(filename);

     // Read the first line to get # of points
    int n;
    infile >> n;

    // Declare a vector pair to store coordinates post-reading
    vector<pair<int, int>> points(n);
    for(int i = 0; i < n; i++){
        infile >> points[i].first >> points[i].second;
    }
    infile.close();
    return points;
}