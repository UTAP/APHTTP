#include "../utils/request.hpp"
#include "../utils/response.hpp"
#include "client.hpp"
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
  Request req("POST");
  Client *c = new Client("127.0.0.1", 80);
  req.setPath("/login_page");
  Response *res = c->get(req);
  res->log();
}
