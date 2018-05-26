#include "../include.hpp"
#include "../utils/request.hpp"
#include "../utils/response.hpp"
#include <string>

class RequestHandler;

class Route {
public:
  Method method;
  std::string path;
  Route(Method _method, std::string _path);
  bool isMatch(Method, std::string url);
  RequestHandler *handler;
  Response *handle(Request *req);
};
