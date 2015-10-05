/*
John Burns

Interpreter for parsing mathematical expressions.
contains + - / * ^
parenthesis only work in simple cases ie. (2+3)*4
*/
using System;
using System.IO;

  public class Interpreter
  {
    static StreamReader sr;
      static void Main(String[] args)
      {
        sr = new StreamReader(@args[0]);
        // Print sigle digit result
        if(File.Exists(@args[0]))
        {
          Console.WriteLine("Result = " + Exp());
        }
        else
        {
          Console.WriteLine("Unable to open file");
        }
      }
      // Starts the Interpreter
      public static int Exp()
      {
        // S or starting point of the language
        return Exp2(Term());
      }

      // returns the result of a Term
      public static int Term()
      {
          return Term2(Fact());
      }

      // Determines if the next symbol is a + or -
      // may only return inp in some cases
      //calls the paren function to handle ) case
      public static int Exp2(int inp)
      {
          int result = inp;
          if(sr.Peek() >= 0)
          {
            if((char)sr.Peek() == '+')
            {
              sr.Read();
              result = Exp2(result + Term());
            }
            else if((char)sr.Peek() == '-')
            {
              sr.Read();
              result = Exp2(result - Term());
            }
          }

          if((char)sr.Peek() == ')')
          {
            Console.WriteLine(result);
            return paren(result);
          }

          return result;
      }

      // determines is the next character is a * or /
      // if result is + or - the char is put back into the input stream
      // may only return inp

      public static int Term2(int inp)
      {
        int result = inp;
        if(sr.Peek() >= 0)
        {
          if ((char)sr.Peek() == '*')
          {
            sr.Read();
            result = Term2(result * Fact());
          }

          else if ((char)sr.Peek() == '/')
          {
            sr.Read();
            result = Term2(result / Fact());
          }

          else if ((char)sr.Peek() == '+' || (char)sr.Peek() == '-')
          {}
        }
        return result;
      }

      // Calls the Num function and starts fact2 to check for ^
      public static int Fact()
      {
        return Fact2(Num());
      }

      // determins if next character is a ^
      // if so, executes the power function on the result of Num()
      public static int Fact2(int inp)
      {
        int result = inp;
        if(sr.Peek() >= 0)
        {
          if((char)sr.Peek() == '^')
          {
            sr.Read();
            return Fact2(Convert.ToInt32(Math.Pow(result, Num())));
          }
        }
        return result;
      }

      // returns a number and checks for parenthesis
      public static int Num()
      {
        if(sr.Peek() >= 0)
        {

          if((char)sr.Peek() == '(')
          {
            sr.Read();
          }
          char a;
          a = (char)sr.Read();
          return (a - '0');
        }
        return 0;
      }

      // calls exp() recursively and strips ) out of the stream
      public static int paren(int inp)
      {
        sr.Read();
        if((char)sr.Peek() == '+'){
          sr.Read();
          return (inp + Exp());
        }
        if((char)sr.Peek() == '-'){
          sr.Read();
          return (inp - Exp());
        }
        if((char)sr.Peek() == '/'){
          sr.Read();
          return (inp / Exp());
        }
        if((char)sr.Peek() == '*'){
          sr.Read();
          return (inp * Exp());
        }
        if((char)sr.Peek() == ')'){
          sr.Read();
          return paren(inp);
        }
        return 0;
      }
  }
