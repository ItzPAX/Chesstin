#pragma once
#include "includes.h"

#define LONG 1
#define SHORT 2

struct vec2 {
    int column, row;
    bool operator== (vec2 rhs) {
        return rhs.column == this->column && rhs.row == this->row;
    }
    void operator= (vec2 rhs) {
        column = rhs.column; row = rhs.row;
    }
};

struct Move {
    void PrintMove() {
        char finalmove[4];
        finalmove[0] = 8 - from.column;
        finalmove[1] = from.row + 'a';
        finalmove[2] = 8 - to.column;
        finalmove[3] = to.row + 'a';
        std::cout << finalmove[1] << (int)finalmove[0] << finalmove[3] << (int)finalmove[2];
    }

    vec2 from, to, from2, to2;
    bool pawnpromotion = false;
    bool castle = false;
    int castletype = 0;
    char figfrom, figfrom2;
    char figto;

    bool changedblacklong = false, changedblackshort = false, changedwhitelong = false, changedwhiteshort = false;

    bool operator== (Move rhs) {
        return rhs.from == this->from && rhs.to == this->to;
    }
    void operator=(Move rhs) {
        from = rhs.from; to = rhs.to; pawnpromotion = rhs.pawnpromotion; figfrom = rhs.figfrom; figto = rhs.figto; castle = rhs.castle;
        from2 = rhs.from2; to2 = rhs.to2; figfrom2 = rhs.figfrom2; changedblacklong = rhs.changedblacklong; changedblackshort = rhs.changedblackshort;
        changedwhitelong = rhs.changedwhitelong = changedblackshort = rhs.changedblackshort; castletype = rhs.castletype;
    }
}; 

struct MoveScored {
    Move move;
    int score;
};

class Board
{
public:
	char board[8][8];

    int checkswhite = 0, checksblack = 0;

    bool whitelongcastle = true, whiteshortcastle = true, blacklongcastle = true, blackshortcastle = true;
    bool bwlongcastle, bwshortcastle, bblongcastle, bbshortcastle;

    bool whitecastled = false, blackcastled = false;

    void SetupMoves(std::vector<MoveScored>& InitialMoves) {
        // just fill in last values for each move
        for (auto& pMove : InitialMoves) {
            pMove.move.figfrom = board[pMove.move.from.column][pMove.move.from.row];
            pMove.move.figto = board[pMove.move.to.column][pMove.move.to.row];
        }
    }
    void SetupMoves(std::vector<Move>& white, std::vector<Move>& black, std::vector<Move>& whitecheck, std::vector<Move>& blackcheck) {
        // just fill in last values for each move
        for (auto& pMove : white) {
            pMove.figfrom = board[pMove.from.column][pMove.from.row];
            pMove.figto = board[pMove.to.column][pMove.to.row];
        }
        for (auto& pMove : black) {
            pMove.figfrom = board[pMove.from.column][pMove.from.row];
            pMove.figto = board[pMove.to.column][pMove.to.row];
        }
        for (auto& pMove : whitecheck) {
            pMove.figfrom = board[pMove.from.column][pMove.from.row];
            pMove.figto = board[pMove.to.column][pMove.to.row];
        }
        for (auto& pMove : blackcheck) {
            pMove.figfrom = board[pMove.from.column][pMove.from.row];
            pMove.figto = board[pMove.to.column][pMove.to.row];
        }
    }

    void FillBoard(char* pBoardInfo) {
        int column = 0, row = 0;
        for (int i = 0; pBoardInfo[i] != 0; i++) {
            // we have empty rows
            if (pBoardInfo[i] >= '0' && pBoardInfo[i] <= '9') {
                int emptyspots = pBoardInfo[i] - '0';
                for (int j = 0; j < emptyspots; j++) {
                    board[column][row] = '.';
                    row++;
                }
            }
            else if (pBoardInfo[i] == '/') {
                column++;
                row = 0;
            }
            else {
                board[column][row] = pBoardInfo[i];
                row++;
            }
        }
    }

    std::string GetFen(int turn) {
        std::string fen;
        int emptyspace = 0;

        for (int col = 0; col < 8; col++) {
            for (int row = 0; row < 8; row++) {
                char figure = board[col][row];
                if (figure == '.')
                    emptyspace++;
                if (figure != '.') {
                    if (emptyspace != 0) {
                        fen.push_back(emptyspace + '0');
                        emptyspace = 0;
                    }
                    fen.push_back(figure);
                }
            }
            if (emptyspace > 0) {
                fen.push_back(emptyspace + '0');
                emptyspace = 0;
            }
            if (col != 7)
                fen.push_back('/');
        }

        if (turn == WHITE)
            fen.append(" w");
        else
            fen.append(" b");

        fen.push_back(' ');

        if (whitelongcastle)
            fen.push_back('Q');
        if (whiteshortcastle)
            fen.push_back('K');
        if (blacklongcastle)
            fen.push_back('q');
        if (blackshortcastle)
            fen.push_back('k');
        if (!blackshortcastle && !blacklongcastle && !whitelongcastle && !whiteshortcastle)
            fen.push_back('-');


        return fen;
    }

