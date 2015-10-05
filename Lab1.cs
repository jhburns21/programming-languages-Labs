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

      public static int Exp2(int inp)
      {
        int result = inp;
        char a;
        a = (char)sr.Read();
          if(a >= 0)
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

      // returns a digit or a symbol(+-/*). also the first function to return a result
      public static int Fact()
      {
        char a;
        a = (char)sr.Read();
        Console.WriteLine(a);
        Console.WriteLine(a - '0');
        return (a - '0');
      }

  }
