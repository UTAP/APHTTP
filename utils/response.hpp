#ifndef __RESPONSE__
#define __RESPONSE__
#include "../include.hpp"
#include <cstdio>
#include <iostream>
#include <map>
#include <string>

using namespace std;

#define BUFSIZE 8096

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

private:
  int code;
  string phrase;
  string body;
  map<string, string> headers;
};

#endif
