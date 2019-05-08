#ifndef __TEMPLATE_PARSER__
#define __TEMPLATE_PARSER__
#include <string>
#include "../utils/utilities.hpp"

class TemplateParser {
private:
    std::string filePath;
    std::string code;

    std::string parseTemplate(std::string unparsedTemplate);
    int findStartCodeBlock(int start, std::string unparsedTemplate);
    int findEndCodeBlock(int start, std::string unparsedTemplate);

public:
    TemplateParser(std::string _filePath);
    std::string getParsedHtml();
};

#endif