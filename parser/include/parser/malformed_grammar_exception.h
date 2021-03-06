#ifndef PARSER_MALFORMED_GRAMMAR_EXCEPTION_H_
#define PARSER_MALFORMED_GRAMMAR_EXCEPTION_H_

#include <stdexcept>
#include <string>

namespace parser {

// This exception is thrown when a user attempts to construct a parser from a
// malformed grammar. The grammar may be malformed for several reasons. It may
// not be implementable for the type of parser requested, it may be ambiguous,
// it may be empty, etc...
class malformed_grammar_exception : public std::runtime_error {
 public:
  // Constructs this exception with a message. The message is returned by a
  // call to what().
  explicit malformed_grammar_exception(const std::string& message)
      : std::runtime_error(message) { }
};
} // namespace parser
#endif
