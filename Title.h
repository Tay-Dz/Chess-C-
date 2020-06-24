//Tay Dzonu - C++ Chess code April 2020
//Title.h - header file with non-class functions used both in classes and main
#ifndef TITLE
#define TITLE

#include <iostream>

inline void title() { //function to output the program title
	std::cout << "    _____ _    _ ______  _____ _____ " << std::endl;
	std::cout << "   / ____| |  | |  ____|/ ____/ ____|" << std::endl;
	std::cout << "  | |    | |__| | |__  | (___| (___  " << std::endl;
	std::cout << "  | |    |  __  |  __|  \\___ \\\\___ \\ " << std::endl;
	std::cout << "  | |____| |  | | |____ ____) |___) |" << std::endl;
	std::cout << "   \\_____|_|  |_|______|_____/_____/ " << std::endl << std::endl;
	std::cout << "Created by Tay Dzonu , April 2020."<<std::endl<<std::endl;
}
inline std::string int_to_grid(int i) {//function to convert an integer to the corrsponding letter/grid value
	if (i == 1) { return "A"; }
	else if (i == 2) { return "B"; }
	else if (i == 3) { return "C"; }
	else if (i == 4) { return "D"; }
	else if (i == 5) { return "E"; }
	else if (i == 6) { return "F"; }
	else if (i == 7) { return "G"; }
	else if (i == 8) { return "H"; }
	else { return ""; }
}

#endif