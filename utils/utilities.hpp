#ifndef __UTILILITES__
#define __UTILILITES__
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>

#define BUFFER_SIZE 8096

using namespace std;
struct comp {
    bool operator() (const string& lhs, const string& rhs) const;
};

typedef map<string, string, comp> cimap;

string readFile(const char *filename);
void printVector(vector<string>);
vector<string> split(string s, string d);

std::string urlEncode(std::string const &);
std::string urlDecode(std::string const &);

#endif
