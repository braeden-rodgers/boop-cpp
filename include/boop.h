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

// An object of Space class represents a single square in the 6x6 game board
class Space{
    public:
        // Space constructor
        Space() {curr_state = 0; location = "N/A";}

        // Getter function for the space's state
        int get_current_state() const;

        // Getter function to get the space's location
        std::string get_location() const;

        // Mutator function to change the state of the space
        void change_current_state(int state);

        // Mutator function to change the name of the location
        void name_location(std::string &name);
        
        // Printing function to display either one of the players' kitten or cat piece depending on the current state of the space
        void display_piece(std::ostream &outs) const;
    
    private:
        int curr_state;         // Mutable space of the space; There are 5 possible states one space can have:
                                // 1 - Empty space
                                // 2 - Contains player 1's kitten piece
                                // 3 - Contains player 1's cat piece
                                // 4 - Contains player 2's kitten piece
                                // 5 - Contains player 2's cat piece
        std::string location;   // The named location of the space
};

// A derived class of Game class representing an entire round of the "boop." game
class Boop: public main_savitch_14::Game {
    public:
        static const int SIZE = 6;
        Boop();

        // Getter function for player 1's kitten pieces 
        int get_p1_kitten_pieces() const;

        // Getter function for player 1's cat pieces 
        int get_p1_cat_pieces() const;

        // Getter function for player 2's kitten pieces 
        int get_p2_kitten_pieces() const;

        // Getter function for player 2's cat pieces 
        int get_p2_cat_pieces() const;

        // *******************************************************************
        // VIRTUAL FUNCTIONS THAT MUST BE OVERRIDDEN:
        // The overriding function should call the original when it finishes.
        // *******************************************************************

        // Virtual function to have the next player make a specified move
        void make_move(const std::string& move);

        // Function to restart the game from the beginning
        void restart();

        // *******************************************************************
        // PURE VIRTUAL FUNCTIONS:
        // The pure virtual functions must be provided for each derived class
        // *******************************************************************

        // Virtual function that clones
	    main_savitch_14::Game* clone() const;

        // Virtual function that computes all the moves that the next player can make
		void compute_moves(std::queue<std::string>& moves) const;

        // Virtual Function to display the status of the game
		void display_status() const;

        // Virtual function to evaluate a board position
		int evaluate() const;

        // Virtual function to determine whether or not the game is finished
		bool is_game_over() const;

        // Virtual function to determine whether or not the given move is legal for the next player
		bool is_legal(const std::string& move) const;

    private:
        Space board[SIZE][SIZE];    // 6x6 two-dimensional array of Space as the board of Boop game.
        int p1_kitten_pieces;
        int p1_cat_pieces;
        int p2_kitten_pieces;
        int p2_cat_pieces;
};

// Overloaded << operator
std::ostream& operator << (std::ostream& outs, const Space& obj);

#endif  // BOOP_H
