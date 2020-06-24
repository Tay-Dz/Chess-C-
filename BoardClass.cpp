//Tay Dzonu - C++ Chess code April 2020
//BoardClass.cpp - cpp file defining chess_board class functions

#include "BoardClass.h"


chess_board::chess_board() {//constructor
    grid_info = new std::unique_ptr<chess_pieces>[64]; // unique pointer of chess pieces
    // Placing chess pieces in correct start position
    grid_info[index(1, 1)] = std::make_unique<rook>("w");
    grid_info[index(1, 8)] = std::make_unique<rook>("w");
    grid_info[index(1, 2)] = std::make_unique<knight>("w");
    grid_info[index(1, 7)] = std::make_unique<knight>("w");
    grid_info[index(1, 3)] = std::make_unique<bishop>("w");
    grid_info[index(1, 6)] = std::make_unique<bishop>("w");
    grid_info[index(1, 4)] = std::make_unique<king>("w");
    grid_info[index(1, 5)] = std::make_unique<queen>("w");
    grid_info[index(8, 1)] = std::make_unique<rook>("b");
    grid_info[index(8, 8)] = std::make_unique<rook>("b");
    grid_info[index(8, 2)] = std::make_unique<knight>("b");
    grid_info[index(8, 7)] = std::make_unique<knight>("b");
    grid_info[index(8, 3)] = std::make_unique<bishop>("b");
    grid_info[index(8, 6)] = std::make_unique<bishop>("b");
    grid_info[index(8, 4)] = std::make_unique<king>("b");
    grid_info[index(8, 5)] = std::make_unique<queen>("b");
    for (int i = 1; i <= 8; i++) { // for loop to adding multiple pawns and empty pieces
        grid_info[index(7, i)] = std::make_unique<pawn>("b");
        grid_info[index(2, i)] = std::make_unique<pawn>("w");
        for (int j = 3; j <= 6; j++) {
            grid_info[index(j, i)] = std::make_unique<empty>();
        }
    }
}
chess_board::chess_board(std::vector<std::pair<std::string, int>> board) {//parameterised constructor from load file info
    grid_info = new std::unique_ptr<chess_pieces>[64]; //create a unique pointer array filled with empty pieces
    for (size_t i = 0; i < 64; i++) {
        grid_info[i] = std::make_unique<empty>();
    }
    for (auto it = board.begin(); it != board.end(); it++) { // iterator over vector which contains piece and location. Replaces empty piece by given piece in a location
        if (it->first == "bp") { grid_info[it->second] = std::make_unique < pawn>("b"); }
        else if (it->first == "wp") { grid_info[it->second] = std::make_unique < pawn>("w"); }
        else if (it->first == "br") { grid_info[it->second] = std::make_unique<rook>("b"); }
        else if (it->first == "wr") { grid_info[it->second] = std::make_unique<rook>("w"); }
        else if (it->first == "bn") { grid_info[it->second] = std::make_unique<knight>("b"); }
        else if (it->first == "wn") { grid_info[it->second] = std::make_unique<knight>("w"); }
        else if (it->first == "bb") { grid_info[it->second] = std::make_unique<bishop>("b"); }
        else if (it->first == "wb") { grid_info[it->second] = std::make_unique<bishop>("w"); }
        else if (it->first == "bq") { grid_info[it->second] = std::make_unique<queen>("b"); }
        else if (it->first == "wq") { grid_info[it->second] = std::make_unique<queen>("w"); }
        else if (it->first == "bk") { grid_info[it->second] = std::make_unique<king>("b"); }
        else if (it->first == "wk") { grid_info[it->second] = std::make_unique<king>("w"); }
        else {}
    }
}

std::string chess_board::winner = " "; //initialise static winner
std::string chess_board::p_to_q = ""; //initialise static p_to_q

int chess_board::index(int board_x_pos, int board_y_pos) const { // Return position in 1d array from 2d position
    if (board_x_pos > 0 && board_x_pos <= 8 && board_y_pos > 0 && board_y_pos <= 8) return (board_y_pos - 1) + (board_x_pos - 1) * 8;
    else { std::cout << "Error: out of range" << std::endl; exit(1); } //error message if index is invalid
}
bool chess_board::is_empty(int board_x_pos, int board_y_pos) {// checks if there is an empty piece in a given location
    if (grid_info[index(board_x_pos, board_y_pos)]->col() == " ") { return true; }
    else { return false; }
}
bool chess_board::right_colour(int board_x_pos, int board_y_pos, std::string colour) { // Compares piece colour and player colour : returns true if they are the same
    if ((grid_info[index(board_x_pos, board_y_pos)]->col() == "w" && colour == "White") || (grid_info[index(board_x_pos, board_y_pos)]->col() == "b" && colour == "Black")) {
        return true;
    }
    else { return false; }
}
std::string chess_board::who_won() { //Returns winner colour depending on value of static winner
    if (winner == "b") { return "Black"; }
    if (winner == "w") { return "White"; }
    else { return " "; }
}

