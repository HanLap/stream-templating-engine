#ifndef LEXER_H
#define LEXER_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>



extern char *LEXER_PREFIX;
extern char *LEXER_POSTFIX;

enum TokenClass {
    TEXT   = 0, // everything that is not in between the provided delimiters
    OBLOCK = 1, // provided template prefix
    CBLOCK = 2, // provided template postfix
    RELOP  = 3, // <=, ==, >=, !=
    INTLIT = 4, // numbers
    ID     = 5, // variable identifiers
    IF     = 6, // if
    FI     = 7,
    ELIF   = 8, // elseif
    ELSE   = 9, // else
    END    = 10 // end of file
};

extern char *token_class_names[];

typedef struct token {
    enum TokenClass  tokcls;
    char            *value;
    size_t           line;
    size_t           col;
} Token;


typedef struct lexer {
    FILE   *stream;
    size_t  pos;
    size_t  line;
    size_t  col;
    bool    inblock;
} Lexer;


bool init_lexer(Lexer *lexer, FILE *stream);


/**
 * 
 **/
bool next_token(Lexer *lexer, Token *token);



#endif
