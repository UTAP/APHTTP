#include "template_parser.hpp"
using namespace std;

TemplateParser::TemplateParser(string _filePath){
    filePath = _filePath;
    code = "";
}

string TemplateParser::getParsedHtml(){
    string unparsedTemplate = readFile(filePath);
    parseTemplate(unparsedTemplate);
    return code;
}

void TemplateParser::parseTemplate(string unparsedTemplate){
    int parsePointer = 0;
    while(parsePointer < unparsedTemplate.size()){
        int begin = findBeginOfCodeBlock(parsePointer, unparsedTemplate);
        int end = findEndOfCodeBlock(parsePointer, unparsedTemplate);
        if(begin < 0)
            break;
        appendHTMLToCode(parsePointer, begin, unparsedTemplate);
        appendCodeBlockToCode(begin, end, unparsedTemplate);
        parsePointer = end + endCodeBlockTag.size();
    }
    appendHTMLToCode(parsePointer, unparsedTemplate.size(), unparsedTemplate);
}

int TemplateParser::findBeginOfCodeBlock(int startPosition, string &unparsedTemplate){
    return findSubStrPosition(unparsedTemplate, beginCodeBlockTag, startPosition);
}

int TemplateParser::findEndOfCodeBlock(int startPosition, string &unparsedTemplate){
    return findSubStrPosition(unparsedTemplate, endCodeBlockTag, startPosition);
}

void TemplateParser::appendHTMLToCode(int begin, int end, string const &unparsedTemplate){
    code += "cout << ";
    code += unparsedTemplate.substr(begin, end - begin);
    code += "\n";
}

void TemplateParser::appendCodeBlockToCode(int begin, int end, string &unparsedTemplate){
    if(end <= begin || begin < 0)
        return;
    //TODO: Add throwing exception for end not found.
    code += unparsedTemplate.substr(begin + beginCodeBlockTag.size(),
                                    end - begin - beginCodeBlockTag.size() - endCodeBlockTag.size());
}