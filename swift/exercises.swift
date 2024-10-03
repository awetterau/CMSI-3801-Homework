import Foundation

struct NegativeAmountError: Error {}
struct NoSuchFileError: Error {}

func change(_ amount: Int) -> Result<[Int:Int], NegativeAmountError> {
    if amount < 0 {
        return .failure(NegativeAmountError())
    }
    var (counts, remaining) = ([Int:Int](), amount)
    for denomination in [25, 10, 5, 1] {
        (counts[denomination], remaining) = 
            remaining.quotientAndRemainder(dividingBy: denomination)
    }
    return .success(counts)
}

// Write your first then lower case function here

// First requirement: Function with predicate
func firstThenLowerCase(of array: [String], satisfying predicate: (String) -> Bool) -> String? {
    return array.first(where: predicate)?.lowercased()
}

// Write your say function here

class Phrase {
    private var words: [String]
    
    init(_ words: [String] = []) {
        self.words = words
    }
    
    var phrase: String {
        return words.joined(separator: " ")
    }
    
    func and(_ word: String) -> Phrase {
        return Phrase(words + [word])
    }
}

func say(_ word: String = "") -> Phrase {
    return Phrase([word])
}
// Write your meaningfulLineCount function here

func meaningfulLineCount(_ filename: String) async -> Result<Int, Error> {
    do {
        let fileURL = URL(fileURLWithPath: filename)
        let meaningfulLines = try await withThrowingTaskGroup(of: Int.self) { group in
            let fileHandle = try FileHandle(forReadingFrom: fileURL)
            defer { try? fileHandle.close() }
            
            for try await line in fileHandle.bytes.lines {
                group.addTask {
                    let trimmedLine = line.trimmingCharacters(in: .whitespacesAndNewlines)
                    return (!trimmedLine.isEmpty && !trimmedLine.hasPrefix("#")) ? 1 : 0
                }
            }
            
            return try await group.reduce(0, +)
        }
        return .success(meaningfulLines)
    } catch {
        return .failure(error)
    }
}

// Write your Quaternion struct here

struct Quaternion: Equatable, CustomStringConvertible {
    let a: Double
    let b: Double
    let c: Double
    let d: Double

    init(a: Double = 0, b: Double = 0, c: Double = 0, d: Double = 0) {
        self.a = a
        self.b = b
        self.c = c
        self.d = d
    }

    static let ZERO = Quaternion()
    static let I = Quaternion(b: 1)
    static let J = Quaternion(c: 1)
    static let K = Quaternion(d: 1)

    var coefficients: [Double] { [a, b, c, d] }

    var conjugate: Quaternion {
        Quaternion(a: a, b: -b, c: -c, d: -d)
    }

    static func + (lhs: Quaternion, rhs: Quaternion) -> Quaternion {
        Quaternion(a: lhs.a + rhs.a, b: lhs.b + rhs.b, c: lhs.c + rhs.c, d: lhs.d + rhs.d)
    }

    static func * (lhs: Quaternion, rhs: Quaternion) -> Quaternion {
        Quaternion(
            a: lhs.a * rhs.a - lhs.b * rhs.b - lhs.c * rhs.c - lhs.d * rhs.d,
            b: lhs.a * rhs.b + lhs.b * rhs.a + lhs.c * rhs.d - lhs.d * rhs.c,
            c: lhs.a * rhs.c - lhs.b * rhs.d + lhs.c * rhs.a + lhs.d * rhs.b,
            d: lhs.a * rhs.d + lhs.b * rhs.c - lhs.c * rhs.b + lhs.d * rhs.a
        )
    }

    var description: String {
        let components = [(a, ""), (b, "i"), (c, "j"), (d, "k")]
        let formattedComponents = components.enumerated().compactMap { index, component -> String? in
            let (value, unit) = component
            if value == 0 { return nil }
            
            let sign = value < 0 ? "-" : (index == 0 ? "" : "+")
            let absValue = abs(value)
            
            let valueString: String
            if absValue == 1 && unit != "" {
                valueString = ""
            } else if absValue.truncatingRemainder(dividingBy: 1) == 0 {
                valueString = String(format: "%.0f", absValue)
            } else {
                valueString = String(format: "%.2f", absValue)
            }
            
            return "\(sign)\(valueString)\(unit)"
        }
        
        return formattedComponents.isEmpty ? "0" : formattedComponents.joined()
    }
}

// Write your Binary Search Tree enum here
