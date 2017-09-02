#include "tokenize.h"

#include <stdlib.h>
#include <assert.h>

typedef enum {
  LIST,
  INTEGER,
  SYMBOL
} ExpressionType;

struct sExpressionVector;
struct sExpression;

typedef struct sExpressionVector ExpressionVector;
typedef struct sExpression Expression;

struct sExpressionVector {
  size_t size;
  size_t position;
  Expression ** expressions;
};

struct sExpression {
  ExpressionType type;
  union {
    int integer;
    char * symbol;
    ExpressionVector * list;
  };
};

ExpressionVector * newExpressionVector() {
  ExpressionVector * vector = malloc(sizeof(newExpressionVector));
  vector->size = 32; // This is just a small number meant to be large enough to hold most subexpressions without resizing.
  vector->position = 0;
  vector->expressions = malloc(sizeof(Expression *) * vector->size);
}

void appendExpressionVector(ExpressionVector * vector, Expression * expr) {
  vector->expressions[vector->position++] = expr;
  if (vector->position == vector->size) {
    vector->size *= 2; // Double the size of the vector after each overflow.
    vector->expressions = realloc(vector->expressions, sizeof(Expression *) * vector->size);
  }
}

Expression * newInteger(int value) {
  Expression * expr = malloc(sizeof(Expression));
  expr->type = INTEGER;
  expr->integer = value;
  return expr;
}

Expression * newList(ExpressionVector * expressions) {
  Expression * expr = malloc(sizeof(Expression));
  expr->type = LIST;
  expr->list = expressions;
}

Expression * newSymbol(char * symbol) {
  Expression * expr = malloc(sizeof(Expression));
  expr->type = SYMBOL;
  expr->symbol = symbol;
  return expr;
}

Expression * atomToExpr(Token * atom) {
  assert(atom->type == ATOM);
  //TODO! Make this handle other expressions besides symbols.
  return newSymbol(atom->text);
}

Expression * parse(Token * token) {
  ExpressionVector * exprVector = newExpressionVector();
  while (token != NULL) {
    if (token->type == OPEN_PAREN) {
      appendExpressionVector(exprVector, parse(token));
    } else if (token->type == CLOSE_PAREN) {
      return newList(exprVector);
    } else if (token->type == ATOM) {
      appendExpressionVector(exprVector, atomToExpr(token));
    } else {
      //TODO! CRASH HARD
    }
  }
  return newList(exprVector);
}

void printExpression(Expression * expression) {
  if (expression == NULL) {
    return;
  } else if (expression->type == LIST) {
    printf("(");
    for (int i = 0; i < expression->list->position; i++) {
      printExpression(expression->list->expressions[i]);
    }
    printf(")");
  } else if (expression->type == SYMBOL) {
    printf("<%s>", expression->symbol);
  } else if (expression->type == INTEGER) {
    printf("<%d>", expression->integer);
  } else {
    //TODO! CRASH HARD
  }
}

int main() {
  char * source = "(- (+ 1 2) (+ 45 78))";
  Token * token = tokenize(source);
  Expression * expr = parse(token);
  printExpression(expr);
  
  return 0;
}
