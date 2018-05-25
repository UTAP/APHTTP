#include "../utils/request.hpp"
#include "../utils/response.hpp"
#include "http.hpp"
#include <cstdio>
#include <cstring>

void OnBegin(const happyhttp::Response *r, void *userdata);
void OnData(const happyhttp::Response *r, void *userdata,
            const unsigned char *data, int n);
void OnComplete(const happyhttp::Response *r, void *userdata);
class Client {
private:
  string ip;
  int port;

public:
  Client(string _ip = "127.0.0.1", int _port = 80);
  Response *get(Request r);
  Response *post(Request r);
};
