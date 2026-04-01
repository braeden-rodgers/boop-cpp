/**
 * boop.cc
 * 
 * The implementation file for the boop header file (boop.h).
 * 
 */

#include <iostream>     // Provides cin, cout
#include <queue>        // Provides queue<string>
#include <string>       // Provides string
#include "boop.h"       // Provides Game class
#include "colors.h"     // Provides text colors

using namespace std;
using namespace main_savitch_14;

// *******************************************************************
// CELL CLASS
// *******************************************************************

Cell::Cell() {
    state = 0; 
    location = "N/A";
    fill(piece, piece + CELL_WIDTH, ' ');
}

int Cell::get_state() const {return state;}

string Cell::get_location() const {return location;}

void Cell::get_piece(int i) const {
    switch (state) {
        case 0:
            cout << piece[i];
            break;
        case 1:
            cout << YELLOW << piece[i] << RESET;
            break;
        case 2:
            cout << H_YELLOW << piece[i] << RESET;
            break;
        case 3:
            cout << BLUE << piece[i] << RESET;
            break;
        case 4:
            cout << H_BLUE << piece[i] << RESET; 
            break;
    }
}

void Cell::set_state(int val) {state = val;}

void Cell::set_location(string name) {location = name;}

void Cell::set_piece(int state) {
    if (state == 1 || state == 3)
        // The cell's piece is set to a kitten piece
        strcpy(piece, " (^o.o^*)/m ");
    else if (state == 2 || state == 4)
        // The cell's piece is set to a cat piece
        strcpy(piece, "(=^0w0^=)==>");
}

// *******************************************************************
// PLAYER CLASS
// *******************************************************************

Player::Player() {
    kitten_pieces = cat_pieces = 8;
}

int Player::get_kitten_pieces() const {return kitten_pieces;}

int Player::get_cat_pieces() const {return cat_pieces;}

void Player::set_kitten_pieces(int pieces) {kitten_pieces = pieces;}

void Player::set_cat_pieces(int pieces) {cat_pieces = pieces;}

void Player::incr_kitten_pieces() {++kitten_pieces;}

void Player::decr_kitten_pieces() {--kitten_pieces;}

void Player::incr_cat_pieces() {++cat_pieces;}

void Player::decr_cat_pieces() {--cat_pieces;}

// *******************************************************************
// BOOP CLASS
// *******************************************************************

Boop::Boop() {
    p1 = p2 = Player();
    char row_letter = 'A';
    char col_num = '1';
    
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            Cell cell;
            string location;
            location = string(1, row_letter) + col_num;
            cell.set_location(location);
            board[i][j] = cell;
            ++col_num;
        }
        row_letter++;
        col_num = '1';
    }
}

void Boop::boop_pieces() {
    //  [i-1][j-1]      [i-1][j]        [i-1][j+1]
    //  [i][j-1]        [i][j]          [i][j+1]
    //  [i+1][j-1]      [i+1][j]        [i+1][j+1]

    // Notes:
    // - Adjacement kittens are booped regardless of color
    // - Booping does not cause chain reactions
    // - If two pieces in line are already set and a piece is placed, those two pieces do not move



}

/*
void Boop::graduate_pieces() const {

}
*/

void Boop::make_move(const std::string& move) {
    Cell cell;
    int state;
    bool cat = false;

    // Ask the current player if they want to use an available cat piece

    // Place the upcoming piece on the board
    for(int i = 0; i < SIZE; i++) {
        for(int j = 0; j < SIZE; j++) {
            if (move == (board[i][j]).get_location()){
                // Set player 1's piece
                if (next_mover() == HUMAN){
                    if (!cat) {
                        state = 1;
                        p1.decr_kitten_pieces();
                    }
                    else {
                        state = 2;
                        p1.decr_cat_pieces();
                    }
                }
                // Set player 2's piece
                else {
                    if (!cat) {
                        state = 3;
                        p2.decr_kitten_pieces();
                    }
                    else {
                        state = 4;
                        p2.decr_cat_pieces();
                    }
                }
                (board[i][j]).set_state(state);
                (board[i][j]).set_piece(state);
                break;
            }
        }
    }

    // Call the booping mechanism so that the adjacent kitten pieces are booped once the piece has been set

    // Graduate kitten pieces into cat pieces

    Game::make_move(move);
}

void Boop::restart() {
    // Implement code here
    return;
}

Game* Boop::clone() const{
    return new Boop(*this);
}

void Boop::compute_moves(queue<string>& moves) const{
    // STUB METHOD
    return;
}

void Boop::display_status() const{
    string spacing = "\t\t\t\t";
    string kpieces_str = "Kitten Pieces:";
    string cpieces_str = "Cat Pieces:";

    // Display the entire game board
    cout << "    ";
    for (int i = 0; i < SIZE; i++) {
        // Print the column labels
        for (int j = 0; j < CELL_WIDTH; j++) 
            cout << " ";
        cout << char('A' + i);
    }
    cout << endl;

    for (int r = 0; r < SIZE; r++) {
        // Print the top border
        cout << "   +";
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < CELL_WIDTH; j++)
                cout << "-";
            cout << "+";
        }
        cout << endl;

        // Print the cell height
        for (int h = 0; h < CELL_HEIGHT; h++) {
            // Print the row labels
            if (h == CELL_HEIGHT / 2)
                cout << " " << r + 1 << " |";
            else
                cout << "   |";

            // Print the cell width
            for (int c = 0; c < SIZE; c++) {
                for (int w = 0; w < CELL_WIDTH; w++) {
                    // Print the center piece
                    if (h == CELL_HEIGHT / 2) 
                        (board[c][r]).get_piece(w);
                    else
                        cout << " ";
                }
                cout << "|";
            }
            cout << endl;
        }
    }

    // Print the bottom border
    cout << "   +";
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < CELL_WIDTH; j++) 
            cout << "-";
        cout << "+";
    }
    cout << endl;

    // Print the current status of the players
    cout << spacing << BOLD << "Moves completed: " << RESET << moves_completed() << endl; 
    cout << BOLD << YELLOW << "\tPlayer 1's status:" << spacing 
         << BLUE << "Player 2's status:" << RESET << endl;
    cout << string(26, '-') << spacing << string(26, '-') << endl;
    cout << YELLOW << "\t  " << kpieces_str << " " << RESET << p1.get_kitten_pieces()
         << BLUE << spacing << kpieces_str << " " << RESET << p2.get_kitten_pieces() << endl;
    cout << YELLOW << "\t     " << cpieces_str << " " <<  RESET << p1.get_cat_pieces()
         << BLUE << spacing << cpieces_str << "    " << RESET << p2.get_cat_pieces() << endl;
    cout << endl;
}

int Boop::evaluate() const {
    // Implement code here
    return 0;
}

bool Boop::is_game_over() const {
    // Check if the player has all 8 cat pieces on the board

    // Check for 3-piece cat rows

    // Check for 3-piece cat verticals

    // Check for 3-piece cat rising diagonals

    // Check for 3-piece cat falling diagonals

    return false;
}

bool Boop::is_legal(const std::string& move) const {
    // Verify the length of the move string
    if (move.length() != 2) 
        return false;

    char column = move.at(0);
    char row = move.at(1);

    // Verify the column letter and the row number
    if (column >= 'A' && column <= 'F') {
        if (row >= '1' && row <= '6') {
            Cell cell;

            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    cell = board[i][j];
                    
                    // Verify that the selected cell is empty
                    if (move == cell.get_location()){
                        if (cell.get_state() == 0)
                            return true;
                        else
                            return false;
                    }
                }
            }
        }
    }
    
    return false;
}
