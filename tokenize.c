#include "tokenize.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

Token * newToken(TokenType type, char * text) {
  Token * token = malloc(sizeof(Token));
  token->type = type;
  token->text = text;
  token->next = NULL;
}

Token * appendToken(Token * head, Token * new) {
  if (head == NULL) {
    new->next = NULL;
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

Token * tokenize(char * source) {
  Token * head = NULL;
  char text[TEXT_MAX_SIZE];
  size_t text_position = 0;
  while (*source != '\0') {
    if (*source == '(') {
      if (text_position != 0) {
	text[text_position] = '\0';
	text_position = 0;
	head = appendToken(head, newToken(ATOM, copyText(text)));
      }
      head = appendToken(head, newToken(OPEN_PAREN, "("));
    } else if (*source == ')') {
      if (text_position != 0) {
	text[text_position] = '\0';
	text_position = 0;
	head = appendToken(head, newToken(ATOM, copyText(text)));
      }
      head = appendToken(head, newToken(CLOSE_PAREN, ")"));
    } else if (*source == ';') {
      if (text_position != 0) {
	text[text_position] = '\0';
	text_position = 0;
	head = appendToken(head, newToken(ATOM, copyText(text)));
      }
      while (*source && (*source != '\n')) {
	source++;
      }
    } else if (*source == ' ') {
      if (text_position != 0) {
	text[text_position] = '\0';
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
    text[text_position] = '\0';    
    text_position = 0;
    head = appendToken(head, newToken(ATOM, copyText(text)));
  }

  Token * reverseHead = NULL;
  while (head != NULL) {
    Token * next_head = head->next;
    reverseHead = appendToken(reverseHead, head);
    head = next_head;
  }
  return reverseHead;
}

