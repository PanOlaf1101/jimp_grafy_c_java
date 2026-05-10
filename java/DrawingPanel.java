import javax.swing.*;
import java.awt.*;

public class DrawingPanel extends JFrame {
	Graph graph;

	public DrawingPanel(Graph graph) {
		this.graph = graph;
	}

	@Override
	public void paintComponents(Graphics g) {
		super.paintComponents(g);
		Graphics2D g2d = (Graphics2D) g;
		for(Edge i : graph.edges) {
			g2d.drawLine(graph.vertices.get(i.u).x(), graph.vertices.get(i.u).y(), graph.vertices.get(i.v).x(), graph.vertices.get(i.v).y());
		}
	}
}