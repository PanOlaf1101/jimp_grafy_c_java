import java.util.HashMap;

public final class Algorithms {
	private static final int MAX_ITERATIONS = 100;

	private static boolean cww(Vertex a, Vertex b, Vertex c) {
		return (c.y() - a.y()) * (b.x() - a.x()) > (b.y() - a.y()) * (c.x() - a.x());
	}

	private static boolean intersect(Vertex a, Vertex b, Vertex c, Vertex d) {
		return cww(a, c, d) != cww(b, c, d) && cww(a, b, c) != cww(a, b, d);
	}

	public static boolean isTutteLayoutPlanar(final Graph graph) {
		var it = graph.edges.iterator();
		while(it.hasNext()) {
			Edge a = it.next();
			try {
				it.forEachRemaining(b -> {
					if (a.u != b.u && a.v != b.v && a.u != b.v && a.v != b.u && intersect(graph.vertices.get(a.u), graph.vertices.get(a.v), graph.vertices.get(b.u), graph.vertices.get(b.v)))
						throw new IllegalArgumentException();
				});
			} catch(IllegalArgumentException _) {
				return false;
			}
		}
		return true;
	}

	public static void tutte(Graph graph, final DrawingPanel panel) {
		if(graph.vertices.size() < 3)
			return;
		var v = new Vertex(panel.getWidth(), panel.getHeight());
		double cx = v.x() / 2.0;
		double cy = v.y() / 2.0;
		double radius = Math.min(panel.getWidth(), panel.getHeight()) / 3.0;
		var it = graph.vertices.keySet().iterator();
		for(int i = 0; i < 4 && it.hasNext(); ++i) {
			double angle = Math.PI * i / 2;
			graph.vertices.replace(it.next(), new Vertex((int)Math.round(cx + radius * Math.cos(angle)), (int)Math.round(cy + radius * Math.sin(angle))));
		}
		while(it.hasNext())
			graph.vertices.replace(it.next(), v);

		for(int iter = 0; iter < MAX_ITERATIONS; ++iter) {
			it = graph.vertices.keySet().stream().skip(4).iterator();
			while(it.hasNext()) {
				final short k = it.next();
				var i = graph.edges.stream()
					.filter(e -> e.u == k || e.v == k)
					.mapToInt(e -> e.u != k ? e.u : e.v)
					.distinct()
					.iterator();

				int sumx = 0, sumy = 0, c = 0;
				while(i.hasNext()) {
					var node = graph.vertices.get(i.next());
					sumx += node.x();
					sumy += node.y();
					c++;
				}
				if(c > 0)
					graph.vertices.replace(k, new Vertex((int)Math.round(sumx/(double)c), (int)Math.round(sumy/(double)sumy)));
			}
		}
	}

	private static double forceAttraction(double dist, double k) {
		return (dist*dist)/k;
	}

	public static void fruchterman(Graph graph, final DrawingPanel panel) {
		double temp = 400;
		final int area = panel.getWidth() * panel.getHeight();
		double k = Math.sqrt((double)area/graph.vertices.size());
		double gravity = 0.15;
		final double cx = panel.getWidth() / 2.0, cy = panel.getHeight() / 2.0;
		HashMap<Short, Vertex> forces = new HashMap<>();

		for(int iter = 0; iter < MAX_ITERATIONS; ++iter) {
			for(var i : graph.vertices.entrySet()) {
				double fx = (cx - i.getValue().x())*gravity;
				double fy = (cx - i.getValue().y())*gravity;
				for(var j : graph.vertices.entrySet()) {
					if(i.getKey().equals(j.getKey()))
						continue;
					double vx = i.getValue().x() - j.getValue().x();
					double vy = i.getValue().y() - j.getValue().y();
					double dist = Math.max(Math.sqrt(vx*vx + vy*vy), 0.01);
					double f = forceAttraction(k, dist);
					fx += vx/dist * f;
					fy += vy/dist * f;
				}
				forces.put(i.getKey(), new Vertex((int)Math.round(fx), (int)Math.round(fy)));
			}
		}

		for(var i : graph.edges) {
			Vertex u = graph.vertices.get(i.u);
			Vertex v = graph.vertices.get(i.v);
			double dist = Math.max(Math.sqrt(Math.pow(v.x() - u.x(), 2) + Math.pow(v.y() - u.y(), 2)), 0.01);
			double f = forceAttraction(dist, k);
			double fx = (v.x() - u.x()) / dist * f;
			double fy = (v.y() - u.y()) / dist * f;
			forces.replace(i.u, new Vertex((int)Math.round(u.x() - fx), (int)Math.round(u.y() - fy)));
			forces.replace(i.u, new Vertex((int)Math.round(v.x() + fx), (int)Math.round(v.y() + fy)));
		}

		for(var i : graph.vertices.entrySet()) {
			final Vertex fv = forces.get(i.getKey());
			double dist = Math.sqrt(fv.x()*fv.x() + fv.y()*fv.y());
			if(dist > 0) {
				double l = Math.min(dist, temp);
				graph.vertices.replace(i.getKey(), new Vertex(
					Math.clamp((int) Math.round(i.getValue().x() + fv.x() / dist * l), 10, panel.getWidth()-10),
					Math.clamp((int) Math.round(i.getValue().y() + fv.y() / dist * l), 10, panel.getHeight()-10)
				));
			}
			temp *= 0.95;
		}
	}
}