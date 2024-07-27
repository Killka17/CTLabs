package game;


import java.util.Map;
import java.util.Stack;

public class Tournament {
    private static final Map<Integer, Result> RES = Map.of(
            1, Result.WIN,
            2, Result.LOSE,
            0, Result.DRAW
    );

    Stack<AbstractPlayer> results = new Stack<>();
    int mainCounter;
    Stack<AbstractPlayer> newTournament;

    public Tournament(Stack<AbstractPlayer> newTournament, int mainCounter) {

        this.mainCounter = mainCounter;
        this.newTournament = newTournament;
        final SetMNK setMnk = new SetMNK();
        makeTour();
    }


    public void makeTour() {

        while (newTournament.size() != 1) {
            while (!newTournament.isEmpty()){

                AbstractPlayer a = newTournament.pop();
                AbstractPlayer b = newTournament.pop();
                final Game game = new Game(false, a, b);
                int result;
                do {
                    result = game.play(new Mnk());
                } while (RES.get(result) == Result.DRAW);
                if (RES.get(result) == Result.WIN) {
                    results.add(a);
                    System.out.println(mainCounter);
                    mainCounter++;
                    System.out.println(b.getName() + " - " + mainCounter + " место");
                    mainCounter--;
                    if (newTournament.isEmpty() && results.size() == 1) {
                        System.out.println("1 место - " + a.getName());
                    }
                } else if (RES.get(result) == Result.LOSE) {
                    results.add(b);
                    mainCounter++;
                    System.out.println(a.getName() + " - " + mainCounter + " место");
                    mainCounter--;
                    if (newTournament.isEmpty() && results.size() == 1) {
                        System.out.println("1 место - " + b.getName());
                    }
                }

            }

            while (!results.isEmpty()) {
                newTournament.add(results.pop());
            }
            mainCounter = mainCounter / 2;
        }
    }
}
