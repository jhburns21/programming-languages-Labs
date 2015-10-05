/*
Interpreter for the Simplified Infix Arethmetic Expresion in C
*/

#include <stdio.h>
#include <stdlib.h>

int Exp(), Term(), Exp2(int), Term2(int), Fact();

// Main Function
int main()
{
  // Print sigle digit result
  printf("result= %d\n", Exp());
}

// Starts the Interpreter
int Exp()
{
  // S or starting point of the language
  return Exp2(Term());
}

// returns the result of a Term
int Term()
{
    return Term2(Fact());
}

// Determines if the next symbol is a + or -
// may only return inp in some cases

int Exp2(int inp)
{
  int result = inp;
  char a;
    if((a = getchar()) != '\n')
    {
      if(a == '+')
      {
        result = Exp2(result + Term());
      }
      else if(a == '-')
      {
        result = Exp2(result - Term());
      }
    }
    return result;
}

// determines is the next character is a * or /
// if result is + or - the char is put back into the input stream
// may only return inp

int Term2(int inp)
{
  int result = inp;
  char a;
  if((a = getchar()) != '\n')
  {
    if (a == '*')
      result = Term2(result * Fact());
    else if (a == '/')
      result = Term2(result / Fact());
    else if (a == '+' || a == '-')
      ungetc(a, stdin);
  }
  return result;
}

// returns a digit or a symbol(+-/*). also the first function to return a result
int Fact()
{
  char a = getchar();
  return atoi(&a);
}
