//Tay Dzonu - C++ Chess code April 2020
//Chess_pieces_class.cpp - cpp file defining chess_pieces class functions

#include "Chess_pieces_class.h"

std::vector<std::vector<std::pair<int, int>>>  empty::move() {//empty piece cannot move ->empty vector
	std::vector<std::vector<std::pair<int, int>>> move_all;
	return move_all;
}

int pawn::direction() {//provides direction pawn can move in depending on colour
	if (colour == "b") { return -1; }
	if (colour == "w") { return 1; }
	else { return 0; }
}
std::vector<std::vector<std::pair<int, int>>>   pawn::move() {//pawn moves: move1 and move2 are for taking pieces, move3 for moving to empty space
	std::vector<std::pair<int, int>> move1;
	std::vector<std::pair<int, int>> move2;
	std::vector<std::pair<int, int>> move3;
	std::pair<int, int> move_temp;
	move_temp.first = direction();
	move_temp.second = 1;
	move2.push_back(move_temp);
	move_temp.second = -1;
	move3.push_back(move_temp);
	move_temp.second = 0;
	move1.push_back(move_temp);
	if (not_moved) { move_temp.first = 2 * direction(); move1.push_back(move_temp); } //adds additional move if the pawn has not moved yet
	std::vector<std::vector<std::pair<int, int>>> move_all;
	move_all.push_back(move1);
	move_all.push_back(move2);
	move_all.push_back(move3);
	return move_all;
}

std::vector<std::vector<std::pair<int, int>>>  rook::move() {//rook moves for horizontal and vertical directions
	std::vector<std::pair<int, int>> move1;
	std::vector<std::pair<int, int>> move2;
	std::vector<std::pair<int, int>> move3;
	std::vector<std::pair<int, int>> move4;
	std::pair<int, int> move_temp; // relative position from start position
	for (int i = 1; i <= 7; i++) { // <= 7 as this is the maximum change in position due to move in an 8x8 board -> repeated in subsequent move functions (except for king)
		move_temp.first = 0; move_temp.second = i; move1.push_back(move_temp);
		move_temp.first = i; move_temp.second = 0; move2.push_back(move_temp);
		move_temp.first = 0; move_temp.second = -i; move3.push_back(move_temp);
		move_temp.first = -i; move_temp.second = 0; move4.push_back(move_temp);
	}
	std::vector<std::vector<std::pair<int, int>>> move_all;
	move_all.push_back(move1);
	move_all.push_back(move2);
	move_all.push_back(move3);
	move_all.push_back(move4);

	return move_all;
}

std::vector<std::vector<std::pair<int, int>>>  knight::move() { //knight moves in L shape : 2 vertical + 1 horzontal, or viceversa. 1 possible move in each direction
	std::vector<std::pair<int, int>> move1;
	std::vector<std::pair<int, int>> move2;
	std::vector<std::pair<int, int>> move3;
	std::vector<std::pair<int, int>> move4;
	std::vector<std::pair<int, int>> move5;
	std::vector<std::pair<int, int>> move6;
	std::vector<std::pair<int, int>> move7;
	std::vector<std::pair<int, int>> move8;
	std::pair<int, int> move_temp;
	move_temp.first = 2; move_temp.second = 1; move1.push_back(move_temp);
	move_temp.first = 2; move_temp.second = -1; move2.push_back(move_temp);
	move_temp.first = -2; move_temp.second = 1; move3.push_back(move_temp);
	move_temp.first = -2; move_temp.second = -1; move4.push_back(move_temp);
	move_temp.first = 1; move_temp.second = 2; move5.push_back(move_temp);
	move_temp.first = 1; move_temp.second = -2; move6.push_back(move_temp);
	move_temp.first = -1; move_temp.second = 2; move7.push_back(move_temp);
	move_temp.first = -1; move_temp.second = -2; move8.push_back(move_temp);
	std::vector<std::vector<std::pair<int, int>>> move_all;
	move_all.push_back(move1);
	move_all.push_back(move2);
	move_all.push_back(move3);
	move_all.push_back(move4);
	move_all.push_back(move5);
	move_all.push_back(move6);
	move_all.push_back(move7);
	move_all.push_back(move8);
	return move_all;
}

