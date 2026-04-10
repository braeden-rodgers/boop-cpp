/**
 * game.cc
 * 
 * The implementation file for the game header file (game.h).
 * 
 */

#include <cassert>    	// Provides assert
#include <climits>   	// Provides INT_MAX and INT_MIN
#include <iostream>   	// Provides cin, cout
#include <queue>      	// Provides queue<string>
#include <string>     	// Provides string
#include "game.h"		// Provides definition of game class
#include <colors.h>		// Provides text colors

using namespace std;

namespace main_savitch_14 {
    Game::who Game::play() {
		restart();

		while(!is_game_over()) {
			display_status();
			//if (last_mover() == COMPUTER)
				make_human_move();
			//else
				//make_computer_move();
		}
        
		display_status();
		return HUMAN;
    }

    void Game::display_message(const string& message) const {
		cout << message;
	}

    string Game::get_user_move() const {
		string move;

		display_message("Your move, please: ");
		getline(cin, move);

		// Case sensitivity is automatically handled
    	// move[0] = (char)toupper(move[0]);
		return move;
    }

    Game::who Game::winning() const {
        // Evaluate based on the move that was just made
		int val = evaluate();

		if (val > 0)
			return last_mover();
		else if (val < 0)
			return next_mover();
		else
			return NEUTRAL;
    }

    int Game::eval_with_lookahead(int look_ahead, int beat_this) {
        // Evaluate a board position with lookahead.
        // --int look_aheads:  How deep the lookahead should go to evaluate the move.
        // --int beat_this: Value of another move that we?re considering. If the
        // current board position can't beat this, then cut it short.
        // The return value is large if the position is good for the player who just
        // moved. 

    	queue<string> moves;	// All possible opponent moves
		int val;             	// Value of a board position after opponent moves
    	int best_val;        	// Evaluation of best opponent move
    	Game* future;           // Pointer to a future version of this game
	
        // Base case
		if (look_ahead == 0 || is_game_over()) {
			if (last_mover() == COMPUTER)
				return evaluate();
			else
			    return -evaluate();
		}

        // Recursive case:
        // The level is above 0, so try all possible opponent moves. Keep the
		// value of the best of these moves from the opponent's perspective.
    	compute_moves(moves); 
		// assert(!moves.empty());
    	best_val = INT_MIN;

    	while (!moves.empty()) {
			future = clone();
			future -> make_move(moves.front());
			val = future -> eval_with_lookahead(look_ahead - 1, best_val);
			delete future;

			if (val > best_val)
				best_val = val;

			moves.pop();
    	}

    	// The value was calculated from the opponent's perspective.
    	// The answer we return should be from player's perspective, so multiply times -1:
    	return -best_val;
    }

    void Game::make_computer_move() {
		queue<string> moves;
		int val;
		int best_val;
		string best_move;
		Game* future;
		
		// Compute all legal moves that the computer could make.
		compute_moves(moves);
		//assert(!moves.empty());
		
		// Evaluate each possible legal move, saving the index of the best
		// in best_index and saving its value in best_value.
		best_val = INT_MIN;
		while (!moves.empty()) {
			future = clone();
			future -> make_move(moves.front());
			val = future -> eval_with_lookahead(SEARCH_LEVELS, best_val);
			delete future;
			if (val >= best_val) {
				best_val = val;
				best_move = moves.front();
			}
			moves.pop();
		}
	    
		// Make the best move.
		make_move(best_move);
    }

    void Game::make_human_move() {
        string move;
		move = get_user_move();
		
		// Check the validity of the user's next move
		while (!is_legal(move)) {
			cout << RED;
			display_message("Illegal move.\n");
			cout << RESET;
			move = get_user_move();
        }
		
		make_move(move);
    }
}
