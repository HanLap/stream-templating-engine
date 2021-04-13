#include <stdlib.h>
#include <unistd.h>

#include "lexer.h"



int main(int argc, char *argv[]) {

  LEXER_PREFIX  = "<#{";
  LEXER_POSTFIX = "}#>";
  

  fprintf(stdout, "%s\n", LEXER_PREFIX);

  lexer lex = {0};
  init_lexer(&lex, stdin);

  token tok = {0};

  if (next_token(&lex, &tok)) {
    fprintf(stdout, "token: %s\n", tok.value);
  } else {
    fprintf(stderr, "could not parse token\n");
  }
  return 0; 
}