#include "utilities.hpp"

string readFile(const char *filename) {
  string s = "";
  char buffer[BUFFER_SIZE];
  ifstream infile(filename);
  infile.seekg(0, infile.end);
  size_t length = infile.tellg();
  infile.seekg(0, infile.beg);
  if (length > sizeof(buffer))
    length = sizeof(buffer);

  infile.read(buffer, length);
  for (size_t i = 0; i < length; i++) {
    s += buffer[i];
  }
  return s;
}

string urlEncode(string const &str) {
  char encode_buf[4];
  string result;
  encode_buf[0] = '%';
  result.reserve(str.size());

  // character selection for this algorithm is based on the following url:
  // http://www.blooberry.com/indexdot/html/topics/urlencoding.htm

  for (size_t pos = 0; pos < str.size(); ++pos) {
    switch (str[pos]) {
    default:
      if (str[pos] >= 32 && str[pos] < 127) {
        // character does not need to be escaped
        result += str[pos];
        break;
      }
      // else pass through to next case
    case '$':
    case '&':
    case '+':
    case ',':
    case '/':
    case ':':
    case ';':
    case '=':
    case '?':
    case '@':
    case '"':
    case '<':
    case '>':
    case '#':
    case '%':
    case '{':
    case '}':
    case '|':
    case '\\':
    case '^':
    case '~':
    case '[':
    case ']':
    case '`':
      // the character needs to be encoded
      sprintf(encode_buf + 1, "%02X", str[pos]);
      result += encode_buf;
      break;
    }
  };
  return result;
}

string urlDecode(string const &str) {
  char decode_buf[3];
  string result;
  result.reserve(str.size());

  for (size_t pos = 0; pos < str.size(); ++pos) {
    switch (str[pos]) {
    case '+':
      // convert to space character
      result += ' ';
      break;
    case '%':
      // decode hexidecimal value
      if (pos + 2 < str.size()) {
        decode_buf[0] = str[++pos];
        decode_buf[1] = str[++pos];
        decode_buf[2] = '\0';
        result += static_cast<char>(strtol(decode_buf, nullptr, 16));
      } else {
        // recover from error by not decoding character
        result += '%';
      }
      break;
    default:
      // character does not need to be escaped
      result += str[pos];
    }
  };
  return result;
}
