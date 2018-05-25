#ifndef __REQUEST__
#define __REQUEST__
#include "../include.hpp"
#include <iostream>
#include <map>

using namespace std;

#define BUFSIZE 8096

#define SERVER_NAME "Web++"
#define SERVER_VERSION "1.0.1"

class Request {
public:
  Request(string method);
  string getPath();
  void setPath(string);
  Method getMethod();
  string getQueryParam(string key);
  void setQueryParam(string key, string value);
  string getBodyParam(string key);
  void setBodyParam(string key, string value);
  string getHeader(string key);
  void setHeader(string key, string value);
  string getBody();
  void log();

private:
  string path;
  Method method;
  map<string, string> headers;
  map<string, string> query;
  map<string, string> body;
};
#endif
