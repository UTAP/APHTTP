#ifndef __UTILILITES__
#define __UTILILITES__
#include <cstring>
#include <map>
#include <string>
#include <vector>

#define BUFFER_SIZE 4145152

struct comp {
  bool operator()(const std::string &lhs, const std::string &rhs) const;
};

typedef std::map<std::string, std::string, comp>
    cimap; // Case-Insensitive <string, string> map

std::string readFile(const char *filename);
std::string readFile(std::string filename);
std::string getExtension(std::string filePath);
void printVector(std::vector<std::string>);
std::vector<std::string> split(std::string s, std::string d, bool trim = true);

std::string urlEncode(std::string const &);
std::string urlDecode(std::string const &);

std::string toLowerCase(std::string);

std::vector<std::string> tokenize(std::string const &, char delimiter);
void replaceAll(std::string &str, const std::string &from,
                const std::string &to);

int findSubStrPosition(std::string &str, std::string const &subStr,
                       int const &pos);
int writeObjectToFile(const char *object, int sizem,
                      std::string const &filePath);
int writeToFile(std::string const &str, std::string const &filePath);
int readMapFromFile(std::string fname, std::map<std::string, std::string> *m);

cimap getCimapFromString(std::string);
#endif
