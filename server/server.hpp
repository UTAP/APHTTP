#include "../include.hpp"
#include "../utils/request.hpp"
#include "../utils/response.hpp"
#include "route.hpp"
#include <algorithm>
#include <dirent.h>
#include <fstream>
#include <iostream>
#include <limits.h>
#include <map>
#include <netinet/in.h>
#include <sstream>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <vector>

using namespace std;

class RequestHandler {
public:
  virtual Response *callback(Request *req) {}
};

class Server {
public:
  Server(int port = 5000);
  void run();
  void get(string path, RequestHandler *handler);
  void post(string path, RequestHandler *handler);

private:
  int sc;
  int port;
  vector<Route *> routes;
};
