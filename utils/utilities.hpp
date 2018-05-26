#include <string>

#define BUFFER_SIZE 8096

std::string readFile(const char *filename);
std::string urlEncode(std::string const &);
std::string urlDecode(std::string const &);
