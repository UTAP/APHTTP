#include "client.hpp"
#include <cstdio>
#include <cstring>

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
  Response *res = new Response();
  happyhttp::Connection conn(ip.c_str(), port);
  conn.setcallbacks(OnBegin, OnData, OnComplete, res);

  conn.request("GET", r.getPath().c_str(), 0, 0, 0);

  while (conn.outstanding())
    conn.pump();
  return res;
}

Response *Client::post(Request r) {
  const char *headers[] = {"Connection",
                           "close",
                           "Content-type",
                           "application/x-www-form-urlencoded",
                           "Accept",
                           "text/plain",
                           0};

  happyhttp::Connection conn(ip.c_str(), port);
  Response *res = new Response();
  conn.setcallbacks(OnBegin, OnData, OnComplete, res);
  conn.request("POST", r.getPath().c_str(), headers,
               (const unsigned char *)(r.getBody().c_str()),
               strlen(r.getBody().c_str()));

  while (conn.outstanding())
    conn.pump();
  return res;
}
