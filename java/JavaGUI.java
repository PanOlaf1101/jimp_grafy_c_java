//import java.io.File;
import javax.swing.*;
import javax.swing.filechooser.FileSystemView;
import java.awt.*;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.FileNotFoundException;

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
		graph = new Graph();

		JPanel buttons = new JPanel();
		buttons.setLayout(new BoxLayout(buttons, BoxLayout.PAGE_AXIS));
		add(buttons,  BorderLayout.WEST);

		JTextArea textArea = new JTextArea();
		textArea.setEditable(false);

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
					textArea.setText(input_file.getAbsolutePath());
					graph.readFromFile(input_file);
					graph.randomizeCoordinates(drawingPanel.getX(), drawingPanel.getY(),  drawingPanel.getWidth(), drawingPanel.getHeight());
					drawingPanel.setGraph(graph);
					drawingPanel.paintComponents(this.getGraphics());
				} catch (FileNotFoundException e) {
					showError("Nie można otwrzyć pliku " + input_file.getAbsolutePath());
				} catch (NumberFormatException e) {
					showError("Niepoprawny format w pliku wejściowym!");
				}
			}
		});


		Btn("exit", buttons, _ -> System.exit(0));
	}

	static void main(String[] args) {
		SwingUtilities.invokeLater(JavaGUI::new);
	}
}
