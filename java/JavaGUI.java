//import java.io.File;
import javax.swing.*;
import javax.swing.filechooser.FileSystemView;
import java.awt.*;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;

/*enum Algorithm {
	FRUCHTER,
	TUTTE
}*/

/*class Config {
	public File input_file;
	public File output_file;
	public Algorithm algo;
	public Config() {}
}*/

public class JavaGUI extends JFrame {
	private File input_file;
	private File output_file;
	private Graph graph;
	private JDialog dialog;
	private DrawingPanel drawingPanel;

	private void Btn(String text, JPanel buttons, ActionListener listener) {
		JButton btn = new JButton(text);
		btn.addActionListener(listener);
		buttons.add(btn);
	}

	public JavaGUI() {
		setTitle("Grafy");
		setSize(800, 600);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setLayout(new BorderLayout());
		graph = new Graph();
		dialog = new JDialog();
		dialog.setSize(200, 400);
		dialog.setLocationRelativeTo(this);

		JPanel buttons = new JPanel();
		buttons.setLayout(new BoxLayout(buttons, BoxLayout.PAGE_AXIS));

		add(buttons,  BorderLayout.WEST);
		JTextArea textArea = new JTextArea();
		textArea.setEditable(false);

		Btn("Wybierz plik wejściowy", buttons, _ -> {
			JFileChooser chooser = new JFileChooser(FileSystemView.getFileSystemView().getHomeDirectory());
			input_file = chooser.getSelectedFile();
			if(chooser.showOpenDialog(null) == JFileChooser.APPROVE_OPTION) {
				input_file = chooser.getSelectedFile();
				textArea.setText(input_file.getAbsolutePath());
				try {
					graph.readFromFile(input_file);
					graph.randomizeCoordinates();
					drawingPanel = new DrawingPanel(graph);
					drawingPanel.paintComponents(this.getGraphics());
					add(drawingPanel);
				} catch (FileNotFoundException e) {
					dialog.add(new JLabel("Nie można otwrzyć pliku " + input_file.getAbsolutePath()));
					dialog.setVisible(true);
				} catch (NumberFormatException e) {
					dialog.add(new JLabel("Niepoprawny format w pliku wejściowym!"));
					dialog.setVisible(true);
				}
			}
		});

		Btn("", buttons, _ -> IO.println("Saving..."));
		Btn("exit", buttons, _ -> System.exit(0));

		add(textArea, BorderLayout.CENTER);
		setVisible(true);
	}

	static void main(String[] args) {
		SwingUtilities.invokeLater(JavaGUI::new);
	}
}
