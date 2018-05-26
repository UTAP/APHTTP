#include <fstream>
#include <string>

#define BUFFER_SIZE 8096

using namespace std;

string readFile(const char *filename);
string urlEncode(string const &);
string urlDecode(string const &);