    bool IsInEndgame() {
        int queens = 0;
        int minorpieceswhite = 0;
        int minorpiecesblack = 0;

        for (int col = 0; col < 8; col++) {
            for (int row = 0; row < 8; row++) {
                char figure = board[row][col];
                if (figure == 'q' || figure == 'Q')
                    queens++;
                if (figure == 'B' || figure == 'N')
                    minorpieceswhite++;
                if (figure == 'b' || figure == 'n')
                    minorpiecesblack++;
            }
        }

        // no more queens, consider this an endgame
        if (queens == 0)
            return true;
        // queen(s) on board but only one minor piece left also endgame
        if (minorpieceswhite <= 1 && minorpiecesblack <= 1)
            return true;

        return false;
    }

    void PrintBoard() {
        for (int i = 0; i < 8; i++) {
            std::cout << 8 - i << " | ";
            for (int j = 0; j < 8; j++) {
                std::cout << " " << board[i][j] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << "   -------------------------" << std::endl;
        std::cout << "     a  b  c  d  e  f  g  h \n";
    }

    void GenAllMoves(std::vector<Move>& moveswhite, std::vector<Move>& movesblack, std::vector<Move>& checkswhite, std::vector<Move>& checksblack) {
        // iterate through board
        moveswhite.reserve(200); movesblack.reserve(200); checkswhite.reserve(50); checksblack.reserve(50);

        for (int col = 0; col < 8; col++) {
            for (int row = 0; row < 8; row++) {
                char figure = board[col][row];
                if (figure == '.')
                    continue;

                // pawn
                if (figure == 'p') {
                    // pawn can promote
                    if (col == 7) {
                        Move move = Move{ vec2{col, row}, vec2{col, row}, true };
                        movesblack.push_back(move);
                        continue;
                    }

                    // board is empty
                    if (board[col + 1][row] == '.') {
                        Move move = Move{ vec2{col, row}, vec2{col + 1, row} };
                        movesblack.push_back(move);
                    }

                    // pawn hasnt moved yet?
                    if (col == 1 && board[col + 2][row] == '.' && board[col + 1][row] == '.') {
                        Move move = Move{ vec2{col, row}, vec2{col + 2, row} };
                        movesblack.push_back(move);
                    }

                    // can we attack
                    char attackpos = board[col + 1][row - 1];
                    if (row >= 0 && isupper(attackpos)) {
                        Move move = Move{ vec2{col, row}, vec2{col + 1, row - 1} };

                        // we are giving a check special rules apply
                        if (attackpos == 'K')
                            checksblack.push_back(move);
                        else
                            movesblack.push_back(move);
                    }
                    attackpos = board[col + 1][row + 1];
                    if (row < 8 && isupper(attackpos)) {
                        Move move = Move{ vec2{col, row}, vec2{col + 1, row + 1} };

                        if (attackpos == 'K')
                            checksblack.push_back(move);
                        else
                            movesblack.push_back(move);
                    }
                }
                if (figure == 'P') {
                    // pawn can promote
                    if (col == 0) {
                        Move move = Move{ vec2{col, row}, vec2{col, row}, true };
                        moveswhite.push_back(move);
                        continue;
                    }

                    // board is empty
                    if (board[col - 1][row] == '.') {
                        Move move = Move{ vec2{col, row}, vec2{col - 1, row} };
                        moveswhite.push_back(move);
                    }

                    // pawn hasnt moved yet?
                    if (col == 6 && board[col - 2][row] == '.' && board[col - 1][row] == '.') {
                        Move move = Move{ vec2{col, row}, vec2{col - 2, row} };
                        moveswhite.push_back(move);
                    }

                    // can we attack
                    char attackpos = board[col - 1][row - 1];
                    if (row >= 0 && islower(attackpos)) {
                        Move move = Move{ vec2{col, row}, vec2{col - 1, row - 1} };

                        // we are giving a check special rules apply
                        if (attackpos == 'k')
                            checkswhite.push_back(move);
                        else
                            moveswhite.push_back(move);
                    }
                    attackpos = board[col - 1][row + 1];
                    if (row < 8 && islower(attackpos)) {
                        Move move = Move{ vec2{col, row}, vec2{col - 1, row + 1} };

                        if (attackpos == 'k')
                            checkswhite.push_back(move);
                        else
                            moveswhite.push_back(move);
                    }
                }
                // rook / queen
                if (figure == 'r' || figure == 'q') {
                    for (int i = col + 1; i < 8; i++) {
                        char target = board[i][row];
                        if (islower(target))
                            break;

                        if (isupper(target)) {
                            Move move{ vec2{col, row}, vec2{i, row} };
                            if (target == 'K')
                                checksblack.push_back(move);
                            else
                                movesblack.push_back(move);
                            break;
                        }

                        if (target == '.') {
                            Move move = Move{ vec2{col, row},vec2{i, row} };
                            movesblack.push_back(move);
                        }
                    }
                    // down
                    for (int i = col - 1; i >= 0; i--) {
                        char target = board[i][row];
                        if (islower(target))
                            break;

                        if (isupper(target)) {
                            Move move{ vec2{col, row}, vec2{i, row} };
                            if (target == 'K')
                                checksblack.push_back(move);
                            else
                                movesblack.push_back(move);
                            break;
                        }

                        if (target == '.') {
                            Move move = Move{ vec2{col, row},vec2{i, row} };
                            movesblack.push_back(move);
                        }
                    }
                    // right
                    for (int i = row + 1; i < 8; i++) {
                        char target = board[col][i];
                        if (islower(target))
                            break;

                        if (isupper(target)) {
                            Move move{ vec2{col, row}, vec2{col, i} };
                            if (target == 'K')
                                checksblack.push_back(move);
                            else
                                movesblack.push_back(move);
                            break;
                        }

                        if (target == '.') {
                            Move move = Move{ vec2{col, row},vec2{col, i} };
                            movesblack.push_back(move);
                        }
                    }
                    // left
                    for (int i = row - 1; i >= 0; i--) {
                        char target = board[col][i];
                        if (islower(target))
                            break;

                        if (isupper(target)) {
                            Move move{ vec2{col, row}, vec2{col, i} };
                            if (target == 'K')
                                checksblack.push_back(move);
                            else
                                movesblack.push_back(move);
                            break;
                        }

                        if (target == '.') {
                            Move move = Move{ vec2{col, row},vec2{col, i} };
                            movesblack.push_back(move);
                        }
                    }
                }

                if (figure == 'R' || figure == 'Q') {
                    // down
                    for (int i = col + 1; i < 8; i++) {
                        char target = board[i][row];
                        if (isupper(target))
                            break;

                        if (islower(target)) {
                            Move move{ vec2{col, row}, vec2{i, row} };
                            if (target == 'k')
                                checkswhite.push_back(move);
                            else
                                moveswhite.push_back(move);
                            break;
                        }

                        if (target == '.') {
                            Move move = Move{ vec2{col, row},vec2{i, row} };
                            moveswhite.push_back(move);
                        }
                    }
                    // up
                    for (int i = col - 1; i >= 0; i--) {
                        char target = board[i][row];
                        if (isupper(target))
                            break;

                        if (islower(target)) {
                            Move move{ vec2{col, row}, vec2{i, row} };
                            if (target == 'k')
                                checkswhite.push_back(move);
                            else
                                moveswhite.push_back(move);
                            break;
                        }

                        if (target == '.') {
                            Move move = Move{ vec2{col, row},vec2{i, row} };
                            moveswhite.push_back(move);
                        }
                    }
                    // right
                    for (int i = row + 1; i < 8; i++) {
                        char target = board[col][i];
                        if (isupper(target))
                            break;

                        if (islower(target)) {
                            Move move{ vec2{col, row}, vec2{col, i} };
                            if (target == 'k')
                                checkswhite.push_back(move);
                            else
                                moveswhite.push_back(move);
                            break;
                        }

                        if (target == '.') {
                            Move move = Move{ vec2{col, row},vec2{col, i} };
                            moveswhite.push_back(move);
                        }
                    }
                    // left
                    for (int i = row - 1; i >= 0; i--) {
                        char target = board[col][i];
                        if (isupper(target))
                            break;

                        if (islower(target)) {
                            Move move{ vec2{col, row}, vec2{col, i} };
                            if (target == 'k')
                                checkswhite.push_back(move);
                            else
                                moveswhite.push_back(move);
                            break;
                        }

                        if (target == '.') {
                            Move move = Move{ vec2{col, row},vec2{col, i} };
                            moveswhite.push_back(move);
                        }
                    }
                }
                // bishop / queen
                if (figure == 'b' || figure == 'q') {
                    for (int i = 1; i < 8; i++) {
                        if (col + i > 7 || row + i > 7)
                            break;

                        char target = board[col + i][row + i];
                        if (islower(target))
                            break;

                        if (isupper(target)) {
                            Move move{ vec2{col, row}, vec2{col + i, row + i} };
                            if (target == 'K')
                                checksblack.push_back(move);
                            else
                                movesblack.push_back(move);
                            break;
                        }

                        if (target == '.') {
                            Move move = Move{ vec2{col, row},vec2{col + i, row + i} };
                            movesblack.push_back(move);
                        }
                    }
                    for (int i = 1; i < 8; i++) {
                        if (col - i < 0 || row - i < 0)
                            break;

                        char target = board[col - i][row - i];
                        if (islower(target))
                            break;

                        if (isupper(target)) {
                            Move move{ vec2{col, row}, vec2{col - i, row - i} };
                            if (target == 'K')
                                checksblack.push_back(move);
                            else
                                movesblack.push_back(move);
                            break;
                        }

                        if (target == '.') {
                            Move move = Move{ vec2{col, row},vec2{col - i, row - i} };
                            movesblack.push_back(move);
                        }
                    }
                    for (int i = 1; i < 8; i++) {
                        if (col - i < 0 || row + i > 7)
                            break;

                        char target = board[col - i][row + i];
                        if (islower(target))
                            break;

                        if (isupper(target)) {
                            Move move{ vec2{col, row}, vec2{col - i, row + i} };
                            if (target == 'K')
                                checksblack.push_back(move);
                            else
                                movesblack.push_back(move);
                            break;
                        }

                        if (target == '.') {
                            Move move = Move{ vec2{col, row},vec2{col - i, row + i} };
                            movesblack.push_back(move);
                        }
                    }
                    for (int i = 1; i < 8; i++) {
                        if (col + i > 7 || row - i < 0)
                            break;

                        char target = board[col + i][row - i];
                        if (islower(target))
                            break;
                        if (isupper(target)) {
                            Move move{ vec2{col, row}, vec2{col + i, row - i} };
                            if (target == 'K')
                                checksblack.push_back(move);
                            else
                                movesblack.push_back(move);
                            break;
                        }

                        if (target == '.') {
                            Move move = Move{ vec2{col, row},vec2{col + i, row - i} };
                            movesblack.push_back(move);
                        }
                    }
                }

                if (figure == 'B' || figure == 'Q') {
                    for (int i = 1; i < 8; i++) {
                        if (col + i > 7 || row + i > 7)
                            break;

                        char target = board[col + i][row + i];
                        if (isupper(target))
                            break;

                        if (islower(target)) {
                            Move move{ vec2{col, row}, vec2{col + i, row + i} };
                            if (target == 'k')
                                checkswhite.push_back(move);
                            else
                                moveswhite.push_back(move);
                            break;
                        }

                        if (target == '.') {
                            Move move = Move{ vec2{col, row},vec2{col + i, row + i} };
                            moveswhite.push_back(move);
                        }
                    }
                    for (int i = 1; i < 8; i++) {
                        if (col - i < 0 || row - i < 0)
                            break;

                        char target = board[col - i][row - i];
                        if (isupper(target))
                            break;

                        if (islower(target)) {
                            Move move{ vec2{col, row}, vec2{col - i, row - i} };
                            if (target == 'k')
                                checkswhite.push_back(move);
                            else
                                moveswhite.push_back(move);
                            break;
                        }

                        if (target == '.') {
                            Move move = Move{ vec2{col, row},vec2{col - i, row - i} };
                            moveswhite.push_back(move);
                        }
                    }
                    for (int i = 1; i < 8; i++) {
                        if (col - i < 0 || row + i > 7)
                            break;

                        char target = board[col - i][row + i];
                        if (isupper(target))
                            break;

                        if (islower(target)) {
                            Move move{ vec2{col, row}, vec2{col - i, row + i} };
                            if (target == 'k')
                                checkswhite.push_back(move);
                            else
                                moveswhite.push_back(move);
                            break;
                        }

                        if (target == '.') {
                            Move move = Move{ vec2{col, row},vec2{col - i, row + i} };
                            moveswhite.push_back(move);
                        }
                    }
                    for (int i = 1; i < 8; i++) {
                        if (col + i > 7 || row - i < 0)
                            break;

                        char target = board[col + i][row - i];
                        if (isupper(target))
                            break;
                        if (islower(target)) {
                            Move move{ vec2{col, row}, vec2{col + i, row - i} };
                            if (target == 'K')
                                checkswhite.push_back(move);
                            else
                                moveswhite.push_back(move);
                            break;
                        }

                        if (target == '.') {
                            Move move = Move{ vec2{col, row},vec2{col + i, row - i} };
                            moveswhite.push_back(move);
                        }
                    }
                }
                // knight
                if (figure == 'n') {
                    // 8 different moves
                    if (col + 2 < 8 && row + 1 < 8) {
                        char target = board[col + 2][row + 1];
                        if (!islower(target)) {
                            Move move = Move{ vec2{col, row}, vec2{col + 2, row + 1} };
                            if (target == 'K')
                                checksblack.push_back(move);
                            else
                                movesblack.push_back(move);
                        }
                    }
                    if (col + 2 < 8 && row - 1 >= 0) {
                        char target = board[col + 2][row - 1];
                        if (!islower(target)) {
                            Move move = Move{ vec2{col, row}, vec2{col + 2, row - 1} };
                            if (target == 'K')
                                checksblack.push_back(move);
                            else
                                movesblack.push_back(move);
                        }
                    }
                    if (col + 1 < 8 && row + 2 < 8) {
                        char target = board[col + 1][row + 2];
                        if (!islower(target)) {
                            Move move = Move{ vec2{col, row}, vec2{col + 1, row + 2} };
                            if (target == 'K')
                                checksblack.push_back(move);
                            else
                                movesblack.push_back(move);
                        }
                    }
                    if (col - 1 >= 0 && row + 2 < 8) {
                        char target = board[col - 1][row + 2];
                        if (!islower(target)) {
                            Move move = Move{ vec2{col, row}, vec2{col - 1, row + 2} };
                            if (target == 'K')
                                checksblack.push_back(move);
                            else
                                movesblack.push_back(move);
                        }
                    }
                    if (col - 2 >= 0 && row + 1 < 8) {
                        char target = board[col - 2][row + 1];
                        if (!islower(target)) {
                            Move move = Move{ vec2{col, row}, vec2{col - 2, row + 1} };
                            if (target == 'K')
                                checksblack.push_back(move);
                            else
                                movesblack.push_back(move);
                        }
                    }
                    if (col - 2 >= 0 && row - 1 >= 0) {
                        char target = board[col - 2][row - 1];
                        if (!islower(target)) {
                            Move move = Move{ vec2{col, row}, vec2{col - 2, row - 1} };
                            if (target == 'K')
                                checksblack.push_back(move);
                            else
                                movesblack.push_back(move);
                        }
                    }
                    if (col + 1 < 8 && row - 2 >= 0) {
                        char target = board[col + 1][row - 2];
                        if (!islower(target)) {
                            Move move = Move{ vec2{col, row}, vec2{col + 1, row - 2} };
                            if (target == 'K')
                                checksblack.push_back(move);
                            else
                                movesblack.push_back(move);
                        }
                    }
                    if (col - 1 >= 0 && row - 2 >= 0) {
                        char target = board[col - 1][row + 2];
                        if (!islower(target)) {
                            Move move = Move{ vec2{col, row}, vec2{col - 1, row - 2} };
                            if (target == 'K')
                                checksblack.push_back(move);
                            else
                                movesblack.push_back(move);
                        }
                    }
                }
                if (figure == 'N') {
                    // 8 different moves
                    if (col + 2 < 8 && row + 1 < 8) {
                        char target = board[col + 2][row + 1];
                        if (!isupper(target)) {
                            Move move = Move{ vec2{col, row}, vec2{col + 2, row + 1} };
                            if (target == 'k')
                                checkswhite.push_back(move);
                            else
                                moveswhite.push_back(move);
                        }
                    }
                    if (col + 2 < 8 && row - 1 >= 0) {
                        char target = board[col + 2][row - 1];
                        if (!isupper(target)) {
                            Move move = Move{ vec2{col, row}, vec2{col + 2, row - 1} };
                            if (target == 'k')
                                checkswhite.push_back(move);
                            else
                                moveswhite.push_back(move);
                        }
                    }
                    if (col + 1 < 8 && row + 2 < 8) {
                        char target = board[col + 1][row + 2];
                        if (!isupper(target)) {
                            Move move = Move{ vec2{col, row}, vec2{col + 1, row + 2} };
                            if (target == 'k')
                                checkswhite.push_back(move);
                            else
                                moveswhite.push_back(move);
                        }
                    }
                    if (col - 1 >= 0 && row + 2 < 8) {
                        char target = board[col - 1][row + 2];
                        if (!isupper(target)) {
                            Move move = Move{ vec2{col, row}, vec2{col - 1, row + 2} };
                            if (target == 'k')
                                checkswhite.push_back(move);
                            else
                                moveswhite.push_back(move);
                        }
                    }
                    if (col - 2 >= 0 && row + 1 < 8) {
                        char target = board[col - 2][row + 1];
                        if (!isupper(target)) {
                            Move move = Move{ vec2{col, row}, vec2{col - 2, row + 1} };
                            if (target == 'k')
                                checkswhite.push_back(move);
                            else
                                moveswhite.push_back(move);
                        }
                    }
                    if (col - 2 >= 0 && row - 1 >= 0) {
                        char target = board[col - 2][row - 1];
                        if (!isupper(target)) {
                            Move move = Move{ vec2{col, row}, vec2{col - 2, row - 1} };
                            if (target == 'k')
                                checkswhite.push_back(move);
                            else
                                moveswhite.push_back(move);
                        }
                    }
                    if (col + 1 < 8 && row - 2 >= 0) {
                        char target = board[col + 1][row - 2];
                        if (!isupper(target)) {
                            Move move = Move{ vec2{col, row}, vec2{col + 1, row - 2} };
                            if (target == 'k')
                                checkswhite.push_back(move);
                            else
                                moveswhite.push_back(move);
                        }
                    }
                    if (col - 1 >= 0 && row - 2 >= 0) {
                        char target = board[col - 1][row + 2];
                        if (!isupper(target)) {
                            Move move = Move{ vec2{col, row}, vec2{col - 1, row - 2} };
                            if (target == 'k')
                                checkswhite.push_back(move);
                            else
                                moveswhite.push_back(move);
                        }
                    }
                }
                // king
                if (figure == 'k') {
                    if (col + 1 < 8 && row + 1 < 8) {
                        char target = board[col + 1][row + 1];
                        if (!islower(target)) {
                            Move move = Move{ vec2{col, row}, vec2{col + 1, row + 1} };
                            if (target == 'K')
                                checksblack.push_back(move);
                            else
                                movesblack.push_back(move);
                        }
                    }
                    if (col + 1 < 8) {
                        char target = board[col + 1][row];
                        if (!islower(target)) {
                            Move move = Move{ vec2{col, row}, vec2{col + 1, row} };
                            if (target == 'K')
                                checksblack.push_back(move);
                            else
                                movesblack.push_back(move);
                        }
                    }
                    if (col + 1 < 8 && row - 1 >= 0) {
                        char target = board[col + 1][row - 1];
                        if (!islower(target)) {
                            Move move = Move{ vec2{col, row}, vec2{col + 1, row - 1} };
                            if (target == 'K')
                                checksblack.push_back(move);
                            else
                                movesblack.push_back(move);
                        }
                    }
                    if (row - 1 >= 0) {
                        char target = board[col][row - 1];
                        if (!islower(target)) {
                            Move move = Move{ vec2{col, row}, vec2{col, row - 1} };
                            if (target == 'K')
                                checksblack.push_back(move);
                            else
                                movesblack.push_back(move);
                        }
                    }
                    if (row + 1 < 8) {
                        char target = board[col][row + 1];
                        if (!islower(target)) {
                            Move move = Move{ vec2{col, row}, vec2{col, row + 1} };
                            if (target == 'K')
                                checksblack.push_back(move);
                            else
                                movesblack.push_back(move);
                        }
                    }
                    if (col - 1 >= 0 && row + 1 < 8) {
                        char target = board[col - 1][row + 1];
                        if (!islower(target)) {
                            Move move = Move{ vec2{col, row}, vec2{col - 1, row + 1} };
                            if (target == 'K')
                                checksblack.push_back(move);
                            else
                                movesblack.push_back(move);
                        }
                    }
                    if (col - 1 >= 0) {
                        char target = board[col - 1][row];
                        if (!islower(target)) {
                            Move move = Move{ vec2{col, row}, vec2{col - 1, row} };
                            if (target == 'K')
                                checksblack.push_back(move);
                            else
                                movesblack.push_back(move);
                        }
                    }
                    if (col - 1 >= 0 && row - 1 >= 0) {
                        char target = board[col - 1][row - 1];
                        if (!islower(target)) {
                            Move move = Move{ vec2{col, row}, vec2{col - 1, row - 1} };
                            if (target == 'K')
                                checksblack.push_back(move);
                            else
                                movesblack.push_back(move);
                        }
                    }
                }
                if (figure == 'K') {
                    if (col + 1 < 8 && row + 1 < 8) {
                        char target = board[col + 1][row + 1];
                        if (!isupper(target)) {
                            Move move = Move{ vec2{col, row}, vec2{col + 1, row + 1} };
                            if (target == 'k')
                                checkswhite.push_back(move);
                            else
                                moveswhite.push_back(move);
                        }
                    }
                    if (col + 1 < 8) {
                        char target = board[col + 1][row];
                        if (!isupper(target)) {
                            Move move = Move{ vec2{col, row}, vec2{col + 1, row} };
                            if (target == 'k')
                                checkswhite.push_back(move);
                            else
                                moveswhite.push_back(move);
                        }
                    }
                    if (col + 1 < 8 && row - 1 >= 0) {
                        char target = board[col + 1][row - 1];
                        if (!isupper(target)) {
                            Move move = Move{ vec2{col, row}, vec2{col + 1, row - 1} };
                            if (target == 'k')
                                checkswhite.push_back(move);
                            else
                                moveswhite.push_back(move);
                        }
                    }
                    if (row - 1 >= 0) {
                        char target = board[col][row - 1];
                        if (!isupper(target)) {
                            Move move = Move{ vec2{col, row}, vec2{col, row - 1} };
                            if (target == 'k')
                                checkswhite.push_back(move);
                            else
                                moveswhite.push_back(move);
                        }
                    }
                    if (row + 1 < 8) {
                        char target = board[col][row + 1];
                        if (!isupper(target)) {
                            Move move = Move{ vec2{col, row}, vec2{col, row + 1} };
                            if (target == 'k')
                                checkswhite.push_back(move);
                            else
                                moveswhite.push_back(move);
                        }
                    }
                    if (col - 1 >= 0 && row + 1 < 8) {
                        char target = board[col - 1][row + 1];
                        if (!isupper(target)) {
                            Move move = Move{ vec2{col, row}, vec2{col - 1, row + 1} };
                            if (target == 'k')
                                checkswhite.push_back(move);
                            else
                                moveswhite.push_back(move);
                        }
                    }
                    if (col - 1 >= 0) {
                        char target = board[col - 1][row];
                        if (!isupper(target)) {
                            Move move = Move{ vec2{col, row}, vec2{col - 1, row} };
                            if (target == 'k')
                                checkswhite.push_back(move);
                            else
                                moveswhite.push_back(move);
                        }
                    }
                    if (col - 1 >= 0 && row - 1 >= 0) {
                        char target = board[col - 1][row - 1];
                        if (!isupper(target)) {
                            Move move = Move{ vec2{col, row}, vec2{col - 1, row - 1} };
                            if (target == 'k')
                                checkswhite.push_back(move);
                            else
                                moveswhite.push_back(move);
                        }
                    }
                }
            }
        }
        // different castles
        if (whitelongcastle) {
            if (board[7][1] == '.' && board[7][2] == '.' && board[7][3] == '.') {
                Move wlongcastle;
                wlongcastle.castle = true;
                wlongcastle.from = vec2{7,4};
                wlongcastle.to = vec2{7,2};
                wlongcastle.figfrom = 'K';
                wlongcastle.from2 = vec2{7,0};
                wlongcastle.to2 = vec2{7,3};
                wlongcastle.figfrom2 = 'R';
                wlongcastle.castletype = LONG;
                moveswhite.push_back(wlongcastle);
            }
        }
        if (whiteshortcastle) {
            if (board[7][5] == '.' && board[7][6] == '.') {
                Move wshortcastle;
                wshortcastle.castle = true;
                wshortcastle.from = vec2{7,4};
                wshortcastle.to = vec2{7,6};
                wshortcastle.figfrom = 'K';
                wshortcastle.from2 = vec2{7,7};
                wshortcastle.to2 = vec2{7,5};
                wshortcastle.figfrom2 = 'R';
                wshortcastle.castletype = SHORT;
                moveswhite.push_back(wshortcastle);
            }
        }
        if (blacklongcastle) {
            if (board[0][1] == '.' && board[0][2] == '.' && board[0][3] == '.') {
                Move blongcastle;
                blongcastle.castle = true;
                blongcastle.from = vec2{0,4};
                blongcastle.to = vec2{0,2};
                blongcastle.figfrom = 'k';
                blongcastle.from2 = vec2{0,0};
                blongcastle.to2 = vec2{0,3};
                blongcastle.figfrom2 = 'r';
                blongcastle.castletype = LONG;
                movesblack.push_back(blongcastle);
            }
        }
        if (blackshortcastle) {
            if (board[0][5] == '.' && board[0][6] == '.') {
                Move bshortcastle;
                bshortcastle.castle = true;
                bshortcastle.from = vec2{0,4};
                bshortcastle.to = vec2{0,6};
                bshortcastle.figfrom = 'k';
                bshortcastle.from2 = vec2{0,7};
                bshortcastle.to2 = vec2{0,5};
                bshortcastle.figfrom2 = 'r';
                bshortcastle.castletype = SHORT;
                movesblack.push_back(bshortcastle);
            }
        }
    }

    void ApplyMoveToBoard(Move& move) {
        // check for castling rights
        if (!move.castle) {
            if (move.figfrom == 'r') {
                if (blacklongcastle && move.from.column == 0 && move.from.row == 0) {
                    blacklongcastle = false;
                    move.changedblacklong = true;
                }
                if (blackshortcastle && move.from.column == 0 && move.from.row == 7) {
                    blackshortcastle = false;
                    move.changedblackshort = true;
                }
            }
            if (move.figfrom == 'R') {
                if (whitelongcastle && move.from.column == 7 && move.from.row == 0) {
                    whitelongcastle = false;
                    move.changedwhitelong = true;
                }
                if (whiteshortcastle && move.from.column == 7 && move.from.row == 7) {
                    whiteshortcastle = false;
                    move.changedwhiteshort = true;
                }
            }
            if (move.figfrom == 'k') {
                if (blacklongcastle) {
                    blacklongcastle = false;
                    move.changedblacklong = true;
                }
                if (blackshortcastle) {
                    blackshortcastle = false;
                    move.changedblackshort = true;
                }
            }
            if (move.figfrom == 'K') {
                if (whitelongcastle) {
                    whitelongcastle = false;
                    move.changedwhitelong = true;
                }
                if (whiteshortcastle) {
                    whiteshortcastle = false;
                    move.changedwhiteshort = true;
                }
            }
            board[move.from.column][move.from.row] = '.';
            board[move.to.column][move.to.row] = move.figfrom;
            return;
        }

        if (move.figfrom == 'K') {
            bwlongcastle = whitelongcastle; bwshortcastle = whiteshortcastle;
            whitelongcastle = false; whiteshortcastle = false;
            whitecastled = true;
        }
        if (move.figfrom == 'k') {
            bblongcastle = blacklongcastle; bbshortcastle = blackshortcastle;
            blacklongcastle = false; blackshortcastle = false;
            blackcastled = true;
        }
        board[move.from.column][move.from.row] = '.';
        board[move.to.column][move.to.row] = move.figfrom;
        board[move.from2.column][move.from2.row] = '.';
        board[move.to2.column][move.to2.row] = move.figfrom2;
    }

    void UndoMove(Move& move) {
        if (!move.castle) {
            // restore castling rights
            if (move.changedblacklong)
                blacklongcastle = true;
            if (move.changedblackshort)
                blackshortcastle = true;
            if (move.changedwhitelong)
                whitelongcastle = true;
            if (move.changedwhiteshort)
                whiteshortcastle = true;

            board[move.to.column][move.to.row] = move.figto;
            board[move.from.column][move.from.row] = move.figfrom;
            return;
        }

        if (move.figfrom == 'K') {
            whitelongcastle = bwlongcastle; whiteshortcastle = bwshortcastle;
            whitecastled = false;
        }
        if (move.figfrom == 'k') {
            blacklongcastle = bblongcastle; blackshortcastle = bbshortcastle;
            blackcastled = false;
        }

        board[move.to.column][move.to.row] = '.';
        board[move.from.column][move.from.row] = move.figfrom;
        board[move.to2.column][move.to2.row] = '.';
        board[move.from2.column][move.from2.row] = move.figfrom2;
    }

    void GenerateLegalMoves(std::vector<Move> legalmoves[2], char* pBoardInfo, bool boardfilled = false) {
        // generate all moves

        if (!boardfilled)
            FillBoard(pBoardInfo);

        // make generated moves
        std::vector<Move> backupmovesblack; std::vector<Move> backupchecksblack; std::vector<Move> backupmoveswhite; std::vector<Move> backupcheckswhite;
        GenAllMoves(backupmoveswhite, backupmovesblack, backupcheckswhite, backupchecksblack);
        SetupMoves(backupmoveswhite, backupmovesblack, backupcheckswhite, backupchecksblack);

        checkswhite = backupcheckswhite.size();
        checksblack = backupchecksblack.size();

        // seperate illegal moves
        // idea here is to apply every possible move for white and then get every move for black
        // if black has a check move, since its blacks turn we would lose, therefore the move is illegal
        for (auto& move : backupmoveswhite) {
            ApplyMoveToBoard(move);

            std::vector<Move> movesblack; std::vector<Move> checksblack; std::vector<Move> moveswhite; std::vector<Move> checkswhite;
            GenAllMoves(moveswhite, movesblack, checkswhite, checksblack);

            // reset board
            UndoMove(move);

            // black has no checks, therefore this move is legal
            if (checksblack.size() == 0) {
                legalmoves[WHITE].push_back(move);
            }
        }
        for (auto& move : backupcheckswhite) {
            ApplyMoveToBoard(move);

            std::vector<Move> movesblack; std::vector<Move> checksblack; std::vector<Move> moveswhite; std::vector<Move> checkswhite;
            GenAllMoves(moveswhite, movesblack, checkswhite, checksblack);

            // reset board
            UndoMove(move);

            // move blocks check but also gives a check to the enmy king
            if (checksblack.size() == 0) {
                legalmoves[WHITE].push_back(move);
            }
        }
        // same idea as with white
        for (auto& move : backupmovesblack) {
            ApplyMoveToBoard(move);

            std::vector<Move> movesblack; std::vector<Move> checksblack; std::vector<Move> moveswhite; std::vector<Move> checkswhite;
            GenAllMoves(moveswhite, movesblack, checkswhite, checksblack);

            // reset board
            UndoMove(move);

            if (checkswhite.size() == 0) {
                legalmoves[BLACK + 1].push_back(move);
            }

        }
        for (auto& move : backupchecksblack) {
            ApplyMoveToBoard(move);

            std::vector<Move> movesblack; std::vector<Move> checksblack; std::vector<Move> moveswhite; std::vector<Move> checkswhite;
            GenAllMoves(moveswhite, movesblack, checkswhite, checksblack);

            // reset board
            UndoMove(move);

            if (checkswhite.size() == 0) {
                legalmoves[BLACK + 1].push_back(move);
            }
        }
    }
};
