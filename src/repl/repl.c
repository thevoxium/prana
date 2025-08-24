#include "repl.h"
#include "../lexer/lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PROMPT ">> "
#define MAX_LINE_LEN 1024

void start_repl(void) {
  char line[MAX_LINE_LEN];

  while (1) {
    printf(PROMPT);
    if (!fgets(line, MAX_LINE_LEN, stdin)) {
      break;
    }

    size_t len = strlen(line);
    if (len > 0 && line[len - 1] == '\n') {
      line[len - 1] = '\0';
    }
    if (strcmp(line, "exit") == 0) {
      break;
    }
    Lexer lexer = init_lexer(line);
    read_char(&lexer);

    Token tok = next_token(&lexer);
    while (strcmp(tok.type, EOF_TOKEN) != 0) {
      printf("{Type: %s, Literal: %s}\n", tok.type, tok.literal);
      if (strcmp(tok.type, IDENT) == 0 || strcmp(tok.type, INT) == 0) {
        free((void *)tok.literal);
      }
      if (strcmp(tok.type, EQ) == 0 || strcmp(tok.type, NOT_EQ) == 0) {
        free((void *)tok.literal);
      }
      tok = next_token(&lexer);
    }
    if (tok.literal && tok.literal[0] != '\0') {
      free((void *)tok.literal);
    }
  }
}
