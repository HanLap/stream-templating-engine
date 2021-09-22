#include <stdlib.h>
#include <string.h>

#include "lexer.h"

char *LEXER_PREFIX  = 0;
char *LEXER_POSTFIX = 0;

char *token_class_names[] = {
  "TEXT",
  "OBLOCK",
  "CBLOCK",
  "RELOP",
  "INTLIT",
  "ID",
  "IF",
  "FI",
  "ELIF",
  "ELSE",
  "END"
};

bool init_lexer(Lexer *lex, FILE *stream) {
  lex->stream  = stream;
  lex->pos     = 0;
  lex->line    = 0;
  lex->col     = 0;
  lex->inblock = false;
  return true;
}


bool is_prefix(Lexer *lex) {
  for(size_t i = 1; i < strlen(LEXER_PREFIX); i++) {
    char c = getc(lex->stream); 
    if (c != LEXER_PREFIX[i]) {
      ungetc(c, lex->stream);
      for (size_t j = i - 1; j > 0; j--) {
        ungetc(LEXER_PREFIX[j], lex->stream);
      }
      return false;
    }
  }
  for (size_t i = strlen(LEXER_PREFIX); i > 0; i--) {
    ungetc(LEXER_PREFIX[i - 1], lex->stream);
  }
  return true;
}


bool parse_to_next_block(Lexer *lex, Token *tok) {
  size_t newpos  = lex->pos;
  size_t newline = lex->line;
  size_t newcol  = lex->col;


  // todo handle dynamic buffer size;
  char *buf = malloc(40);
  size_t buf_i = 0;

  while (true) {
    char c = fgetc(lex->stream);

    if (c == '\n') {
      newline++;
      newcol = 0;
    }

    if (c == EOF && buf_i == 0) {
      ungetc(c, lex->stream);
      buf[buf_i] = '\0';
      tok->col    = lex->col;
      tok->line   = lex->line;
      tok->tokcls = END;
      tok->value  = buf;
      break;
    }

    if (c == EOF) {
      buf[buf_i    ] = EOF;
      buf[buf_i + 1] = '\0';
      tok->col    = lex->col;
      tok->line   = lex->line;
      tok->tokcls = TEXT;
      tok->value  = buf;
      break;
    }

    if (is_prefix(lex)) {
      buf[buf_i] = '\0';
      tok->col    = lex->col;
      tok->line   = lex->line;
      tok->tokcls = TEXT;
      tok->value  = buf;

      lex->inblock = true;
      break;
    }

    newcol++;
    newpos++;

    buf[buf_i] = c;
    buf_i++;
  }
  
  lex->col  = newcol;
  lex->line = newline;
  lex->pos  = newpos;
  return true;
}


bool parse_oblock(Lexer *lex, Token *tok) {
  for (size_t i = 0; i < strlen(LEXER_PREFIX); i++) {
    if (fgetc(lex->stream) != LEXER_PREFIX[i]) {
      return false;
    }
  }

  tok->tokcls = OBLOCK;
  tok->value  = strndup(LEXER_PREFIX, strlen(LEXER_PREFIX));
  tok->line   = lex->line;
  tok->col    = lex->col;

  return true;
}

bool parse_cblock(Lexer *lex, Token *tok) {
  for (size_t i = 0; i < strlen(LEXER_POSTFIX); i++) {
    if (fgetc(lex->stream) != LEXER_POSTFIX[i]) {
      return false;
    }
  }

  tok->tokcls = CBLOCK;
  tok->value  = strndup(LEXER_POSTFIX, strlen(LEXER_POSTFIX));
  tok->line   = lex->line;
  tok->col    = lex->col;

  lex->inblock = false;
  return true;
}

bool parse_if(Lexer *lex, Token *tok) {
  return false;
}

bool parse_elif(Lexer *lex, Token *tok) {
  return false;
}

bool parse_else(Lexer *lex, Token *tok) {
  return false;
}

bool parse_fi(Lexer *lex, Token *tok) {
  return false;
}

bool parse_id(Lexer *lex, Token *tok) {
  return false;
}

bool parse_relop(Lexer *lex, Token *tok) {
  return false;
}

bool parse_intlit(Lexer *lex, Token *tok) {
  char *buf = malloc(40);
  int buf_i = 0;
  
  while (true) {
    char c = fgetc(lex->stream);

    
    if (c == ' ') {
      tok->tokcls = INTLIT;
      tok->value  = buf;
      tok->line   = lex->line;
      tok->col    = lex->col; 

      return true;
    }

    if (c == EOF) {
      fprintf(stdout, "reached eof while parsing intlit");
      exit(1);
    }
  }
  
}

bool parse_block(Lexer *lex, Token *tok) {

  char c = fgetc(lex->stream);
  while (c == ' ') {
    c = fgetc(lex->stream);
  }

  if (c == LEXER_PREFIX[0]) {
    ungetc(c, lex->stream);
    return parse_oblock(lex, tok);
  }

  if (c == LEXER_POSTFIX[0]) {
    ungetc(c, lex->stream);
    return parse_cblock(lex, tok);
  }

  char *buf = malloc(2);
  buf[0] = c;
  buf[1] = '\0';

  tok->tokcls = TEXT;
  tok->value  = buf;
  tok->line   = lex->line;
  tok->col    = lex->col;
  
  return true;
}


bool next_token(Lexer *lex, Token *tok) {

  if(!lex->inblock) {
    return parse_to_next_block(lex, tok);
  } 

  return parse_block(lex, tok);
}