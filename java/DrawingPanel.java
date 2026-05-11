import javax.swing.*;
import java.awt.*;
import java.awt.geom.Ellipse2D;
import java.util.Random;

public class DrawingPanel extends JPanel {
	private Graph graph;

	public void setGraph(Graph graph) {
		this.graph = graph;
	}

	@Override
	public void paintComponents(Graphics g) {
		super.paintComponents(g);
		IO.println("Number of edges: " + graph.edges.size());
		IO.println("Number of vertices: " + graph.vertices.size());
		Graphics2D g2d = (Graphics2D) g;
		g2d.setStroke(new BasicStroke(2));
		var r = new Random();
		for(Edge i : graph.edges) {
			try {
				g2d.drawLine(graph.vertices.get(i.u).x(), graph.vertices.get(i.u).y(), graph.vertices.get(i.v).x(), graph.vertices.get(i.v).y());
			} catch(NullPointerException e) {
				System.err.println(e.getMessage());
			} finally {
				IO.println(graph.vertices.get(i.u).x() + " " + graph.vertices.get(i.u).y() + "\t" + graph.vertices.get(i.v).x() + " " + graph.vertices.get(i.v).y());
			}
		}
		graph.vertices.forEach((k, v) -> {
			var circle = new Ellipse2D.Double(v.x()-5, v.y()-5, 10, 10);
			g2d.setColor(Color.LIGHT_GRAY);
			g2d.fill(circle);
			g2d.setColor(Color.DARK_GRAY);
			g2d.setStroke(new BasicStroke(2, BasicStroke.CAP_ROUND, BasicStroke.JOIN_ROUND));
			g2d.draw(circle);
			g2d.setColor(Color.BLACK);
			g2d.drawString(k.toString(), v.x()-5, v.y()-8);
		});
	}
}