/**
 * boop.cc
 * 
 * The implementation file for the boop header file (boop.h).
 * 
 */

#include <iomanip>
#include <iostream>
#include <queue>
#include <string>
#include "boop.h"
#include "colors.h"

using namespace std;
using namespace main_savitch_14;

// *******************************************************************
// CELL CLASS
// *******************************************************************

Cell::Cell() {
    state = 0; 
    location = "N/A";
    for (int i = 0; i < 12; i++) {
        piece[i] = ' ';
    }
}

int Cell::get_state() const {return state;}

string Cell::get_location() const {return location;}

void Cell::set_state(int s) {state = s;}

void Cell::set_location(string l) {location = l;}
        
void Cell::display_piece(ostream &outs) const {
    // This specific function may need some major tweaks in the future
    // Kitten piece to copy and paste: ₍˄·͈༝·͈˄*₎◞ ̑̑ 
    // Cat piece to copy and paste: ≽(•⩊ •マ≼
    switch (state) {
        case 0:
            // Print empty space
            break;
        case 1:
            // Print player 1's kitten piece
            break;
        case 2:
            // Print player 1's cat piece
            break;
        case 3:
            // Print player 2's kitten piece
            break;
        case 4:
            // Print player 2's cat piece
            break;
    }
}

// *******************************************************************
// BOOP CLASS
// *******************************************************************

Boop::Boop() {
    p1_kpieces = 8;
    p1_cpieces = 8;
    p2_kpieces = 8;
    p2_cpieces = 8;

    char row_letter = 'A';
    char col_num = '1';

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            Cell cell;
            string location;

            cell.set_state(0);
            location = string(1, row_letter) + col_num;
            cell.set_location(location);
            board[i][j] = cell;
            ++col_num;
        }

        row_letter++;
        col_num = '1';
    }
}

int Boop::get_p1_kpieces() const {return p1_kpieces;}

int Boop::get_p1_cpieces() const {return p1_cpieces;}

int Boop::get_p2_kpieces() const {return p2_kpieces;}

int Boop::get_p2_cpieces() const {return p2_cpieces;}

void Boop::make_move(const std::string& move) {
    // Implement code here

    Game::make_move(move);
}

void Boop::restart() {
    // STUB METHOD
    return;
}

Game* Boop::clone() const{
    // STUB METHOD
    return NULL;
}

void Boop::compute_moves(queue<string>& moves) const{
    // STUB METHOD
    return;
}

void Boop::display_status() const{
    // Print the column labels
    cout << "    ";
    for (int col = 0; col < SIZE; col++) {
        for (int i = 0; i < CELL_WIDTH; i++) cout << " ";
        cout << char('A' + col);
    }
    cout << endl;

    for (int row = 0; row < SIZE; row++) {
        // Print the top border
        cout << "   +";
        for (int col = 0; col < SIZE; col++) {
            for (int i = 0; i < CELL_WIDTH; i++) cout << "-";
            cout << "+";
        }
        cout << endl;

        // Print the cell height
        for (int height = 0; height < CELL_HEIGHT; height++) {
            if (height == CELL_HEIGHT / 2)
                cout << " " << row + 1 << " |";
            else
                cout << "   |";

            // Print the cell width
            for (int col = 0; col < SIZE; col++) {
                for (int width = 0; width < CELL_WIDTH; width++) {
                    // Print the center piece (This may need some tweaks in the future)
                    if (height == CELL_HEIGHT / 2 && width == CELL_WIDTH / 2)
                        cout << "X";
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
    for (int col = 0; col < SIZE; col++) {
        for (int i = 0; i < CELL_WIDTH; i++) cout << "-";
        cout << "+";
    }
    cout << endl;

    // Display the current status
    cout << "\t\t\t\t    " << BOLD << "Moves completed: " << RESET << moves_completed() << endl; 
    cout << BOLD << YELLOW << "\t\tPlayer 1's status:" << "\t\t\t" << BLUE << "Player 2's status:" << RESET << endl;
    cout << "----------------------------------\t\t\t----------------------------------" << endl;
    cout << YELLOW << "\t\t  Kitten pieces: " << RESET << p1_kpieces << BLUE << "\t\t\tKitten Pieces: " << RESET << p1_cpieces << endl;
    cout << YELLOW << "\t\t     Cat pieces: " << RESET << p2_kpieces << BLUE << "\t\t\tCat Pieces:    " << RESET << p2_cpieces << endl;
    cout << endl;
}

int Boop::evaluate() const {
    // STUB METHOD
    return 0;
}

bool Boop::is_game_over() const {
    // STUB METHOD
    return false;
}

bool Boop::is_legal(const std::string& move) const {
    // Verify the length of the move string
    if (move.length() != 2) 
        return false;

    // Handle case sensitivity by automatically turning the row letter into an uppercase letter
	char row_letter = (char)toupper(move.at(0));
    char col_num = move.at(1);
    string new_move = string(1, row_letter) + col_num;

    // Verify the row letter and then the column number
    if (row_letter >= 'A' && row_letter <= 'F') {
        if (col_num >= '1' && col_num <= '6') {
            Cell cell;

            // Verify that the selected cell is empty
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    cell = board[i][j];

                    if (new_move == cell.get_location()){
                        if(cell.get_state() == 0) {
                            return true;
                        }
                        else
                            return false;   // Selected cell is already occupied
                    }
                }
            }
        }
    }
    
    return false;
}

// ostream& operator << (ostream &outs, const Cell& cell){
//     cell.display_piece(outs);
//     return outs;
// }
