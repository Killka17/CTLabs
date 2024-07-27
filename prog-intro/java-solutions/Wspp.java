import java.io.*;
import java.nio.charset.StandardCharsets;
import java.util.ArrayList;
import java.util.LinkedHashMap;
import java.util.Map;

public class Wspp {
    public static boolean inWhiteList(int symbol) {
        if (Character.getType(symbol) == Character.DASH_PUNCTUATION || Character.isLetter(symbol) || (char) symbol == '\'') {
            return true;
        }
        return false;
    }


    public static void main(String[] args) {

        LinkedHashMap<String, ArrayList<Integer>> counter = new LinkedHashMap<>();
        

        try (BufferedReader in = new BufferedReader(new InputStreamReader(
                new FileInputStream(args[0]),
                StandardCharsets.UTF_8
        ))) {
            char[] buffer = new char[128];
            int pointer = 0;
            int ch = in.read();
            boolean start = false;
            int ind = 0;


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
                    ind++;

                    if (!counter.containsKey(word)) {
                        ArrayList<Integer> Start = new ArrayList<>();
                        Start.add(1);
                        Start.add(ind);
                        counter.put(word, Start);

                    } else {
                        ArrayList<Integer> temp = counter.get(word);
                        temp.set(0, temp.get(0) + 1);
                        temp.add(ind);
                        counter.replace(word, temp);
//                        System.err.println();
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

            for(Map.Entry<String, ArrayList<Integer>> entry: counter.entrySet()) {
                out.write(entry.getKey() + " ");
                int i;
                for (i = 0; i <  (entry.getValue()).size(); i++){
                    out.write(entry.getValue().get(i).toString());
                    if (i < entry.getValue().size() - 1) {
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