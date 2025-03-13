#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map> // Built-in RBT
using namespace std;

// Global counter
long counter = 0;

// Function prototype
vector<pair<int, int>> readInput(const string& filename);
vector<vector<pair<int, int>>> findMaximalLayers(vector<pair<int, int>>& points);
void printLayersToFile(const string& filename, const vector<vector<pair<int, int>>>& layers);

// Main function
int main(void){
    string inputFile = "./input.txt";
    string outputFile = "output.txt";

    vector<pair<int, int>> points = readInput(inputFile);
    vector<vector<pair<int, int>>> layers = findMaximalLayers(points);
    printLayersToFile(outputFile, layers);

    cout << "Total # of operations: " << counter << endl;
    cout << "Total time taken: O(nlogn + nlogn) = O(nlogn)" << endl;

    return 0;
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
        return (a.first > b.first) || (a.first == b.first && a.second < b.second);
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
        auto iterator = staircase.lower_bound(p.second);
        if (iterator != staircase.begin()) --iterator;
        // If upper.bound(p.sec) returns staircase.end -> p.second is smaller than all existing y-values
        // ...so a new layer needs to be created, for which layers.size() provides the index
        // Else, an existing layer is found, so p will be placed in that index (aka iterator value)
        int layerIndex = (iterator != staircase.end() && iterator->first <= p.second) ? iterator->second : layers.size();

        // Create a new layer if the point doesn't fit in any existing layer
        if (layerIndex == layers.size()){
            layers.push_back({});
        }

        // Add the point to the layer
        layers[layerIndex].push_back(p);

        // Update the staircase
        staircase[p.second] = layerIndex;
    }

    return layers;
};

void printLayersToFile(const string& filename, const vector<vector<pair<int, int>>>& layers){
    ofstream outfile(filename);

    for(size_t i = 0; i < layers.size(); i++){
        // Begin each new layer with a newline
        if(i > 0) outfile << "\n";

        // Sort each layer by y in ascending order
        // ...or x ascending if any y's are equal
        vector<pair<int, int>> sortedLayer = layers[i];
        sort(sortedLayer.begin(), sortedLayer.end(), [](const pair<int, int> &a, const pair<int, int> &b) {
            counter++;
            return (a.second < b.second) || (a.second == b.second && a.first > b.first);
        });

        // Iterating over each point in each sorted layer
        for(const auto &p : sortedLayer) {
            outfile << p.first << " " << p.second << "\n";
        }
    }
    outfile.close();
}