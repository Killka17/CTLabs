import java.io.*;
import java.nio.charset.StandardCharsets;
import java.util.Comparator;
import java.util.LinkedHashMap;
import java.util.Map;
import java.util.stream.Collectors;

public class WordStatCount {
    public static boolean inWhiteList(int symbol) {
        if (Character.getType(symbol) == Character.DASH_PUNCTUATION || Character.isLetter(symbol) || (char) symbol == '\'') {
            return true;
        }
        return false;
    }


    public static void main(String[] args) {

        LinkedHashMap<String, Integer> counter = new LinkedHashMap<>();

        try (BufferedReader in = new BufferedReader(new InputStreamReader(
                new FileInputStream(args[0]),
                StandardCharsets.UTF_8
        ))) {
            char[] buffer = new char[128];
            int pointer = 0;
            int ch = in.read();
            boolean start = false;

            while (ch != -1) {

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
                        counter.put(word, 1);

                    } else {
                        counter.put(word, counter.get(word) + 1);
                    }

                    pointer = 0;

                } else if (start && inWhiteList(ch)) {
                    buffer[pointer] = (char) ch;
                    pointer++;
                }
                ch = in.read();
            }
            } catch (IOException e){
                System.out.println("Input error: " + e.getMessage());
                throw new RuntimeException(e);
            }


        try (BufferedWriter out = new BufferedWriter(new OutputStreamWriter(
                new FileOutputStream(args[1]),
                StandardCharsets.UTF_8
        ))) {
            Map<String, Integer> sortedMap = counter.entrySet().stream()
                    .sorted(Comparator.comparingInt(e -> e.getValue()))
                    .collect(Collectors.toMap(
                            Map.Entry::getKey,
                            Map.Entry::getValue,
                            (a, b) -> { throw new AssertionError(); },
                            LinkedHashMap::new
                    ));

            for(Map.Entry<String, Integer> entry: sortedMap.entrySet()) {
                out.write(entry.getKey() + " " + entry.getValue() + System.lineSeparator());
            }
        } catch (IOException e) {
            System.out.println("Output error: " + e.getMessage());
            throw new RuntimeException(e);
        }
    }
}


