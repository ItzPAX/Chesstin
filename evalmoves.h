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
int wknight[8][8]{
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

	if (upper) {
		// pawns in front of king
		if (col < 7 && col > 0 && row < 7 && row > 0) {
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

		safety -= board.checksblack * 3;
	}
	else {
		if (col < 7 && col > 0 && row < 7 && row > 0) {
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

		safety -= board.checkswhite * 3;
	}

	return safety;
}


int SimplePieceVal(char fig) {
	switch (fig) {
	case 'p':
	case 'P':
		return PAWN;
	case 'n':
	case 'N':
		return KNIGHT;
	case 'b':
	case 'B':
		return BISHOP;
	case 'r':
	case 'R':
		return ROOK;
	case 'q':
	case 'Q':
		return QUEEN;
	case 'k':
	case 'K':
		return KING;
	}
	return 0;
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

	std::vector<Move> moves[2];
	board.GenerateMoves(moves, nullptr, true);

	for (const auto& move : moves[activeplayer]) {
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

int Quiesce(Board b, int turn, int alpha, int beta) {
	int stand_pat = EvaluateBoard(b, turn);
	if (stand_pat >= beta)
		return beta;

	if (alpha < stand_pat)
		alpha = stand_pat;

	int score;
	int player = turn == BLACK ? 0 : 1;
	std::vector<Move> captures[2];
	b.GenerateCaptures(captures, nullptr, true);

	for (auto& mov : captures[player]) {
		b.ApplyMoveToBoard(mov);
		score = -Quiesce(b, -turn, -beta, -alpha);
		b.UndoMove(mov);

		if (score >= beta)
			return beta;
		if (score > alpha)
			alpha = score;
	}
	return alpha;
}

int PVS(int alpha, int beta, int depthleft, int turn, Board b) {
	if (depthleft == 0) return Quiesce(b, turn, alpha, beta);

	int bestscore;

	std::vector<MoveScored> moves = EvaluateMoves(b, turn);

	b.ApplyMoveToBoard(moves.front().move);
	bestscore = -PVS(-beta, -alpha, depthleft - 1, -turn, b);
	b.UndoMove(moves.front().move);
	if (bestscore > alpha) {
		if (bestscore >= beta)
			return bestscore;
		alpha = bestscore;
	}

	int score;
	bool skip = true;
	for (auto& move : moves) {
		if (skip) {
			skip = false;
			continue;
		}

		Move mov = move.move;
		b.ApplyMoveToBoard(mov);
		score = -PVS(-alpha - 1, -alpha, depthleft - 1, -turn, b);
		if (score > alpha && score < beta) {
			score = -PVS(-beta, -alpha, depthleft - 1, -turn, b);
			if (score > alpha)
				alpha = score;
		}
		b.UndoMove(mov);
		if (score > bestscore) {
			if (score >= beta)
				return score;
			bestscore = score;
		}
	}
	return bestscore;
}

void GetMoveScore(bool game, std::vector<Move> moves, Board b, int turn, int id, int* pbest, Move* m) {
	for (auto& mov : moves) {
		game ? playingBoard.ApplyMoveToBoard(mov) : b.ApplyMoveToBoard(mov);
		int score = -PVS(INT_MIN, INT_MAX, DEPTH, -turn, game ? playingBoard : b);
		game ? playingBoard.UndoMove(mov) : b.UndoMove(mov);

		std::cout << "Thread " << id << ": ";
		mov.PrintMove();
		std::cout << " " << score << std::endl;

		if (score > *pbest) {
			*pbest = score;
			*m = mov;
		}
	}
}

Move Think(char* pBoardInfo, int currentteam, bool game) {
	Move m;
	int score = INT_MIN;

	std::cout << currentteam << std::endl;

	std::vector<MoveScored> moves;
	Board b;
	if (!game) {
		b.FillBoard(pBoardInfo);
		moves = EvaluateMoves(b, currentteam);
	}
	else {
		moves = EvaluateMoves(playingBoard, currentteam);
	}

	// split all moves into THREAD pieces
	int splitsize = std::ceilf(moves.size() / THREADS);

	// generate splices
	std::vector<Move> splices[THREADS + 1];
	for (int i = 0; i < THREADS; i++)
		splices[i].reserve(splitsize);

	int idx = 0;
	int splicesidx = 0;
	for (auto& move : moves) {
		if (idx == splitsize) {
			idx = 0;
			splicesidx++;
		}
		splices[splicesidx].push_back(move.move);
		idx++;
	}

	// init threads
	for (int i = 0; i < THREADS; i++)
		threads[i] = std::thread(GetMoveScore, game, splices[i], b, currentteam, i, &score, &m);

	// start threads
	for (int i = 0; i < THREADS; i++)
		threads[i].join();

	//std::vector<MoveScored> moves = EvaluateMoves(b, currentteam);
	//m = moves.front().move;

	// format move
	m.PrintMove();
	return m;
}