#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdio>

#include "tokenizer.hpp"

using namespace std;

int main(int argc, char** argv) {
  if (argc == 1) {
    cout << "fatal error: no input files" << endl;
    return 0;
  }

  if (argc != 2) {
    cout << "fatal error: wrong number of parameters" << endl;
    return 0;
  }

  ifstream fin(argv[1]);
  string str;
  getline(fin, str, '\0');

  Tokenizer t(str);
  while (!t.eof()) {
    Token tt = t.nextToken();
    cout << tt._row << '\t' << tt._col << '\t' << tokenTypeNames[tt._type] << '\t' << tt._value << endl;
  }

  return 0;
}