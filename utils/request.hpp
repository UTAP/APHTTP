#ifndef __REQUEST__
#define __REQUEST__
#include "../include.hpp"
#include <map>
#include <string>
#include <vector>

#define BUFSIZE 8096

class Request {
public:
  Request(std::string method = "GET");
  std::string getPath();
  void setPath(std::string);
  Method getMethod();
  std::string getQueryParam(std::string key);
  void setQueryParam(std::string key, std::string value, bool encode = true);
  std::string getBodyParam(std::string key);
  void setBodyParam(std::string key, std::string value, bool encode = true);
  std::string getHeader(std::string key);
  void setHeader(std::string key, std::string value, bool encode = true);
  std::string getBody();
  std::string getQueryString();
  std::map<std::string, std::string> getHeaders();
  void log();

private:
  std::string path;
  Method method;
  std::map<std::string, std::string> headers;
  std::map<std::string, std::string> query;
  std::map<std::string, std::string> body;
};
#endif
