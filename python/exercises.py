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
def first_then_lower_case(a, p):
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


# Write your Quaternion class here
