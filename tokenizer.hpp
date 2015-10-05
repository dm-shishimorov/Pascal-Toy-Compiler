#pragma once

#include <cctype>
#include <string>
#include <vector>
#include <map>

#include "lexems.hpp"
#include "stateTable.hpp"

#define INITIAL_STATE 0
#define FINAL_STATES_BEGIN 1000
#define FINAL_STATES_END 1023

using namespace std;

extern std::map<int, std::string> tokenTypeNames;
extern std::map<int, std::string> errorNames;

struct Token {
  string _value;
  int _type, _col, _row;
  Token() {};
  Token(string& value, int finalState, int col, int row);
};

class Tokenizer {
public:
  Tokenizer(string& text);
  Token getToken();
  Token nextToken();
  bool eof();

private:
  string _text;
  int _textIter, _col, _row;
  Token _token;
  bool _eof;
};

