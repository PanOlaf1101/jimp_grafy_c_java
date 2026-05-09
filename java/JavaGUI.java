//import java.io.File;
import javax.swing.*;
import java.awt.*;

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
	private void Btn(String text, JPanel panel, java.awt.event.ActionListener listener) {
		JButton btn = new JButton(text);
		btn.addActionListener(listener);
		panel.add(btn);
	}
	public JavaGUI() {
		setTitle("Grafy");
		setSize(800, 600);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setLayout(new BorderLayout());
		JPanel panel = new JPanel();
		panel.setLayout(new BoxLayout(panel, BoxLayout.PAGE_AXIS));
		Btn("load", panel, _ -> IO.println("Loading..."));
		Btn("save", panel, _ -> IO.println("Saving..."));
		Btn("exit", panel, _ -> System.exit(0));
		add(panel,  BorderLayout.WEST);
		setVisible(true);
	}

	/*private static Config read_config(String[] args) {
		Config conf = new Config();
		for(int i = 0; i < args.length; ++i) {
			switch(args[i]) {
				case "-i":
					conf.input_file = new File(args[++i]);
					break;
				case "-o":
					conf.output_file = new File(args[++i]);
					break;
				case "-a":
					++i;
					if(args[i] == "f")
						conf.algo = Algorithm.FRUCHTER;
					else if(args[i] == "t")
						conf.algo = Algorithm.TUTTE;
					else
						throw new IllegalArgumentException("Niepoprawny argument");
			}
		}
		if(conf.algo == null)
			throw new IllegalStateException("Nie podano algorytmu");
		return conf;
	}*/

	static void main(String[] args) {
		SwingUtilities.invokeLater(JavaGUI::new);
	}
}
