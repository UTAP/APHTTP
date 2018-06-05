#include "server.hpp"
#include <cstdlib> // for rand and srand
#include <ctime>   // for time
#include <iostream>

using namespace std;

class RandomNumberHandler : public RequestHandler {
public:
  Response *callback(Request *req) {
    Response *res = new Response;
    res->setHeader("Content-Type", "text/html");
    string body;
    body += "<!DOCTYPE html>";
    body += "<html>";
    body += "<body style=\"text-align: center;\">";
    body += "<h1>AP HTTP</h1>";
    body += "<p>";
    body += "a random number in [1, 10] is: ";
    body += to_string(rand() % 10 + 1);
    body += "</p>";
    body += "</body>";
    body += "</html>";
    res->setBody(body);
    return res;
  }
};

class LoginHandler : public RequestHandler {
public:
  Response *callback(Request *req) {
    string username = req->getBodyParam("username");
    string password = req->getBodyParam("password");
    return Response::redirect("/");
  }
};

int main(int argc, char **argv) {
  srand(time(NULL)); // for rand
  try {
    Server server(argc > 1 ? atoi(argv[1]) : 5000);
    server.get("/home_icon", new ShowImage("static/home.png"));
    server.get("/home", new ShowPage("static/home.html"));
    server.get("/login_page", new ShowPage("static/logincss.html"));
    server.get("/rand", new RandomNumberHandler());
    server.post("/login", new LoginHandler());
    server.get("/", new ShowPage("static/home.html"));
    server.run();
  } catch (Server::Exception e) {
    cout << e.getMessage() << endl;
  }
}
