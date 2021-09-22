#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "lexer.h"



int main(int argc, char *argv[]) {

  LEXER_PREFIX  = "<#{";
  LEXER_POSTFIX = "}#>";
  char *variables = "";
  FILE *stream = stdin;

  for (int i = 1; i < argc; i++) {
    if (!strcmp(argv[i], "-p")) {
      i++;
      LEXER_PREFIX = argv[i];
    } else if (!strcmp(argv[i], "-P")) {
      i++;
      LEXER_POSTFIX = argv[i];
    } else if (!strcmp(argv[i], "-v")) {
      i++;
      variables = argv[i];
    } else {
      stream = fmemopen(argv[i], strlen(argv[i]), "r+");
    }
  }

  fprintf(stdout, "%s\n", variables);


  if (!LEXER_PREFIX) {
    fprintf(stderr, "LEXER_PREFIX is not set\n");
    return 1;
  }
  if (!LEXER_POSTFIX) {
    fprintf(stderr, "LEXER_POSTFIX is not set\n");
    return 1;
  }
  

  Lexer lex = {0};
  init_lexer(&lex, stream);

  Token tok = {0};

  while (next_token(&lex, &tok)) {
    fprintf(stdout, "%-6s: %s\n", 
        token_class_names[tok.tokcls],
        tok.value
    );
    free(tok.value);

    if (tok.tokcls == END) {
      break;
    }
  }

  fprintf(stdout, "parsing stopped\n");

  return 0; 
}