#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


#define TEXT_MAX_SIZE 512

typedef enum {
  OPEN_PAREN,
  CLOSE_PAREN,
  ATOM
} TokenType;

typedef struct sToken {
  TokenType type;
  char * text;
  struct sToken * next;
} Token;

Token * newToken(TokenType type, char * text) {
  Token * token = malloc(sizeof(Token));
  token->type = type;
  token->text = text;
  token->next = NULL;
}

Token * appendToken(Token * head, Token * new) {
  if (head == NULL) {
    return new;
  } else {
    new->next = head;
    return new;
  }
}

char * copyText(char * text) {
  char * new_text = malloc(sizeof(char) * TEXT_MAX_SIZE);
  size_t i;
  for (i = 0; i < TEXT_MAX_SIZE; i++) {
    new_text[i] = text[i];
    if (text[i] == '\0') {
      break;
    }
  }
  new_text[i] = '\0';
  return new_text;
}

void printTokens(Token * token) {
  while (token != NULL) {
    printf("%s\n", token->text);
    token = token->next;
  }
}

Token * parse(char * source) {
  Token * head = NULL;
  char text[TEXT_MAX_SIZE];
  size_t text_position = 0;
  while (*source != '\0') {
    if (*source == '(') {
      if (text_position != 0) {
	text[text_position + 1] = '\0';
	text_position = 0;
	head = appendToken(head, newToken(ATOM, copyText(text)));
      }
      head = appendToken(head, newToken(OPEN_PAREN, "("));
    } else if (*source == ')') {
      if (text_position != 0) {
	text[text_position + 1] = '\0';
	text_position = 0;
	head = appendToken(head, newToken(ATOM, copyText(text)));
      }
      head = appendToken(head, newToken(CLOSE_PAREN, ")"));
    } else if (*source == ';') {
      if (text_position != 0) {
	text[text_position + 1] = '\0';
	text_position = 0;
	head = appendToken(head, newToken(ATOM, copyText(text)));
      }
      while (*source && (*source != '\n')) {
	source++;
      }
    } else if (*source == ' ') {
      if (text_position != 0) {
	text[text_position + 1] = '\0';
	text_position = 0;
	head = appendToken(head, newToken(ATOM, copyText(text)));
      }
    } else {
      assert(text_position < (TEXT_MAX_SIZE - 1));      
      text[text_position++] = *source;
    }
    source++;
  }
  if (text_position != 0) {
    text[text_position + 1] = '\0';    
    text_position = 0;
    head = appendToken(head, newToken(ATOM, copyText(text)));
  }
  return head;
}

int main() {
  char source[] = "((+ 1 2) (+ 3 45))";
  Token * tokens = parse(source);
  printTokens(tokens);
}
