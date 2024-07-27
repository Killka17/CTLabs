public class Sum {

    public static void main(String[] args){
        int sum = 0;
        int len_arr = args.length;
        for (int i = 0; i < len_arr; i++){
            for (int k = 0; k < args[i].length(); k++){
                if (Character.isWhitespace(args[i].charAt(k)) && args[i].charAt(k) != ' '){
                    args[i] = args[i].substring(0,k) + " " + args[i].substring(k+1);

                }
            }
            String[] splited = args[i].split(" ");
            for (int j = 0; j < splited.length; j++){
                if (splited[j] != ""){
                    sum = sum + Integer.parseInt(splited[j]);
                }
            }
        }
        System.out.println(sum);
    }
}
