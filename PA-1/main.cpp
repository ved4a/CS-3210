#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include <algorithm>
#include <map> // Built-in RBT
using namespace std;

// Global counter
long counter = 0;

// Function headers
vector<pair<int, int>> readInput(const string& filename);
vector<deque<pair<int, int>>> findMaximalLayers(vector<pair<int, int>>& points);
void printLayersToFile(const string& filename, const vector<deque<pair<int, int>>>& layers);

// Main function
int main(void){
    string inputFile = "./input.txt";
    string outputFile = "output.txt";

    vector<pair<int, int>> points = readInput(inputFile);
    vector<deque<pair<int, int>>> layers = findMaximalLayers(points);
    printLayersToFile(outputFile, layers);
}

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

vector<vector<pair<int, int>>> findMaximalLayers(vector<pair<int, int>>& points){
    // Sort the points in descending order (x-coordinate)
    sort(points.begin(), points.end(), [](const pair<int, int> &a, const pair<int, int> &b) {
        // If 2 points have the same x-coordinate, then sort by descending y-coordinate
        counter++;
        return (a.first > b.first) || (a.first == b.first && a.second > b.second);
    });

    // Make each layer a queue to easily add/remove
    vector<vector<pair<int, int>>> layers;

    // Invoke RBT as staircase
    // Key: y value of a point
    // Value: index of layer where it's stored [M_i]
    map<int, int> staircase;

    // Assign each point to the first layer
    for(const auto &p : points){
        counter++;

        // Points to the immediate next element just greater than y-value
        auto iterator = staircase.upper_bound(p.second);
        // If upper.bound(p.sec) returns staircase.end -> p.second is smaller than all existing y-values
        // ...so a new layer needs to be created, for which layers.size() provides the index
        // Else, an existing layer is found, so p will be placed in that index (aka iterator value)
        int layerIndex = (iterator == staircase.end()) ? layers.size() : iterator->second;
    }

    return layers;
};

void printLayersToFile(const string& filename, const vector<deque<pair<int, int>>>& layers){
    ofstream outfile(filename);

    // Iterating over each layer
    for(size_t i = 0; i < layers.size(); i++){
        if(i > 0) outfile << "\n";

        // Iterating over each point in each layer[i]
        for(const auto &p : layers[i]) {
            outfile << p.first << " " << p.second << "\n";
        }
    }
    outfile.close();
}