#include "server.hpp"
#include <iostream>

using namespace std;

class LoginHandler : public RequestHandler {
public:
  Response *callback(Request *req) {
    Response *res = new Response;
    string username = req->getBodyParam("username");
    string password = req->getBodyParam("password");
    cout << "Received Data: " << username << " - " << password << endl;
    res->setHeader("Content-Type", "text/plain");
    res->setBody("Done!");
    res->setSessionId("123");
    return res;
  }
};

int main(int argc, char **argv) {
  try {
    Server server(argc > 1 ? atoi(argv[1]) : 5000);
    server.get("/home_icon", new ShowImage("static/home.png"));
    server.get("/home", new ShowPage("static/home.html"));
    server.get("/login_page", new ShowPage("static/logincss.html"));
    server.post("/login", new LoginHandler());
    server.get("/", new ShowPage("static/home.html"));
    server.run();
  } catch (Server::Exception e) {
    cout << e.getMessage() << endl;
  }
}
