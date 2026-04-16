/**
 * boop.h
 * 
 * Header file of the Boop class that is a derived class of the game class
 * and includes the Space class, which is not derived from anything. The Space
 * class holds attributes that a single space might have and the Boop class
 * consists of a 6x6 two-dimensional array of Spaces, which becomes the
 * principle private of the Boop class.
 * 
 */

#ifndef BOOP_H
#define BOOP_H

#include <array>    // Provides array<int, N> and array <string, N>
#include <queue>    // Provides queue<string>
#include <string>   // Provides string
#include <vector>   // Provides vector<Graduation> and vector<pair<int, int>>
#include "game.h"   // Provides Game class

namespace boop_config {
    // Variables for the game board display
    constexpr int SIZE = 6;
    constexpr int CELL_HEIGHT = 6;
    constexpr int CELL_WIDTH = CELL_HEIGHT * 2;

    // Variables for the booping mechanism
    constexpr int BOOP_DIRS = 8;
    constexpr std::array<int, BOOP_DIRS> br_dirs = {-1, -1, -1, 0, 0, 1, 1, 1};
    constexpr std::array<int, BOOP_DIRS> bc_dirs = {-1, 0, 1, -1, 1, -1, 0, 1};

    // Variables for the kitten graduation mechanism and checking winning conditions
    constexpr int DIRS = 4;
    constexpr std::array<int, DIRS> r_dirs = {0, 1, 1, 1};
    constexpr std::array<int, DIRS> c_dirs = {1, 0, 1, -1};
}

// Enumeration of possible states a single cell in the game board can possess
enum State {EMPTY, P1_KITTEN, P1_CAT, P2_KITTEN, P2_CAT};

// Enumeration of owners a piece belongs to
enum Owner {PLAYER1, PLAYER2};

// A structure containing attributes that a single player has in the Boop game
struct Player {
    int kittens = 8;
    int cats = 0;
};

// A structure for handling unique cases when performing kitten graduation
struct Graduation {
    std::vector<std::pair<int, int>> cells; // Vector of cells as pairs of indices within the game board
    Owner owner;                            // The owner of a piece
    bool all_kittens;                       // Boolean value if all pieces are kittens
    bool is_mixed;                          // Boolean value if the pieces are a combination of kittens and cats
};


// A class representing a single cell within the game board
class Cell{
    public:
        // Cell constructor
        Cell() : state(EMPTY) {}

        // Getter method for the state of the cell
        State get_state() const {return state;}
        
        // Setter method to change the state of the cell
        void set_state(State val) {state = val;}

    private:
        // Value indicating that the cell contains a kitten piece, cat piece, or nothing
        State state;
};

// A class derived from Game class that represents an entire round of the Boop game
class Boop: public main_savitch_14::Game {
    public:
        // Boop constructor
        Boop();

        // Boop deconstructor
        ~Boop() = default;
        
        // Method to compute the row number of the selected cell
        char row_to_char(int idx) const {return idx + '1';}

        // Method to compute the column letter of the selected cell
        char col_to_char(int idx) const {return idx + 'A';}

        // Method to compute the row index of the selected cell
        int char_to_row(char row) const {return row - '1';}

        // Method to compute the column index of the selected cell
        int char_to_col(char col) const {return col - 'A';}

        // Method to check whether the board indices are in bounds of the board
        bool is_in_bounds(int r, int c) const {return r >= 0 && r < boop_config::SIZE && c >= 0 && c < boop_config::SIZE;}

        // Method to check if the current player has all 8 kitten or cat pieces on the board
        bool has_all_pieces(State state) const;

        // *******************************************************************
        // BOOPING METHODS
        // *******************************************************************

        // Method for when a kitten piece boops ONLY its adjacent kitten pieces
        void boop_kitten(int r, int c, State src_state, Cell& src, Cell& dst);

        // Method for when a cat piece boops ALL its adjacent pieces
        void boop_piece(int r, int c, State src_state, Cell& src, Cell& dst);  

        // Method to boop the adjacent pieces upon placing a piece
        void boop(int r, int c, State placed_state);

        // *******************************************************************
        // GRADUATION METHODS
        // *******************************************************************

        // Method to find all groups of 3 pieces on the game board that can be graduated into cats
        void find_graduations(std::vector<Graduation>& groups);

        // Method to verify the player's selection of kitten to graduate
        bool validate_kselection(const std::string& move, Player& player);

        // Method to let the current player choose a kitten to graduate into a cat
        void select_kitten(Player& player);

        // Method to allow the current player to select one group of pieces to graduate
        Graduation select_graduation(const std::vector<Graduation>& groups);

        // Method to graduate kitten pieces into cat pieces after booping
        void graduate(Player& player);

        // *******************************************************************
        // OVERRIDDEN VIRTUAL METHODS
        // *******************************************************************

        // Overriding method to have the next player make a specified move
        void make_move(const std::string& move) override;

        // Overriding method to restart the game from the beginning
        void restart() override;

        // *******************************************************************
        // PURE VIRTUAL METHODS
        // *******************************************************************

        // Derived method that calls the copy constructor to make a copy of the current game
	    Game* clone() const override {return new Boop(*this);}

        // Derived method to compute all the moves that the next player can make
		void compute_moves(std::queue<std::string>& moves) const override;

        // Derived method to display the status of the game
		void display_status() const override;

        // Derived method to evaluate a board position
		int evaluate() const override;

        // Derived method to scan the game board and check if the winning conditions are met
		bool is_game_over() const override;

        // Derived method to determine whether or not the given move is legal for the next player
		bool is_legal(const std::string& move) const override;

    private: 
        // Two different players with their own kitten and cat pieces
        Player p1;
        Player p2;

        // 2-D Cell array representing the game board
        std::array<std::array<Cell, boop_config::SIZE>, boop_config::SIZE> board;

        // String arrays representing ASCII art
        std::array<std::string, boop_config::CELL_HEIGHT> empty;
        std::array<std::string, boop_config::CELL_HEIGHT> kitten;
        std::array<std::string, boop_config::CELL_HEIGHT> cat;
};

#endif  // BOOP_H
