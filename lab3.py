import sys
sys.setrecursionlimit(10000)

filePath = sys.argv[1]
f = open(filePath, 'r+')

symbolTable = {}

def main():
    word = getWord()
    if word.lower() == 'program':
        Declarations()
        Statements()
        w = getWord()
        if w.lower() != 'end':
            print("SyntaxError: 'program' with no paired 'end' found")
            return
    else:
        print("Lexical/SyntaxError: Programs must begin with the word 'Program'")
        return

def Declarations():
    word = getWord()
    if word.lower() == 'begin':
        return
    elif word.lower() == 'var':
        Declaration()
        Declarations()

def Declaration():
    varName = getWord2()
    while True:
        if varName == '':
            print('SyntaxError')
            return
        symbolTable[varName[0]] = None

        if varName[-1] == ';':
            return
        varName = getWord2()

def Statements():
    x = f.tell()
    word = getWord()
    if word.lower() == "end":
        f.seek(x)
        return
    if word == '':
        return
    Statement(word)
    Statements()

def Statement(word):
    #print(word)
    if word.lower() == "input":
        Input()
    elif word.lower() == "output":
        Output()
    else:
        Assignment(word)

def Input():
    id = f.read(1)
    if id.isalpha():
        if id in symbolTable:
            x = input("Enter a Number: ")
            x = int(x)
            if isinstance(x, int):
                symbolTable[id] = x

            else:
                print("SyntaxError: Value Must be a Number")
                return
        else:
            print("SemanticError: " + str(id) + " Value Assigned but not Declared")
            return
    else:
        print("LexicalError: Not a Valid Variable Name")
        return

def Output():
    x = f.tell()
    id = f.read(1)
    if id.isalpha():
        if id in symbolTable:
            print(symbolTable[id])
        else:
            print("SemanticError: " + str(id) + " Value Assigned but not Declared")
            return
    else:
        f.seek(x)
        x = f.tell()
        print(str(int(Exp())))
        f.seek(x)
        getWord()

def Assignment(word):
    eq = getWord()
    if eq == "=":
        x = f.tell()
        temp = Exp()
        f.seek(x)
        getWord()
        if word in symbolTable:
            symbolTable[word] = temp
        else:
            print("Semantic Error: " + str(word) + " Value Assigned but not Declared")
            return
    else:
        print("SyntaxError: No '=' Found")
        return
    return

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

def getWord():
    a = f.read(1)

    while a.isspace() or a == ';' or a == "\n":
        a = f.read(1)

    word = a
    while a != '' and not(a.isspace()) and a != ';':
        a = f.read(1)
        word += a
    if len(word) > 1 and (word[-1] == ',' or word[-1] == ';'):
        word = word[:-1]

    return word.strip()

def getWord2():
    a = f.read(1)
    while a.isspace():
        a = f.read(1)

    word = a
    while a != '' and not(a.isspace()):
        a = f.read(1)
        word += a
    if len(word) > 1 and word[1] == ',':
        word = word[0]
    return word.strip()

if __name__ == '__main__':
    main()
