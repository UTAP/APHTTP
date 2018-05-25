#include "../include.hpp"
#include "../utils/request.hpp"
#include "../utils/response.hpp"

class RequestHandler;

class Route {
public:
  Method method;
  string path;
  Route(Method _method, string _path);
  bool isMatch(Method, string url);
  RequestHandler *handler;
  Response *handle(Request *req);
};
