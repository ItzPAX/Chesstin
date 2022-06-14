#pragma once
#include "Board.h"
#include "includes.h"
#include <cctype>

#define QUEEN 900
#define PAWN 100
#define BISHOP 330
#define KNIGHT 320
#define ROOK 500
#define KING 20000

#pragma region PieceSquareTables
// pawn
int wpawn[8][8] = {
	{ 0, 0, 0, 0, 0, 0, 0, 0},
	{ 50, 50, 50, 50, 50, 50, 50, 50},
	{ 10, 10, 20, 30, 30, 20, 10, 10},
	{ 5, 5, 10, 25, 25, 10, 5, 5},
	{ 0, 0, 0, 20, 20, 0, 0, 0},
	{ 5, -5, -10, 0, 0, -10, -5, 5},
	{ 5, 10, 10, -20, -20, 10, 10, 5},
	{ 0, 0, 0, 0, 0, 0, 0, 0}
};
int bpawn[8][8] = {
	{ 0, 0, 0, 0, 0, 0, 0, 0},
	{ 5, 10, 10, -20, -20, 10, 10, 5},
	{ 5, -5, -10, 0, 0, -10, -5, 5},
	{ 0, 0, 0, 20, 20, 0, 0, 0},
	{ 5, 5, 10, 25, 25, 10, 5, 5},
	{ 10, 10, 20, 30, 30, 20, 10, 10},
	{ 50, 50, 50, 50, 50, 50, 50, 50},
	{ 0, 0, 0, 0, 0, 0, 0, 0}
};

// knight
int wknight[8][8] {
	{-50, -40, -30, -30, -30, -30, -40, -50 },
	{-40, -20, 0, 0, 0, 0, -20, -40 },
	{-30, 0, 10, 15, 15, 10, 0, -30 },
	{-30, 5, 15, 20, 20, 15, 5, -30 },
	{ -30, 0, 15, 20, 20, 15, 0, -30 },
	{ -30, 5, 10, 15, 15, 10, 5, -30 },
	{-40, -20, 0, 5, 5, 0, -20, -40 },
	{ -50, -40, -30, -30, -30, -30, -40, -50 }
};
int bknight[8][8]{
	{-50, -40, -30, -30, -30, -30, -40, -50 },
	{-40, -20, 0, 5, 5, 0, -20, -40 },
	{ -30, 5, 10, 15, 15, 10, 5, -30 },
	{ -30, 0, 15, 20, 20, 15, 0, -30 },
	{-30, 5, 15, 20, 20, 15, 5, -30 },
	{-30, 0, 10, 15, 15, 10, 0, -30 },
	{-40, -20, 0, 0, 0, 0, -20, -40 },
	{-50, -40, -30, -30, -30, -30, -40, -50 }
};

// bishop
int wbishop[8][8] = {
	{ -20, -10, -10, -10, -10, -10, -10, -20},
	{ -10, 0, 0, 0, 0, 0, 0, -10},
	{ -10, 0, 5, 10, 10, 5, 0, -10},
	{ -10, 5, 5, 10, 10, 5, 5, -10},
	{ -10, 0, 10, 10, 10, 10, 0, -10},
	{ -10, 10, 10, 10, 10, 10, 10, -10},
	{ -10, 5, 0, 0, 0, 0, 5, -10},
	{ -20, -10, -10, -10, -10, -10, -10, -20}
};
int bbishop[8][8] = {
	{ -20, -10, -10, -10, -10, -10, -10, -20},
	{ -10, 5, 0, 0, 0, 0, 5, -10},
	{ -10, 10, 10, 10, 10, 10, 10, -10},
	{ -10, 0, 10, 10, 10, 10, 0, -10},
	{ -10, 5, 5, 10, 10, 5, 5, -10},
	{ -10, 0, 5, 10, 10, 5, 0, -10},
	{ -10, 0, 0, 0, 0, 0, 0, -10},
	{ -20, -10, -10, -10, -10, -10, -10, -20}
};

