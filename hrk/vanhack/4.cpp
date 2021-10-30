#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <math.h>
#include <vector>
#include <string>
#include <random>

using namespace std;

long solution(int n, vector<int> affected, vector<int> poisonous) {
    int m[100005];
    for (int i = 0; i <= n; i++) {
        m[i] = n+1;
    }
    for (int i = 0; i < affected.size(); i++) {
        if (affected[i] > poisonous[i]) {
            int t = affected[i];
            affected[i] = poisonous[i];
            poisonous[i] = t;
        }
    }
    for (int i = 0; i < affected.size(); i++) {
        if (m[affected[i]] > poisonous[i]) {
            m[affected[i]] = poisonous[i];
        }
    }
    int furthest = m[n];
    long rs = 0;
    for (int i = n; i >= 1; i--) {
        if (m[i] < furthest) {
            furthest = m[i];
        }
        // printf("%d %d %d\n", i, m[i], furthest-i);
        rs += (long)(furthest-i);
    }
    return rs;
}

long bioHazard(int n, vector<int> affected, vector<int> poisonous) {
    int m[100005];
    for (int i = 0; i < affected.size(); i++) {
        if (affected[i] > poisonous[i]) {
            int t = affected[i];
            affected[i] = poisonous[i];
            poisonous[i] = t;
        }
    }
    for (int i = 0; i < affected.size(); i++) {
        if (m[affected[i]] == 0 || m[affected[i]] > poisonous[i]) {
            m[affected[i]] = poisonous[i];
        }
    }
    int furthest = n;
    long rs = 0;
    for (int i = n; i >= 1; i--) {
        if (m[i] == i) {
            if (m[i]-1 > 0 && m[i]-1 < furthest) {
                furthest = m[i]-1;
            }
            continue;
        }
        if (m[i]-1 > 0 && (m[i]-1) < furthest) {
            furthest = m[i]-1;
        }
        // printf("%d %d %d\n", i, m[i], furthest-i+1);
        rs += (long)(furthest-i+1);
    }
    return rs;
}


int main () {
    // int n = 8;
    // vector<int> affected = {1,5,5};
    // vector<int> poisonous = {2,3,4};
    // int n = 5;
    // vector<int> affected = {1,2};
    // vector<int> poisonous = {3,5};
    // int n = 8;
    // vector<int> affected = {2,3,4,3};
    // vector<int> poisonous = {8,5,6,4};
    // printf("%ld %ld\n", bioHazard(n, affected, poisonous), solution(n, affected, poisonous));
    random_device rd; // obtain a random number from hardware
    mt19937 eng(rd()); // seed the generator
    uniform_int_distribution<> distribution(1, 20000); // define the range
    for (int i = 0; i < 100; i++) {
        int n = distribution(eng);
        int m = distribution(eng);
        uniform_int_distribution<> distribution1(1, n); // define the range
        vector<int> affected;
        vector<int> poisonous;
        for (int j = 0; j < m; j++) {
            affected.push_back(distribution1(eng));
            poisonous.push_back(distribution1(eng));
        }
        if (solution(n, affected, poisonous) != bioHazard(n, affected, poisonous)) {
            string s = "";
            string ss = "";
            for (int j = 0; j < m; j++) {
                s += to_string(affected[j]) + " ";
                ss += to_string(poisonous[j]) + " ";
            }
            printf("%s\n", s.c_str());
            printf("%s\n", ss.c_str());
        }
    }
    return 0;
}