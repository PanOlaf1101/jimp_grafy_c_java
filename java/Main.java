import java.io.File;

enum Algorithm {
	FRUCHTER,
	TUTTE
}

class Config {
	public File input_file;
	public File output_file;
	public Algorithm algo;
	public Config() {}
}

public class Main {
	private static Config read_config(String[] args) {
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
	}

	public static void main(String[] args) {
		Config conf = read_config(args);
	}
}
