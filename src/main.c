#include <stdlib.h>
#include <unistd.h>

#include "lexer.h"



int main(int argc, char *argv[]) {

  LEXER_PREFIX  = "<#{";
  LEXER_POSTFIX = "}#>";
  

  Lexer lex = {0};
  init_lexer(&lex, stdin);

  Token tok = {0};

  while (next_token(&lex, &tok)) {
    fprintf(stdout, "token: %s\n", tok.value);
  }

  fprintf(stdout, "parsing stopped\n");

  return 0; 
}