import java.lang.*;
public class SumDoubleSpace {

    public static void main(String[] args){
        double sum = 0.0;
        int start = -1;
        int len_arr = args.length;
        for (int i = 0; i < len_arr; i++){
            start = - 1;
            for (int k = 0; k < args[i].length(); k++){
                if (Character.getType(args[i].charAt(k)) != Character.SPACE_SEPARATOR){
                    if(start == -1){
                        start = k;
                    }
                }
                else{
                    if (start != -1){
                        sum = sum + Double.parseDouble(args[i].substring(start, k));
                        start = -1;
                    }
                }
                if (k == args[i].length() - 1 && start != -1){
                    sum = sum + Double.parseDouble(args[i].substring(start, k + 1));
                }
            }
        }
        System.out.println(sum);
    }

}
