import sys

filePath = sys.argv[1]
f = open(filePath, 'r+')

def main():
    for x in range(20):
        getWord()

def getWord():
    a = f.read(1)
    while a.isspace():
        a = f.read(1)

    word = a
    while a != '' and not(a.isspace()) and a != ';':
        a = f.read(1)
        word += a
    if len(word) > 1 and (word[-1] == ',' or word[-1] == ';'):
        word = word[:-1]
    print("1 " + word.strip())
    return word.strip()

if __name__ == '__main__':
    main()
