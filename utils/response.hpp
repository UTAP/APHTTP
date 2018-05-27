#ifndef __RESPONSE__
#define __RESPONSE__
#include "../include.hpp"
#include "../utils/utilities.hpp"
#include <map>
#include <string>
using namespace std;
#define BUFSIZE 8096

const string SERVER_NAME = "AP HTTP Server";

class Response {
public:
  Response();
  char *print();
  void log();
  void setHeader(string name, string value);
  void setBody(string _body);
  void setStatus(int code, string phrase);
  int getStatusCode();
  string getStatusPhrase();
  string getHeader(string name);
  void setSessionId(string sessionId);

private:
  int code;
  string phrase;
  string body;
  cimap headers;
};

#endif
