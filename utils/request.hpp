#ifndef __REQUEST__
#define __REQUEST__
#include "../utils/include.hpp"
#include "../utils/utilities.hpp"
#include <string>

class Request {
public:
  Request(std::string method = "GET");
  std::string getPath();
  void setPath(std::string);
  Method getMethod();
  void setMethod(Method);
  std::string getQueryParam(std::string key);
  void setQueryParam(std::string key, std::string value, bool encode = true);
  std::string getBodyParam(std::string key);
  void setBodyParam(std::string key, std::string value, bool encode = true);
  std::string getHeader(std::string key);
  void setHeader(std::string key, std::string value, bool encode = true);
  std::string getBody();
  std::string getSessionId();
  void setSessionId(std::string);
  std::string getQueryString();
  cimap getHeaders();
  std::string getHeadersString();
  void setHeaders(std::string);
  void setQuery(std::string);
  void setBody(std::string);
  void log();
  static void serializeToFile(Request *req, std::string filePath);
  static void deserializeFromFile(Request *req, std::string filePath);

private:
  std::string path;
  Method method;
  cimap headers;
  cimap query;
  cimap body;
};
#endif
