
#include "Matrix_Class.h"

int grid_to_int(char grid_pos) {
	if (grid_pos == 'a' ||grid_pos== 'A') { return 1; }
	else if (grid_pos == 'b' || grid_pos == 'B') { return 2; }
	else if (grid_pos == 'c' || grid_pos == 'C') { return 3; }
	else if (grid_pos == 'd' || grid_pos == 'D') { return 4; }
	else if (grid_pos == 'e' || grid_pos == 'E') { return 5; }
	else if (grid_pos == 'f' || grid_pos == 'F') { return 6; }
	else if (grid_pos == 'g' || grid_pos == 'G') { return 7; }
	else if (grid_pos == 'h' || grid_pos == 'H') { return 8; }
	else { return 0; }
}
void help() { std::cout << "help" << std::endl; } //Write help 

std::pair<int,int> choose_piece(std::string go, matrix board) {
	std::pair<int, int> initial_pos;
	bool can_move = false;
	char grid_in;
	while (!can_move) {
		std::cin.clear();
		std::cout << "Please enter the row and column of the piece would you like to move, or R for the rules and help." << std::endl;
		std::cin >> grid_in;
		if (grid_in == 'r' || grid_in == 'R') { help(); }
		else {
			std::cin >> initial_pos.second;
			try { initial_pos.first = grid_to_int(grid_in); }
			catch (int wrong_input) { initial_pos.first = 0; }
			if (initial_pos.first < 1 || initial_pos.first > 8 || initial_pos.second < 1 || initial_pos.second > 8||std::cin.fail()) {
				std::cout << "This position is not loacated on the board. please select a row between A and H, and colomn between 1 and 8" << std::endl;
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
	}
	return initial_pos;
}
void move_piece(std::string go, matrix board, std::pair<int, int> start) {
	std::pair<int, int> end;
	board.moves_out(start.first, start.second);
	std::cout << "It is " << go << "'s turn." << std::endl;
	char grid_in;
	bool possible_move = false;
	std::cout << "Your possible moves are shown by the X's. Where would you like to move?"<<std::endl;
	while (!possible_move) {
		std::cin.clear();
		std::cin >> grid_in;
		if (grid_in == 'r' || grid_in == 'R') { help(); }
		else {
			std::cin >> end.second;
			try { end.first = grid_to_int(grid_in); }
			catch (int wrong_input) { end.first = 0; }
			if (!board.move_here(start.first, start.second, end.first, end.second) || std::cin.fail()) {
				std::cout << "This move is not valid. Please select a valid move shown by the X's." << std::endl;
			}
			else { possible_move = true; }
		}
	}
	board.move_piece(start.first, start.second, end.first, end.second);
	std::cout << board;
	std::cout <<go<< " moved from " << int_to_grid(start.first) << " " << start.second << " to " << int_to_grid(end.first) << " " << end.second << std::endl;
	std::cout << board.has_queened();

}
std::string turn(std::string go, matrix board) {
	std::cout << "It is " << go << "'s turn." << std::endl;
	std::pair<int, int> start = choose_piece(go, board);
	move_piece(go, board, start);
	if (go == "White") { return "Black"; }
	else { return "White"; }
}
/*std::pair<matrix, std::string> */void load() {}
bool another_game() {
	std::string yes_no;
	while (yes_no != "y" && yes_no != "Y" && yes_no != "N" && yes_no != "n") {
		std::cin.clear();
		std::cout << "Do you want to play another game?  Type y for yes or n for no." << std::endl;
		std::cin >> yes_no;
	}
	if (yes_no != "y" || yes_no != "Y") { return true; }
	if (yes_no != "n" || yes_no != "N") { return false; }
	else { return false; }

}

void save() {}
std::pair<matrix,std::string> start() {
	system("CLS");
	title();
	std::pair<matrix, std::string> board_turn;
	std::string play_or_help;
	std::string new_or_load;
	bool play = 0;
	while (!play) {
		std::cout << "Welcome to Chess in C++. For the how to play and help press [h]. To play a game please press [p].";
		std::cin >> play_or_help;
		if (play_or_help == "h") { help(); }
		else {
			play = 1;
		}
	}
	std::cout << "Would you like to start a new game [n] or load a saved game [l]?";
	std::cin >> new_or_load;
	if (new_or_load == "l") { load(); matrix chessboard; board_turn.first = chessboard; board_turn.second = "Black"; return board_turn;}
	else { matrix chessboard; board_turn.first = chessboard; board_turn.second = "White"; return board_turn; }
}

void play_game(matrix board, std::string start) {
	std::cout << board;
	std::string whos_go = start;
	std::string winner =" ";
	while (winner == " ") {
		whos_go =turn(whos_go, board);
		winner = board.who_won();
	}
	std::cout << "Congratulations " << board.who_won() << " has won" << std::endl;
}

int main() 
{
	bool play_again = true;
	while (play_again){
	std::pair<matrix, std::string> chessboard_first = start();
	play_game(chessboard_first.first,chessboard_first.second);
	play_again = another_game();
	}
	return 0;
}