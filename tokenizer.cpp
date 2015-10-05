#include "tokenizer.hpp"
#include <iostream>
using namespace std;

std::map<int, std::string> tokenTypeNames = {
  { TOKEN_TYPE_ERROR,            "error" },
  { TOKEN_TYPE_INTEGER,          "integer" },
  { TOKEN_TYPE_REAL,             "real" },
  { TOKEN_TYPE_OPERATOR,         "operator" },
  { TOKEN_TYPE_RESERVED_WORD,    "reserved_word" },
  { TOKEN_TYPE_IDENTIFIER,       "identifier" },
  { TOKEN_TYPE_LIMITER,          "limiter" },
  { TOKEN_TYPE_STRING,           "string" },
  { TOKEN_TYPE_HEX,              "hex" },
  { TOKEN_TYPE_CHAR,             "char" },
  { TOKEN_TYPE_COMMENT,          "comment" },
};

std::map<int, std::string> errorNames = {
  { fsBadCC, "BadCC" },
  { fsNoCC, "NoCC" },
  { fsNoHex, "NoHex" },
  { fsNoFract, "NoFract" },
  { fsNoExp, "NoExp" },
  { fsBadChar, "BadChar" },
  { fsBadEOF, "BadEOF" },
  { fsBadNL, "BadNL" },
  { fsUnexpEOF, "UnexpEOF" }
};

Token::Token(string& value, int finalState, int col, int row) {
  _col = col;
  _row = row;

  FinalStateType fst = static_cast<FinalStateType>(finalStateMap[finalState].first);
  if (fst == fstError) {
    _value = errorNames[finalState];
  }
  else {
    _value = value;
  }

  switch (fst) {
    case fstError:
      _type = TOKEN_TYPE_ERROR;
      break;
    case fstStr:
      _type = (value.size() == 3) ? TOKEN_TYPE_CHAR : TOKEN_TYPE_STRING;
      break;
    case fstVar:
      _type = lexems[value] ? lexems[value] : TOKEN_TYPE_IDENTIFIER;
      break;
    case fstInt:
      _type = TOKEN_TYPE_INTEGER;
      break;
    case fstHex:
      _type = TOKEN_TYPE_HEX;
      break;
    case fstLim:
      _type = TOKEN_TYPE_LIMITER;
      break;
    case fstOp:
      _type = TOKEN_TYPE_OPERATOR;
      break;
    case fstComment:
      _type = TOKEN_TYPE_COMMENT;
      break;
    case fstChar:
      _type = TOKEN_TYPE_CHAR;
      break;
    case fstReal:
      _type = TOKEN_TYPE_REAL;
      break;
    default:
      _type = TOKEN_TYPE_ERROR;
  }
}

Tokenizer::Tokenizer(string& text) {
  _textIter = 0;
  _col = _row = 1;

  _text = text;
  if (_text.empty()) {
    _eof = true;
    return;
  }

  int i = _text.size() - 1;
  while (isspace(_text[i])) i--;
  _text = _text.substr(0, i+1);
  _eof = _text.empty() ? true : false;
}

Token Tokenizer::getToken() {
  return _token;
}

Token Tokenizer::nextToken() {
  string tkValue;
  int lastCol;
  int i = INITIAL_STATE;
  while (!(i >= FINAL_STATES_BEGIN && i <= FINAL_STATES_END)) {
    char c = _text[_textIter++];
    i = stateTable[i][charMap[c]];
    if (c == '\n') {
      _row++;
      lastCol = _col;
      _col = 1;
    }

    if (i == INITIAL_STATE) {
      if (c == 9 || c == 32) {
        _col++;
      }
      continue;
    }

    tkValue += c;
  }

  int back = finalStateMap[i].second;
  _textIter -= back;

  if (back > 0) {
    if (tkValue[tkValue.size()-1] == '\n') {
      _row--;
      _col = lastCol;
    }
  }

  _token = Token(tkValue.substr(0, tkValue.size() - back), i, _col, _row);
  _col += tkValue.size();

  if (_textIter == _text.size() || _token._type == TOKEN_TYPE_ERROR) {
    _eof = true;
  }

  return _token;
}

bool Tokenizer::eof() {
  return _eof;
}