std::vector<std::pair<int, int>>  chess_board::possible_moves(int board_x_pos, int board_y_pos) {
    std::vector<std::vector<std::pair<int, int>>> move_list;
    move_list = grid_info[index(board_x_pos, board_y_pos)]->move(); // Takes possible moves from move() function for the piece in the given location
    std::pair<int, int > move; //possible final location of piece
    std::vector < std::pair<int, int>> all_moves;//vector to take in all possible final locations of a piece once checks are done
    if (grid_info[index(board_x_pos, board_y_pos)]->pic() == "p") { // checks if piece is a pawn: special case due to differences when taking pieces
        for (auto directions : move_list) {
            bool not_blocked = true; // indicates move is not blocked by any previos moves
            for (auto relative_positions : directions) {
                int x = relative_positions.first + board_x_pos;
                int y = relative_positions.second + board_y_pos;
                if (x > 8 || x < 1 || y > 8 || y < 1) { not_blocked = 0; } // checks if final position is out of the board
                else {
                    if (directions == move_list[0]) { // checks if it is a non-taking move
                        if (grid_info[index(x, y)]->pic() == " " && not_blocked == true) { //checks if position is empty and unblocked by piece in previous location
                            move.first = x;
                            move.second = y;
                            all_moves.push_back(move);
                        }
                        else {not_blocked = false;} // move not possible and notifies all subsequent moves in that direction that they are not possible
                    }
                    else if (grid_info[index(x, y)]->pic() != " " && grid_info[index(board_x_pos, board_y_pos)]->col() != grid_info[index(x, y)]->col()) { // for taking moves: checks if there is a piece of the opposite colour in taking positions
                        move.first = x;
                        move.second = y;
                        all_moves.push_back(move);
                    }
                }
            }
        }
    }
    else { // case for all pieces that aren't pawns
        for (auto directions : move_list) {
            bool not_blocked = 1;// indicates move is not blocked by any previos moves
            for (auto relative_positions : directions) {
                if (not_blocked) {
                    int x = relative_positions.first + board_x_pos;
                    int y = relative_positions.second + board_y_pos;
                    if (x > 8 || x < 1 || y > 8 || y < 1 || grid_info[index(board_x_pos, board_y_pos)]->col() == grid_info[index(x, y)]->col()) { //does not save new position if it is off the board or a piece of the same colour
                        not_blocked = false; // indicates all subsequent moves are also not possible
                    }
                    else if (grid_info[index(x, y)]->col() == " ") { // saves location if moving into location of empty piece
                        move.first = x;
                        move.second = y;
                        all_moves.push_back(move);
                    }
                    else {// case of taking a piece of opposite colour: saves location then indicates all subsequent moves in the direction are blocked by that piece
                        move.first = x;
                        move.second = y;
                        all_moves.push_back(move);
                        not_blocked = 0;
                    }

                }
            }
        }
    }

    return all_moves;
}
bool chess_board::test_move_here(int board_x_pos_start, int board_y_pos_start, int board_x_pos_end, int board_y_pos_end) {// checks if a piece in a given position cand move to another position
    std::pair<int, int> location;
    location.first = board_x_pos_end;
    location.second = board_y_pos_end;
    std::vector<std::pair<int, int>> move = possible_moves(board_x_pos_start, board_y_pos_start);
    for (auto it_a = move.begin(); it_a != move.end(); it_a++) {
        if (it_a->first == board_x_pos_end && it_a->second == board_y_pos_end) { return true; } // returns true if end position is in vector prided by possible_moves() function
    }
    return false;
}
std::string chess_board::move_here_str(int board_x_pos_start, int board_y_pos_start, int board_x_pos_end, int board_y_pos_end) { // returns X if move is possible, used in show_moves_out function
    if (test_move_here(board_x_pos_start, board_y_pos_start, board_x_pos_end, board_y_pos_end)) { return "X"; }
    else { return " "; }
}
void chess_board::pawn_to_queen(int board_x_pos, int board_y_pos) { // function which changes a pawn to a queen if it reaches the opposite side of the board
    p_to_q = ""; // reset p_to_q
    if (grid_info[index(board_x_pos, board_y_pos)]->piece_out() == "bp" && board_x_pos == 1) { // black pawn case
        grid_info[index(board_x_pos, board_y_pos)] = std::make_unique<queen>("b");
        p_to_q = "Black pawn has changed into a Queen.\n";
        ;
    }
    else if (grid_info[index(board_x_pos, board_y_pos)]->piece_out() == "wp" && board_x_pos == 8) {//white pawn case
        grid_info[index(board_x_pos, board_y_pos)] = std::make_unique<queen>("w");
        p_to_q = "White pawn has changed into a Queen.\n";
    }
    return;
}
void chess_board::move_piece(int board_x_pos_start, int board_y_pos_start, int board_x_pos_end, int board_y_pos_end) {// function which moves piece
    if (grid_info[index(board_x_pos_start, board_y_pos_start)]->pic() == "p") { grid_info[index(board_x_pos_start, board_y_pos_start)]->has_moved(); } //if pawn is moved changes value of not_moved so it cant move 2 spaces from now on
    if (grid_info[index(board_x_pos_end, board_y_pos_end)]->pic() == "k") { winner = grid_info[index(board_x_pos_start, board_y_pos_start)]->col(); } //if king is taken returns which player has one into winner
    std::swap(grid_info[index(board_x_pos_start, board_y_pos_start)], grid_info[index(board_x_pos_end, board_y_pos_end)]); // swaps the pieces in the initial and end position
    grid_info[index(board_x_pos_start, board_y_pos_start)] = std::make_unique<empty>(); // replaces the piece which was taken by an empty piece
    pawn_to_queen(board_x_pos_end, board_y_pos_end); // checks if pawn turns into a queen
} 

