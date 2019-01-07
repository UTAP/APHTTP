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
    body += "<p>";
    body += "SeddionId: ";
    body += req->getSessionId();
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
    cout << "username: " << username << ",\tpassword: " << password << endl;
    Response *res = Response::redirect("/rand");
    res->setSessionId("SID");
    return res;
  }
};

class UploadHandler : public RequestHandler {
public:
  Response *callback(Request *req) {
    string name = req->getBodyParam("file_name");
    string file = req->getBodyParam("file");
    cout << name << ":\n" << file << endl;
    Response *res = Response::redirect("/");
    return res;
  }
};

int main(int argc, char **argv) {
  srand(time(NULL)); // for rand
  try {
    Server server(argc > 1 ? atoi(argv[1]) : 5000, "static/404.html");
    server.get("/login", new ShowPage("static/logincss.html"));
    server.post("/login", new LoginHandler());
    server.get("/up", new ShowPage("static/upload_form.html"));
    server.post("/up", new UploadHandler());
    server.get("/rand", new RandomNumberHandler());
    server.get("/home.png", new ShowImage("static/home.png"));
    server.get("/", new ShowPage("static/home.html"));
    server.run();
  } catch (Server::Exception e) {
    cerr << e.getMessage() << endl;
  }
}
