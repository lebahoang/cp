#include <stdio.h>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

vector<string> split(string a, string delim) {
    vector<string> rs;
    int i = 0;
    while(i < a.length()) {
        int pos = a.find(delim, i);
        if (pos == string::npos) {
            pos = a.length();
        }
        rs.push_back(a.substr(i,pos-i));
        i = pos+1;
    }
    return rs;
}

int main()
{
    // read the string filename
    string filename = "x.txt";
    // cin >> filename;
    ifstream infile;
    infile.open(filename);
    string oneLine;
    vector<vector<string>> line;
    while (getline(infile, oneLine)) {
        vector<string> a = split(oneLine, " ");
        line.push_back(a);
    }
    unordered_map<string, int> m;
    for (int i = 0; i < line.size(); i++) {
        int length = line[i][3].length();
        string ts = line[i][3].substr(1);
        // printf("%s\n", ts.c_str());
        if (m.find(ts) != m.end()) {
            m[ts]++;
        } else {
            m[ts] = 1;
        }
    }
    ofstream outfile;
    outfile.open("req_" + filename);
    unordered_map<string, int>::iterator p;
    for (p = m.begin(); p != m.end(); p++) {
        if (p->second > 1) {
            printf("%s\n", p->first.c_str());
            outfile << p->first << "\n";
        }
    }
    outfile.close();
    return 0;
}