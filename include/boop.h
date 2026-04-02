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

static const int SIZE = 6;
static const int CELL_HEIGHT = 6;
static const int CELL_WIDTH = CELL_HEIGHT * 2;

// A helper class for Boop class representing a single cell within the game board
class Cell{
    public:
        // Cell constructor
        Cell();

        // Getter method for the state of the cell
        int get_state() const;

        // Getter method to get the named location of the cell
        std::string get_location() const;
        
        // Getter method to display either one of the players' kitten or cat piece depending on the cell's state
        void get_piece(int i) const;

        // Setter method to change the state of the cell
        void set_state(int val);

        // Setter method to change the name of the location
        void set_location(std::string name);

        // Setter method to change the cell's piece
        void set_piece(int state);

        // Overloaded method for the == operator to check the winning conditions
        bool operator == (const Cell &obj) const;

    private:
        int state;              // Mutable state of the cell; There are 5 possible states a cell can have:
                                // 0 - Empty cell
                                // 1 - Contains player 1's kitten piece
                                // 2 - Contains player 1's cat piece
                                // 3 - Contains player 2's kitten piece
                                // 4 - Contains player 2's cat piece
        std::string location;   // The named location of the cell        
        char piece[CELL_WIDTH]; // One-line character array depicting a kitten piece, cat piece, or nothing
};

// A helper class containing attributes that a single player has in the "boop." game
class Player {
    public:
        // Player constructor
        Player();

        // Getter method for the player's kitten pieces
        int get_kitten_pieces() const;

        // Getter method for the player's cat pieces
        int get_cat_pieces() const;

        // Setter method for the player's kitten pieces
        void set_kitten_pieces(int pieces);

        // Setter method for the player's cat pieces
        void set_cat_pieces(int pieces);

        // Method to increment the value of the player's kitten pieces
        void incr_kitten_pieces();

        // Method to decrement the value of the player's kitten pieces
        void decr_kitten_pieces();

        // Method to increment the value of the player's cat pieces
        void incr_cat_pieces();

        // Method to decrement the value of the player's cat pieces
        void decr_cat_pieces();

    private:
        int kitten_pieces;  // The player's kitten pieces
        int cat_pieces;     // The player's cat pieces
};

// A derived class of Game class representing an entire round of the "boop." game
class Boop: public main_savitch_14::Game {
    public:
        // Boop constructor
        Boop();

        // Helper method for make_move when a kitten piece boops its adjacent kitten pieces
        void boop_kpieces(int i, int j);

        // Helper method for make_move when a cat piece boops its adjacent pieces
        void boop_pieces(int i, int j);

        // Helper method for make_move to graduate kitten pieces into cat pieces
        void graduate_pieces();

        // *******************************************************************
        // VIRTUAL METHODS THAT MUST BE OVERRIDDEN (The overriding method
        // should call the original when it finishes)
        // *******************************************************************

        // Overriding method to have the next player make a specified move
        void make_move(const std::string& move);

        // Overriding method to restart the game from the beginning
        void restart();

        // *******************************************************************
        // PURE VIRTUAL METHODS (The pure virtual methods must be provided
        // for each derived class)
        // *******************************************************************

        // Derived method that calls the copy constructor to make a copy of the current game
	    main_savitch_14::Game* clone() const;

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
        Cell board[SIZE][SIZE]; // 2-D array of Cell objects as the 6x6 game board.
        Player p1;              // Player 1 with their kitten and cat pieces
        Player p2;              // Player 2 with their kitten and cat pieces
};

#endif  // BOOP_H