//rook
int wrook[8][8] = {
	{ 0, 0, 0, 0, 0, 0, 0, 0},
	{ 5, 10, 10, 10, 10, 10, 10, 5},
	{ -5, 0, 0, 0, 0, 0, 0, -5},
	{ -5, 0, 0, 0, 0, 0, 0, -5},
	{ -5, 0, 0, 0, 0, 0, 0, -5},
	{ -5, 0, 0, 0, 0, 0, 0, -5},
	{ -5, 0, 0, 0, 0, 0, 0, -5},
	{ 0, 0, 0, 5, 5, 0, 0, 0}
};
int brook[8][8] = {
	{ 0, 0, 0, 5, 5, 0, 0, 0},
	{ -5, 0, 0, 0, 0, 0, 0, -5},
	{ -5, 0, 0, 0, 0, 0, 0, -5},
	{ -5, 0, 0, 0, 0, 0, 0, -5},
	{ -5, 0, 0, 0, 0, 0, 0, -5},
	{ -5, 0, 0, 0, 0, 0, 0, -5},
	{ 5, 10, 10, 10, 10, 10, 10, 5},
	{ 0, 0, 0, 0, 0, 0, 0, 0}
};

//queen
int wqueen[8][8] = {
	{ -20,-10,-10, -5, -5,-10,-10,-20},
	{ -10,  0,  0,  0,  0,  0,  0,-10},
	{ -10,  0,  5,  5,  5,  5,  0,-10},
	{  -5,  0,  5,  5,  5,  5,  0, -5},
	{   0,  0,  5,  5,  5,  5,  0, -5},
	{ -10,  5,  5,  5,  5,  5,  0,-10},
	{ -10,  0,  5,  0,  0,  0,  0,-10},
	{ -20,-10,-10, -5, -5,-10,-10,-20}
};
int bqueen[8][8] = {
	{ -20,-10,-10, -5, -5,-10,-10,-20},
	{ -10,  0,  5,  0,  0,  0,  0,-10},
	{ -10,  5,  5,  5,  5,  5,  0,-10},
	{   0,  0,  5,  5,  5,  5,  0, -5},
	{  -5,  0,  5,  5,  5,  5,  0, -5},
	{ -10,  0,  5,  5,  5,  5,  0,-10},
	{ -10,  0,  0,  0,  0,  0,  0,-10},
	{ -20,-10,-10, -5, -5,-10,-10,-20}
};

// king mid
int wkingmid[8][8] = {
	{-30,-40,-40,-50,-50,-40,-40,-30},
	{-30,-40,-40,-50,-50,-40,-40,-30},
	{-30,-40,-40,-50,-50,-40,-40,-30},
	{-30,-40,-40,-50,-50,-40,-40,-30},
	{-20,-30,-30,-40,-40,-30,-30,-20},
	{-10,-20,-20,-20,-20,-20,-20,-10},
	{ 20, 20,  0,  0,  0,  0, 20, 20},
	{ 20, 30, 10,  0,  0, 10, 30, 20}
};
int bkingmid[8][8] = {
	{ 20, 30, 10,  0,  0, 10, 30, 20},
	{ 20, 20,  0,  0,  0,  0, 20, 20},
	{-10,-20,-20,-20,-20,-20,-20,-10},
	{-20,-30,-30,-40,-40,-30,-30,-20},
	{-30,-40,-40,-50,-50,-40,-40,-30},
	{-30,-40,-40,-50,-50,-40,-40,-30},
	{-30,-40,-40,-50,-50,-40,-40,-30},
	{-30,-40,-40,-50,-50,-40,-40,-30}
};

// king end
int wkingend[8][8] = {
	{-50,-40,-30,-20,-20,-30,-40,-50},
	{-30,-20,-10,  0,  0,-10,-20,-30},
	{-30,-10, 20, 30, 30, 20,-10,-30},
	{-30,-10, 30, 40, 40, 30,-10,-30},
	{-30,-10, 30, 40, 40, 30,-10,-30},
	{-30,-10, 20, 30, 30, 20,-10,-30},
	{-30,-30,  0,  0,  0,  0,-30,-30},
	{-50,-30,-30,-30,-30,-30,-30,-50}
};
int bkingend[8][8] = {
	{-50,-30,-30,-30,-30,-30,-30,-50},
	{-30,-30,  0,  0,  0,  0,-30,-30},
	{-30,-10, 20, 30, 30, 20,-10,-30},
	{-30,-10, 30, 40, 40, 30,-10,-30},
	{-30,-10, 30, 40, 40, 30,-10,-30},
	{-30,-10, 20, 30, 30, 20,-10,-30},
	{-30,-20,-10,  0,  0,-10,-20,-30},
	{-50,-40,-30,-20,-20,-30,-40,-50}
};
#pragma endregion

