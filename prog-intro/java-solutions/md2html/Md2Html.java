package md2html;

public class Md2Html {
	public static void main(String[] args) {
		if (args.length == 2) {
			new Parser(args[0], args[1]);
		} else {
			System.err.println("Wrong arguments");
			System.exit(0);
		}
	}
}
