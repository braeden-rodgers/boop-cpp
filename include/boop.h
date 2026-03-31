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

#include <iomanip>
#include <iostream>
#include <queue>
#include <string>
#include "game.h"

// An independent class representing a single cell within the "boop." game board
class Cell{
    public:
        // Cell constructor
        Cell();

        // Getter method for the state of the cell
        int get_state() const;

        // Getter method to get the named location of the cell
        std::string get_location() const;

        // Setter method to change the state of the cell
        void set_state(int state);

        // Setter method to change the name of the location
        void set_location(std::string name);
        
        // Printing method to display either one of the players' kitten or cat piece depending on the current state of the space
        void display_piece(std::ostream &outs) const;
    
    private:
        int state;              // Mutable state of the cell; There are 5 possible states a cell can have:
                                // 0 - Empty cell
                                // 1 - Contains player 1's kitten piece
                                // 2 - Contains player 1's cat piece
                                // 3 - Contains player 2's kitten piece
                                // 4 - Contains player 2's cat piece
        std::string location;   // The named location of the cell
        char piece[12];         // One line character array depicting a kitten piece, cat piece, or nothing
};

// A derived class of Game class representing an entire round of the "boop." game
class Boop: public main_savitch_14::Game {
    public:
        const static int SIZE = 6;
        const static int CELL_HEIGHT = SIZE;
        const static int CELL_WIDTH = SIZE * 2;

        // Boop constructor
        Boop();

        // Getter method for player 1's kitten pieces 
        int get_p1_kpieces() const;

        // Getter method for player 1's cat pieces 
        int get_p1_cpieces() const;

        // Getter method for player 2's kitten pieces 
        int get_p2_kpieces() const;

        // Getter method for player 2's cat pieces 
        int get_p2_cpieces() const;

        // *******************************************************************
        // VIRTUAL METHODS THAT MUST BE OVERRIDDEN (The overriding method
        // should call the original when it finishes)
        // *******************************************************************

        // Virtual method to have the next player make a specified move
        void make_move(const std::string& move);

        // Virtual method to restart the game from the beginning
        void restart();

        // *******************************************************************
        // PURE VIRTUAL METHODS (The pure virtual methods must be provided
        // for each derived class)
        // *******************************************************************

        // Virtual method that clones
	    main_savitch_14::Game* clone() const;

        // Virtual method that computes all the moves that the next player can make
		void compute_moves(std::queue<std::string>& moves) const;

        // Virtual method to display the status of the game
		void display_status() const;

        // Virtual method to evaluate a board position
		int evaluate() const;

        // Virtual method to determine whether or not the game is finished
		bool is_game_over() const;

        // Virtual method to determine whether or not the given move is legal for the next player
		bool is_legal(const std::string& move) const;

    private:
        Cell board[SIZE][SIZE]; // 2-D array of Cell objects as the 6x6 board of Boop game.
        int p1_kpieces;         // Player 1's kitten pieces
        int p1_cpieces;         // Player 1's cat pieces
        int p2_kpieces;         // Player 2's kitten pieces
        int p2_cpieces;         // Player 2's cat pieces
};

// Overloaded << operator
// std::ostream& operator << (std::ostream& outs, const Cell& cell);

#endif  // BOOP_H
