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
  const string NC = "\033[0;39m";
  const string K = "\033[1m";
  const string H = "\033[33;1m";
  string log = "";
  log += H + string("------- Request --------") + NC + string("\n");
  log +=
      K + string("Method:\t") + NC + (method ? "POST" : "GET") + string("\n");
  log += K + string("Path:\t") + NC + path + string("\n");
  log += K + string("Headers:") + NC + string("\n");
  for (auto it = headers.begin(); it != headers.end(); it++)
    log += "  " + it->first + ": " + it->second + string("\n");
  log += K + string("Query:") + NC + string("\n");
  for (auto it = query.begin(); it != query.end(); it++)
    log += "  " + it->first + ": " + it->second + string("\n");
  log += K + string("Body:") + NC + string("\n");
  for (auto it = body.begin(); it != body.end(); it++)
    log += "  " + it->first + ": " + it->second + string("\n");
  log += H + string("------------------------") + NC + string("\n");
  cerr << log << endl;
}
