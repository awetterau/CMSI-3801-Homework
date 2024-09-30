import java.util.List;
import java.util.Map;
import java.util.HashMap;
import java.util.Optional;
import java.util.function.Predicate;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class Exercises {
    static Map<Integer, Long> change(long amount) {
        if (amount < 0) {
            throw new IllegalArgumentException("Amount cannot be negative");
        }
        var counts = new HashMap<Integer, Long>();
        for (var denomination : List.of(25, 10, 5, 1)) {
            counts.put(denomination, amount / denomination);
            amount %= denomination;
        }
        return counts;
    }

    // Write your first then lower case function here

    		// use list.of

	public static String first_then_lower_case(List<String> a, Predicate<String> p) {
		return a.stream()
			   .filter(p)
			   .findFirst()
			   .map(String::toLowerCase)
			   .orElse(null);
	}

    // Write your say function here

    // Write your line count function here
		// Use a BufferedReader and a try-with-resources block. Process the file using the lines() method to produce a stream.

	public void meaningful_line_count() {
		try (BufferedReader read = new BufferedReader(new FileReader("../test-for-line-count.txt"))) {
			long validLineCount = read.lines()
			.filter(line -> !line.trim().isEmpty())
			.filter(line -> !line.trim().startsWith("#"))
			.count(); 
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}

// Write your Quaternion record class here
	// use records!
		// public record Point(double x, double y) { // fields are at the top
		// 	public static final Point ORIGIN = new Point(0, 0); // use i j k 0 to go here
			
		// 	public Point { // validation check on homework
		// 		if (Double.isNaN(x) || Double.isNaN(y)) {
		// 			throw new IllegalArgumentException("Coordinates can not be NaN");
		// 		}
		// 	}
			
		// 	public double distanceFromOrigin() { // methods such as coefficients are added to record right here
		// 		return Math.hypot(x, y);
		// 	}
			
		// 	public Point reflectionAboutOrigin() {
		// 		return new Point(-x, -y);
		// 	}
			
		// 	public static Point midpointOf(Point p, Point q) {
		// 		return new Point((p.x + q.x) / 2.0, (p.y + q.y) / 2.0);
		// 	}
		// }

public record Quaternion(double a, double b, double c, double d) {
	public static final D = new Quaternion(i, j, k, 0);

	public Quaternion {
		if (Double.isNan(a) || Double.isNan(b) || Double.isNan(c) || Double.isNan(d)) {
			throw new IllegalArgumentException("inputs cannot be NaN");
		}
	}
}

	@Override
	public Quaternion add(Quaternion other) {
		return new Quaternion(this.a + other.a, this.b + other.b, this.c + other.c, this.d + other.d);
	}

	public Quaternion coefficients() {
		return (this.a, this.b, this.c, this.d);
	}

	@Override
	public Quaternion mul(Quaternion other) {
		double w = this.a * other.a - this.b * other.b - this.c * other.c - this.d * other.d
		double x = this.a * other.b + this.b * other.a + this.c * other.d - this.d * other.c
		double y = this.a * other.c - this.b * other.d + this.c * other.a + this.d * other.b
		double z = this.a * other.d + this.b * other.c - this.c * other.b + this.d * other.a
		return new Quaternion(w, x, y, z)
	}

	public Quaternion conjugate() {
		return new Quaternion(this.a, -this.b, -this.c, this.d)
	}

	@Override
	public String toString() {
		return
	}
}

// Write your BinarySearchTree sealed interface and its implementations here
sealed interface BinarySearchTree permits Empty, Node {
	int size();
	BinarySearchTree insert(String item);
	boolean contains(String item); // tostring is already an object
}

// each list has three things that can happen, the empty and node classes
// have these three methods in them both

final class Empty implements List {

	public int size() {
		return 0;
	}
	
	public BinarySearchTree insert(String item) {
		return new Node(item, this.left, this.right);
	}
	
	public boolean contains(String item) {
		return false;
	}
}

final class Node implements BinarySearchTree {
	final String head;
	final BinarySearchTree left;
    	final BinarySearchTree right;
	
	Node(String head, BinarySearchTree left, BinarySearchTree right) {
		this.head = head;
		this.left = left;
		this.right = right;
	}
	
	int size() {
        	return 1+ left.size, 1+ right.size; 
	}
	
	public BinarySearchTree insert(String head) {
		return new Node(head, this);
	}
	
	public boolean contains(String head) {
		return this.head.equals(head) || left.contains(head) || right.contains(head);
	}
}