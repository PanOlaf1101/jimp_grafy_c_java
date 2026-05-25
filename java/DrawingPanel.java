import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.geom.Ellipse2D;
import javax.swing.*;

public class DrawingPanel extends JPanel {
	private Graph graph;

	private Color edgeColor = Color.BLACK;
	private int edgeThickness = 2;
	private Settings.LabelMode labelMode = Settings.LabelMode.SHOW;

	private Short hoveredVertex = null;//gggg


	public void setGraph(Graph graph) {
		this.graph = graph;
	}

public DrawingPanel() {

		addMouseMotionListener(new java.awt.event.MouseMotionAdapter() {

			@Override
			public void mouseMoved(java.awt.event.MouseEvent e) {

				if(graph == null) return;

				final Short[] newHover = new Short[1];

				graph.vertices.forEach((k, v) -> {

					double dx = e.getX() - v.x();
					double dy = e.getY() - v.y();

					double dist2 = dx * dx + dy * dy;

					if(dist2 <= 144) {
						newHover[0] = k;
					}
				});

				hoveredVertex = newHover[0];
				repaint();
			}
		});
	}

	@Override
	public void paintComponent(Graphics g) {
		Graphics2D g2 = (Graphics2D) g;
		super.paintComponent(g);

		g2.setColor(edgeColor);
		g2.setStroke(new BasicStroke(edgeThickness));

		super.paintComponents(g);
		IO.println("Number of edges: " + graph.edges.size());
		IO.println("Number of vertices: " + graph.vertices.size());
		Graphics2D g2d = g2;
		g2d.setStroke(new BasicStroke(edgeThickness));
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
			g2d.setStroke(new BasicStroke(edgeThickness, BasicStroke.CAP_ROUND, BasicStroke.JOIN_ROUND));
			g2d.draw(circle);
			g2d.setColor(Color.BLACK);
			if (labelMode == Settings.LabelMode.SHOW) {

				g2d.drawString(k.toString(), v.x()-5, v.y()-8);

			} else if (labelMode == Settings.LabelMode.HOVER) {

				if (hoveredVertex != null && hoveredVertex.equals(k)) {

					g2d.drawString(k.toString(), v.x()-5, v.y()-8);
				}
			}
		});
	}


	public void setEdgeColor(Color color) {
		this.edgeColor = color;
	}

	public void setEdgeThickness(int thickness) {
		this.edgeThickness = thickness;
	}

	public void setLabelMode(Settings.LabelMode mode) {
		this.labelMode = mode;
	}
}
