//Tay Dzonu - C++ Chess code April 2020
//Chess_pieces_class.h - header file initiallising chess_pieces class and inherited classes
#ifndef CHESS_PIECES
#define CHESS_PIECES

#include <string>
#include <vector>
#include <utility>

class chess_pieces { //Abstract base class for chess pieces
protected:
	//strings to contain piece colour and type
	std::string colour{};
	std::string piece{};

public:
	~chess_pieces() {};
	virtual std::vector<std::vector<std::pair<int,int>>> move() = 0; //virtual function for list of moves : vector of directions -> vector of relative positions in given direction
	// accessor functions to return colour piece and combination
	inline std::string piece_out() {return colour + piece;}
	inline std::string col() { return colour; }
	inline std::string pic() { return piece; }
	virtual void has_moved() = 0; // virtual void to see if a piece has moved : only required by pawn
};

class empty : public chess_pieces { //derived class for empty piece from chess pieces : placed in the board when no other pieces are located there
public:
	inline empty() { colour = " "; piece = " "; }
	std::vector<std::vector<std::pair<int, int>>>  move();
	void has_moved() {}
};

class pawn : public chess_pieces {//derived class for pawn piece from chess pieces
private:
	bool not_moved = true; // bool to see if the pawn has moved
public:
	inline pawn(std::string b_or_w) {colour = b_or_w; piece = "p";} //constructor which takes in piece colour to produce a piece of given coulour and piece type -> repeated in other derived classes
	int direction(); // direction function as pawns can only move in one direction depending on colour
	inline void has_moved() { not_moved = false; } // change value of not_moved once the pawn has moved
	std::vector<std::vector<std::pair<int, int>>>   move();
};

class rook : public chess_pieces {//derived class for rook piece from chess pieces
public:
	inline rook(std::string b_or_w) { colour = b_or_w; piece = "r"; }
	std::vector<std::vector<std::pair<int, int>>>  move();
	inline void has_moved() {}
};

class knight : public chess_pieces {//derived class for knight piece from chess pieces
public:
	inline knight(std::string b_or_w) { colour = b_or_w; piece = "n"; } // pieces is given as "n" to differentiate from king
	std::vector<std::vector<std::pair<int, int>>>  move();
	inline void has_moved() {}
};

class bishop : public chess_pieces {//derived class for bishop piece from chess pieces
public:
	inline bishop(std::string b_or_w) { colour = b_or_w; piece = "b"; }
	std::vector<std::vector<std::pair<int, int>>>  move();
	inline void has_moved() {}
};

class queen : public chess_pieces {//derived class for queen piece from chess pieces
public:
	inline queen(std::string b_or_w) { colour = b_or_w; piece = "q"; }
	std::vector<std::vector<std::pair<int, int>>>  move();
	inline void has_moved() {}
};

class king : public chess_pieces {//derived class for king piece from chess pieces
public:
	inline king(std::string b_or_w) { colour = b_or_w; piece = "k"; }
	std::vector<std::vector<std::pair<int, int>>>  move();
	inline void has_moved() {}
};

#endif