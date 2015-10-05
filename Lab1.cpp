/*
Interpreter for the Simplified Infix Arethmetic Expresion in C
*/

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

int Exp(), Term(), Exp2(int), Term2(int), Fact();
ifstream testfile;

// Main Function
int main(int argc, char* argv[])
{
  testfile.open(argv[1]);
  // Print sigle digit result
  if(testfile.is_open())
  {
    cout << "Result = " << Exp() << '\n';
    testfile.close();
  }
  else
  {
    cout << "Unable to open file";
  }

  return 0;
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
  testfile.get(a);
    if(a != EOF)
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
  testfile.get(a);
  if(a != EOF)
  {
    if (a == '*')
      result = Term2(result * Fact());
    else if (a == '/')
      result = Term2(result / Fact());
    else if (a == '+' || a == '-')
      testfile.putback(a);
  }
  return result;
}

// returns a digit or a symbol(+-/*). also the first function to return a result
int Fact()
{
  char a;
  testfile.get(a);
  return (a - '0');
}
