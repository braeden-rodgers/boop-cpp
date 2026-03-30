/**
 * game.h
 * 
 * Header file consisting attributes and functions that a board game would have. 
 * It also contains multiple possible game outcomes: human, neutral, and computer.
 * 
 */

#ifndef MAIN_SAVITCH_GAME
#define MAIN_SAVITCH_GAME

#include <queue>    // Provides queue<string>
#include <string>   // Provides string

namespace main_savitch_14 {
    class Game {
        public:
            // Possible game outcomes
            enum who {HUMAN, NEUTRAL, COMPUTER};

            // Game constructor
            Game() {move_num = 0;}

            // Game deconstructor
            virtual ~Game() {}
            
            // The play function should not be overridden. It plays one game,
		    // with the human player moving first and the computer second.
		    // The computer uses an alpha-beta look ahead algorithm to select its
		    // moves. The return value is the winner of the game (or NEUTRAL for
		    // a tie).
            who play();

        protected:
            // *******************************************************************
            // OPTIONAL VIRTUAL FUNCTIONS (Overriding is optional)
            // *******************************************************************

            // Virtual function to display a message
            virtual void display_message(const std::string& message) const;

            // Virtual function to get the user move object
            virtual std::string get_user_move() const;

            // Virtual function to determine which player is the previous mover
            virtual who last_mover() const 
                {return (move_num % 2 == 1 ? HUMAN : COMPUTER);}

            // Virtual function to compute the value of moves completed
            virtual int moves_completed() const 
                {return move_num;}

            // Virtual function to determine which player is the next mover
            virtual who next_mover() const
                {return (move_num % 2 == 0 ? HUMAN : COMPUTER);}

            // Virtual function to determine which player is the opposite of the current player
            virtual who opposite(who player) const 
                {return (player == HUMAN) ? COMPUTER : HUMAN;}

            // Virtual function to determine who wins the round of the game
            virtual who winning() const;

            // *******************************************************************
            // VIRTUAL FUNCTIONS THAT MUST BE OVERRIDDEN (Overriding function
            // should call the original when it finishes)
            // *******************************************************************

            // Virtual function to have the next player make a specified move
            virtual void make_move(const std::string& move) 
                {++move_num;}

            // Virtual function to restart the game from the beginning
            virtual void restart() 
                {move_num = 0;}

            // *******************************************************************
            // PURE VIRTUAL FUNCTIONS (Must be provided for each derived class)
            // *******************************************************************

            // Pure virtual function that clones
            virtual Game* clone() const = 0;

            // Pure virtual function to compute all the moves that the next player can make
            virtual void compute_moves(std::queue<std::string>& moves) const = 0;

           // Pure virtual function to display the status of the game
            virtual void display_status() const = 0;

            // Pure virtual function to evaluate a board position
            virtual int evaluate() const = 0;

            // Pure virtual function to determine whether or not the game is finished
            virtual bool is_game_over() const = 0;

            // Pure virtual function to determine whether or not the given move is legal for the next player
            virtual bool is_legal(const std::string& move) const = 0;
            
        private:
            int move_num;                       // Numbers of moves made so far
            static const int SEARCH_LEVELS = 2; // Levels for look-ahead evaluation
            
            // Private function that evalauates with look ahead
            int eval_with_lookahead(int look_ahead, int beat_this);

            // Private function to make a computer move
            void make_computer_move();

            // Private function to make a human move
            void make_human_move();
    };
};

#endif  // MAIN_SAVITCH_GAME