std::vector<std::vector<std::pair<int, int>>>  bishop::move() {// bishops move diagonally
	std::vector<std::pair<int, int>> move1;
	std::vector<std::pair<int, int>> move2;
	std::vector<std::pair<int, int>> move3;
	std::vector<std::pair<int, int>> move4;
	std::pair<int, int> move_temp;
	for (int i = 1; i <= 7; i++) {
		move_temp.first = i; move_temp.second = i; move1.push_back(move_temp);
		move_temp.first = i; move_temp.second = -i; move2.push_back(move_temp);
		move_temp.first = -i; move_temp.second = i; move3.push_back(move_temp);
		move_temp.first = -i; move_temp.second = -i; move4.push_back(move_temp);
	}
	std::vector<std::vector<std::pair<int, int>>> move_all;
	move_all.push_back(move1);
	move_all.push_back(move2);
	move_all.push_back(move3);
	move_all.push_back(move4);
	return move_all;
}

std::vector<std::vector<std::pair<int, int>>>  queen::move() {// queens can move horizontally, vertically and diagonally 
	std::vector<std::pair<int, int>> move1;
	std::vector<std::pair<int, int>> move2;
	std::vector<std::pair<int, int>> move3;
	std::vector<std::pair<int, int>> move4;
	std::vector<std::pair<int, int>> move5;
	std::vector<std::pair<int, int>> move6;
	std::vector<std::pair<int, int>> move7;
	std::vector<std::pair<int, int>> move8;
	std::pair<int, int> move_temp;
	for (int i = 1; i <= 7; i++) {
		move_temp.first = i; move_temp.second = i; move1.push_back(move_temp);
		move_temp.first = i; move_temp.second = -i; move2.push_back(move_temp);
		move_temp.first = 0; move_temp.second = i; move3.push_back(move_temp);
		move_temp.first = i; move_temp.second = 0; move4.push_back(move_temp);
		move_temp.first = -i; move_temp.second = i; move5.push_back(move_temp);
		move_temp.first = -i; move_temp.second = -i; move6.push_back(move_temp);
		move_temp.first = 0; move_temp.second = -i; move7.push_back(move_temp);
		move_temp.first = -i; move_temp.second = 0; move8.push_back(move_temp);
	}
	std::vector<std::vector<std::pair<int, int>>> move_all;
	move_all.push_back(move1);
	move_all.push_back(move2);
	move_all.push_back(move3);
	move_all.push_back(move4);
	move_all.push_back(move5);
	move_all.push_back(move6);
	move_all.push_back(move7);
	move_all.push_back(move8);
	return move_all;
}

std::vector<std::vector<std::pair<int, int>>>  king::move() { //kings can move to any adjacent space
	std::vector<std::pair<int, int>> move1;
	std::vector<std::pair<int, int>> move2;
	std::vector<std::pair<int, int>> move3;
	std::vector<std::pair<int, int>> move4;
	std::vector<std::pair<int, int>> move5;
	std::vector<std::pair<int, int>> move6;
	std::vector<std::pair<int, int>> move7;
	std::vector<std::pair<int, int>> move8;
	std::pair<int, int> move_temp;
	move_temp.first = 1; move_temp.second = 1; move1.push_back(move_temp);
	move_temp.first = 1; move_temp.second = -1; move2.push_back(move_temp);
	move_temp.first = 0; move_temp.second = 1; move3.push_back(move_temp);
	move_temp.first = 1; move_temp.second = 0; move4.push_back(move_temp);
	move_temp.first = -1; move_temp.second = 1; move5.push_back(move_temp);
	move_temp.first = -1; move_temp.second = -1; move6.push_back(move_temp);
	move_temp.first = 0; move_temp.second = -1; move7.push_back(move_temp);
	move_temp.first = -1; move_temp.second = 0; move8.push_back(move_temp);
	std::vector<std::vector<std::pair<int, int>>> move_all;
	move_all.push_back(move1);
	move_all.push_back(move2);
	move_all.push_back(move3);
	move_all.push_back(move4);
	move_all.push_back(move5);
	move_all.push_back(move6);
	move_all.push_back(move7);
	move_all.push_back(move8);
	return move_all;
}
