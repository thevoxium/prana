#include "lexer.h"
#include <stdlib.h>
#include <string.h>

bool is_letter(char ch) {
  return 'a' <= ch && ch <= 'z' || 'A' <= ch && ch <= 'Z' || ch == '_';
}

bool is_digit(char ch) { return '0' <= ch && ch <= '9'; }

char peek_char(Lexer *l) {
  if (l->readPosition >= strlen(l->input)) {
    return 0;
  } else {
    return l->input[l->readPosition];
  }
}

char *read_identifier(Lexer *l) {
  int startPos = l->position;
  while (is_letter(l->ch)) {
    read_char(l);
  }
  int length = l->position - startPos;
  char *identifier = malloc((length + 1) * sizeof(char));
  if (!identifier)
    return NULL;

  strncpy(identifier, l->input + startPos, length);
  identifier[length] = '\0';
  return identifier;
}

void skip_whitespace(Lexer *l) {
  while (l->ch == ' ' || l->ch == '\t' || l->ch == '\n' || l->ch == '\r') {
    read_char(l);
  }
}

Lexer init_lexer(const char *input) {
  Lexer l;
  l.input = input;
  l.readPosition = 0;
  l.position = 0;
  l.ch = input[0];
  return l;
}

Token new_token(TokenType type, char ch) {
  Token tok;
  tok.type = type;
  char *literal = malloc(2 * sizeof(char));
  literal[0] = ch;
  literal[1] = '\0';
  tok.literal = literal;
  return tok;
}

void free_token(Token *tok) {
  if (tok) {
    free((void *)tok->literal);
    return;
  }
  return;
}

char *read_number(Lexer *l) {
  int startPos = l->position;
  while (is_digit(l->ch)) {
    read_char(l);
  }
  int length = l->position - startPos;
  char *number = malloc((length + 1) * sizeof(char));
  if (!number)
    return NULL;
  strncpy(number, l->input + startPos, length);
  number[length] = '\0';
  return number;
}
void read_char(Lexer *l) {
  if (l->readPosition >= strlen(l->input)) {
    l->ch = 0;
  } else {
    l->ch = l->input[l->readPosition];
  }
  l->position = l->readPosition;
  l->readPosition++;
}

Token next_token(Lexer *l) {
  Token tok;
  skip_whitespace(l);

  switch (l->ch) {
  case '+':
    tok = new_token(PLUS, l->ch);
    break;
  case '-':
    tok = new_token(MINUS, l->ch);
    break;
  case '/':
    tok = new_token(SLASH, l->ch);
    break;
  case '*':
    tok = new_token(ASTERISK, l->ch);
    break;
  case '<':
    tok = new_token(LT, l->ch);
    break;
  case '>':
    tok = new_token(GT, l->ch);
    break;
  case ';':
    tok = new_token(SEMICOLON, l->ch);
    break;
  case ',':
    tok = new_token(COMMA, l->ch);
    break;
  case '(':
    tok = new_token(LPAREN, l->ch);
    break;
  case ')':
    tok = new_token(RPAREN, l->ch);
    break;
  case '{':
    tok = new_token(LBRACE, l->ch);
    break;
  case '}':
    tok = new_token(RBRACE, l->ch);
    break;
  case '!':
    if (peek_char(l) == '=') {
      read_char(l);
      tok = new_token(NOT_EQ, '=');
      char *literal = malloc(3 * sizeof(char));
      literal[0] = '!';
      literal[1] = '=';
      literal[2] = '\0';
      tok.literal = literal;
    } else {
      tok = new_token(BANG, l->ch);
    }
    break;

  case '=':
    if (peek_char(l) == '=') {
      read_char(l);
      tok = new_token(EQ, '=');
      char *literal = malloc(3 * sizeof(char));
      literal[0] = '=';
      literal[1] = '=';
      literal[2] = '\0';
      tok.literal = literal;
    } else {
      tok = new_token(ASSIGN, l->ch);
    }
    break;
  case 0:
    tok.type = EOF_TOKEN;
    tok.literal = "";
    break;
  default:
    if (is_letter(l->ch)) {
      tok.literal = read_identifier(l);
      if (strcmp(tok.literal, "let") == 0) {
        tok.type = LET;
      } else if (strcmp(tok.literal, "fn") == 0) {
        tok.type = FUNCTION;
      } else if (strcmp(tok.literal, "true") == 0) {
        tok.type = TRUE;
      } else if (strcmp(tok.literal, "false") == 0) {
        tok.type = FALSE;
      } else if (strcmp(tok.literal, "if") == 0) {
        tok.type = IF;
      } else if (strcmp(tok.literal, "else") == 0) {
        tok.type = ELSE;
      } else if (strcmp(tok.literal, "return") == 0) {
        tok.type = RETURN;
      } else {
        tok.type = IDENT;
      }
      return tok;
    } else if (is_digit(l->ch)) {
      tok.type = INT;
      tok.literal = read_number(l);
      return tok;
    } else {
      tok = new_token(ILLEGAL, l->ch);
    }
  }

  read_char(l);
  return tok;
}
