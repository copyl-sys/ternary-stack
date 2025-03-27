from typing import List, Tuple

BASE_81 = 81

class TritError(Exception):
    pass

class T81BigInt:
    def __init__(self, digits: List[int], sign: int = 0):
        self.sign = sign  # 0 = positive, 1 = negative
        self.digits = digits or [0]  # Little-endian
        self.len = len(self.digits)

    @staticmethod
    def from_int(value: int) -> 'T81BigInt':
        if value < 0:
            sign = 1
            value = -value
        else:
            sign = 0
        digits = []
        while value > 0:
            digits.append(value % BASE_81)
            value //= BASE_81
        return T81BigInt(digits or [0], sign)

    def __str__(self) -> str:
        return ('-' if self.sign else '') + ''.join(str(d) for d in reversed(self.digits))

def copy_t81bigint(x: T81BigInt) -> T81BigInt:
    return T81BigInt(x.digits.copy(), x.sign)

def t81bigint_compare(A: T81BigInt, B: T81BigInt) -> int:
    if A.sign != B.sign:
        return -1 if A.sign else 1
    if A.len > B.len:
        return 1
    elif A.len < B.len:
        return -1
    for a, b in zip(reversed(A.digits), reversed(B.digits)):
        if a > b:
            return 1
        elif a < b:
            return -1
    return 0

def tritjs_add_big(A: T81BigInt, B: T81BigInt) -> T81BigInt:
    a = int(str(A), BASE_81)
    b = int(str(B), BASE_81)
    return T81BigInt.from_int(a + b)

def tritjs_subtract_big(A: T81BigInt, B: T81BigInt) -> T81BigInt:
    a = int(str(A), BASE_81)
    b = int(str(B), BASE_81)
    return T81BigInt.from_int(a - b)

def tritjs_multiply_big(A: T81BigInt, B: T81BigInt) -> T81BigInt:
    a = int(str(A), BASE_81)
    b = int(str(B), BASE_81)
    return T81BigInt.from_int(a * b)

def t81_recursive_divide_big(A: T81BigInt, B: T81BigInt) -> Tuple[T81BigInt, T81BigInt]:
    if t81bigint_compare(A, B) < 0:
        return T81BigInt.from_int(0), copy_t81bigint(A)

    d = copy_t81bigint(B)
    q = T81BigInt.from_int(1)

    while True:
        d_doubled = tritjs_add_big(d, d)
        if t81bigint_compare(d_doubled, A) > 0:
            break
        q = tritjs_add_big(q, q)
        d = d_doubled

    A_minus_d = tritjs_subtract_big(A, d)
    q2, r2 = t81_recursive_divide_big(A_minus_d, B)
    final_q = tritjs_add_big(q, q2)
    return final_q, r2

class T81Float:
    def __init__(self, mantissa: T81BigInt, exponent: int, sign: int = 0):
        self.mantissa = mantissa
        self.exponent = exponent
        self.sign = sign

    def normalize(self):
        while len(self.mantissa.digits) > 1 and self.mantissa.digits[-1] == 0:
            self.mantissa.digits.pop()
            self.mantissa.len -= 1
        if self.mantissa.digits == [0]:
            self.exponent = 0
            self.sign = 0
            return
        leading_zeros = 0
        for d in self.mantissa.digits:
            if d != 0:
                break
            leading_zeros += 1
        if leading_zeros > 0 and self.mantissa.len > leading_zeros:
            self.mantissa.digits = self.mantissa.digits[leading_zeros:]
            self.mantissa.len -= leading_zeros
            self.exponent -= leading_zeros

    def __str__(self):
        return f"(mantissa) {self.mantissa}, exponent: {self.exponent}"

def t81float_multiply(A: T81Float, B: T81Float) -> T81Float:
    product = tritjs_multiply_big(A.mantissa, B.mantissa)
    result = T81Float(product, A.exponent + B.exponent, 1 if A.sign != B.sign else 0)
    result.normalize()
    return result

def t81float_divide(A: T81Float, B: T81Float) -> T81Float:
    if t81bigint_compare(B.mantissa, T81BigInt.from_int(0)) == 0:
        raise TritError("Division by zero")
    quotient, _ = t81_recursive_divide_big(A.mantissa, B.mantissa)
    result = T81Float(quotient, A.exponent - B.exponent, 1 if A.sign != B.sign else 0)
    result.normalize()
    return result

class T81Fraction:
    def __init__(self, numerator: T81BigInt, denominator: T81BigInt):
        if t81bigint_compare(denominator, T81BigInt.from_int(0)) == 0:
            raise TritError("Division by zero")
        self.numerator = numerator
        self.denominator = denominator

    def __str__(self):
        return f"{self.numerator} / {self.denominator}"

def parse_trit_string(s: str) -> T81BigInt:
    sign = 1 if s.startswith('-') else 0
    s = s.lstrip('-')
    digits = [int(d) for d in reversed(s) if 0 <= int(d) < BASE_81]
    return T81BigInt(digits, sign)
