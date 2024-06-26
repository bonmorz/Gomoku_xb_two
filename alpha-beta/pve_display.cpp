#include "../src/gomoku.h"
#include "gomokuAI.h"
#include "../src/players.h"
#include "../src/display.h"
#include "../kmod/vga_gomoku.h"
#include <unistd.h>

void applyEndgame(Gomoku *game)
{
    game->board[7][7] = 1;
    game->board[8][8] = 2;
    game->board[8][9] = 1;
    game->board[7][8] = 2;
    game->board[9][7] = 1;
    game->board[8][7] = 2;
}

// void applyEndgame(Gomoku *game)
// {
//     game->board[2][2] = 1;
//     game->board[2][3] = 2;
//     game->board[3][2] = 1;
//     game->board[3][3] = 2;
// }

int main() {
    Gomoku game(1);
    Player p1(&game, 1);
    GomokuAI ai(&game, 1);  // Use strategy 1 for best performance.
	GMKDisplay display(VGA_DRIVER_FILENAME);
	if(!display.open_display())
		return -1;
    cout << "\n\nGame started. " << endl;

    //applyEndgame(&game);
    
    game.displayBoard();
	display.clear_board();
    while (1) {
        int x, y;
        std::cin >> x >> y;
        
        // User makes a move.
        if (p1.makeMove(make_pair(x - 1, y - 1))) {
            cout << "Invalid move!" << '\n' << endl;
            continue;
        }
        game.record.push_back(make_pair(x - 1, y - 1));
		display.update_piece_info(x-1,y-1,1,1);
		display.update_select(x-1,y-1);

        if (game.state == 1) {
            game.displayBoard();
            cout << "You win!" << endl;
            break;
        }

        // AI makes a move.
        pair<int, int> bestMove= ai.findBestMove();
        ai.makeMove(bestMove);
        game.record.push_back(bestMove);
		display.update_piece_info(bestMove.first,bestMove.second,2,1);

        cout << "You made a move at " << x << ", " << y << ", " << "AI made a move at " 
        << bestMove.first + 1 << ", " << bestMove.second + 1 << "\n" << endl;

        game.displayBoard();

        if (game.state == 1) {
            cout << "You lose!" << endl;
            break;
        }
    }

    return 0;
}
