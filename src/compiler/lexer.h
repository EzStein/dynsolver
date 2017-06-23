#ifndef LEXER_GUARD
#define LEXER_GUARD
#include <iostream>
#include <map>
#include "reg_def.h"
#include "compiler/token.h"
#include "compiler/NFA.h"

class lexer {
public:
  /*Constructs a lexer with the given input stream of characters
  * and a rule set for identifying tokens*/
  lexer(std::istream&, const std::map<std::string, token>&);

  /*Attempts to read the longest matchable lexeme in the stream. If it exists, it, returns
  that lexeme along with its corresponding token. If no such lexeme could be found but there is still input left in the stream,
  the string containing the null character is returned along with the token ERROR. If there is no input left in the stream,
  the token ENDPOINT is returned along with the string containing the null character*/
  token next_token(std::string& lexeme);

private:
  std::istream& stream;
  NFA fa;

  /*Maps accepting states to tokens*/
  std::map<state_type, token> tokenMap;
};
#endif
