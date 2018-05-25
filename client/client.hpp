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
  int port;
  string ip;

public:
  Client();
  Client(string _ip);
  Client(string _ip, int _port);
  Response *get(Request r);
  Response *post(Request r);
};
