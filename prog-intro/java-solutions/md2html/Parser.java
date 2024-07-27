package md2html;

import java.io.*;
import java.nio.charset.StandardCharsets;
import java.util.ArrayList;

public class Parser {
	public Parser(String input, String output) {
		try (BufferedReader in = new BufferedReader(new FileReader(input, StandardCharsets.UTF_8))) {

			ArrayList<StringBuilder> blocks = new ArrayList<>();
			StringBuilder block = new StringBuilder();

			String str = in.readLine();

			while (str != null) {
				if (str.isEmpty()) {

					if (!block.isEmpty()) {
						block.append("\n");
						blocks.add(block);
						block = new StringBuilder();
					}

				} else {
					if (!block.isEmpty())
						block.append("\n");

					block.append(str);
				}
				str = in.readLine();

				if (str == null)
					blocks.add(block);
			}

			ParseMd parser = new ParseMd();
			String htmlText = String.valueOf(parser.parse(blocks));

			try (BufferedWriter out = new BufferedWriter(new FileWriter(output, StandardCharsets.UTF_8));) {
				out.write(htmlText);
			} catch (IOException e) {
				System.err.println("Error closing the writer: " + e.getMessage());
			}

		} catch (IOException e) {
			System.err.println("Error closing the reader: " + e.getMessage());
		}

	}
}
