#include "includes.h"
#include "evalmoves.h"

#if defined(WIN32) || defined(_WIN32) || defined(_WIN32) && !defined(__CYGWIN__)
bool windows = true;
#else
bool windows = false;
#endif

void ChooseMode() {
	std::string userinput;

	while (true) {
		std::cout << "Gamemode: (pvp)player vs player or (pve)player vs engine: ";
		std::cin >> userinput;

		if (userinput == "pve") {
			std::cout << "Set Mode to PVE\n";
			mode = PVE;
			break;
		}
		if (userinput == "pvp") {
			std::cout << "Set Mode to PVP\n";
			mode = PVP;
			break;
		}
		std::cout << "Unknown input: " << userinput << std::endl;
	}

	if (mode == PVE) {
		std::cout << "Player team: (b)lack, (w)hite: ";
		std::cin >> userinput;

		if (userinput == "b") {
			std::cout << "Player: black, Engine: white\n";
			engineteam = WHITE;
		}
		if (userinput == "w") {
			std::cout << "Player: white, Engine: black\n";
			engineteam = BLACK;
		}

		std::cout << "Depth: ";
		std::cin >> DEPTH;
		std::cout << "Set engine depth to: " << DEPTH << std::endl;
	}
}

const char* StringFromTeam(int team) {
	if (team == WHITE)
		return "w";
	return "b";
}

void StartGame() {
	Move move = Move{ vec2{0,0},vec2{0,0} };
	int movecount = 0;
	long long elapsedtime = 0;

	//playingBoard.FillBoard((char*)"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
	playingBoard.FillBoard((char*)"r1bq1rk1/1p3pp1/p1np4/2pPp2p/2P4P/2NP2P1/PP3PB1/R1Q2RK1");

	// game loop
	while (true) {
		std::cout << "FEN: " << playingBoard.GetFen(turn) << std::endl;
		std::cout << "Last input Move("; move.PrintMove(); std::cout << ") figfrom(" << move.figfrom << ")" << " figto(" << move.figto << ")" << std::endl;
		std::cout << "Engine took: " << elapsedtime << " seconds!\n\n";
		playingBoard.PrintBoard();

		// engine
		if (turn == engineteam) {
			std::cout << "(" << movecount << ") " << "Engine's(" << StringFromTeam(turn) << ")" << " turn...\n";

			std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
			move = Think(nullptr, engineteam, true);
			std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

			elapsedtime = std::chrono::duration_cast<std::chrono::seconds>(end - begin).count();

			playingBoard.ApplyMoveToBoard(move);
		}

		// player
		else {
			std::cout << "(" << movecount << ") " << "Player's(" << StringFromTeam(turn) << ")" << " turn(only positional moves) : ";

			std::string movinput;
			std::cin >> movinput;

			// special moves
			if (movinput == "resign") {
				std::cout << StringFromTeam(turn) << " resigns " << StringFromTeam(-turn) << " wins\n";
				break;
			}

			// check if move is correctly formatted
			if (movinput.size() != 4 && movinput != "O-O" && movinput != "O-O-O") {
				system(windows ? "cls" : "clear");
				std::cout << "Illegal Move! : " << movinput << std::endl;
				continue;
			}

			std::vector<Move> legalmoves[2];
			playingBoard.GenerateLegalMoves(legalmoves, nullptr, true);

			if (movinput.size() == 4) {
				int fromcol = 8 - ((int)movinput[1] - '0');
				int fromrow = (int)movinput[0] - 'a';
				int tocol = 8 - ((int)movinput[3] - '0');
				int torow = (int)movinput[2] - 'a';

				// make move
				move = Move{ vec2{fromcol, fromrow}, vec2{tocol, torow} };

				// Setup Move
				move.figfrom = playingBoard.board[move.from.column][move.from.row];
				move.figto = playingBoard.board[move.to.column][move.to.row];
			}

			// check if input move is legal
			bool movelegal = false;
			for (auto& mov : legalmoves[turn == BLACK ? BLACK + 1 : WHITE]) {
				if (mov == move) {
					movelegal = true;
					break;
				}
				if (mov.castle) {
					if ((mov.castletype == SHORT && movinput == "O-O") || (mov.castletype == LONG && movinput == "O-O-O")) {
						move = mov;
						movelegal = true;
						break;
					}
				}
			}
			if (!movelegal) {
				system(windows ? "cls" : "clear");
				std::cout << "Illegal Move! : " << movinput << std::endl;
				continue;
			}

			playingBoard.ApplyMoveToBoard(move);
		}

		turn = -turn;
		movecount++;
		system(windows ? "cls" : "clear");
	}
}

int main(int argc, char* argv[]) {
#ifdef _DEBUG
	const char* pBoardInfo = "r1bq1rk1/1p3pp1/p1np4/2pPp2p/2P4P/2NP2P1/PP3PB1/R1Q2RK1";
	DEPTH = 4;
	int currentteam = WHITE;
	Think((char*)pBoardInfo, currentteam, false);
#else
	if (argv[1][0] == '-' && argv[1][1] == 'g') {
		ChooseMode();
		StartGame();
	}
	else {
		char* pBoardInfo = argv[1];
		int currentteam = argv[2][0] == 'b' ? BLACK : WHITE;
		DEPTH = (int)(argv[3][0] - '0');
		Think(pBoardInfo, currentteam, false);
	}
#endif
	return 0;
}