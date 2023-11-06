#include <string.h>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

// #define DEBUG
// #define COUNT
#define ONLINEJUDGE

#ifdef COUNT
#include <chrono>
#endif

template <typename T>
void fillMatrix(vector<vector<T>> &matrix, T filler, size_t x, size_t y) {
    for (size_t i = 0; i < y; i++) {
        vector<T> temp;
        for (size_t j = 0; j < x; j++) {
            temp.push_back(filler);
        }
        matrix.push_back(temp);
    }
}

#ifdef DEBUG
template <typename T>
void printMatrix(vector<vector<T>> matrix) {
    for (vector<T> vect : matrix) {
        for (T val : vect) {
            std::cout << val << " ";
        }
        std::cout << endl;
    }
    std::cout << endl;
}
#endif

int checkNode(vector<vector<int>> &lookup, vector<vector<char>> init, int current, int target, size_t depth) {
    // Look up on the lookup matrix if the value has been recorded already
    if (lookup.at(current).at(depth) != -1) {
        return lookup.at(current).at(depth);
    }

    #ifdef DEBUG
    // Print the current node
    std::cout << init.at(current).at(0) << depth << endl;
    #endif

    // Stop the recursion
    if (depth == 0) {
        int res = 0;
        if (target == current) res = 1;

        lookup.at(current).at(depth) = res;
        return res;
    }

    // Recursively check through all the children of the node
    int count = 0;
    bool root = false;
    for (char children : init.at(current)) {
        // Skip the first character that's the label of the state
        if (!root) {
            root = true;
            continue;
        }

        count += checkNode(lookup, init, children - 'A', target, depth - 1);
        #ifdef DEBUG
        std::cout << "Next node of " << init.at(current).at(0) << depth << endl;
        #endif
    }
    #ifdef DEBUG
    std::cout << "Going up with count " << count << endl;
    #endif

    // Update the lookup table and return the counted value
    lookup.at(current).at(depth) = count;
    return count;
}

int main() {
    // Initialize the file input
    #ifndef ONLINEJUDGE
    ifstream file("input.txt");
    #endif

    #ifdef COUNT
    size_t count = 0;
    auto start = chrono::high_resolution_clock::now();
    #endif
    while (true) {
        // Stop the read if there's no more

        #ifndef ONLINEJUDGE
        if (file.eof()) break;
        #endif

        // Amount of states and moves able to make
        int stateNum = -1, moveNum = -1;
        #ifdef ONLINEJUDGE
        cin >> stateNum;
        #endif
        #ifndef ONLINEJUDGE
        file >> stateNum;
        #endif

        // End of file for empty line at EOF
        #ifdef ONLINEJUDGE
        if (stateNum == EOF) break;
        #endif
        #ifndef ONLINEJUDGE
        if (file.eof()) break;
        #endif

        // Collect all the information for each state
        vector<vector<char>> states;
        vector<size_t> specialIdx; 

        // Fill with null;
        fillMatrix(states, '\0', 1, stateNum);

        // Fill the vectors with the inputs
        for (size_t i = 0; i < stateNum; i++) {
            char name, path0, path1, special;
            #ifdef ONLINEJUDGE
            cin >> name >> path0 >> path1 >> special;
            #endif
            #ifndef ONLINEJUDGE
            file >> name >> path0 >> path1 >> special;
            #endif

            states.at(i).at(0) = i + 'A';

            states.at(path0 - 'A').push_back(name);
            states.at(path1 - 'A').push_back(name);

            if (special == 'x') specialIdx.push_back(i);
        }

        // Last line is the amount of moves
        #ifdef ONLINEJUDGE
        cin >> moveNum;
        #endif
        #ifndef ONLINEJUDGE
        file >> moveNum;
        #endif
        #ifdef DEBUG
        printMatrix(states);
        #endif

        // Skip on trivial case
        if (specialIdx.size() == 0) {
            std::cout << 0 << endl;
            continue;
        }

        // Create the lookup matrix that fills with recorded values
        vector<vector<int>> found;
        fillMatrix(found, -1, moveNum + 1, stateNum);
        #ifdef DEBUG
        printMatrix(found);
        #endif

        // Check through all the children of all the special nodes and accumulate the result
        size_t depth = moveNum;
        int res = 0;
        for (size_t special : specialIdx) {
            res += checkNode(found, states, special, 0, moveNum);
        }
        std::cout << res << endl;
        #ifdef DEBUG
        printMatrix(found);
        #endif

        #ifdef COUNT
        count++;
        #endif
    }

    #ifdef COUNT
    std::cout << "Test Amount: " << count << endl;
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    std::cout << "Elapsed: " << duration.count() << endl;
    #endif
    return 0;
}

