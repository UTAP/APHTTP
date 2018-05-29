#include "server.hpp"
#include "../utils/utilities.hpp"
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

using namespace std;

void split(string str, string separator, int max, vector<string> *results) {
  int i = 0;
  size_t found = str.find_first_of(separator);

  while (found != string::npos) {
    if (found > 0)
      results->push_back(str.substr(0, found));
    str = str.substr(found + 1);
    found = str.find_first_of(separator);

    if (max > -1 && ++i == max)
      break;
  }
  if (str.length() > 0)
    results->push_back(str);
}

Request *parse_headers(char *headers) {
  Request *req;

  try {
    int i = 0;
    char *pch;
    for (pch = strtok(headers, "\r\n"); pch; pch = strtok(NULL, "\r\n")) {
      if (i++ == 0) {
        vector<string> R;
        string line(pch);

        split(line, " ", 3, &R);
        if (R.size() != 3) {
          throw Server::Exception("Invalid header");
        }
        req = new Request(R[0]);
        req->setPath(R[1]);
        size_t pos = req->getPath().find('?');
        if (pos != string::npos) {
          vector<string> Q1;
          split(req->getPath().substr(pos + 1), "&", -1, &Q1);
          for (vector<string>::size_type q = 0; q < Q1.size(); q++) {
            vector<string> Q2;
            split(Q1[q], "=", -1, &Q2);
            if (Q2.size() == 2)
              req->setQueryParam(Q2[0], Q2[1], false);
          }
          req->setPath(req->getPath().substr(0, pos));
        }
      } else {
        vector<string> R;
        string line(pch);
        split(line, ": ", 2, &R);
        if (R.size() == 2) {
          req->setHeader(R[0], R[1], false);
        }
        vector<string> body;
        split(line, "&", 10, &body);
        if (body.size() > 1) {
          for (size_t i = 0; i < body.size(); i++) {
            vector<string> field;
            split(body[i], "=", 2, &field);
            req->setBodyParam(field[0], field[1], false);
          }
        }
      }
    }
  } catch (...) {
    throw Server::Exception("Error on parsing header");
  }
  return req;
}

Server::Server(int _port) { port = _port; }

void Server::get(string path, RequestHandler *handler) {
  Route *route = new Route(GET, path);
  route->setHandler(handler);
  routes.push_back(route);
}

void Server::post(string path, RequestHandler *handler) {
  Route *route = new Route(POST, path);
  route->setHandler(handler);
  routes.push_back(route);
}

class NotFoundHandler : public RequestHandler {
public:
  Response *callback(Request *req) {
    Response *res = new Response;
    res->setBody(readFile("htmlFiles/404.html"));
    res->setHeader("Content-Type", "text/html");
    res->setStatus(404, "Not Found");
    return res;
  }
};

void Server::run() {
  sc = socket(AF_INET, SOCK_STREAM, 0);
  if (sc < 0)
    throw Exception("Error on opening socket");
  struct sockaddr_in serv_addr;
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(port);

  if (::bind(sc, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) != 0)
    throw Exception("Error on binding");

  listen(sc, 5);

  RequestHandler *notFoundHandler = new NotFoundHandler();
  struct sockaddr_in cli_addr;
  socklen_t clilen;
  clilen = sizeof(cli_addr);
  int newsc;

  fd_set fds;
  struct timeval timeout;
  timeout.tv_sec = 1;
  timeout.tv_usec = 0;
  FD_ZERO(&fds);
  FD_SET(sc, &fds);
  while (true) {
    newsc = accept(sc, (struct sockaddr *)&cli_addr, &clilen);
    FD_SET(newsc, &fds);
    if (newsc < 0)
      throw Exception("Error on accept");

    string headers = "";
    long len = 0;
    while (select(newsc + 1, &fds, NULL, NULL, &timeout) &&
           FD_ISSET(newsc, &fds)) {
      char data[BUFSIZE + 1];
      long ret = read(newsc, data, BUFSIZE);
      if (ret <= 0)
        break;
      data[ret >= 0 ? ret : 0] = 0;
      len += ret;
      headers += data;
    }
    char headers_array[headers.size()];
    strcpy(headers_array, headers.c_str());
    Request *req = parse_headers(headers_array);
    req->log();
    Response *res = new Response();
    size_t i = 0;
    for (; i < routes.size(); i++) {
      if (routes[i]->isMatch(req->getMethod(), req->getPath())) {
        res = routes[i]->handle(req);
        break;
      }
    }
    if (i == routes.size()) {
      res = notFoundHandler->callback(req);
    }
    char *header_buffer = res->print();
    write(newsc, header_buffer, strlen(header_buffer));
    FD_CLR(newsc, &fds);
    close(newsc);
  }
}

const char *Server::Exception::getMessage() { return pMessage; }

Response *RequestHandler::callback(Request *req) { return NULL; }
