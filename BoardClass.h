//Tay Dzonu - C++ Chess code April 2020
//BoardClass.h - header file initiallising chess_board class

#ifndef CHESS_BOARD
#define CHESS_BOARD

#include<iostream>
#include<string>
#include"Chess_pieces_class.h"

class chess_board {//chess_board class
    friend std::ostream& operator<<(std::ostream& os, const chess_board& mat); //friend output function to show current state of the board
private:
    std::unique_ptr<chess_pieces>* matrix_data{ nullptr }; // 1d array of chesspieces to represent board
    static std::string winner ; // static string to show if someone has one
    static std::string p_to_q;  //static string used when outputting result of pawn becoming a queen
public:
    //Constructors and destructors
    chess_board();    
    chess_board(std::vector<std::pair<std::string, int>> board); //constructor taking in pieces and locations from load function in main.cpp
    ~chess_board() {};    

    // Access functions
    int index(int m, int n) const; //converts 2d grid position to position in 1d array
    bool is_empty(int x, int y); // checks if an empty piece is in a given location
    bool right_colour(int x, int y, std::string colour); // checks if a player is attempting to move a piece of the corresponding colour
    inline std::string piece(int x, int y) { return matrix_data[index(x, y)]->piece_out(); } //returns piece colour and type at given location
    std::string who_won(); // changes value of winner depending on if someone has won

    //Functions purely for changing values of static class members
    inline std::string has_queened() { return p_to_q; } // indicates if pawn has become a queen
    inline void restart() { winner = " "; } // resets value of winner when another game is played

    //Functions used for moving pieces
    std::vector<std::pair<int, int>>  possible_moves(int i, int j); // function returns vector of possible moves for a piece in a given location
    bool test_move_here(int i, int j, int x, int y); // indicates if a piece can move to a location
    std::string move_here_str(int i, int j, int x, int y); // gives X's used in moves_out function for poassible moves
    void pawn_to_queen(int i, int j); // changes pawn to a queen once it reaches the other side of the board
    void move_piece(int m, int n, int p, int q); // function which moves the location of a piece on the board
    void show_moves_out(int x, int y); // function which displays the chess board with the possible moves for a piece at the given location

    //Save function
    std::vector<std::pair<std::string, int>> save_board(); // saves the location of all remaining non empty pieces in play for use in main.cpp save() function
};

#endif