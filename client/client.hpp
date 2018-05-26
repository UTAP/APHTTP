#include "../utils/request.hpp"
#include "../utils/response.hpp"
#include "http.hpp"
#include <string>

void OnBegin(const happyhttp::Response *r, void *userdata);
void OnData(const happyhttp::Response *r, void *userdata,
            const unsigned char *data, int n);
void OnComplete(const happyhttp::Response *r, void *userdata);
class Client {
private:
  std::string ip;
  int port;
  Response *get(Request r);
  Response *post(Request r);

public:
  Client(std::string _ip = "localhost", int _port = 80);
  Response *send(Request r);
};
