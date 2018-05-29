#include "../utils/utilities.hpp"
#include "server.hpp"
#include <iostream>

using namespace std;

class ShowPage : public RequestHandler {
  string filePath;

public:
  ShowPage(string _filePath) { filePath = _filePath; }
  Response *callback(Request *req) {
    Response *res = new Response;
    res->setHeader("Content-Type", "text/html");
    string body = readFile(filePath.c_str());
    res->setBody(readFile(filePath.c_str()));
    return res;
  }
};

class ShowImage : public RequestHandler {
  string filePath;
public:
  ShowImage(string _filePath) { filePath = _filePath; }
  Response *callback(Request *req) {
    Response *res = new Response;
    res->setHeader("Content-Type", "image/png");
    string body = readFile(filePath.c_str());
    res->setBody(body);
    return res;
  }
};

class LoginHandler : public RequestHandler {
public:
  Response *callback(Request *req) {
    Response *res = new Response;
    string username = req->getBodyParam("username");
    string password = req->getBodyParam("password");
    cout << "Received Data: " << username << " - " << password << endl;
    res->setHeader("Content-Type", "text/html");
    res->setBody(readFile("htmlFiles/login.html"));
    res->setSessionId("123");
    return res;
  }
};



int main(int argc, char **argv) {
  try {
    Server server(argc > 1 ? atoi(argv[1]) : 5000);
    server.get("/home_icon", new ShowImage("htmlFiles/home.png"));
    server.get("/home", new ShowPage("htmlFiles/home.html"));
    server.get("/login_page", new ShowPage("htmlFiles/login.html"));
    server.post("/login", new LoginHandler());
    server.run();
  } catch (Server::Exception e) {
    cout << e.getMessage() << endl;
  }
}
