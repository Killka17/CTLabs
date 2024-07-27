import java.io.IOException;
import java.util.Objects;


class List{

    Integer[] vector = new Integer[2];
    int pointer = 1;

    public void pushBack(Integer newInt){

        if (this.pointer == -1) {
            this.pointer = this.vector.length - 1;

            Integer[] newVektor = new Integer[(this.pointer + 1) * 2];

            System.arraycopy(this.vector, 0, newVektor, this.pointer + 1, this.pointer + 1);
            newVektor[this.pointer] = newInt;

            this.vector = newVektor;
        } else {

            this.vector[this.pointer] = newInt;
        }

        this.pointer--;
    }
}


public class Reverse {

    public static void main(String[] args) throws IOException {
        MyScanner scanner = new MyScanner();

        List list = new List();
        String line;

        int k = 0;

        while (scanner.nextLine()) {

            while (scanner.hasNextInt())
                list.pushBack(scanner.nextInt());

            if (k == 0) {
                line = scanner.getLine();

                if (line.length() == 1 && line.charAt(0) == '\n')
                    list.pushBack(null);
            }

            list.pushBack(null);
            k++;
        }

        int i = list.pointer + 2;

        while (i <= list.vector.length - 1) {

            if (list.vector[i] == null) {
                System.out.print("\n");
                i++;

                continue;
            }

            System.out.print(list.vector[i]);
            System.out.print(" ");

            i++;
        }
    }
}
