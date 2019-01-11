AP HTTP
===
[![Travis (.org)](https://travis-ci.com/UTAP/APHTTP.svg)](https://travis-ci.com/UTAP/APHTTP)
[![code style: LLVM](https://img.shields.io/badge/code_style-LLVM-brightgreen.svg)](https://llvm.org/docs/CodingStandards.html)

**AP HTTP::_server_** is a simple web application server-side blocking framework for C++ based on simplified versions of [W++](http://konteck.github.io/wpp/), [HappyHTTP](http://scumways.com/happyhttp/happyhttp.html), and [cpp-netlib](http://cpp-netlib.org/).

## Quick How-to & Examples

### Creating a New Server

To create a new server, you should create a new object of `Server` class. The constructor of `Server` class has two optional arguments:
1. `int port`: specifies on which port server will be listen
2. `std::string notFoundErrPage`: address of .html file which should be served when a request with an invalid address is received

After that, You should define some `Route`s to server and add a  `POST` and/or `GET` handler to every one of them. You can do this by calling `get(std::string path, RequestHandler *handler)` and `post(std::string path, RequestHandler *handler)`.

At last, you should call `run()` method to start server.

Server will throw a `Server::Exception` object on failure.

Your `main` can be like:

```cpp
int main(int argc, char **argv) {
  try {
    Server server(argc > 1 ? atoi(argv[1]) : 5000);
    server.post("/login", new LoginHandler());  // get data from client-side
    server.get("/rand", new RandomNumberHandler());  // serve dynamic page
    server.get("/home.png", new ShowImage("static/home.png"));  // serve static image
    server.get("/", new ShowPage("static/home.html"));  // serve static page
    server.run();
  } catch (Server::Exception e) {
    cerr << e.getMessage() << endl;
  }
}
```

### Request Handlers

As mentioned above, any `Route` may have some handlers to handle incoming requests. Any request handler should be a class derived from `RequestHandler` class:

```cpp
class RequestHandler {
public:
  virtual Response *callback(Request *req) = 0;
};
```

`RequestHandler` is a pure abstract class which has only one function: `callback` which should be overridden.

#### Serving Static Files

Some useful request handlers or serving static files are provided in library:

* `ShowFile`: takes `filePath` and `fileType`(MIME type) parameters in it's constructor and serves related file

* `ShowPage`: takes a `filePath` parameter in it's constructor and serves `text` page, specially an .html page

* `ShowImage`: takes a `filePath` parameter in it's constructor and serves `image`

Also, you can write your own handlers.

#### Serving Dynamic Files

You should write your own request handler to server dynamic pages. Your handler should inherits from `RequestHandler` class and override `callback` function. `callback` function take a `Request *`, which comes from client-side, and give a `Response *`, which will be send to client-side.
You should create an appropriate `Response *` and return it while overriding this function.

This is an example which serves a dynamic html page:

```cpp
class RandomNumberHandler : public RequestHandler {
public:
  Response *callback(Request *req) {
    Response *res = new Response;
    res->setHeader("Content-Type", "text/html");
    string body;
    body += "<!DOCTYPE html>";
    body += "<html>";
    body += "<body style=\"text-align: center;\">";
    body += "<h1>AP HTTP</h1>";
    body += "<p>";
    body += "a random number in [1, 10] is: ";
    body += to_string(rand() % 10 + 1);
    body += "</p>";
    body += "</body>";
    body += "</html>";
    res->setBody(body);
    return res;
  }
};
```

#### Getting Data from Client-side

To get data from client-side, specially using a `POST` request, you should write your own handler, too. You should return a `Response *` as well at the end of `callback` function. Sometimes you should redirect client to a new address after handling `POST` request.

##### Redirection

You may want to redirect client to a new page when handling a request, specially after handling a `POST` request. `Response::redirect(std::string url)` is a static function of `Response` class which returns a `Response *` which will redirects client to `url` and can be returned in a `RequestHandler::callback`.

```cpp
class LoginHandler : public RequestHandler {
public:
  Response *callback(Request *req) {
    string username = req->getBodyParam("username");
    string password = req->getBodyParam("password");
    // do something with username and password
    return Response::redirect("/");
  }
};
```

### `Request`

```cpp
Request(std::string method = "GET")
```
* `method` can be `"GET"` and `"POST"`.

#### Request-Line

You can access and modify contents of Requset-Line using following functions:

* `Method getMethod()`
```cpp
enum Method { GET, POST };
```

* `std::string getPath()`
* `void setPath(std::string)`

#### Query

You can access and modify contents of Query using following functions:

* `std::string getQueryString()`: `?`-started, `&`-separated url-encoded query string
* `std::string getQueryParam(std::string key)`
* `void setQueryParam(std::string key, std::string value, bool encode = true)`

#### Haeder

You can access and modify contents of Header using following functions:

* `std::string getHeader(std::string key)`
* `cimap getHeaders()`: `cimap` is a Case-Insensitive `std::map<std::string, std::string>`
* `void setHeader(std::string key, std::string value, bool encode = true)`

#### Body

You can access and modify contents of Body using following functions:

* `std::string getBody()`
And for `application/x-www-form-urlencoded` requests:
* `std::string getBodyParam(std::string key)`
* `void setBodyParam(std::string key, std::string value, bool encode = true)`

### `Response`

```cpp
Response(int code = 200)
```

* `code` can be any HTTP or userd-defined response code

#### Status-Line

You can access and modify contents of Status-Line using following functions:

* `int getStatusCode()`
* `std::string getStatusPhrase()`
* `void setStatus(int code, std::string phrase = "")`: automatically assigns `phrase` based on `code` if not provided and `code` is known to class

Also, status of response can be specified when creating an object of `Response` by optional parameter `int code` of its constructor. Otherwise, status `200 OK` will be assigned to created object.

#### Header

You can access and modify contents of Header using following functions:

* `std::string getHeader(std::string name)`
* `void setHeader(std::string name, std::string value)`

#### Body

You can modify contents of Body using following function:

* `void setBody(std::string _body)`

### Session

You can handle sessions using SessionId and using following functions in handlers:

* `void Response::setSessionId(std::string sessionId)`

* `void Request::setSessionId(std::string sessionId)`
* `std::string Request::getSessionId()`

### Utilities

Some useful function are available in utilities.hpp header:

* `std::string readFile(std::string filePath)`: returns contents of a file

* `std::string getExtension(std::string filePath)`: returns extension of a file based on its name

* `void printVector(std::vector<std::string>)`: prints contents of a vector

* `std::vector<std::string> split(std::string s, std::string d)`: split string `s` by delimiter `d`

* `std::string urlEncode(std::string const &)` & `std::string urlDecode(std::string const &)`: url-encode and url-decode a string, specially useful when passing data through url-encoded forms and urls

## Compile and Run

There is an example main.cpp under server directory. Also, makefile is provided for that example. After installing a c++ compiler, specially `g++`, run `make` in project folder and run `./server.out` to start application. Also, You can specify port number like `./server.out 5000`. While running server.out, application is available at `http://localhost:5000` at your machine. In addition, a `make clean` command is provided in makefile.

Write your own makefile based on the provided one for your project.
