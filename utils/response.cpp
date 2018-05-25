#include "response.hpp"
#include <cstring>

Response::Response() {
  code = 200;
  phrase = "Ok";
  headers["Content-Type"] = "text/plain";
}

int Response::getStatusCode() { return code; }

string Response::getStatusPhrase() { return phrase; }

void Response::setStatus(int _code, string _phrase) {
  phrase = _phrase;
  code = _code;
}

char *Response::print() {
  char *header_buffer = new char[BUFSIZE];
  string h = "";
  h += "HTTP/1.0 " + to_string(code) + " " + phrase + "\r\n";
  h += "Server: AP HTTP Server \r\n";
  h += "Content-Length: " + to_string(strlen(body.c_str())) + "\r\n";
  for (auto it = headers.begin(); it != headers.end(); it++)
    h += it->first + ": " + it->second + "\r\n";
  h += "\r\n";
  h += body;
  strcpy(header_buffer, h.c_str());
  return header_buffer;
}

void Response::log() {
  cout << "------- Response -------" << endl;
  cout << "Status: " << to_string(code) << " " << phrase << endl;
  cout << "Body: " << body << endl;
  cout << "------------------------" << endl;
}

void Response::setHeader(string name, string value) { headers[name] = value; }

void Response::setBody(string _body) { body = _body; }

string Response::getHeader(string name) { return ""; }
