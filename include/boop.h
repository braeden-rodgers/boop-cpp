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

#include <array>    // Provides array<string, N>
#include <queue>    // Provides queue<string>
#include <string>   // Provides string
#include <vector>   // Provides vector<Graduation> and vector<pair<int, int>>
#include "game.h"   // Provides Game class

// Variables for the game board display
static const int SIZE = 6;
static const int CELL_HEIGHT = 6;
static const int CELL_WIDTH = CELL_HEIGHT * 2;

// Variables for the booping mechanism
static const int BOOP_DIRS = 8;
static const int br_dirs[BOOP_DIRS] = {-1, -1, -1, 0, 0, 1, 1, 1};
static const int bc_dirs[BOOP_DIRS] = {-1, 0, 1, -1, 1, -1, 0, 1};

// Varaibles for the kitten graduation mechanism and checking winning conditions
static const int DIRS = 4;
static const int r_dirs[DIRS] = {0, 1, 1, 1};
static const int c_dirs[DIRS] = {1, 0, 1, -1};

// A structure for handling rare cases when performing kitten graduation
struct Graduation {
    std::vector<std::pair<int, int>> cells; // Vector of cells as pairs of indices within the game board
    int owner;                              // Player 1 (0) or Player 2 (1)
    bool all_kittens;                       // Boolean value if all pieces are kittens
    bool is_mixed;                          // Boolean value if the pieces are a combination of kittens and cats
};

// A helper class for Boop class representing a single cell within the game board
class Cell{
    public:
        // Cell constructor
        Cell() : state(0) {piece.fill(std::string(CELL_WIDTH, ' '));}

        // Getter method for the state of the cell
        int get_state() const {return state;}
        
        // Getter method to display either one of the players' kitten or cat piece depending on the cell's state
        char get_piece(int i, int j) const {return piece[i][j];}

        // Setter method to change the state of the cell
        void set_state(int val) {state = val;}

        // Setter method to change the cell's piece
        void set_piece(std::array<std::string, CELL_HEIGHT> new_piece) {piece = new_piece;}

        // Method to update both data members
        void update(int val, std::array<std::string, CELL_HEIGHT> new_piece) {state = val; piece = new_piece;}

    private:
        int state;                                  // Mutable state of the cell:
                                                    // 0 - Empty cell
                                                    // 1 - Contains player 1's kitten piece
                                                    // 2 - Contains player 1's cat piece
                                                    // 3 - Contains player 2's kitten piece
                                                    // 4 - Contains player 2's cat piece
        std::array<std::string, CELL_HEIGHT> piece; // The cell's piece depending on the state
};

// A helper class containing attributes that a single player has in the "boop." game
class Player {
    public:
        // Player constructor
        Player() : kittens(8), cats(0) {}

        // Getter method for the player's kitten pieces
        int get_kittens() const {return kittens;}

        // Getter method for the player's cat pieces
        int get_cats() const {return cats;}

        // Setter method for the player's kitten pieces
        void set_kittens(int val) {kittens = val;}

        // Setter method for the player's cat pieces
        void set_cats(int val) {cats = val;}

        // Method to increment the value of the player's kitten pieces
        void incr_kittens() {kittens++;}

        // Method to decrement the value of the player's kitten pieces
        void decr_kittens() {kittens--;}

        // Method to increment the value of the player's cat pieces
        void incr_cats() {cats++;}

        // Method to decrement the value of the player's cat pieces
        void decr_cats() {cats--;}

        // Method to add cat pieces to the active pool from the reserve
        void add_cats(int val) {cats += val;}

    private:
        int kittens;  // The player's active kitten pieces
        int cats;     // The player's active cat pieces
};

// A derived class of Game class representing an entire round of the "boop." game
class Boop: public main_savitch_14::Game {
    public:
        // Boop constructor
        Boop();

        // Boop deconstructor
        ~Boop() {}

        // *******************************************************************
        // HELPER METHODS
        // *******************************************************************

        // Method to compute the row number of the selected cell
        char get_row(int idx) const {return idx + '1';}

        // Method to compute the column letter of the selected cell
        char get_col(int idx) const {return idx + 'A';}

        // Method to compute the row index of the selected cell
        int get_row_idx(char row) const {return row - '1';}

        // Method to compute the column index of the selected cell
        int get_col_idx(char col) const {return col - 'A';}

        // Method to check whether the board indices are in bounds of the board
        bool is_in_bounds(int i, int j) const {return i >= 0 && i < SIZE && j >= 0 && j < SIZE;}

        // Method to check if the current player has all 8 kitten or cat pieces on the board
        bool has_all_pieces(int state) const;

        // *******************************************************************
        // BOOPING METHODS
        // *******************************************************************

        // Method for when a kitten piece boops ONLY its adjacent kitten pieces
        void boop_kitten(int i, int j, int src_state, Cell& src, Cell& dst);

        // Method for when a cat piece boops ALL its adjacent pieces
        void boop_piece(int i, int j, int src_state, Cell& src, Cell& dst);  

        // Method to boop the adjacent pieces upon placing a piece
        void boop(int i, int j, bool is_cat);

        // *******************************************************************
        // GRADUATION METHODS
        // *******************************************************************

        // Method to find all groups of 3 pieces on the game board that can be graduated into cats
        void find_graduations(std::vector<Graduation>& groups);

        // Method to verify the player's selection of kitten to graduate
        bool validate_selection(std::string move, Player& player);

        // Method to let the current player choose a kitten to graduate into a cat
        void select_kitten(Player& player);

        // Method to allow the current player to select one group of pieces to graduate
        Graduation select_graduation(std::vector<Graduation> groups);

        // Method to graduate kitten pieces into cat pieces after booping
        void graduate(Player& player);

        // *******************************************************************
        // OVERRIDDEN VIRTUAL METHODS
        // *******************************************************************

        // Overriding method to have the next player make a specified move
        void make_move(const std::string& move);

        // Overriding method to restart the game from the beginning
        void restart();

        // *******************************************************************
        // PURE VIRTUAL METHODS
        // *******************************************************************

        // Derived method that calls the copy constructor to make a copy of the current game
	    main_savitch_14::Game* clone() const {return new Boop(*this);}

        // Derived method to compute all the moves that the next player can make
		void compute_moves(std::queue<std::string>& moves) const;

        // Derived method to display the status of the game
		void display_status() const;

        // Derived method to evaluate a board position
		int evaluate() const;

        // Derived method to scan the game board and check if the winning conditions are met
		bool is_game_over() const;

        // Derived method to determine whether or not the given move is legal for the next player
		bool is_legal(const std::string& move) const;

    private:        
        std::array<std::string, CELL_HEIGHT> empty;     // Empty array
        std::array<std::string, CELL_HEIGHT> kitten;    // Array containing kitten text art
        std::array<std::string, CELL_HEIGHT> cat;       // Array containing cat text art
        Cell board[SIZE][SIZE];                         // 2-D array of Cell objects as the 6x6 game board
        Player p1;                                      // Player 1 with their kitten and cat pieces
        Player p2;                                      // Player 2 with their kitten and cat pieces
};

#endif  // BOOP_H
