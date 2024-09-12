import { open } from "node:fs/promises"

export function change(amount) {
  if (!Number.isInteger(amount)) {
    throw new TypeError("Amount must be an integer")
  }
  if (amount < 0) {
    throw new RangeError("Amount cannot be negative")
  }
  let [counts, remaining] = [{}, amount]
  for (const denomination of [25, 10, 5, 1]) {
    counts[denomination] = Math.floor(remaining / denomination)
    remaining %= denomination
  }
  return counts
}

// Write your first then lower case function here
export function firstThenLowerCase(a, p) {
  return a.find(p)?.toLowerCase()
}

// Write your powers generator here
export function* powersGenerator({ ofBase, upTo }) {
  let power = 0
  while (true) {
    const result = ofBase ** power
    if (result > upTo) {
      return
    }
    yield result
    power += 1
  }
}

// Write your say function here
export function say(word = undefined) {
  const words = []

  function nextWord(word = undefined) {
    if (word == undefined) {
      return words.join(" ")
    }
    words.push(word)
    return extra
  }
  return nextWord(word)
}

// Write your line count function here

// Write your Quaternion class here
