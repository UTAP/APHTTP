#ifndef __TEMPLATE_PARSER__
#define __TEMPLATE_PARSER__
#include <string>
#include <iostream>
#include <dlfcn.h> //dynamic library loading, dlopen() etc
#include "../utils/utilities.hpp"
#include "../utils/request.hpp"

const std::string beginCodeBlockTag =  "<%";
const std::string endCodeBlockTag = "%>";
const std::string requestClassHeaderPath = "utils/request.hpp";
const std::string utilitiesHeaderPath = "utils/utilities.hpp";
const std::string requestClassPath = "utils/request.cpp";
const std::string utilitiesPath = "utils/utilities.cpp";
const std::string cc = "g++ -std=c++11 -Wall -pedantic";
const std::string compileDirectory = "templateCompile";
const std::string compiledFile = "compiled.cpp";
const std::string staticTemplate = "staticTemplate.html";

class TemplateParser {
private:
    std::string filePath;
    std::string code;
    Request *req;
    int variableCount;
    std::string html;

    void parseTemplate(std::string unparsedTemplate);
    int findBeginOfCodeBlock(int startPosition, std::string &unparsedTemplate);
    int findEndOfCodeBlock(int startPosition, std::string &unparsedTemplate);
    void appendHTMLToCode(int begin, int end, std::string const &html);
    void appendCodeBlockToCode(int begin, int end, std::string &unparsedTemplate);
    void generateCode();
    void addIncludesToCode();
    void addReadFromTemplateToCode();
    void addReturnToCode();
    void runGeneratedCode();

public:
    TemplateParser(std::string _filePath, Request *_req);
    std::string getParsedHtml();
};

#endif