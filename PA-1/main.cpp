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
    vector<vector<Point>> layers;

    for (const auto &p: points) {
        // Check is a point is assigned to some Mi
        bool assigned = false;

        // First try placing in an existing layer
        for (auto &layer: layers) {
            // If the LAST point in the layer being processed has a smaller y-value than the current point
            if(layer.back().second < p.second){
                // Then place the current point in this layer
                layer.push_back(p);
                assigned = true;
                break;
            }
        }

        // Create a new layer if point wasn't assigned to any layer
        if (!assigned){
            layers.push_back({p});
        }
    }

    for (size_t i = 0; i < layers.size(); i++) {
        // Sort each layer by y in ascending order
        sort(layers[i].begin(), layers[i].end(), [](const Point &a, const Point &b) {
            return a.second < b.second;
        });
        
        // Write all points in this layer to output.txt
        for (const auto &p : layers[i]) {
            output << p.first << " " << p.second << "\n";
        }
        
        // Add a blank line between layers
        // Exclude last layer from this
        if (i != layers.size() - 1) {
            output << "\n";
        }
    }  

    return 0;
}