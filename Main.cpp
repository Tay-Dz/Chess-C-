
#include "Matrix_Class.h"
std::pair<int,int> choose_piece(std::string go, matrix board) {
	std::pair<int, int> initial_pos;
	bool can_move = false;
	while (!can_move) {
		std::cout << "Please enter the row and column of the piece would you like to move" << std::endl;
		std::cin >> initial_pos.first >> initial_pos.second;
		if (initial_pos.first < 1 || initial_pos.first > 8 || initial_pos.second < 1 || initial_pos.second > 8) {
			std::cout << "This position is not loacated on the board. please select both a row and colomn between 1 and 8" << std::endl;
		}
		else if (board.is_empty(initial_pos.first, initial_pos.second)) {
			std::cout << "There are no pieces located here. Please select another position." << std::endl;
		}
		else if (!board.right_colour(initial_pos.first, initial_pos.second, go)) {
			std::cout << "You have selected a piece of the whong colour. please select a " << go << " piece." << std::endl;
		}
		else if (board.possible_moves(initial_pos.first, initial_pos.second).empty()) {
			std::cout << "This piece has no possible moves. Please select another piece." << std::endl;
		}
		else { can_move = true; }
	}
	return initial_pos;
}
void move_piece(std::string go, matrix board, std::pair<int, int> start) {
	std::pair<int, int> end;
	board.moves_out(start.first, start.second);
	std::cout << "It is " << go << "'s turn." << std::endl;
	bool possible_move = false;
	while (!possible_move) {
		std::cout << "Your possible moves are shown by the X's. Where would you like to move?"<<std::endl;
		std::cin >> end.first >> end.second;
		if (!board.move_here(start.first, start.second, end.first, end.second)) {
			std::cout << "This move is not valid. Please select a valid move shown by the X's."<<std::endl;
		}
		else { possible_move = true; }
	}
	board.move_piece(start.first, start.second, end.first, end.second);
	std::cout << board;
	std::cout <<go<< " moved from " << start.first << "," << start.second << " to " << end.first << " , " << end.second << std::endl;

}
std::string turn(std::string go, matrix board) {
	std::cout << "It is " << go << "'s turn." << std::endl;
	std::pair<int, int> start = choose_piece(go, board);
	move_piece(go, board, start);
	if (go == "White") { return "Black"; }
	else { return "White"; }
}

void help() {}
void save() {}
void start(){}
void load() {}


int main() 
{
	title();
	matrix chessboard;
	std::cout << chessboard.move_here_str(2, 2, 3, 2)<<std::endl;
	std::cout << chessboard.move_here_str(2, 2, 4, 2) << std::endl;
	std::cout << chessboard.move_here_str(2, 2, 5, 2) << std::endl;

	int x = 2;
	std::string whos_go = "White";
	std::cout << chessboard;
	while (x == 2) {
		whos_go =turn(whos_go, chessboard);
	}
	return 0;
}