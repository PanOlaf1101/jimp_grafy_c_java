import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.Scanner;

public class Graph {
	HashSet<Edge> edges;
	ArrayList<Vertex> vertices;

	public Graph() {
		edges = new HashSet<>();
		vertices = new ArrayList<>();
	}

	public void addEdge(Edge e) {
		edges.add(e);
	}

	public void addEdge(String name, int u, int v, double weight) {
		addEdge(new Edge(name, u, v, weight));
	}

	public void readFromFile(File file) {
		try {
			var sc = new Scanner(file);
			while(sc.hasNextLine()) {
				String[] tokens = sc.nextLine().split(" ");
				int u = Integer.parseInt(tokens[1]);
				int v = Integer.parseInt(tokens[2]);
				double weight = Double.parseDouble(tokens[3]);
				addEdge(tokens[0], u, v, weight);
			}
		} catch (FileNotFoundException e) {
			throw new RuntimeException("Nie można otworzyć pliku " + file.getAbsolutePath());
		} catch (NumberFormatException e) {
			throw new RuntimeException("Niepoprawny format! " + e.getMessage());
		}
	}
}

class Edge {
	public String name;
	public int u;
	public int v;
	public double weight;
	static private int biggest_v = 0;

	public Edge(String name, int _u, int _v, double weight) {
		if(_u < 1 || _v < 1)
			throw new IllegalArgumentException();
		u = _u - 1;
		v = _v - 1;
		this.weight = weight;
		this.name = name;
		if(u > v) {
			u ^= v;
			v ^= u;
			u ^= v;
		}
		if(v > biggest_v)
			biggest_v = v+1;
	}

	public boolean equals(Edge e) {
		return u == e.u && v == e.v;
	}

	@Override
	public boolean equals(Object obj) {
		if(obj instanceof Edge)
			return equals((Edge)obj);
		else
			return false;
	}

	@Override
	public String toString() {
		return "(%s, u = %d, v = %d, weight = %.6f)".formatted(name, u, v, weight);
	}

	@Override
	public int hashCode() {
		return u * biggest_v + v;
	}
}

record Vertex(int id, double x, double y) {}