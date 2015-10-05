#pragma once

#include <map>
#include <vector>
#include <string>

#define TOKEN_TYPE_ERROR              0
#define TOKEN_TYPE_INTEGER            1
#define TOKEN_TYPE_REAL               2
#define TOKEN_TYPE_OPERATOR           3
#define TOKEN_TYPE_RESERVED_WORD      4
#define TOKEN_TYPE_IDENTIFIER         5
#define TOKEN_TYPE_LIMITER            6
#define TOKEN_TYPE_STRING             7
#define TOKEN_TYPE_HEX                8
#define TOKEN_TYPE_CHAR               9
#define TOKEN_TYPE_COMMENT            10

extern std::map<std::string, int> lexems;