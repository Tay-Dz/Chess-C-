
#ifndef CHESS_PIECES
#define CHESS_PIECES
#include<string>
#include <vector>
#include<utility>

class chess_pieces {
protected:
	std::string colour{};
	std::string piece{};

public:
	~chess_pieces() {};
	virtual std::vector<std::vector<std::pair<int,int>>> move() = 0;
	std::string piece_out() {
		return colour + piece;
	}
	std::string col() { return colour; }
	std::string pic() { return piece; }
	virtual void has_moved() = 0;
};

class empty : public chess_pieces {
private:
public:
	empty() { colour = " "; piece = " "; }
	std::vector<std::vector<std::pair<int, int>>>  move() {
		std::vector<std::vector<std::pair<int, int>>> moves;
		return moves;
	}
	void has_moved() {}

};

class pawn : public chess_pieces {
private:
	bool no_move = 1;
public:
	pawn(std::string b_or_w) {colour = b_or_w; piece = "p";}
	int direction(){
		if (colour == "b") { return -1; }
		if (colour == "w") { return 1; }
		else { return 0; }
	}
	void has_moved() { no_move = 0; }
	std::vector<std::vector<std::pair<int, int>>>   move() {
		std::vector<std::pair<int, int>> move1;
		std::vector<std::pair<int, int>> move2;
		std::vector<std::pair<int, int>> move3;
		std::pair<int, int> movex;
		movex.first = direction();
		movex.second = 1;
		move2.push_back(movex); 
		movex.second = -1;
		move3.push_back(movex);
		movex.second = 0;
		move1.push_back(movex);
		if (no_move) { movex.first = 2*direction(); move1.push_back(movex); }
		std::vector<std::vector<std::pair<int, int>>> move_tot;
		move_tot.push_back(move1);
		move_tot.push_back(move2);
		move_tot.push_back(move3);
		return move_tot;
	}

};

class rook : public chess_pieces {
public:
	rook(std::string b_or_w) { colour = b_or_w; piece = "r"; }
	std::vector<std::vector<std::pair<int, int>>>  move() {
		std::vector<std::pair<int, int>> move1;
		std::vector<std::pair<int, int>> move2;
		std::vector<std::pair<int, int>> move3;
		std::vector<std::pair<int, int>> move4;
		std::pair<int, int> movex;
		for (int i = 1; i <= 7; i++) {
			movex.first = 0; movex.second = i; move1.push_back(movex);
			movex.first = i; movex.second = 0; move2.push_back(movex);
			movex.first = 0; movex.second = -i; move3.push_back(movex);
			movex.first = -i; movex.second = 0; move4.push_back(movex);
		}
		std::vector<std::vector<std::pair<int, int>>> moves;
		moves.push_back(move1);
		moves.push_back(move2);
		moves.push_back(move3);
		moves.push_back(move4);

		return moves;
	}
	void has_moved() {}

};

class knight : public chess_pieces {
public:
	knight(std::string b_or_w) { colour = b_or_w; piece = "n"; }
	std::vector<std::vector<std::pair<int, int>>>  move() {
		std::vector<std::pair<int, int>> move1;
		std::vector<std::pair<int, int>> move2;
		std::vector<std::pair<int, int>> move3;
		std::vector<std::pair<int, int>> move4;
		std::vector<std::pair<int, int>> move5;
		std::vector<std::pair<int, int>> move6;
		std::vector<std::pair<int, int>> move7;
		std::vector<std::pair<int, int>> move8;
		std::pair<int, int> movex;
		movex.first = 2; movex.second = 1; move1.push_back(movex);
		movex.first = 2; movex.second = -1; move2.push_back(movex);
		movex.first = -2; movex.second = 1; move3.push_back(movex);
		movex.first = -2; movex.second = -1; move4.push_back(movex);
		movex.first = 1; movex.second = 2; move5.push_back(movex);
		movex.first = 1; movex.second = -2; move6.push_back(movex);
		movex.first = -1; movex.second = 2; move7.push_back(movex);
		movex.first = -1; movex.second = -2; move8.push_back(movex);
		std::vector<std::vector<std::pair<int, int>>> moves;
		moves.push_back(move1);
		moves.push_back(move2);
		moves.push_back(move3);
		moves.push_back(move4);
		moves.push_back(move5);
		moves.push_back(move6);
		moves.push_back(move7);
		moves.push_back(move8);
		return moves;
	}
	void has_moved() {}

};

