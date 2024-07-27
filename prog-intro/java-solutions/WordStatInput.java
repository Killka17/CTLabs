import java.io.*;
import java.nio.charset.StandardCharsets;
import java.util.LinkedHashMap;
import java.util.Map;


public class WordStatInput {

    public static boolean inWhiteList(int symbol) {
        if (Character.getType(symbol) == Character.DASH_PUNCTUATION || Character.isLetter(symbol) || (char) symbol == '\'') {
            return true;
        }
        return false;
    }


    public static void main(String[] args) {

        LinkedHashMap<String, Integer> counter = new LinkedHashMap<>();

        try {

            BufferedReader in = new BufferedReader(new InputStreamReader(
                    new FileInputStream(args[0]),
                    StandardCharsets.UTF_8
            ));

            try {

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

            } finally {
                in.close();
            }
        } catch (IOException e) {
            throw new RuntimeException(e);
        }

        try (BufferedWriter out = new BufferedWriter(new OutputStreamWriter(
                    new FileOutputStream(args[1]),
                    StandardCharsets.UTF_8
            ))){


            for(Map.Entry<String, Integer> entry: counter.entrySet()) {
                out.write(entry.getKey() + " " + entry.getValue() + System.lineSeparator());
            }
        } catch (IOException e) {
            System.out.println("You lose");
        }
    }
}


//                if (start) {
//                    char[] wordChars = new char[pointer];
//                    System.arraycopy(buffer, 0, wordChars, 0, pointer);
//                    String word = new String(wordChars).toLowerCase();
//
//                    if (!counter.containsKey(word)) {
//                        counter.put(word, 1);
//
//                    } else {
//                        counter.put(word, counter.get(word) + 1);
//                    }
//                    System.out.println(word);
//                }

//if (pointer == buffer.length - 1) {
//        char[] newBuffer = new char[(pointer + 1) * 2];
//        System.arraycopy(buffer, 0, newBuffer, 0, pointer + 1);
//        buffer = newBuffer;
//        buffer[pointer] = (char) ch;
//        pointer++;
//        }