#ifndef __UTILILITES__
#define __UTILILITES__
#include <map>
#include <string>
#include <vector>

#define BUFFER_SIZE 4145152

struct comp {
  bool operator()(const std::string &lhs, const std::string &rhs) const;
};

typedef std::map<std::string, std::string, comp> cimap;

std::string readFile(const char *filename);
std::string getExtention(std::string filePath);
void printVector(std::vector<std::string>);
std::vector<std::string> split(std::string s, std::string d);

std::string urlEncode(std::string const &);
std::string urlDecode(std::string const &);

#endif
