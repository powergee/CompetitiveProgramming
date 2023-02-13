import sys
sys.setrecursionlimit(int(1e6))

class ParseError(Exception):
    pass

class Calculator:
    def __init__(self, str) -> None:
        self.str = str
        self.index = 0
        self.result = self.expression()
        if self.index != len(self.str):
            raise ParseError()

    # Expression -> Term (('+'|'-') Term)*
    def expression(self) -> int:
        # First(Term) = First(Factor) = { '0'-'9', '(' }
        if self.index == len(self.str) or (not str.isdigit(self.str[self.index]) and self.str[self.index] != '('):
            raise ParseError()

        sum = self.term()
        while self.index < len(self.str) and (self.str[self.index] == '+' or self.str[self.index] == '-'):
            op = self.str[self.index]
            self.index += 1
            t = self.term()
            if op == '+':
                sum += t
            else:
                sum -= t
        return sum

    # Term -> Factor (('*'|'/') Factor)*
    def term(self) -> int:
        # First(Factor) = { '0'-'9', '(' }
        if self.index == len(self.str) or (not str.isdigit(self.str[self.index]) and self.str[self.index] != '('):
            raise ParseError()
        
        mult = self.factor()
        while self.index < len(self.str) and (self.str[self.index] == '*' or self.str[self.index] == '/'):
            op = self.str[self.index]
            self.index += 1
            t = self.factor()
            if op == '*':
                mult *= t
            elif t != 0 and mult % t == 0:
                mult //= t
            else:
                raise ParseError()
        return mult

    # Factor -> Number | ( Expression )
    def factor(self) -> int:
        if self.index == len(self.str):
            raise ParseError()
        if str.isdigit(self.str[self.index]):
            return self.number()
        if self.str[self.index] == '(':
            self.index += 1
            sub = self.expression()
            if self.index < len(self.str) and self.str[self.index] == ')':
                self.index += 1
                return sub
            else:
                raise ParseError()
        raise ParseError()

    # Number -> ['0'-'9']+
    def number(self) -> int:
        begin = self.index
        while self.index < len(self.str) and str.isdigit(self.str[self.index]):
            self.index += 1
        if begin == self.index:
            raise ParseError()
        return int(self.str[begin:self.index])

try:
    print(Calculator(input()).result)
except ParseError:
    print("ROCK")