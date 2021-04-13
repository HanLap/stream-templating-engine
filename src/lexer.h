#ifndef LEXER_H
#define LEXER_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>



extern char *LEXER_PREFIX;
extern char *LEXER_POSTFIX;

enum TokenClass {
    TEXT,    // everything that is not in between the provided delimiters
    OBLOCK,  // provided template prefix
    CBLOCK,  // provided template postfix
    RELOP,   // <=, ==, >=, !=
    INTLIT,  // numbers
    ID,      // variable identifiers
    IF,      // if
    ELIF,    // elseif
    ELSE     // else
};

typedef struct token {
    enum TokenClass  tokcls;
    const char      *value;
    size_t           line;
    size_t           col;
} token;


typedef struct lexer {
    FILE   *stream;
    size_t  pos;
    size_t  line;
    size_t  col;
    bool    inblock;
} lexer;

bool init_lexer(lexer *in, FILE *stream);


bool next_token(lexer *in, token* tok);



#endif