std::ostream& operator<<(std::ostream& os, const chess_board& mat) { // overloaded << operator to output current state of board
    system("CLS"); //clears the out put screen for improved readability whilst playing game -> prevents the need toi scroll
    title(); 
    std::string grid = "         1       2       3       4       5       6       7       8 ";  // top grid numbers
    std::cout << grid << std::endl << std::endl;
    //next 5 lines are strings representing the outer boarder and inner boarders of the chess board
    std::string barrier = "     ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||";
    std::string next = "     ||      ||      ||      ||      ||      ||      ||      ||      ||";
    std::string begin = "||  ";
    std::string mid = "  ||  ";
    std::string end = "  ||";
    for (int i = 1; i <= 8; i++) {
        std::cout << barrier << std::endl << next << std::endl;
        std::cout << "  " << int_to_grid(i) << "  " << begin; //side grid position, turns integer into relevent letter
        for (int j = 1; j <= 8; j++) {
            if (j == 8) { std::cout << mat.grid_info[mat.index(i, j)]->piece_out() << end; } // outputs the piece in the given location
            else { std::cout << mat.grid_info[mat.index(i, j)]->piece_out() << mid; }
        }

        std::cout << std::endl << next << std::endl;
    }
    std::cout << barrier << std::endl;
    return os;
};
void chess_board::show_moves_out(int board_x_pos, int board_y_pos) { // function which outputs the chess board, representing the possible moves for a piece at the given location: similar to overloaded << operator ->differences stated
    system("CLS");
    title();
    std::string grid = "         1       2       3       4       5       6       7       8 ";
    std::cout << grid << std::endl << std::endl;
    std::string barrier = "     ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||";
    std::string next = "     ||      ||      ||      ||      ||      ||      ||      ||      ||";
    std::string begin = "|| ";
    std::string mid = " || ";
    std::string end = " ||";
    for (int i = 1; i <= 8; i++) {
        std::cout << barrier << std::endl;
        std::cout << "     " << begin;
        for (int j = 1; j <= 8; j++) {
            if (j == 8) { std::cout << " " << move_here_str(board_x_pos, board_y_pos, i, j) << move_here_str(board_x_pos, board_y_pos, i, j) << " " << end; } // outputs X's in positions which the piece can move to
            else { std::cout << " " << move_here_str(board_x_pos, board_y_pos, i, j) << move_here_str(board_x_pos, board_y_pos, i, j) << " " << mid; }  // similar implementation in the next 2 for loops
        }
        std::cout << std::endl << "  " << int_to_grid(i) << "  " << begin;
        for (int j = 1; j <= 8; j++) {
            if (j == 8) { std::cout << move_here_str(board_x_pos, board_y_pos, i, j) << grid_info[index(i, j)]->piece_out() << move_here_str(board_x_pos, board_y_pos, i, j) << end; }
            else { std::cout << move_here_str(board_x_pos, board_y_pos, i, j) << grid_info[index(i, j)]->piece_out() << move_here_str(board_x_pos, board_y_pos, i, j) << mid; }
        }

        std::cout << std::endl << "     " << begin;
        for (int j = 1; j <= 8; j++) {
            if (j == 8) { std::cout << " " << move_here_str(board_x_pos, board_y_pos, i, j) << move_here_str(board_x_pos, board_y_pos, i, j) << " " << end; }
            else { std::cout << " " << move_here_str(board_x_pos, board_y_pos, i, j) << move_here_str(board_x_pos, board_y_pos, i, j) << " " << mid; }
        }
        std::cout << std::endl;
    }
    std::cout << barrier << std::endl;
}

std::vector<std::pair<std::string, int>> chess_board::save_board() { // function to save locations of pieces and the type of piece
    std::vector<std::pair<std::string, int>> board;
    std::pair<std::string, int> piece_location;
    for (size_t i = 0; i < 64; i++) {
        if (grid_info[i]->piece_out() != "  ") { // checks where non empty pieces are located
            piece_location.first = grid_info[i]->piece_out();
            piece_location.second = i;
            board.push_back(piece_location);
        }
    }
    return board;
}