// will return a factor considering how usefull the pawn is
float pawnstructeval(Board board, int col, int row, int upper) {
	float pawnfactor = 1.f;

	// check for multiple pawns on same row
	for (int i = 0; i < 8; i++) {
		char fig = board.board[col][i];
		if (fig == 'p' && !upper) {
			pawnfactor /= 2;
		}
		if (fig == 'P' && upper) {
			pawnfactor /= 2;
		}
	}
	return pawnfactor;
}

int kingshield(Board board, int col, int row, int upper) {
	int safety = 0;

	// the further the king the less safe he is
	if (upper) {
		safety -= col * 3;
	}
	else {
		safety -= (7 - col) * 3;
	}

	if (upper) {
		// pawns in front of king
		if (board.board[col + 1][row] == 'P')
			safety += 15;
		if (board.board[col + 1][row + 1] == 'P')
			safety += 15;
		if (board.board[col + 1][row - 1] == 'P')
			safety += 15;

		// enemy figures in front of king
		if (islower(board.board[col + 1][row]))
			safety -= 15;
		if (islower(board.board[col + 1][row + 1]))
			safety -= 15;
		if (islower(board.board[col + 1][row - 1]))
			safety -= 15;
	}
	else {
		// pawns in front of king
		if (board.board[col - 1][row] == 'p')
			safety += 15;
		if (board.board[col - 1][row + 1] == 'p')
			safety += 15;
		if (board.board[col - 1][row - 1] == 'p')
			safety += 15;

		// enemy figures in front of king
		if (isupper(board.board[col - 1][row]))
			safety -= 15;
		if (isupper(board.board[col - 1][row + 1]))
			safety -= 15;
		if (isupper(board.board[col - 1][row - 1]))
			safety -= 15;
	}

	return safety;
}

int GetPointsForFigure(Board board, char figure, int col, int row, bool endgame) {
	switch (figure) {
	case 'p':
		return (int)(PAWN * pawnstructeval(board, col, row, 0)) + bpawn[col][row];
		break;
	case 'P':
		return (int)(PAWN * pawnstructeval(board, col, row, 1)) + wpawn[col][row];
		break;
	case 'b':
		return BISHOP + bbishop[col][row];
		break;
	case 'B':
		return BISHOP + wbishop[col][row];
		break;
	case 'n':
		return KNIGHT + bknight[col][row];
		break;
	case 'N':
		return KNIGHT + wknight[col][row];
		break;
	case 'r':
		return ROOK + brook[col][row];
		break;
	case 'R':
		return ROOK + wrook[col][row];
		break;
	case 'q':
		return QUEEN + bqueen[col][row];
		break;
	case 'Q':
		return QUEEN + wqueen[col][row];
		break;
	case 'k':
		return KING + endgame ? bkingend[col][row] : bkingmid[col][row];
		break;
	case 'K':
		return KING + endgame ? wkingend[col][row] : wkingmid[col][row];
		break;
	}
	return 0;
}

bool DidPieceMove(int col, int row, char p) {
	if (p == 'p' && col == 6) return true;
	if (p == 'P' && col == 2) return true;

	if (islower(p) && p != 'p' && col == 7) return true;
	if (isupper(p) && p != 'P' && col == 1) return true;

	return false;
}

int EvaluateBoard(Board board, int turn) {
	int score = 0;

	for (int col = 0; col < 8; col++) {
		for (int row = 0; row < 8; row++) {
			char figure = board.board[col][row];
			int points = GetPointsForFigure(board, figure, col, row, board.IsInEndgame());

			if (isupper(figure))
				score += points;
			else
				score -= points;

			if (figure == 'k')
				score -= kingshield(board, col, row, 0);
			if (figure == 'K')
				score += kingshield(board, col, row, 1);
		}
	}

	return score * turn;
}

