#include "client.hpp"
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

void OnBegin(const happyhttp::Response *r, void *userdata) {
  Response *res = (Response *)userdata;
  res->setStatus(r->getstatus(), r->getreason());
}

void OnData(const happyhttp::Response *r, void *userdata,
            const unsigned char *data, int n) {
  Response *res = (Response *)userdata;
  const char *s = reinterpret_cast<const char *>(data);
  res->setBody(string(s));
}

void OnComplete(const happyhttp::Response *r, void *userdata) {}

Client::Client(string _ip, int _port) : ip(_ip), port(_port) {}

Response *Client::get(Request r) {
  map<string, string> headers_map = r.getHeaders();
  const char *headers[2 * headers_map.size() + 1];
  int j = 0;
  for (map<string, string>::iterator i = headers_map.begin();
       i != headers_map.end(); i++, j += 2) {
    headers[j] = (i->first).c_str();
    headers[j + 1] = (i->second).c_str();
  }
  headers[j] = 0;

  Response *res = new Response();
  happyhttp::Connection conn(ip.c_str(), port);
  conn.setcallbacks(OnBegin, OnData, OnComplete, res);

  conn.request("GET", (r.getPath() + r.getQueryString()).c_str(), headers,
               (const unsigned char *)(r.getBody().c_str()),
               strlen(r.getBody().c_str()));

  while (conn.outstanding())
    conn.pump();
  return res;
}

Response *Client::post(Request r) {
  r.setHeader("Connection", "close");
  r.setHeader("Content-type", "application/x-www-form-urlencoded");
  r.setHeader("Accept", "text/plain");
  map<string, string> headers_map = r.getHeaders();
  const char *headers[2 * headers_map.size() + 1];
  int j = 0;
  for (map<string, string>::iterator i = headers_map.begin();
       i != headers_map.end(); i++, j += 2) {
    headers[j] = (i->first).c_str();
    headers[j + 1] = (i->second).c_str();
  }
  headers[j] = 0;

  cerr << r.getBody() << endl;

  happyhttp::Connection conn(ip.c_str(), port);
  Response *res = new Response();
  conn.setcallbacks(OnBegin, OnData, OnComplete, res);
  conn.request("POST", (r.getPath() + r.getQueryString()).c_str(), headers,
               (const unsigned char *)(r.getBody().c_str()),
               strlen(r.getBody().c_str()));

  while (conn.outstanding())
    conn.pump();
  return res;
}

Response *Client::send(Request r) {
  switch (r.getMethod()) {
  case GET:
    return this->get(r);
  case POST:
    return this->post(r);
  }
  return NULL;
}
