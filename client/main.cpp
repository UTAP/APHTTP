#include "../utils/request.hpp"
#include "../utils/response.hpp"
#include "client.hpp"
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
  Request req("POST");
  Client *c = new Client("localhost", 5000);
  req.setPath("/login");
  req.setQueryParam("gg", "jj");
  req.setHeader("sessionId", "Shahr baraz");
  req.setBodyParam("username", "AP&Ghamar=Gholam");
  req.setBodyParam("password", "p@ss");
  req.log();
  Response *res = c->send(req);
  res->log();
}
