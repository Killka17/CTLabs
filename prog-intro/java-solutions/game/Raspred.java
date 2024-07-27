package game;

import java.util.Stack;

public class Raspred {

    Stack<AbstractPlayer> newTournament = new Stack<>();
    int res;

    public Raspred(int res) {

        this.res = res;
        int counter = 1;
        while (res > counter) {counter = counter * 2;
        }
        int mainCounter = counter / 2;

        int botsCounter = counter - res;

        for (int i = 0; i < res; i++) {
            AbstractPlayer player = new HumanPlayer();
            player.setName("Player" + i);
            newTournament.add(player);
        }

        for (int i = 0; i < botsCounter; i++) {
            AbstractPlayer botPlayer = new RandomPlayer();
            botPlayer.setName("botPlayer" + i);
            newTournament.add(botPlayer);
        }
        new Tournament(newTournament, mainCounter);

    }
}
