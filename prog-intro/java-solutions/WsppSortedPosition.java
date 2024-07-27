import java.io.*;
import java.nio.charset.StandardCharsets;
import java.util.*;

public class WsppSortedPosition {
    public static boolean inWhiteList(int symbol) {
        if (Character.getType(symbol) == Character.DASH_PUNCTUATION || Character.isLetter(symbol) || (char) symbol == '\'') {
            return true;
        }
        return false;
    }


    public static void main(String[] args) {

        Map<String, ArrayList<Integer>> counter = new LinkedHashMap<>();
        ArrayList<Integer> lineCount = new ArrayList<>();
        lineCount.add(1);


        try (
                MyScanner scanner = new MyScanner(args[0]);
        ) {
            char[] buffer = new char[128];
            int pointer = 0;
            int ch = scanner.getNextChar();
            boolean start = false;

            int lineNumber = 1;
            int wordNumber = 0;


            while (ch != -1) {
                StringBuilder lineSeparator = new StringBuilder();

                if (!start && inWhiteList(ch)) {
                    start = true;
                    buffer[pointer] = (char) ch;
                    pointer++;
                } else if (start && !inWhiteList(ch)) {

                    start = false;
                    char[] wordChars = new char[pointer];
                    System.arraycopy(buffer, 0, wordChars, 0, pointer);
                    String word = new String(wordChars).toLowerCase();

                    if (!counter.containsKey(word)) {
                        ArrayList<Integer> Start = new ArrayList<>();
                        Start.add(0, 1);

                        Start.add(lineNumber);
                        Start.add(wordNumber);
                        wordNumber++;
                        counter.put(word, Start);

                    } else {
                        ArrayList<Integer> temp = counter.get(word);
                        temp.set(0, temp.get(0) + 1);
                        temp.add(lineNumber);
                        temp.add(wordNumber);
                        wordNumber++;
                        counter.replace(word, temp);

                    }

                    pointer = 0;

                } else if (start && inWhiteList(ch)) {
                    buffer[pointer] = (char) ch;
                    pointer++;
                }

                if ((char) ch == System.lineSeparator().charAt(0)) {
                    lineSeparator.append((char) ch);

                    while (!lineSeparator.toString().equals(System.lineSeparator()))
                        lineSeparator.append((char) scanner.getNextChar());

                    lineCount.add(wordNumber);
                    lineNumber++;
                    wordNumber = 0;
                }

                ch = scanner.getNextChar();
            }

        } catch (IOException e){
            System.out.println("Input error: " + e.getMessage());
            throw new RuntimeException(e);
        }



        try (BufferedWriter out = new BufferedWriter(new OutputStreamWriter(
                new FileOutputStream(args[1]),
                StandardCharsets.UTF_8
        ))) {
            ArrayList<String> keys = new ArrayList<>(counter.keySet());

            Collections.sort(keys);

            LinkedHashMap<String, ArrayList<Integer>> sortedCounter = new LinkedHashMap<>();
            for (String key : keys) {
                sortedCounter.put(key, counter.get(key));
            }

            for(Map.Entry<String, ArrayList<Integer>> entry: sortedCounter.entrySet()) {
                out.write(entry.getKey() + " ");
                int i;

                out.write(entry.getValue().get(0) + " ");

                for (i = 1; i < entry.getValue().size() - 1; i += 2){
                    int lineNumber = entry.getValue().get(i);
                    int linePos = lineCount.get(entry.getValue().get(i)) - entry.getValue().get(i + 1);
                    out.write(lineNumber + ":" +  linePos);

                    if (i+2 < entry.getValue().size()-1) {
                        out.write(" ");
                    }
                }
                out.write(System.lineSeparator());

            }
        } catch (IOException e) {
            System.out.println("Output error: " + e.getMessage());
            throw new RuntimeException(e);
        }
    }
}