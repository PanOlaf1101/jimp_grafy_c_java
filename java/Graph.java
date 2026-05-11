import java.io.File;
import java.io.FileNotFoundException;
import java.util.*;

public class Graph {
	public final HashSet<Edge> edges;
	public final HashMap<Short, Vertex> vertices;

	public Graph() {
		edges = new HashSet<>();
		vertices = new HashMap<>();
	}

	public void addEdge(Edge e) {
		edges.add(e);
	}

	//Do testowania
	public void randomizeCoordinates(int x, int y, int w, int h) {
		var r = new Random();
		int size = vertices.size();
		vertices.clear();
		for(short i = 1; i <= size; i++) {
			vertices.put(i, new Vertex(r.nextInt(200) + x + w/2 - 100, r.nextInt(200) + y + h/2 - 100));
		}
	}

	public void addEdge(String name, short u, short v, double weight) {
		addEdge(new Edge(name, u, v, weight));
	}

	public void readFromFile(File file) throws FileNotFoundException, NumberFormatException {
		var sc = new Scanner(file);
		ArrayList<Edge> edge_list = new ArrayList<>();
		while(sc.hasNextLine()) {
			String[] tokens = sc.nextLine().split(" ");
			short u = Short.parseShort(tokens[1]);
			short v = Short.parseShort(tokens[2]);
			double weight = Double.parseDouble(tokens[3]);
			edge_list.add(new Edge(tokens[0], u, v, weight));
			vertices.putIfAbsent(u, new Vertex(500, 500));
			vertices.putIfAbsent(v, new Vertex(500, 500));
		}
		for(Edge e : edge_list)
			addEdge(e);
		edge_list.clear();
	}
}

class Edge {
	public String name;
	public short u;
	public short v;
	public double weight;

	public Edge(String name, short u, short v, double weight) throws IllegalArgumentException {
		if(u < 1 || v < 1)
			throw new IllegalArgumentException("Numery wierzchołków muszą być większe od 0");
		this.u = u;
		this.v = v;
		this.weight = weight;
		this.name = name;
		if(u > v) {
			u ^= v;
			v ^= u;
			u ^= v;
		}
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
		return (u << 16) + v;
	}
}

