//Tay Dzonu - C++ Chess code April 2020
// Main.cpp - cpp file containing the main code to run the chess game and defining all functions required
#include<fstream>
#include<iomanip>
#include "BoardClass.h"
#include"Title.h"

//basic functions: changing between variables and commonly used outputs
int grid_to_int(char grid_pos) { // converts grid position letter into the corresponding integer 
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
void help() { //function to output help info
	std::cout <<std::endl<< "BASIC RULES:" << std::endl; 
	std::cout << "Each player takes turns moving one piece at a time, with white always taking the first move." << std::endl;
	std::cout << "The aim of the game is to capture the opposing players king. the first to do so wins." << std::endl << std::endl;

	std::cout << "BOARD LAYOUT:" << std::endl;
	std::cout << "The chess board is an 8x8 grid. With the white pieces initially at the top two rows and the black pieces on the bottom two rows." << std::endl;
	std::cout << "Each grid position is denoted by a letter and number, e.g A5. These values are shown on the outer edge of the board." << std::endl;
	std::cout << "Each piece is donoted by two letters. The first letter is either a B or W. This corresponds to whos the piece belongs to." << std::endl;
	std::cout << "The second letter denotes the type of piece it is. This list will be denoted in the PIECE MOVES section." << std::endl;
	std::cout << "Once you have selected a piece to move, the possible moves are denoted by X's located on the grid." << std::endl << std::endl;
	
	std::cout << "PIECE MOVES:" << std::endl;
	std::cout << "Pawn   [p]: Can move forwards into an empty space.They can move up to 2 spaces on their first move and only one move on subsequent moves." << std::endl;
	std::cout << "            To take pieces they must attck diagonally." << std::endl;
	std::cout << "            When reaching the opposite side of the board they are converted into a queen." << std::endl;
	std::cout << "Rook   [r]: Can only move horizontally and vertically." << std::endl;
	std::cout << "Bishop [b]: Can only move diagonally." << std::endl;
	std::cout << "Knight [n]: Can move in an L-shape (2 moves verically and one horizontally or viceversa). They can jump over other pieces." << std::endl;
	std::cout << "Queen  [q]: Can move horizontally, vertiaclly and diagonally." << std::endl;
	std::cout << "King   [k]: Can move to an horizontally, vertiaclly and diagonally adjacent space. " << std::endl;
	std::cout << "            The game is complete once one of the kings has been taken." << std::endl<<std::endl;
	std::cout << "Press [enter] to continue." << std::endl;
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	char end;
	while(std::cin.get() != '\n') { //allows program to continue when enter is presses
		std::cin >> end; }
	std::cout<<std::endl;
} //Write help 
void cout_go(std::string go){ std::cout << "It is " << go << "'s turn." << std::endl; } // function which outputs whos go it currently is

//functions for saving and loading games
void save(std::string go, chess_board board) { // function to save current state of board into save file
	std::string file_name;
	std::cout << "You have selected to save your game. Please enter a file name to save your game as." << std::endl;
	std::cin >> file_name; // takes in desired name for save file
	file_name = file_name + ".txt";
	std::vector<std::pair<std::string, int>> saved_board = board.save_board(); // takes in info for all remaining pieces for the chess board
	std::ofstream save_file{ file_name };
	save_file << go << std::endl; // outputs whos go is next into save file
	for (auto it = saved_board.begin(); it != saved_board.end(); it++) {//iterator to output piece info into file
		save_file << it->first << it->second; 
		if (it != saved_board.end() - 1) { save_file << std::endl; }
		else{}
	}
	save_file.close();
	std::cout << "Your game has been saved as " << file_name<<"."<<std::endl;
	std::ofstream file_name_list("save_files.txt", std::ios::app); //opens the file with save game names at the end of the file
	file_name_list << std::endl << file_name; // adds save file name to list
	file_name_list.close();
	exit(EXIT_SUCCESS); //ends program
}
std::pair<chess_board, std::string>  load() { // function to load a game info from a save file
	std::pair<chess_board, std::string> load_game;
	std::vector<std::string> file_names;
	std::string entry;
	int list_number = 0;
	int file_number;
	bool file_opened = false;
	std::cout << " You have selected to load a saved game file. The saved game files available are:" << std::endl;
	std::ifstream save_file_names{ "save_files.txt" }; // opens file with save game file names
	if (!save_file_names.good()) { // checks if it can be opened
		std::cerr << std::endl << "Error: file could not be opened" << std::endl
			<<"New game will be played instead"<<std::endl;
		chess_board chessboard; load_game.first = chessboard; load_game.second = "White"; return load_game; //returns new game if file isnt found
	}
	std::getline(save_file_names, entry);
	while (!save_file_names.eof()) {
		list_number++;
		std::getline(save_file_names, entry); // gets the save file name
		file_names.push_back(entry);
		std::cout <<"["<<list_number<<"] "<< entry << std::endl; //shows user save files
	}
	save_file_names.close();
	while (!file_opened) { // loops until a file has been sucessfully opened
		std::cout << std::endl << "Please enter which file number you like to open or 0 to play a new game?" << std::endl;
		std::cin >> file_number;
		if (std::cin.fail() || file_number<0 || file_number>list_number) { // checks if a valid input has been entered
			std::cout << "Input was invalid. Please enter a number between 1 and " << list_number << "." << std::endl;
		}
		else {
			if(file_number==0){ chess_board chessboard; load_game.first = chessboard; load_game.second = "White"; return load_game; } // returns new game if player decides not to open load game
			else {
				std::ifstream board_file{ file_names[file_number - 1] }; // opens chosen file
				if (!board_file.good()) { //checks if file can be opened
					std::cerr << std::endl << "Error: file could not be opened" << std::endl
						<< "Plese choose another file" << std::endl;
					continue;
				}
				else {
					std::getline(board_file, load_game.second);
					if (load_game.second != "White" && load_game.second != "Black") {//finds whos go is next from first line of save file
						std::cout << "File is corrupted. Please select another file." << std::endl;
						board_file.close();
						continue;
					}
					else {
						std::vector<std::pair<std::string, int>> board_input;
						std::string piece_info;
						std::pair<std::string, int> piece_info_pair;
						std::string location_str;
						bool working = true;
						while (!board_file.eof()&&working) {//loop until the end of the file has been reached
							std::getline(board_file, piece_info);//gets info
							piece_info_pair.first = piece_info.substr(0,2); // takes first two characters for piece type
							if (piece_info_pair.first != "bp" && piece_info_pair.first != "wp" && piece_info_pair.first != "br" && piece_info_pair.first != "wr" && piece_info_pair.first != "bb" && piece_info_pair.first != "wb" && piece_info_pair.first != "bn" && piece_info_pair.first != "wn" && piece_info_pair.first != "bq" && piece_info_pair.first != "wq" && piece_info_pair.first != "bk" && piece_info_pair.first != "wk") {
								std::cout << "File is corrupted. Please select another file." << std::endl; // checks if piece type is valid
								board_file.close(); // closes file and returns to start of loop so another file can be chosen
								working = false;
								continue;
							}
							else {
								location_str = piece_info.substr(2, 2);// takes the 3rd and 4th character for location
								try {
									piece_info_pair.second = std::stoi(location_str); //attempts to convert string to integer
									if (piece_info_pair.second < 0 || piece_info_pair.second >= 64) { // checks if location is on the board or not
										std::cout << "File is corrupted. Please select another file." << std::endl;
										board_file.close();// closes file and returns to start of loop so another file can be chosen
										working = false;
										continue;
									}
									else {}
								}
								catch (int exception) { // return to file selection if conversion is not possible
									(void)exception;
									std::cout << "File is corrupted. Please select another file." << std::endl;
									board_file.close();
									working = false;
									continue;
								}
							} 
							board_input.push_back(piece_info_pair); // saves piece info
							file_opened = true;
						}
						if (working) { board_file.close();
							load_game.first = chess_board(board_input); //cretes a chess board from the load data
							return load_game; 
						}
						else { continue; }
					}
				}
			}
		}
	}
}

// functions required for each players turn
std::pair<int,int> choose_piece(std::string go, chess_board board) { // function to allow the player to select which piece they want to move -> outpus location into an integer pair
	std::pair<int, int> initial_pos;
	bool can_move = false;
	char grid_in;
	while (!can_move) { // while loop until a piece that can move is chosen
		std::cin.clear();
		std::cout << "Please enter the row and column of the piece would you like to move, or R for the rules and help or S to save game." << std::endl;
		std::cin >> grid_in;
		if (grid_in == 'r' || grid_in == 'R') { help(); } // shows the help function info
		else if (grid_in == 's' || grid_in == 'S') { save(go,board); } // saves the game
		else {
			std::cin >> initial_pos.second;
			try { initial_pos.first = grid_to_int(grid_in); } // checks if initial grid position character is valid and converts to an integer if it is
			catch (int wrong_input) { initial_pos.first = 0; (void) wrong_input; } // returns 0 if not possible
			if (initial_pos.first < 1 || initial_pos.first > 8 || initial_pos.second < 1 || initial_pos.second > 8||std::cin.fail()) { //checks if position is on the board
				std::cout << "This position is not loacated on the board. please select a row between A and H, and colomn between 1 and 8" << std::endl;
			}
			else if (board.is_empty(initial_pos.first, initial_pos.second)) { // check if the chosen position is empty
				std::cout << "There are no pieces located here. Please select another position." << std::endl;
			}
			else if (!board.right_colour(initial_pos.first, initial_pos.second, go)) { // checks if theuser has selected a piece of the right colour
				std::cout << "You have selected a piece of the whong colour. please select a " << go << " piece." << std::endl;
			}
			else if (board.possible_moves(initial_pos.first, initial_pos.second).empty()) { // checks if the piece has any posssible moves
				std::cout << "This piece has no possible moves. Please select another piece." << std::endl;
			}
			else { can_move = true; } // ends loop if valid position has been chosen
		}
	}
	return initial_pos;
}
std::pair<int, int> move_piece(std::string go, chess_board board, std::pair<int, int> start) { //function to move the piece chosen to a valid position
	std::pair<int, int> end;
	board.show_moves_out(start.first, start.second); // outputs possible moves
	cout_go(go);
	char grid_in;
	bool possible_move = false;
	std::cout << "Your possible moves are shown by the X's. Where would you like to move? Or press U to change piece, R for help or S to save game."<<std::endl;
	while (!possible_move) { // loop until a valid move has been chosen
		std::cin.clear();
		std::cin >> grid_in;
		if (grid_in == 'u' || grid_in == 'U') { return start; } // Checks if the player wants to change which piece they wan to move
		else if (grid_in == 'r' || grid_in == 'R') { help(); } // show help
		else if (grid_in == 's' || grid_in == 'S') { save(go, board); } // save game
		else {
			std::cin >> end.second;
			try { end.first = grid_to_int(grid_in); }
			catch (int wrong_input) { end.first = 0; (void)wrong_input;}
			if (!board.test_move_here(start.first, start.second, end.first, end.second) || std::cin.fail()) { // checks if move is possible
				std::cout << "This move is not valid. Please select a valid move shown by the X's." << std::endl;
			}
			else { possible_move = true; } // valid move chosen
		}
	}
	board.move_piece(start.first, start.second, end.first, end.second); // moves the desired piece
	std::cout << board;
	std::cout <<go<< " moved from " << int_to_grid(start.first) << " " << start.second << " to " << int_to_grid(end.first) << " " << end.second << std::endl;
	std::cout << board.has_queened(); // outputs whether a pawn has become a queen
	return end;

}
std::pair<std::pair<std::string,std::string>,std::pair<std::pair<int,int>,std::pair<int,int>>> turn(std::string go, chess_board board) { // function for a player taking their turn -> records info of move and whos turn is next
	std::pair<std::pair<std::string, std::string>, std::pair<std::pair<int, int>, std::pair<int, int>>> record;
	cout_go(go);
	bool made_move = false;
	while (!made_move) {// loop until a move has been made
		std::pair<int, int> start = choose_piece(go, board);
		record.second.first = start;
		std::string piece = board.piece(start.first, start.second);
		record.first.second = piece;
		std::pair<int, int> end = move_piece(go, board, start);
		record.second.second = end;
		if (end != start) { made_move = true; } // checks if a piece has been moved
		else { std::cout << board; cout_go(go); } // restarts loop if player chose to change the piece they want to move
	}
	if (go == "White") { record.first.first = "Black"; } // gives whos go is next depending on who just moved
	else { record.first.first = "White"; }
	return record;
}

//Starting game function
std::pair<chess_board,std::string> start() { // function which shows the start screen of the game and creates the chess board for the game and whos go is next
	system("CLS");
	title();
	std::pair<chess_board, std::string> board_turn;
	std::string play_or_help;
	std::string new_or_load;
	bool game_start = false;
	bool play = 0;
	std::cout << "Welcome to Chess in C++. For the rules how to play and help press [R]. To play a game please press [P].";
	while (!play) { // check if the players are ready to play a game
		std::cin >> play_or_help;
		if (play_or_help == "r"||play_or_help=="R") { help(); std::cout << "Welcome to Chess in C++. For the rules how to play and help press [R]. To play a game please press [P].";} // show help function
		else if(play_or_help =="p"||play_or_help =="P"){play = 1;} 
		else { std::cout << "Input is invalid. Please enter [R] to get rules and help or [P] to play a game." << std::endl; }
	}
	std::cout << "Would you like to start a new game [N] or load a saved game [L]?";
	while (!game_start) { // loop to check if they want to play a new game or load a game
		std::cin >> new_or_load;
		if (new_or_load == "l" || new_or_load == "L") { return load(); } // return a board defined by a save file
		else if (new_or_load == "n" || new_or_load == "N") { game_start = true; }
		else { std::cout << "Input is invalid. Please enter [N] to start a new game or [L] to load a game." << std::endl; }
	}
	chess_board chessboard; // cretes default chess board
	board_turn.first = chessboard;
	board_turn.second = "White";
	return board_turn;
}

//End game functions
bool another_game(chess_board board) { // function to see if the players want to play again once a game has ended
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
void print_record(std::vector<std::string> piece_moved, std::vector<std::pair<int, int>> initial_position, std::vector<std::pair<int, int>> end_position) { // function to print out the list of moves made during the game
	std::string yes_no;
	while (yes_no != "y" && yes_no != "Y" && yes_no != "N" && yes_no != "n") { // loop until correct input has been entered
		std::cin.clear();
		std::cout << "Do you want to see the list of moves for the game? Type y for yes or n for no." << std::endl;
		std::cin >> yes_no;
	}
	if (yes_no == "n" || yes_no == "N") {  } // do nothing if the players dont want to see the move list
	else {  // output the list of moves
		system("cls");
		title();
		std::cout << "MOVE LIST:" << std::endl;
		for (size_t i = 0; i < piece_moved.size(); i++) {
			std::cout << piece_moved[i] << " Moved from " << int_to_grid(initial_position[i].first) << initial_position[i].second << " to " << int_to_grid(end_position[i].first) << end_position[i].second << std::endl;
		}
	}



}

//function to run the game
void play_game(chess_board board, std::string start) { // function for playing the game the game
	std::pair<std::pair<std::string, std::string>, std::pair<std::pair<int, int>, std::pair<int, int>>> record;
	std::vector<std::string> piece_moved;
	std::vector<std::pair<int, int>> initial_position;
	std::vector<std::pair<int, int>> end_position;
	std::cout << board;
	std::string whos_go = start;
	std::string winner =" ";
	while (winner == " ") { // loops until soeone has one 
		record =turn(whos_go, board); //player takes turn
		whos_go = record.first.first; // changes whos go is next
		piece_moved.push_back(record.first.second); // adds which piece was moved to list
		initial_position.push_back(record.second.first); //adds initial position
		end_position.push_back(record.second.second);//adds end position
		winner = board.who_won(); // checks if someone has one
	}
	std::cout << "Congratulations " << board.who_won() << " has won" << std::endl;
	print_record(piece_moved, initial_position, end_position); // outputs list of moves
}

int main() {// main function for running program
	bool play_again = true;
	while (play_again==true){ //loop until the players no longer want to play another game
	std::pair<chess_board, std::string> chessboard_first = start(); // start screen + finds if they want to play a new game or saved game
	play_game(chessboard_first.first,chessboard_first.second); // run game
	play_again = another_game(chessboard_first.first); // checks if they want to play again
	}
	std::cout << std::endl << "Thank you for playing!" << std::endl;
	return 0;
}
