import sys

filePath = sys.argv[1]
f = open(filePath, 'r+')

def main():
    print("Result: " + str(int(Exp())))

def Exp():
    return Exp2(Term())

def Term():
    return Term2(Pwr())

def Exp2(inp):
    result = inp
    x = f.tell()
    a = f.read(1)
    if a != '' :
        if a == '+':
            result = Exp2(result + Term())
        elif a == '-':
            result = Exp2(result - Term())
        elif a == ')':
            f.seek(x)
    return result

def Term2(inp):
    result = inp
    x = f.tell()
    a = f.read(1)
    if f.read != '':
        if a == '*':
            result = Term2(result * Pwr())
        elif a == '/':
            result = Term2(result / Pwr())
        elif (a == '+' or a == '-' or a == ')'):
            f.seek(x)
    return result

def Pwr():
    p = Fact()
    x = f.tell()
    a = f.read(1)

    if a != '':
        if a == '^':
            p = pow(p, Pwr())
        if a == '+' or a == '-' or a == '*' or a == '/' or a == ')':
            f.seek(x)
    return int(p)

def Fact():
    x = f.tell()
    a = f.read(1)
    
    if a == '(':
        exp = Exp()
        a = f.read(1)
        if a == ')':
            return exp
    return int(a)

if __name__ == '__main__':
    main()