int Sort(MoveScored m1, MoveScored m2) {
	return m1.score > m2.score;
}

std::vector<MoveScored> EvaluateMoves(Board board, int turn) {
	// store result moves here
	std::vector<MoveScored> movesscored;

	int activeplayer = turn == BLACK ? BLACK + 1 : WHITE;

	std::vector<Move> legalmoves[2];
	board.GenerateLegalMoves(legalmoves, nullptr, true);

	for (const auto& move : legalmoves[activeplayer]) {
		MoveScored ScoredMove = MoveScored{};
		ScoredMove.move = move;

		if (move.castle)
			ScoredMove.score += 25;

		char moveto = board.board[move.to.column][move.to.row];
		char movefrom = board.board[move.from.column][move.from.row];

		bool endgame = board.IsInEndgame();

		int captureval = GetPointsForFigure(board, moveto, move.to.column, move.to.row, endgame);
		int pieceval = GetPointsForFigure(board, movefrom, move.from.column, move.from.row, endgame);

		ScoredMove.score += captureval;
		if (pieceval < captureval) {
			ScoredMove.score += captureval - pieceval;
		}

		if (!DidPieceMove(move.from.column, move.from.row, movefrom))
			ScoredMove.score += 10;

		movesscored.push_back(ScoredMove);
	}
	
	std::sort(movesscored.begin(), movesscored.end(), Sort);
	return movesscored;
}

int alphaBetaMax(Board board, int alpha, int beta, int depthleft, int turn);
int alphaBetaMin(Board board, int alpha, int beta, int depthleft, int turn);

int teamToEval = 0;

int alphaBetaMax(Board board, int alpha, int beta, int depthleft, int turn) {
	if (depthleft == 0) return EvaluateBoard(board, turn);

	std::vector<MoveScored> moves = EvaluateMoves(board, turn);
	board.SetupMoves(moves);

	for (auto& move : moves) {
		Move mov = move.move;
		board.ApplyMoveToBoard(mov);
		int score = alphaBetaMin(board, alpha, beta, depthleft - 1, -turn);
		board.UndoMove(mov);
		if (score >= beta)
			return beta;   // fail hard beta-cutoff
		if (score > alpha)
			alpha = score; // alpha acts like max in MiniMax
	}
	return alpha;
}

int alphaBetaMin(Board board, int alpha, int beta, int depthleft, int turn) {
	if (depthleft == 0) return EvaluateBoard(board, turn);

	std::vector<MoveScored> moves = EvaluateMoves(board, turn);
	board.SetupMoves(moves);

	for (auto& move : moves) {
		Move mov = move.move;
		board.ApplyMoveToBoard(mov);
		int score = alphaBetaMax(board, alpha, beta, depthleft - 1, -turn);
		board.UndoMove(mov);
		if (score <= alpha)
			return alpha; // fail hard alpha-cutoff
		if (score < beta)
			beta = score; // beta acts like min in MiniMax
	}
	return beta;
}

Move Think(char* pBoardInfo, int currentteam, bool game) {

	Move m;
	int score = INT_MIN;

	std::cout << currentteam << std::endl;

	teamToEval = currentteam;

	std::vector<MoveScored> moves;
	Board b;
	if (!game) {
		b.FillBoard(pBoardInfo);
		moves = EvaluateMoves(b, currentteam);
		b.SetupMoves(moves);
	}
	else {
		moves = EvaluateMoves(playingBoard, engineteam);
		playingBoard.SetupMoves(moves);
	}

	for (auto& move : moves) {
		Move mov = move.move;
		
		game ? playingBoard.ApplyMoveToBoard(mov): b.ApplyMoveToBoard(mov);
		int movscore = -alphaBetaMax(game ? playingBoard : b, INT_MIN, INT_MAX, DEPTH, -currentteam);
		game ? playingBoard.UndoMove(mov) : b.UndoMove(mov);
	
		mov.PrintMove();
		std::cout << " " << movscore << std::endl;
	
		if (movscore > score) {
			score = movscore;
			m = mov;
		}
	}

	//std::vector<MoveScored> moves = EvaluateMoves(b, currentteam);
	//m = moves.front().move;

	// format move
	m.PrintMove();
	return m;
}
