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

#include <queue>    // Provides queue<string>
#include <string>   // Provides string
#include "game.h"   // Provides Game class

// Variables for the game board display
static const int SIZE = 6;
static const int CELL_HEIGHT = 6;
static const int CELL_WIDTH = CELL_HEIGHT * 2;

// Variables for the booping mechanism
static const int BOOP_DIRS = 8;
static const int br_dirs[BOOP_DIRS] = {-1, -1, -1, 0, 0, 1, 1, 1};
static const int bc_dirs[BOOP_DIRS] = {-1, 0, 1, -1, 1, -1, 0, 1};

// Varaibles for the kitten graduation mechanism
static const int GRAD_DIRS = 4;
static const int gr_dirs[GRAD_DIRS] = {0, 1, 1, 1};
static const int gc_dirs[GRAD_DIRS] = {1, 0, 1, -1};

// A helper class for Boop class representing a single cell within the game board
class Cell{
    public:
        // Cell constructor
        Cell();

        // Getter method for the state of the cell
        int get_state() const {return state;}
        
        // Getter method to display either one of the players' kitten or cat piece depending on the cell's state
        void get_piece(int i, int j) const;

        // Setter method to change the state of the cell
        void set_state(int val) {state = val;}

        // Setter method to change the cell's piece
        void set_piece(char p[CELL_HEIGHT][CELL_WIDTH]);

        // Method to update both data members
        void update(int val, char p[CELL_HEIGHT][CELL_WIDTH]);

        // Overloaded method for the == operator to check the winning conditions
        bool operator == (const Cell& cell) const {return (state == 2 && cell.get_state() == 2) || (state == 4 && cell.get_state() == 4);}

    private:
        int state;              // Mutable state of the cell; There are 5 possible states a cell can have:
                                // 0 - Empty cell
                                // 1 - Contains player 1's kitten piece
                                // 2 - Contains player 1's cat piece
                                // 3 - Contains player 2's kitten piece
                                // 4 - Contains player 2's cat piece
        char piece[CELL_HEIGHT][CELL_WIDTH];
};

// A helper class containing attributes that a single player has in the "boop." game
class Player {
    public:
        // Player constructor
        Player() {kittens = 8; cats = 0;}

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
        int kittens;  // The player's kitten pieces
        int cats;     // The player's cat pieces
};

// A derived class of Game class representing an entire round of the "boop." game
class Boop: public main_savitch_14::Game {
    public:
        // Boop constructor
        Boop();
        
        // Method to compute the row index of the selected cell
        int get_row_idx(char row) const {return row - '1';}

        // Method to compute the column index of the selected cell
        int get_col_idx(char col) const {return col - 'A';}

        // Helper method for the booping mechanism to check whether the board indices are in bound
        bool is_inbound(int i, int j) {return i >= 0 && i < SIZE && j >= 0 && j < SIZE;}

        // Helper method for make_move when a kitten piece boops ONLY its adjacent kitten pieces
        void boop_kpieces(int i, int j);

        // Helper method for make_move when a cat piece boops ALL its adjacent pieces
        void boop_pieces(int i, int j);        

        // Helper method for make_move to graduate kitten pieces into cat pieces
        void graduate_pieces();

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
        char empty[CELL_HEIGHT][CELL_WIDTH];    // 2-D empty array
        char kitten[CELL_HEIGHT][CELL_WIDTH];   // 2-D array of kitten text art
        char cat[CELL_HEIGHT][CELL_WIDTH];      // 2-D array of cat text art
        Cell board[SIZE][SIZE];                 // 2-D array of Cell objects as the 6x6 game board
        Player p1;                              // Player 1 with their kitten and cat pieces
        Player p2;                              // Player 2 with their kitten and cat pieces
};

#endif  // BOOP_H
