#include <stdlib.h>
#include <string.h>

#include "lexer.h"

char *LEXER_PREFIX  = 0;
char *LEXER_POSTFIX = 0;


bool init_lexer(lexer *lex, FILE *stream) {
  lex->stream  = stream;
  lex->pos     = 0;
  lex->line    = 0;
  lex->col     = 0;
  lex->inblock = false;
  return true;
}


bool is_prefix(lexer *lex) {
  for(size_t i = 1; i < strlen(LEXER_PREFIX); i++) {
    char c = getc(lex->stream); 
    if (c != LEXER_PREFIX[i]) {
      ungetc(c, lex->stream);
      for (size_t j = i - 1; j >= 0; j--) {
        ungetc(LEXER_PREFIX[j], lex->stream);
      }
      return false;
    }
  }
  return true;
}




bool parse_to_next_block(lexer *lex, token *tok) {
  size_t newpos  = lex->pos;
  size_t newline = lex->line;
  size_t newcol  = lex->col;

  while (true) {
    char c = fgetc(lex->stream);

    if (c == '\n') {
      newline++;
      newcol = 0;
    }

    if (c == EOF) {}

    if (c == LEXER_PREFIX[0] && is_prefix(lex)) {
      
    }

    newcol++;
    newpos++;
  }
  
  return true;
}

bool parse_block(lexer *lex, token *tok) {


  return 1;
}



bool next_token(lexer *lex, token *tok) {
  if (!LEXER_PREFIX) {
    fprintf(stderr, "LEXER_PREFIX is not set");
    return false;
  }
  if (!LEXER_POSTFIX) {
    fprintf(stderr, "LEXER_POSTFIX is not set");
    return false;
  }


  if(!lex->inblock) {
    return parse_to_next_block(lex, tok);
  } 

  return parse_block(lex, tok);
}