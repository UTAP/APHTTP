#ifndef __TEMPLATE_PARSER__
#define __TEMPLATE_PARSER__
#include "../server/server.hpp"
#include "../utils/request.hpp"
#include "../utils/utilities.hpp"
#include <iostream>
#include <string>

const std::string beginCodeBlockTag = "<%";
const std::string endCodeBlockTag = "%>";
const std::string requestClassHeaderPath = "utils/request.hpp";
const std::string utilitiesHeaderPath = "utils/utilities.hpp";
const std::string requestClassPath = "utils/request.cpp";
const std::string utilitiesPath = "utils/utilities.cpp";
const std::string cc = "g++ -std=c++11 -Wall -pedantic";
const std::string compileDirectory = "templateCompile";
const std::string toCompileFile = "compiled.cpp";
const std::string staticTemplate = "staticTemplate.html";
const std::string outputFolder = ".template";

class TemplateParser {
private:
  static int lastParserNum;
  int parserNum;
  std::string filePath;
  std::string code;
  Request *req;
  int variableCount;
  std::string html;
  std::string programName;

  void parseTemplate();
  int findBeginOfCodeBlock(int startPosition, std::string &unparsedTemplate);
  int findEndOfCodeBlock(int startPosition, std::string &unparsedTemplate);
  void appendHTMLToCode(int begin, int end, std::string const &html);
  void appendCodeBlockToCode(int begin, int end, std::string &unparsedTemplate);
  void generateCode();
  void addIncludesToCode();
  void addReadFromTemplateToCode();
  void addReturnToCode();
  void addReqToCode();
  std::string runGeneratedCode();
  void makeExecutableTemplate();
  void compileCode();
  void deleteExecutable();
  class TemplateUtils {
  public:
    static void runSystemCommand(std::string command, std::string errorMessage);
  };

public:
  TemplateParser(std::string _filePath);
  ~TemplateParser();
  std::string getHtml(Request *_req);
};

#endif