from dataclasses import dataclass
from collections.abc import Callable


def change(amount: int) -> dict[int, int]:
    if not isinstance(amount, int):
        raise TypeError('Amount must be an integer')
    if amount < 0:
        raise ValueError('Amount cannot be negative')
    counts, remaining = {}, amount
    for denomination in (25, 10, 5, 1):
        counts[denomination], remaining = divmod(remaining, denomination)
    return counts


# Write your first then lower case function here
def first_then_lower_case(a, p, /):
    for string in a:
        if p(string):
            return string.lower()
    return None


# Write your powers generator here
def powers_generator(*, base, limit):
    power = 0
    while True:
        result = base ** power
        if result > limit:
            break
        yield result
        power += 1


# Write your say function here
def say(word=None):
    words = []

    def extra(word=None):
        if word is None:
            return ' '.join(words)
        words.append(word)
        return extra

    return extra(word)

# Write your line count function here
def meaningful_line_count(filename):
    try:
        with open(filename, 'r') as file:
            return sum(1 for line in file 
                       if line.strip() and not line.strip().startswith('#'))
    except FileNotFoundError:
        raise

# Write your Quaternion class here
@dataclass(frozen=True)
class Quaternion:
    def __init__(self, w, x, y, z):
        self.w = w
        self.x = x
        self.y = y
        self.z = z

    def add(self, other):
        return Quaternion(self.w + other.w, self.x + other.x, self.y + other.y, self.z + other.z)
    
    def __mul__(self, other):
        w = self.w * other.w - self.x * other.x - self.y * other.y - self.z * other.z
        x = self.w * other.x + self.x * other.w + self.y * other.z - self.z * other.y
        y = self.w * other.y - self.x * other.z + self.y * other.w + self.z * other.x
        z = self.w * other.z + self.x * other.y - self.y * other.x + self.z * other.w
        return Quaternion(w, x, y, z)
    
    @property
    def coefficients(self):
        return [self.w, self.x, self.y, self.z]
    
    @property
    def conjugate(self):
        return Quaternion(self.w, -self.x, -self.y, -self.z)   
    
    def __eq__(self, other):
        return self.w == other.w and self.x == other.x and self.y == other.y and self.z == other.z

    def __str__(self):
        return f"{self.w} + {self.x}i + {self.y}j + {self.z}k"
    