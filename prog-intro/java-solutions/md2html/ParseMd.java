package md2html;

import java.util.ArrayList;

public class ParseMd {
    private int closerHeaderLevel = 0;

    public StringBuilder parse(ArrayList<StringBuilder> blocks) {
        ArrayList<StringBuilder> convertedBlocks = new ArrayList<>();
        for (StringBuilder block : blocks)
            convertedBlocks.add(parseThisBlock(block));

        StringBuilder htmlPage = new StringBuilder();
        for (StringBuilder block : convertedBlocks)
            htmlPage.append(block);

        return htmlPage;
    }

    public StringBuilder parseThisBlock(StringBuilder block) {
        StringBuilder convertedBlock = new StringBuilder();

        if (thatIsHeader(block))
            convertedBlock.append(parseHeader(block)).append("\n");
        else
            convertedBlock.append(parseParagraph(block)).append("\n");

        return convertedBlock;
    }

    private boolean thatIsHeader(StringBuilder block) {
        if (block.charAt(0) != '#')
            return false;

        int hashTagCount = 1;
        while (hashTagCount < block.length()) {
            if (Character.isWhitespace(block.charAt(hashTagCount))) {
                closerHeaderLevel = hashTagCount;
                return true;
            }
            else if (block.charAt(hashTagCount) == '#')
                hashTagCount++;
            else
                return false;
        }

        return false;
    }

    private StringBuilder parseParagraph(StringBuilder block) {
        StringBuilder convertedParagraph = new StringBuilder();
        String text = parseText(block.toString());

        if (text.length() > 2 && text.charAt(text.length() - 1) == '\n')
            text = text.substring(0, text.length() - 1);

        convertedParagraph.append("<p>").append(text).append("</p>");

        return convertedParagraph;
    }

    private StringBuilder parseHeader(StringBuilder block) {
        String text = parseText(block.substring(closerHeaderLevel + 1));
        StringBuilder convertedHeader = new StringBuilder();

        if (text.length() > 2 && text.charAt(text.length() - 1) == '\n')
            text = text.substring(0, text.length() - 1);

        convertedHeader.append("<h").append(closerHeaderLevel).append(">").append(text).append("</h").append(closerHeaderLevel).append(">");
        return convertedHeader;
    }

    private String parseText(String MdText) {
        MdTextParser mdTextParser = new MdTextParser(MdText);
        return mdTextParser.convertToHtml().toString();
    }

}



