#ifndef LEXER_H
#define LEXER_H

#include "stdbool.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ILLEGAL "ILLEGAL"
#define EOF_TOKEN "EOF"
#define IDENT "IDENT"
#define INT "INT"
#define ASSIGN "="
#define PLUS "+"
#define SEMICOLON ";"
#define LET "LET"
#define LPAREN "("
#define RPAREN ")"
#define COMMA ","
#define LBRACE "{"
#define RBRACE "}"
#define ASSIGN "="
#define PLUS "+"
#define MINUS "-"
#define BANG "!"
#define ASTERISK "*"
#define SLASH "/"
#define LT "<"
#define GT ">"
#define FUNCTION "FUNCTION"
#define LET "LET"
#define TRUE "TRUE"
#define FALSE "FALSE"
#define IF "IF"
#define ELSE "ELSE"
#define RETURN "RETURN"
#define EQ "=="
#define NOT_EQ "!="

typedef const char *TokenType;

typedef struct Token {
  TokenType type;
  const char *literal;
} Token;

typedef struct Lexer {
  const char *input;
  int position;
  int readPosition;
  char ch;
} Lexer;

Token new_token(TokenType type, char ch);
Lexer init_lexer(const char *input);
Token next_token(Lexer *l);
char *read_identifier(Lexer *l);
char *read_number(Lexer *l);
char peek_char(Lexer *l);
bool is_letter(char ch);
bool is_digit(char ch);
void skip_whitespace(Lexer *l);
void read_char(Lexer *l);
void free_token(Token *tok);

#endif // !LEXER_H
