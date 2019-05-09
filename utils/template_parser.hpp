#ifndef __TEMPLATE_PARSER__
#define __TEMPLATE_PARSER__
#include <string>
#include <iostream>
#include "../utils/utilities.hpp"
#include "../utils/request.hpp"
const std::string beginCodeBlockTag =  "<%";
const std::string endCodeBlockTag = "%>";

class TemplateParser {
private:
    std::string filePath;
    std::string code;
    Request *req;
    int variableCount;

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