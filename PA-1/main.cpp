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

vector<deque<pair<int, int>>> findMaximalLayers(vector<pair<int, int>>& points){
    // Sort the points in descending order (x-coordinate)
    sort(points.begin(), points.end(), [](const pair<int, int> &a, const pair<int, int> &b) {
        // If 2 points have the same x-coordinate, then sort by descending y-coordinate
        return (a.first > b.first) || (a.first == b.first && a.second > b.second);
    });

    // Make each layer a queue to easily add/remove
    vector<deque<pair<int, int>>> layers;

    // Assign each point to the first layer
    for(const auto &p : points){

        // Check if a point has been assigned to a layer
        bool assigned = false;

        // For each layer, find the FIRST layer where the point p can be placed
        for(auto &layer : layers) {

            // p is NOT dominated by any point in this layer, so add it
            // Why is it not dominated? Bc its y-coordinate is greater that the last point in the layer
            if (p.second > layer.back().second) {
                layer.emplace_back(p);
                assigned = true;

                // No longer check other layers
                break;
            }
        }

        // If p isn't assigned to any layer, create a new layer for it to be assigned in
        if(!assigned){

            // Add it to the new queue
            layers.emplace_back(deque<pair<int, int>>{p});
        }
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