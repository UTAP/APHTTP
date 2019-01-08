#include "../server/server.hpp"
#include <cstdlib> // for rand and srand
#include <ctime>   // for time
#include <iostream>


class RandomNumberHandler : public RequestHandler {
public:
	Response* callback(Request*);
};

class LoginHandler : public RequestHandler {
public:
	Response* callback(Request*);
};

class UploadHandler : public RequestHandler {
public:	
	Response* callback(Request*);
};