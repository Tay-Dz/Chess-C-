
#include<fstream>
#include<iomanip>
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
void save(std::string go, matrix board) {
	std::string file_name;
	std::cout << "You have selected to save your game. Please enter a file name to save your game as." << std::endl;
	std::cin >> file_name;
	file_name = file_name + ".txt";
	std::vector<std::pair<std::string, int>> saved_board = board.save_board();
	std::ofstream save_file{ file_name };
	save_file << go << std::endl;
	for (size_t i = 0; i < saved_board.size(); i++) {
		save_file << saved_board[i].first << saved_board[i].second;
		if (i != saved_board.size() - 1) { save_file << std::endl; }
		else{}
	}
	save_file.close();
	std::cout << "Your game has been saved as " << file_name<<"."<<std::endl;
	std::ofstream file_name_list("save_files.txt", std::ios::app);
	file_name_list << std::endl << file_name;
	file_name_list.close();
	exit(EXIT_SUCCESS);
}

std::pair<int,int> choose_piece(std::string go, matrix board) {
	std::pair<int, int> initial_pos;
	bool can_move = false;
	char grid_in;
	while (!can_move) {
		std::cin.clear();
		std::cout << "Please enter the row and column of the piece would you like to move, or R for the rules and help or S to save game." << std::endl;
		std::cin >> grid_in;
		if (grid_in == 'r' || grid_in == 'R') { help(); }
		else if (grid_in == 's' || grid_in == 'S') { save(go,board); }
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
	std::cout << "Your possible moves are shown by the X's. Where would you like to move? Or press R for help or S to save game."<<std::endl;
	while (!possible_move) {
		std::cin.clear();
		std::cin >> grid_in;
		if (grid_in == 'r' || grid_in == 'R') { help(); }
		else if (grid_in == 's' || grid_in == 'S') { save(go, board); }
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
std::pair<matrix, std::string>  load() {
	std::pair<matrix, std::string> load_game;
	std::vector<std::string> file_names;
	std::string entry;
	int list_number = 0;
	int file_number;
	bool file_opened = false;
	std::cout << " You have selected to load a saved game file. The saved game files available are:" << std::endl;
	std::ifstream save_file_names{ "save_files.txt" };
	if (!save_file_names.good()) {
		std::cerr << std::endl << "Error: file could not be opened" << std::endl
			<<"New game will be played instead"<<std::endl;
		matrix chessboard; load_game.first = chessboard; load_game.second = "White"; return load_game;
	}
	while (!save_file_names.eof()) {
		list_number++;
		std::getline(save_file_names, entry);
		file_names.push_back(entry);
		std::cout <<"["<<list_number<<"] "<< entry << std::endl;
	}
	save_file_names.close();
	while (!file_opened) {
		std::cout << std::endl << "Please enter which file number you like to open or 0 to play a new game?" << std::endl;
		std::cin >> file_number;
		if (std::cin.fail() || file_number<0 || file_number>list_number) {
			std::cout << "Input was invalid. Please enter a number between 1 and " << list_number << "." << std::endl;
		}
		else {
			if(file_number==0){ matrix chessboard; load_game.first = chessboard; load_game.second = "White"; return load_game; }
			else {
				std::ifstream board_file{ file_names[file_number - 1] };
				if (!board_file.good()) {
					std::cerr << std::endl << "Error: file could not be opened" << std::endl
						<< "Plese choose another file" << std::endl;
					continue;
				}
				else {
					std::getline(board_file, load_game.second);
					if (load_game.second != "White" && load_game.second != "Black") {
						std::cout << "File is corrupted. Please select another file.1" << std::endl;
						board_file.close();
						continue;
					}
					else {
						std::vector<std::pair<std::string, int>> board_input;
						std::string piece_info;
						std::pair<std::string, int> piece_info_pair;
						std::string location_str;
						bool working = true;
						while (!board_file.eof()&&working) {
							std::getline(board_file, piece_info);
							piece_info_pair.first = piece_info.substr(0,2);
							if (piece_info_pair.first != "bp" && piece_info_pair.first != "wp" && piece_info_pair.first != "br" && piece_info_pair.first != "wr" && piece_info_pair.first != "bb" && piece_info_pair.first != "wb" && piece_info_pair.first != "bn" && piece_info_pair.first != "wn" && piece_info_pair.first != "bq" && piece_info_pair.first != "wq" && piece_info_pair.first != "bk" && piece_info_pair.first != "wk") {
								std::cout << "File is corrupted. Please select another file.2" << std::endl;
								board_file.close();
								working = false;
								continue;
							}
							else {
								location_str = piece_info.substr(2, 2);
								try {
									piece_info_pair.second = std::stod(location_str);
									if (piece_info_pair.second < 0 || piece_info_pair.second >= 64) {
										std::cout << "File is corrupted. Please select another file.3" << std::endl;
										board_file.close();
										working = false;
										continue;
									}
									else {}
								}
								catch (int exception) {
									std::cout << "File is corrupted. Please select another file.4" << std::endl;
									board_file.close();
									working = false;
									continue;
								}
							} 
							board_input.push_back(piece_info_pair);
							file_opened = true;
						}
						if (working) { board_file.close();
							load_game.first = matrix(board_input);
							return load_game; }
						else { continue; }
					}
				}
			}
		}
	}
}
bool another_game(matrix board) {
	std::string yes_no;
	while (yes_no != "y" && yes_no != "Y" && yes_no != "N" && yes_no != "n") {
		std::cin.clear();
		std::cout << "Do you want to play another game?  Type y for yes or n for no." << std::endl;
		std::cin >> yes_no;
	}
	if (yes_no == "y" || yes_no == "Y") { board.restart(); return true; }
	else if (yes_no == "n" || yes_no == "N") { return false; }
	else { return false; }

}

std::pair<matrix,std::string> start() {
	system("CLS");
	title();
	std::pair<matrix, std::string> board_turn;
	std::string play_or_help;
	std::string new_or_load;
	bool game_start = false;
	bool play = 0;
	std::cout << "Welcome to Chess in C++. For the rules how to play and help press [R]. To play a game please press [P].";
	while (!play) {
		std::cin >> play_or_help;
		if (play_or_help == "r"||play_or_help=="R") { help(); std::cout << "Welcome to Chess in C++. For the rules how to play and help press [R]. To play a game please press [P].";}
		else if(play_or_help =="p"||play_or_help =="P"){play = 1;}
		else { std::cout << "Input is invalid. Please enter [R] to get rules and help or [P] to play a game." << std::endl; }
	}
	std::cout << "Would you like to start a new game [N] or load a saved game [L]?";
	while (!game_start) {
		std::cin >> new_or_load;
		if (new_or_load == "l" || new_or_load == "L") { return load(); }
		else if (new_or_load == "n" || new_or_load == "N") { matrix chessboard; board_turn.first = chessboard; board_turn.second = "White"; return board_turn; }
		else { std::cout << "Input is invalid. Please enter [N] to start a new game or [L] to load a game." << std::endl; }
	}
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

int main() {
	bool play_again = true;
	while (play_again==true){
	std::pair<matrix, std::string> chessboard_first = start();
	play_game(chessboard_first.first,chessboard_first.second);
	play_again = another_game(chessboard_first.first);
	}
	std::cout << std::endl << "Thank you for playing!" << std::endl;
	return 0;
}