class bishop : public chess_pieces {
public:
	bishop(std::string b_or_w) { colour = b_or_w; piece = "b"; }
	std::vector<std::vector<std::pair<int, int>>>  move() {
		std::vector<std::pair<int, int>> move1;
		std::vector<std::pair<int, int>> move2;
		std::vector<std::pair<int, int>> move3;
		std::vector<std::pair<int, int>> move4;
		std::pair<int, int> movex;
		for (int i = 1; i <= 7; i++) {
			movex.first = i; movex.second = i; move1.push_back(movex);
			movex.first = i; movex.second = -i; move2.push_back(movex);
			movex.first = -i; movex.second = i; move3.push_back(movex);
			movex.first = -i; movex.second = -i; move4.push_back(movex);
		}
		std::vector<std::vector<std::pair<int, int>>> moves;
		moves.push_back(move1);
		moves.push_back(move2);
		moves.push_back(move3);
		moves.push_back(move4);
		return moves;
	}
	void has_moved() {}

};

class queen : public chess_pieces {
public:
	queen(std::string b_or_w) { colour = b_or_w; piece = "q"; }
	std::vector<std::vector<std::pair<int, int>>>  move() {
		std::vector<std::pair<int, int>> move1;
		std::vector<std::pair<int, int>> move2;
		std::vector<std::pair<int, int>> move3;
		std::vector<std::pair<int, int>> move4;
		std::vector<std::pair<int, int>> move5;
		std::vector<std::pair<int, int>> move6;
		std::vector<std::pair<int, int>> move7;
		std::vector<std::pair<int, int>> move8;
		std::pair<int, int> movex;
		for (int i = 1; i <= 7; i++) {
			movex.first = i; movex.second = i; move1.push_back(movex);
			movex.first = i; movex.second = -i; move2.push_back(movex);
			movex.first = 0; movex.second = i; move3.push_back(movex);
			movex.first = i; movex.second = 0; move4.push_back(movex);
			movex.first = -i; movex.second = i; move5.push_back(movex);
			movex.first = -i; movex.second = -i; move6.push_back(movex);
			movex.first = 0; movex.second = -i; move7.push_back(movex);
			movex.first = -i; movex.second = 0; move8.push_back(movex);
		}
		std::vector<std::vector<std::pair<int, int>>> moves;
		moves.push_back(move1);
		moves.push_back(move2);
		moves.push_back(move3);
		moves.push_back(move4);
		moves.push_back(move5);
		moves.push_back(move6);
		moves.push_back(move7);
		moves.push_back(move8);
		return moves;
	}
	void has_moved() {}

};

class king : public chess_pieces {
public:
	king(std::string b_or_w) { colour = b_or_w; piece = "k"; }
	std::vector<std::vector<std::pair<int, int>>>  move() {
		std::vector<std::pair<int, int>> move1;
		std::vector<std::pair<int, int>> move2;
		std::vector<std::pair<int, int>> move3;
		std::vector<std::pair<int, int>> move4;
		std::vector<std::pair<int, int>> move5;
		std::vector<std::pair<int, int>> move6;
		std::vector<std::pair<int, int>> move7;
		std::vector<std::pair<int, int>> move8;
		std::pair<int, int> movex;
		movex.first = 1; movex.second = 1; move1.push_back(movex);
		movex.first = 1; movex.second = -1; move2.push_back(movex);
		movex.first = 0; movex.second = 1; move3.push_back(movex);
		movex.first = 1; movex.second = 0; move4.push_back(movex);
		movex.first = -1; movex.second = 1; move5.push_back(movex);
		movex.first = -1; movex.second = -1; move6.push_back(movex);
		movex.first = 0; movex.second = -1; move7.push_back(movex);
		movex.first = -1; movex.second = 0; move8.push_back(movex);
		std::vector<std::vector<std::pair<int, int>>> moves;
		moves.push_back(move1);
		moves.push_back(move2);
		moves.push_back(move3);
		moves.push_back(move4);
		moves.push_back(move5);
		moves.push_back(move6);
		moves.push_back(move7);
		moves.push_back(move8);
		return moves;
	}
	void has_moved() {}

};
#endif