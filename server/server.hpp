#ifndef __SERVER__
#define __SERVER__
#include "../utils/include.hpp"
#include "../utils/request.hpp"
#include "../utils/response.hpp"
#include "route.hpp"
#include <exception>
#include <string>
#include <vector>

class RequestHandler {
public:
  virtual Response *callback(Request *req);
};

class Server {
public:
  Server(int port = 5000);
  void run();
  void get(std::string path, RequestHandler *handler);
  void post(std::string path, RequestHandler *handler);
  class Exception : public std::exception {
  public:
    Exception() {}
    Exception(const char *pStr) { pMessage = pStr; }
    const char *getMessage();

  private:
    const char *pMessage;
  };

private:
  int sc;
  int port;
  std::vector<Route *> routes;
};
#endif
