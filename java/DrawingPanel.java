import javax.swing.*;
import java.awt.*;

public class DrawingPanel extends JPanel {
	Graph graph;

	public DrawingPanel(Graph graph) {
		this.graph = graph;
	}

	@Override
	public void paintComponents(Graphics g) {
		super.paintComponents(g);
		Graphics2D g2d = (Graphics2D) g;
		IO.println("Number of edges: " + graph.edges.size());
		IO.println("Number of vertices: " + graph.vertices.size());
		for(Edge i : graph.edges) {
			try {
				g2d.drawLine(graph.vertices.get(i.u).x(), graph.vertices.get(i.u).y(), graph.vertices.get(i.v).x(), graph.vertices.get(i.v).y());
			} catch(NullPointerException e) {
				IO.println(e.getMessage());
			} finally {
				IO.println(graph.vertices.get(i.u).x() + " " + graph.vertices.get(i.u).y() + "\t" + graph.vertices.get(i.v).x() + " " + graph.vertices.get(i.v).y());
			}
		}
	}
}