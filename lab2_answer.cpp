#include <iostream>
#include <fstream>
#include <math.h>
#include <string>

int Exp(), Term(), Exp2(int), Term2(int), Fact(), Pwr();
std::ifstream inputFile;

int main(int argc, char* argv[])
{
    std::string fileName = "input4.txt";
    inputFile.open(fileName);

    if(!inputFile.is_open())
    {
        std::cerr << "Unable to open file " << fileName << std::endl;
    }

    std::cout << "Result = " << Exp() << std::endl;

    inputFile.close();
    return 0;
}

int Exp()
{
    return Exp2(Term());
}

int Term()
{
    return Term2(Pwr());
}

int Exp2(int inp)
{
    int result = inp;
    char a;
    if(inputFile >> a)
    {
        if(a == '+')
        {
            result = Exp2(result + Term());
        }
        else if(a == '-')
        {
            result = Exp2(result - Term());
        }
        else if(a == ')')
            inputFile.putback(a);
    }

    return result;
}

int Term2(int inp)
{
    int result = inp;
    char a;
    if(inputFile >> a)
    {
        if (a == '*')
            result = Term2(result * Pwr());
        else if (a == '/')
            result = Term2(result / Pwr());
        else if (a == '+' || a == '-' || a == ')')
            inputFile.putback(a);
    }

    return result;
}

int Pwr() {
    int p = Fact();
    char a;

    if (inputFile >> a) {
        if (a == '^') {
            p = pow(p, Pwr());
        }
        if (a == '+' || a == '-' || a == '*' || a == '/' || a == ')')
            inputFile.putback(a);
    }

    return p;
}

int Fact()
{
    char a;
    inputFile.get(a);
    if (a == '(')
    {
        int exp = Exp();
        inputFile >> a;
        if (a == ')')
        {
            return exp;
        }
    }

    return (a - '0');
}
