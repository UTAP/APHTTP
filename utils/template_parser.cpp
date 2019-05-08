#include "template_parser.hpp"
using namespace std;

TemplateParser::TemplateParser(string _filePath){
    filePath = _filePath;
    code = "";
}

string TemplateParser::getParsedHtml(){
    string unparsedTemplate = readFile(filePath);
    return parseTemplate(unparsedTemplate);
}

string TemplateParser::parseTemplate(string unparsedTemplate){
    int parsePointer = 0;
    while(parsePointer < unparsedTemplate.size()){
        int startCodeBlockPos = findStartCodeBlock(parsePointer, unparsedTemplate);
        int endCodeBlockPos = findEndCodeBlock(parsePointer, unparsedTemplate);
    }
}

int TemplateParser::findStartCodeBlock(int start, int unparsedTemplate){
    return -1;
}
int TemplateParser::findEndCodeBlock(int start, int unparsedTemplate){
    return -1;
}