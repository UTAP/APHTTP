#include "request.hpp"

Request::Request(string _method) {
  if (_method == "GET")
    method = GET;
  if (_method == "POST")
    method = POST;
}

string Request::getQueryParam(string key) { return query[key]; }

string Request::getBodyParam(string key) { return body[key]; }

string Request::getHeader(string key) { return headers[key]; }

string Request::getPath() { return path; }

void Request::setPath(string _path) { path = _path; }

Method Request::getMethod() { return method; }

void Request::setQueryParam(string key, string value) { query[key] = value; }

void Request::setBodyParam(string key, string value) { body[key] = value; }

void Request::setHeader(string key, string value) { headers[key] = value; }

string Request::getBody() {
  string bs = "";
  for (auto it = body.begin(); it != body.end(); it++)
    bs += it->first + "=" + it->second + "&";
  return bs;
}

void Request::log() {
  cout << "------- Request --------" << endl;
  cout << "Method: " << (method ? "POST" : "GET") << endl;
  cout << "Path: " << path << endl;
  cout << "Headers: " << endl;
  for (auto it = headers.begin(); it != headers.end(); it++)
    cout << "  " << it->first << ": " << it->second << endl;
  cout << "Query: " << endl;
  for (auto it = query.begin(); it != query.end(); it++)
    cout << "  " << it->first << ": " << it->second << endl;
  cout << "Body: " << endl;
  for (auto it = body.begin(); it != body.end(); it++)
    cout << "  " << it->first << ": " << it->second << endl;
  cout << "------------------------" << endl;
}
