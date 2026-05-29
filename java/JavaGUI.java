import java.awt.*;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.io.File;
import java.io.FileNotFoundException;
import javax.swing.*;
import javax.swing.filechooser.FileSystemView;

public class JavaGUI extends JFrame {
	private File input_file;
	private File output_file;
	private Graph graph;
	private DrawingPanel drawingPanel;

	private void Btn(String text, JPanel buttons, ActionListener listener) {
		JButton btn = new JButton(text);
		btn.addActionListener(listener);
		buttons.add(btn);
	}

	private void refreshEventListeners() {
		graph.vertices.forEach((k, v) -> {
			var l = new MouseAdapter() {
				private boolean dragged = false;
				private int x = v.x(), y = v.y();
				@Override
				public void mousePressed(MouseEvent e) {
					if(Math.abs(x - e.getX()) <= 5 && Math.abs(y - e.getY()) <= 5)
						dragged = true;
				}
				@Override
				public void mouseReleased(MouseEvent e) {
					if(dragged) {
						dragged = false;
						graph.vertices.replace(k, new Vertex(e.getX(), e.getY()));
						x = e.getX();
						y = e.getY();
						drawingPanel.repaint();
					}
				}
			};
			drawingPanel.removeMouseListener(l);
			drawingPanel.addMouseListener(l);
		});
	}

	private void showError(String text) {
		var dialog = new JDialog();
		dialog.setSize(800, 100);
		dialog.setLocationRelativeTo(this);
		dialog.setTitle("Błąd");
		dialog.add(new JLabel(text));
		dialog.setVisible(true);
		dialog.setResizable(false);
	}

	public JavaGUI() {
		setTitle("Grafy");
		setSize(800, 600);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setLayout(new BorderLayout());
		setResizable(false);
		setVisible(true);

		JPanel buttons = new JPanel();
		buttons.setLayout(new BoxLayout(buttons, BoxLayout.PAGE_AXIS));
		add(buttons,  BorderLayout.WEST);

		drawingPanel = new DrawingPanel();
		drawingPanel.setBackground(new Color(0xDF, 0xDF, 0xDF));
		drawingPanel.setVisible(true);
		add(drawingPanel, BorderLayout.CENTER);

		Btn("Wybierz plik wejściowy", buttons, _ -> {
			JFileChooser chooser = new JFileChooser(FileSystemView.getFileSystemView().getDefaultDirectory());
			input_file = chooser.getSelectedFile();
			if(chooser.showOpenDialog(null) == JFileChooser.APPROVE_OPTION) {
				try {
					input_file = chooser.getSelectedFile();
					graph = new Graph();
					graph.readFromFile(input_file);
					graph.randomizeCoordinates(drawingPanel.getX(), drawingPanel.getY(),  drawingPanel.getWidth(), drawingPanel.getHeight());
					drawingPanel.setGraph(graph);
					drawingPanel.paintComponents(this.getGraphics());
					refreshEventListeners();
				} catch (FileNotFoundException e) {
					showError("Nie można otwrzyć pliku " + input_file.getAbsolutePath());
				} catch (NumberFormatException e) {
					showError("Niepoprawny format w pliku wejściowym!");
				}
			}
		});

		Btn("Algorytm Tutte", buttons, _ -> {
			if(graph != null)
				Algorithms.tutte(graph, drawingPanel);
			refreshEventListeners();
		});

		Btn("Algorytm Fruchterman", buttons, _ -> {
			if(graph != null)
				Algorithms.fruchterman(graph, drawingPanel);
			refreshEventListeners();
		});

		Btn("Ustawienia", buttons, _ -> {
			Settings settings = new Settings(drawingPanel);
			settings.setVisible(true);
		});

		Btn("Exit", buttons, _ -> System.exit(0));
	}

	static void main(String[] args) {
		SwingUtilities.invokeLater(JavaGUI::new);
	}
}
