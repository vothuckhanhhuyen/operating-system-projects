#include <windows.h>
#include<bits/stdc++.h>
#include <string>
#include <iostream>
#include<vector>

using namespace std;

string rawCommands;
boolean validCommands;

string trim(string command) {
    int j = -1, k = command.length(), g = command.length();
    for(int i = 0; i < g; ++i) {
        if(command[i] == ' ') {
            j = i;
        }
        else {
            break;
        }
    }

    for(int i = g - 1; i > j; i--) {
        if(command[i] == ' ') {
            k = i;
        }
        else break;
    }
    string s = "";
    for(int i = j + 1; i < k; ++i) {
        s = s + command[i];
    }
    return s;
}

vector<string> createJobs(string command) {
	vector<string> jobs;
	string s = "";
	int a = command.length();
	for(int i = 0; i < a; ++i) {
		if(command[i] != '>') {
			s = s + command[i];
		}
		else {
			jobs.push_back(s);
			s = "";
		}
	}
	jobs.push_back(s);
	return jobs;
}