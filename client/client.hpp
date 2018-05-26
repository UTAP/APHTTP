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
  Response *get(Request r);
  Response *post(Request r);

public:
  Client(string _ip = "localhost", int _port = 80);
  Response *send(Request r);
};
