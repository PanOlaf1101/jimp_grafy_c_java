import java.io.File;
import java.io.FileNotFoundException;
import java.util.*;

public class Graph {
	public final HashSet<Edge> edges;
	public final ArrayList<Vertex> vertices;

	public Graph() {
		edges = new HashSet<>();
		vertices = new ArrayList<>();
	}

	public void addEdge(Edge e) {
		edges.add(e);
	}

	//Do testowania
	public void randomizeCoordinates() {
		var r = new Random();
		int size = vertices.size();
		vertices.clear();
		for(int i = 0; i < size; i++) {
			vertices.add(new Vertex(r.nextInt(100), r.nextInt(100)));
		}
	}

	public void addEdge(String name, int u, int v, double weight) {
		addEdge(new Edge(name, u, v, weight));
	}

	public void readFromFile(File file) throws FileNotFoundException, NumberFormatException {
		var sc = new Scanner(file);
		ArrayList<Edge>  edges = new ArrayList<>();
		while(sc.hasNextLine()) {
			String[] tokens = sc.nextLine().split(" ");
			int u = Integer.parseInt(tokens[1]);
			int v = Integer.parseInt(tokens[2]);
			double weight = Double.parseDouble(tokens[3]);
			edges.add(new Edge(tokens[0], u, v, weight));
		}
		for(Edge e : edges)
			addEdge(e);
		edges.clear();
	}
}

class Edge {
	public String name;
	public int u;
	public int v;
	public double weight;
	static private int biggest_v = 0;

	public Edge(String name, int _u, int _v, double weight) throws IllegalArgumentException {
		if(_u < 1 || _v < 1)
			throw new IllegalArgumentException("Numery wierzchołków muszą być większe od 0");
		u = _u - 1;
		v = _v - 1;
		this.weight = weight;
		this.name = name;
		if(u > v) {
			u ^= v;
			v ^= u;
			u ^= v;
		}
		if(v >= biggest_v)
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

