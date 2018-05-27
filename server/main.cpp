#include "../utils/utilities.hpp"
#include "server.hpp"
#include <iostream>

using namespace std;

class ShowPage : public RequestHandler {
  string filePath;

public:
  ShowPage(string _filePath) { filePath = _filePath; }
  Response *callback(Request *req) {
    cout<<endl<<"SessionId: "<<req->getSessionId()<<endl<<endl;
    Response *res = new Response;
    res->setBody(readFile(filePath.c_str()));
    res->setHeader("Content-Type", "text/html");
    res->setSessionId("s1");
    return res;
  }
};

class LoginHandler : public RequestHandler {
public:
  Response *callback(Request *req) {
    Response *res = new Response;
    string username = req->getBodyParam("username");
    string password = req->getBodyParam("password");
    cout << "Submitted data: " << username << " : " << password << endl;
    res->setBody(readFile("htmlFiles/login.html"));
    res->setHeader("Content-Type", "text/html");
    res->setSessionId("123");
    return res;
  }
};

int main() {
  Server server;
  server.get("/", new ShowPage("htmlFiles/home.html"));
  server.get("/home", new ShowPage("htmlFiles/home.html"));
  server.get("/login_page", new ShowPage("htmlFiles/login.html"));
  server.post("/login", new LoginHandler());
  server.run();
}
