#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

#define BUFFER_SIZE 8096

using namespace std;

string readFile(const char *filename);
void printVector(vector<string>);
vector<string> split(string s, string d);
