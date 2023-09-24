#include <iostream>
#include <string>
#include <vector>

using namespace std;

// #define DEBUG
// #define FILEOUT

#ifdef FILEOUT
#include <fstream>
#endif

int main() {
    vector<int> results;
    while(true) {
        #ifdef DEBUG
        cout << "<< [canvasY] [canvasX] [toolY] [toolX]: ";
        #endif

        unsigned int canvasY, canvasX, toolY, toolX;
        cin >> canvasY >> canvasX >> toolY >> toolX;

        if ((canvasY | canvasX | toolY | toolX) == 0) break;

        vector<string> rows;
        vector<string> startRows;

        for (unsigned int i = 0; i < canvasY; i++) {
            #ifdef DEBUG
            cout << "<< [row:size=" << canvasX << "]: ";
            #endif

            string row;
            cin >> row;

            rows.push_back(row);
            startRows.push_back(string(canvasX, '0'));
        }

        int op = 0;
        for (unsigned int y = 0; y <= canvasY - toolY; y++) {
            for (unsigned int x = 0; x <= canvasX - toolX; x++) {
                int val = rows.at(y).at(x) & 1;
                int prev = startRows.at(y).at(x) & 1;

                if ((val ^ prev) == 1) {
                    #ifdef DEBUG
                    cout << ">> x:" << x << ",y:" << y << endl;
                    #endif
                    op++;
                    for (unsigned int ty = y; ty < y + toolY; ty++) {
                        for (unsigned int tx = x; tx < x + toolX; tx++) {
                            startRows.at(ty).at(tx) = startRows.at(ty).at(tx) ^ 1;
                        }
                    }
                }
            }
        }

        bool eq = true;
        for (unsigned int i = 0; i < rows.size(); i++) {
            eq = rows.at(i) == startRows.at(i);
            if (!eq) break;
        }
        results.push_back(eq ? op : -1);
    }

    #ifdef FILEOUT
    ofstream file;
    file.open("./out.txt");
    #endif
    for (int result : results) {
        #ifdef FILEOUT
        file << result << endl;
        #endif
        cout << result << endl;
    }
    return 0;
}