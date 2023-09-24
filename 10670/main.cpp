#include <iostream>
#include <string>
#include <vector>

// #define DEBUG
// #define FILEOUTPUT

#ifdef FILEOUTPUT
#include <fstream>
#endif

using namespace std;

void resolveCase(vector<string> &testCase, int caseIdx) {
    int initLoad = stoi(testCase.at(0));
    int targLoad = stoi(testCase.at(1));

    vector<string> names;
    vector<int> costs;

    #ifdef DEBUG
    cout << ">> Agency Limit: "  << agenLimit << endl;
    #endif

    std::cout << "Case " << caseIdx << endl;
    #ifdef FILEOUTPUT
    ofstream file;
    file.open("out.txt", ios_base::app);

    file << "Case " << caseIdx << endl;
    #endif


    for(size_t i = 3; i < testCase.size(); i++) {
        string agency = testCase.at(i);

        int colon = agency.find(':');
        int comma = agency.find(',');

        string agenName = agency.substr(0, colon);
        int unitVal = stoi(agency.substr(colon + 1, comma - (colon + 1)));
        int halfVal = stoi(agency.substr(comma + 1));

        #ifdef DEBUG
        cout << 
            ">> Agency name: " << agenName << endl << 
            ">> Unit value: " << unitVal << endl << 
            ">> Half value: " << halfVal << endl;
        #endif

        int currLoad = initLoad;
        int opCost = 0;
        while(halfVal <= (((currLoad + (currLoad & 1)) * unitVal) >> 1)) {
            #ifdef DEBUG
            cout << "Division limit: " << ((currLoad * unitVal) >> 1) << endl;
            cout << "Current load: " << currLoad << endl;
            #endif

            if ((currLoad >> 1) < targLoad) break;

            currLoad = currLoad >> 1;
            opCost += halfVal;
        }

        opCost += (currLoad - targLoad) * unitVal;
        #ifdef DEBUG
        cout << "Operation cost: " << opCost << endl;
        #endif

        int start = 0;
        int end = costs.size() - 1;
        
        while(start <= end) {
            int mid = (start + end) >> 1;

            #ifdef DEBUG
            cout << ">> Middle: " << mid << endl;
            #endif

            if (costs.at(mid) < opCost) start = mid + 1;
            else end = mid - 1;
        }

        #ifdef DEBUG
        cout << ">> Start: " << start << endl;
        cout << ">> Costs size: " << costs.size() << endl;
        #endif

        while(costs.size() > start && costs.at(start) == opCost) {
            if (agenName > names.at(start)) {
                start++;
            } else {
                break;
            }
        };
        costs.insert(costs.begin() + start, opCost);
        names.insert(names.begin() + start, agenName);
    }

    for(size_t i = 0; i < costs.size(); i++) {
        std::cout << names.at(i) << " " << costs.at(i) << endl;
        #ifdef FILEOUTPUT
        file << names.at(i) << " " << costs.at(i) << endl;
        #endif
    }
}

int main() {
    #ifdef DEBUG
    cout << "<< (case_amount) ";
    #endif

    int caseNum;
    cin >> caseNum;
    vector<vector<string>> cases;

	#ifdef DEBUG
    cout << ">> Amount of cases: " << caseNum << endl;
    #endif

    while(caseNum-- > 0) {
        #ifdef DEBUG
        cout << "<< (starting_load) (target_load) (agency_amount) ";
        #endif

        vector<string> tempCase;
        string startLoad, targetLoad, agencyNum;
        cin >> startLoad >> targetLoad >> agencyNum;

        #ifdef DEBUG
        cout << 
            ">> Start load: " << startLoad << endl <<
            ">> Target load: " << targetLoad << endl <<
            ">> Agency amount: " << agencyNum << endl;
        #endif

        tempCase.push_back(startLoad);
        tempCase.push_back(targetLoad);
        tempCase.push_back(agencyNum);

        int j = stoi(agencyNum);
        while(j-- > 0) {
            #ifdef DEBUG
            cout << "<< (agency_name):(unit_rate),(half_rate) ";
            #endif

            string input;
            cin >> input;

            #ifdef DEBUG
            cout << ">> Agency input: " << input << endl;
            #endif

            tempCase.push_back(input);
        }
        cases.push_back(tempCase);
    }

    int caseIdx = 0;
    for(vector<string> testCase : cases) resolveCase(testCase, ++caseIdx);
    return 0;
}