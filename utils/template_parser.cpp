#include "template_parser.hpp"
using namespace std;

TemplateParser::TemplateParser(string _filePath, Request *_req){
    filePath = _filePath;
    code = "";
    req = _req;
    variableCount = 0;
}

string TemplateParser::getParsedHtml(){
    string unparsedTemplate = readFile(filePath);
    parseTemplate(unparsedTemplate);
    generateCode();
    runGeneratedCode();
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
    code += "\nstring variable" + to_string(variableCount) + ";";
    code += "\nvariable" + to_string(variableCount) + " = unparsedTemplate.substr(";
    code += to_string(begin) + ", " + to_string(end - begin) + ");";
    code += "\ncout << variable" + to_string(variableCount) + ";" ;
    variableCount ++;
}

void TemplateParser::appendCodeBlockToCode(int begin, int end, string &unparsedTemplate){
    if(end <= begin || begin < 0)
        return;
    //TODO: Add throwing exception for end not found.
    code += unparsedTemplate.substr(begin + beginCodeBlockTag.size(),
                                    end - begin - beginCodeBlockTag.size() - endCodeBlockTag.size());
}

void TemplateParser::generateCode(){
    addReadFromTemplateToCode();
    addIncludesToCode();
    addReturnToCode();
}

void TemplateParser::runGeneratedCode(){

}

void TemplateParser::addIncludesToCode(){
    string include = "#include <iostream>\n";
    include += "#include <string>\n";
    include += "#include \"utils/request.hpp\"\n";
    include += "#include \"utils/utilities.hpp\"\n";
    include += "using namespace std;\n";
    code = include + "int main()\n{\n" + code + "\n";
}

void TemplateParser::addReadFromTemplateToCode(){
    code = "string unparsedTemplate = readFile(\"" + filePath + "\");\n" + code;
}

void TemplateParser::addReturnToCode(){
    code += "return 0;\n}\n";
}