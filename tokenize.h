/*
 * This module is for splitting text into tokens. The most important defintions
 * are the token struct, token type enum, and tokenize function.
 */

#ifndef _TOKENIZE
#define _TOKENIZE

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/*
 * The max possible size of a single token.
 */
#define TEXT_MAX_SIZE 512

/*
 * The different possible token types. OPEN_PAREN is for the '(' token and
 * CLOSE_PAREN is for the ')' token. The ATOM type is for any other token,
 * such as literals or symbols.
 */
typedef enum {
  OPEN_PAREN,
  CLOSE_PAREN,
  ATOM
} TokenType;

/*
 * The token object contains the type of a token and the text inside of it. For
 * OPEN_PAREN and CLOSE_PAREN, the text is redundant and will probably be shared
 * between PAREN tokens. The ATOM text is used to parse the ATOM token into an
 * expression later on. Note that tokens can be used as an internal list, with
 * the 'next' pointer pointing to the next element.
 *
 * TODO! Add line and column number token starts on. It'll help for debugging.
 */
typedef struct sToken {
  TokenType type;
  char * text;
  struct sToken * next;
} Token;

/*
 * Allocate a new token with the given type and text.
 * @param type The type of the new token.
 * @param text The text of the token. This is not copied.
 * @return A new heap allocated token struct.
 */
Token * newToken(TokenType type, char * text);

/*
 * TODO!
 */
Token * appendToken(Token * head, Token * new);

/*
 * Copy text into a new heap allocated buffer. Note that the buffer will be
 * shorter than or equal to MAX_TEXT_SIZE. If a longer source string is passed
 * in, then the copy will be truncated.
 * @param text The source text to copy in. It must be null terminated.
 * @return A heap allocated copy of the source text that's maximum length is
 * MAX_TEXT_SIZE. The string will be null terminated.
 */
char * copyText(char * text);

/*
 * Take a character array representing some source code and split it into an
 * internal list of tokens.
 * @param source The string containing the source code.
 * @return An internal list of tokens.
 *
 * TODO! Rewrite this to use a file stream instead of a character array. Then it
 * can be used with stdout or files directly.
 */
Token * tokenize(char * source);

/*
 * Print out a token list seperated by newlines. This is meant for debugging.
 * @param token The first token of the token list.
 */
void printTokens(Token * token);

#endif
