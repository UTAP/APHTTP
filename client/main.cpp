#include "../utils/request.hpp"
#include "../utils/response.hpp"
#include "client.hpp"
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
  Request req("POST");
  Client *c = new Client("localhost", 5000);
  req.setPath("/login");
  req.setBodyParam("username", "AP");
  req.setBodyParam("password", "p@ss");
  Response *res = c->post(req);
  res->log();
}
