#include "template_parser.hpp"
using namespace std;

int TemplateParser::lastParserNum = 0;

TemplateParser::TemplateParser(string _filePath) {
  filePath = _filePath;
  variableCount = 0;
  programName = to_string(TemplateParser::lastParserNum) + ".o";
  parserNum = TemplateParser::lastParserNum++;
  code = "";
  parseTemplate();
  makeExecutableTemplate();
}

string TemplateParser::getHtml(Request *_req) {
  req = _req;
  return runGeneratedCode();
}

void TemplateParser::parseTemplate() {
  string unparsedTemplate = readFile(filePath);
  int parsePointer = 0;
  while (parsePointer < unparsedTemplate.size()) {
    int begin = findBeginOfCodeBlock(parsePointer, unparsedTemplate);
    int end = findEndOfCodeBlock(parsePointer, unparsedTemplate);
    if (begin < 0)
      break;
    appendHTMLToCode(parsePointer, begin, unparsedTemplate);
    appendCodeBlockToCode(begin, end, unparsedTemplate);
    parsePointer = end + endCodeBlockTag.size();
  }
  appendHTMLToCode(parsePointer, unparsedTemplate.size(), unparsedTemplate);
}

int TemplateParser::findBeginOfCodeBlock(int startPosition,
                                         string &unparsedTemplate) {
  return findSubStrPosition(unparsedTemplate, beginCodeBlockTag, startPosition);
}

int TemplateParser::findEndOfCodeBlock(int startPosition,
                                       string &unparsedTemplate) {
  return findSubStrPosition(unparsedTemplate, endCodeBlockTag, startPosition);
}

void TemplateParser::appendHTMLToCode(int begin, int end,
                                      string const &unparsedTemplate) {
  code += "\nstring __variable" + to_string(variableCount) + ";";
  code += "\n__variable" + to_string(variableCount) +
          " = __unparsedTemplate__.substr(";
  code += to_string(begin) + ", " + to_string(end - begin) + ");";
  code += "\ncout << __variable" + to_string(variableCount) + ";";
  variableCount++;
}

void TemplateParser::appendCodeBlockToCode(int begin, int end,
                                           string &unparsedTemplate) {
  if (end <= begin || begin < 0)
    throw Server::Exception("Can not parse template " + filePath);
  int codeBlockSize = end - begin - beginCodeBlockTag.size();
  code +=
      unparsedTemplate.substr(begin + beginCodeBlockTag.size(), codeBlockSize);
}

void TemplateParser::makeExecutableTemplate() {
  generateCode();
  compileCode();
}

void TemplateParser::generateCode() {
  addReadFromTemplateToCode();
  addReqToCode();
  addIncludesToCode();
  addReturnToCode();
}

void TemplateParser::compileCode() {
  if (!writeToFile(code, toCompileFile))
    throw Server::Exception("Can not write generated template code.");

  string cmd = "mkdir -p " + outputFolder + " &&" + cc + " " + toCompileFile +
               " " + requestClassPath + " " + utilitiesPath + " -o " +
               outputFolder + "/" + programName + "&& rm " + toCompileFile;

  int ret = system(cmd.c_str());
  if (WEXITSTATUS(ret) != EXIT_SUCCESS) {
    string error = "Can not compile template " + filePath;
    throw Server::Exception(error);
  }
}

string TemplateParser::runGeneratedCode() {
  Request::serializeToFile(req, ".template/req.txt");

  string cmd =
      "./" + outputFolder + "/" + programName + " " + " > " + staticTemplate;

  int ret = system(cmd.c_str());
  if (WEXITSTATUS(ret) != EXIT_SUCCESS) {
    string error = "Error in running template  " + filePath;
    throw Server::Exception(error);
  }

  string html = readFile(staticTemplate);

  cmd = "rm " + staticTemplate;
  ret = system(cmd.c_str());
  if (WEXITSTATUS(ret) != EXIT_SUCCESS) {
    string error = "Error in deleting static template  " + filePath;
    throw Server::Exception(error);
  }
  return html;
}

void TemplateParser::addIncludesToCode() {
  string include = "#include <iostream>\n";
  include += "#include <string>\n";
  include += "#include \"" + requestClassHeaderPath + "\"\n";
  include += "#include \"" + utilitiesHeaderPath + "\"\n";
  include += "using namespace std;\n";
  code = include + "int main(int argc, char const *argv[])\n{\n" + code + "\n";
}

void TemplateParser::addReadFromTemplateToCode() {
  code =
      "string __unparsedTemplate__ = readFile(\"" + filePath + "\");\n" + code;
}

void TemplateParser::addReturnToCode() { code += "return 0;\n}\n"; }

void TemplateParser::addReqToCode() {
  string reqCode = "Request *req = new Request();\n";
  reqCode += "Request::deserializeFromFile(req, \".template/req.txt\");\n";
  code = reqCode + code;
}