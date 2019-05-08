#ifndef __TEMPLATE_PARSER__
#define __TEMPLATE_PARSER__
#include <string>
#include "../utils/utilities.hpp"
const std::string beginCodeBlockTag =  "<%";
const std::string endCodeBlockTag = "%>";

class TemplateParser {
private:
    std::string filePath;
    std::string code;

    void parseTemplate(std::string unparsedTemplate);
    int findBeginOfCodeBlock(int startPosition, std::string &unparsedTemplate);
    int findEndOfCodeBlock(int startPosition, std::string &unparsedTemplate);
    void appendHTMLToCode(int begin, int end, std::string const &html);
    void appendCodeBlockToCode(int begin, int end, std::string &unparsedTemplate);

public:
    TemplateParser(std::string _filePath);
    std::string getParsedHtml();
};

#endif