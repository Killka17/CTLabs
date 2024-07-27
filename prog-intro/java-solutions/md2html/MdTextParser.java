package md2html;

import base.Pair;
import java.util.*;

public class MdTextParser {
    StringBuilder mdText;
    private final HashMap<String, String> openCloseMarks = new HashMap<>();
    private final HashMap<Character, String> singleMarks = new HashMap<>();
    final Deque<Pair<String, Integer>> tagsDeque = new LinkedList<>();

    MdTextParser(String MdText){
        this.mdText = new StringBuilder(MdText);

        openCloseMarks.put("*", "em>");
        openCloseMarks.put("_", "em>");
        openCloseMarks.put("**", "strong>");
        openCloseMarks.put("__", "strong>");
        openCloseMarks.put("`", "code>");
        openCloseMarks.put("--", "s>");
        openCloseMarks.put("%", "var>");

        singleMarks.put('>', "&gt;");
        singleMarks.put('<', "&lt;");
        singleMarks.put('&', "&amp;");
    }

    private String OpenMark(String key) {
        return "<" + openCloseMarks.get(key);
    }

    private String CloseMark(String key) {
        return "</" + openCloseMarks.get(key);
    }

    public StringBuilder convertToHtml() {
        StringBuilder result = new StringBuilder();

        for (int index = 0; index < mdText.length(); ++index) {
            char symbol = mdText.charAt(index);

            if (symbol == '\\') {
                result.append(mdText.charAt(index + 1));
                index += 1;
                continue;
            }

            if (singleMarks.containsKey(symbol)) {
                result.append(singleMarks.get(symbol));
                continue;
            }

            int nextCharIndex = Math.min(mdText.length(), index + 2);
            String possibleLongKey = mdText.substring(index, nextCharIndex);

            String strKey = null;

            if (openCloseMarks.containsKey(possibleLongKey))
                strKey = possibleLongKey;
            else if (openCloseMarks.containsKey(String.valueOf(symbol)))
                strKey = String.valueOf(symbol);

            if (strKey != null) {

                if (strKey.length() == 2)
                    ++index;

                if (!tagsDeque.isEmpty()) {
                    Pair<String, Integer> topStackElement = tagsDeque.getLast();

                    if (Objects.equals(topStackElement.first, strKey)) {
                        result.append(CloseMark(strKey));
                        tagsDeque.removeLast();
                    }
                    else {
                        result.append(OpenMark(strKey));
                        tagsDeque.addLast(new Pair<>(strKey, index));
                    }

                } else {
                    result.append(OpenMark(strKey));
                    tagsDeque.addLast(new Pair<>(strKey, index));
                }

            } else
                result.append(symbol);

        }

        while (!tagsDeque.isEmpty()) {
            Pair<String, Integer> topStackElement = tagsDeque.getFirst();
            int test = OpenMark(topStackElement.first).length();

            result.replace(topStackElement.second, topStackElement.second + test, topStackElement.first);
            tagsDeque.removeFirst();
        }

        return result;
    }

}
