//Tay Dzonu - C++ Chess code April 2020
//BoardClass.h - header file initiallising chess_board class

#ifndef CHESS_BOARD
#define CHESS_BOARD

#include <iostream>
#include <string>
#include <memory>

#include "Chess_pieces_class.h"
#include "Title.h"

class chess_board {//chess_board class
    friend std::ostream& operator<<(std::ostream& os, const chess_board& mat); //friend output function to show current state of the board
private:
    std::unique_ptr<chess_pieces>* grid_info{ nullptr }; // 1d array of chesspieces to represent board
    static std::string winner ; // static string to show if someone has one
    static std::string p_to_q;  //static string used when outputting result of pawn becoming a queen
public:
    //Constructors and destructors
    chess_board();    
    chess_board(std::vector<std::pair<std::string, int>> board); //constructor taking in pieces and locations from load function in main.cpp
    ~chess_board() {};    

    // Access functions
    int index(int board_x_pos, int board_y_pos) const; //converts 2d grid position to position in 1d array
    bool is_empty(int board_x_pos, int board_y_pos); // checks if an empty piece is in a given location
    bool right_colour(int board_x_pos, int board_y_pos, std::string colour); // checks if a player is attempting to move a piece of the corresponding colour
    inline std::string piece(int board_x_pos, int board_y_pos) { return grid_info[index(board_x_pos, board_y_pos)]->piece_out(); } //returns piece colour and type at given location
    std::string who_won(); // changes value of winner depending on if someone has won
    inline std::string has_queened() { return p_to_q; } // indicates if pawn has become a queen

    //Functions purely for changing values of static class members
    inline void restart() { winner = " "; } // resets value of winner when another game is played

    //Functions used for moving pieces
    std::vector<std::pair<int, int>>  possible_moves(int board_x_pos, int board_y_pos); // function returns vector of possible moves for a piece in a given location
    bool test_move_here(int board_x_pos_start, int board_y_pos_start, int board_x_pos_end, int board_y_pos_end); // indicates if a piece can move to a location
    std::string move_here_str(int board_x_pos_start, int board_y_pos_start, int board_x_pos_end, int board_y_pos_end); // gives X's used in moves_out function for poassible moves
    void pawn_to_queen(int board_x_pos, int board_y_pos); // changes pawn to a queen once it reaches the other side of the board
    void move_piece(int board_x_pos_start, int board_y_pos_start, int board_x_pos_end, int board_y_pos_end); // function which moves the location of a piece on the board
    void show_moves_out(int board_x_pos, int board_y_pos); // function which displays the chess board with the possible moves for a piece at the given location

    //Save function
    std::vector<std::pair<std::string, int>> save_board(); // saves the location of all remaining non empty pieces in play for use in main.cpp save() function
};

#endif