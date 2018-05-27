#include <string>
#include <vector>

#define BUFFER_SIZE 8096

std::string readFile(const char *filename);
void printVector(std::vector<std::string>);
std::vector<std::string> split(std::string s, std::string d);

std::string urlEncode(std::string const &);
std::string urlDecode(std::string const &);
