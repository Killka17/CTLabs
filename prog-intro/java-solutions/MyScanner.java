import java.io.*;
import java.nio.charset.StandardCharsets;
import java.util.NoSuchElementException;

public class MyScanner implements AutoCloseable, Closeable {

    private final StringBuilder line = new StringBuilder(0);
    private final Reader reader;
    private int nextIntIndex = 0;
    private int nextCharIndex = 0;

    private int sizeOfBuffer = 2048;
    private char[] buffer = new char[sizeOfBuffer];
    private int bufferPointer = 0;
    private int lastSizeBuffer = 0;

    public MyScanner() {
        this.reader = new InputStreamReader(System.in);
    }

    public MyScanner(String filePath) throws FileNotFoundException {
        this.reader = new InputStreamReader(new FileInputStream(filePath), StandardCharsets.UTF_8);
    }

    public int getLineLength() {
        return this.line.length();
    }

    public String getLine() {
        return this.line.toString();
    }

    public int getNextChar() throws IOException {
        extendBuffer();

        if (this.lastSizeBuffer < 0)
            return -1;

        char symbol = buffer[bufferPointer];
        bufferPointer++;
        return symbol;
    }

    public void extendBuffer() throws IOException {
        if (this.bufferPointer >= lastSizeBuffer) {
            this.lastSizeBuffer = reader.read(buffer, 0, sizeOfBuffer);

            bufferPointer = 0;
        }
    }

    public boolean nextLine() throws IOException {
        this.line.setLength(0);
        StringBuilder lineSeparator = new StringBuilder();

        while (true) {
            extendBuffer();

            if (this.lastSizeBuffer < 0)
                break;

            char nextChar = buffer[bufferPointer];

            ++bufferPointer;
            if (nextChar == System.lineSeparator().charAt(0)) {
                lineSeparator.append(nextChar);

                while (!lineSeparator.toString().equals(System.lineSeparator())) {
                    extendBuffer();

                    lineSeparator.append(buffer[bufferPointer]);
                    ++bufferPointer;
                }

                if (this.line.isEmpty())
                    this.line.append('\n');

                break;
            }

            line.append(nextChar);
        }

        return !this.line.isEmpty();
    }

    public boolean hasNextInt() {

        for (int index = this.nextIntIndex; index < this.line.length(); index++) {

            if (Character.isDigit(this.line.charAt(index)) ||
                    (this.line.charAt(index) == '-' && Character.isDigit(this.line.charAt(index + 1)))) {
                this.nextIntIndex = index + 1;

                return true;
            }
        }

        return false;
    }


    public boolean hasNextChar() {

        for (int index = this.nextCharIndex; index < this.line.length(); index++) {

            if (this.isInteger(this.line.charAt(index)) ||
                    (this.line.charAt(index) == '-' && this.isInteger(this.line.charAt(index + 1)))) {
                this.nextCharIndex = index + 1;

                return true;
            }
        }

        return false;
    }

    public int nextInt() {
        boolean isParseInt = false;
        int startIntIndex = 0;

        for (int index = this.nextIntIndex - 1; index < this.line.length(); ++index) {

            if (!isParseInt && (Character.isDigit(this.line.charAt(index)) ||
                    (this.line.charAt(index) == '-' && (Character.isDigit(this.line.charAt(index + 1)))))) {

                isParseInt = true;
                startIntIndex = index;

                if (index < this.line.length() - 1) {
                    continue;
                }

            }

            if (isParseInt) {

                if (index == this.line.length() - 1) {

                    this.nextIntIndex = 0;
                    String substring = this.line.substring(startIntIndex, index + 1);
                    this.line.setLength(0);

                    return Integer.parseInt(substring);

                } else if (!Character.isDigit(this.line.charAt(index))) {

                    this.nextIntIndex = index + 1;
                    String substring = this.line.substring(startIntIndex, index);

                    return Integer.parseInt(substring);
                }
            }
        }

        throw new NoSuchElementException("No more integers to read");
    }

    private boolean isInteger(Character symbol) {
        return symbol - 'a' < 10 && symbol - 'a' >= 0;
    }

    public String nextCharSubstr() {
        boolean isParseInt = false;
        int startIntIndex = 0;

        for (int index = this.nextCharIndex - 1; index < this.line.length(); ++index) {

            if (!isParseInt && (this.isInteger(this.line.charAt(index)) ||
                    (this.line.charAt(index) == '-' && (this.isInteger(this.line.charAt(index + 1)))))) {

                isParseInt = true;
                startIntIndex = index;

                if (index < this.line.length() - 1) {
                    continue;
                }

            }

            if (isParseInt) {

                if (index == this.line.length() - 1) {

                    this.nextCharIndex = 0;
                    String substring = this.line.substring(startIntIndex, index + 1);
                    this.line.setLength(0);

                    return substring;

                } else if (!this.isInteger(this.line.charAt(index))) {

                    this.nextCharIndex = index + 1;

                    return this.line.substring(startIntIndex, index);
                }
            }
        }

        throw new NoSuchElementException("No more integers to read");
    }

    public void close() {

        try {
            reader.close();
        } catch (IOException e) {
            System.err.println("Error closing the reader: " + e.getMessage());
        }

    }

}
