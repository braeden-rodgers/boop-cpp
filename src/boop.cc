/**
 * boop.cc
 * 
 * The implementation file for the boop header file (boop.h).
 * 
 */

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
    for (int i = 0; i < CELL_WIDTH; i++)
        piece[i] = ' ';
}

int Cell::get_state() const {return state;}

string Cell::get_location() const {return location;}

void Cell::get_piece(int i) const {
    switch (state) {
        case 0:
            // Print empty space
            cout << piece[i];
            break;
        case 1:
            // Print player 1's kitten piece
            cout << YELLOW << piece[i] << RESET;
            break;
        case 2:
            // Print player 1's cat piece
            cout << H_YELLOW << piece[i] << RESET;
            break;
        case 3:
            // Print player 2's kitten piece
            cout << BLUE << piece[i] << RESET;
            break;
        case 4:
            // Print player 2's cat piece
            cout << H_BLUE << piece[i] << RESET;
            break;
    }
}

void Cell::set_state(int s) {state = s;}

void Cell::set_location(string l) {location = l;}

void Cell::set_piece(int state) {
    // Note that this specific method may need some tweaks in the future
    if (state == 1 || state == 3) {
        // The cell's piece is set to a kitten piece
        piece[0]  = ' ';
        piece[1]  = '(';
        piece[2]  = '^';
        piece[3]  = 'o';
        piece[4]  = '.';
        piece[5]  = 'o';
        piece[6]  = '^';
        piece[7]  = '*';
        piece[8]  = ')';
        piece[9]  = '/';
        piece[10] = 'm';
        piece[11] = ' ';
    }
    else if (state == 2 || state == 4) {
        // The cell's piece is set to a cat piece
        piece[0]  = ' ';
        piece[1]  = '(';
        piece[2]  = '=';
        piece[3]  = '0';
        piece[4]  = 'w';
        piece[5]  = '0';
        piece[6]  = '=';
        piece[7]  = ')';
        piece[8]  = '=';
        piece[9]  = '=';
        piece[10] = '>';
        piece[11] = ' ';
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
    // This implementation is simplified for now; Will be tweaked in the future
    Cell cell;

    for(int i = 0; i < SIZE; i++) {
        for(int j = 0; j < SIZE; j++) {
            cell = board[i][j];

            if (move == cell.get_location()){
                if (next_mover() == HUMAN){
                    cell.set_state(1);
                    board[i][j] = cell;
                    p1_kpieces--;
                }
                else {
                    cell.set_state(3);
                    board[i][j] = cell;
                    p2_kpieces--;
                }

                board[i][j].set_piece((board[i][j]).get_state());
            }
        }
    }

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
    for (int i = 0; i < SIZE; i++) {
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
            if (h == CELL_HEIGHT / 2)
                // Print the row labels
                cout << " " << r + 1 << " |";
            else
                cout << "   |";

            // Print the cell width
            for (int c = 0; c < SIZE; c++) {
                for (int width = 0; width < CELL_WIDTH; width++) {
                    // Print the center piece
                    if (h == CELL_HEIGHT / 2) 
                        board[c][r].get_piece(width);
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
        for (int j = 0; j < CELL_WIDTH; j++) cout << "-";
        cout << "+";
    }
    cout << endl;

    // Display the current status
    cout << "\t\t\t\t" << BOLD << "Moves completed: " << RESET << moves_completed() << endl; 
    cout << BOLD << YELLOW << "\tPlayer 1's status:" << "\t\t\t\t" << BLUE << "Player 2's status:" << RESET << endl;
    cout << "--------------------------\t\t\t\t--------------------------" << endl;
    cout << YELLOW << "\t  Kitten pieces: " << RESET << p1_kpieces << BLUE << "\t\t\t\tKitten Pieces: " << RESET << p2_kpieces << endl;
    cout << YELLOW << "\t     Cat pieces: " << RESET << p1_cpieces << BLUE << "\t\t\t\tCat Pieces:    " << RESET << p2_cpieces << endl;
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

    char column = move.at(0);
    char row = move.at(1);

    // Verify the column letter and the row number
    if (column >= 'A' && column <= 'F') {
        if (row >= '1' && row <= '6') {
            Cell cell;

            // Verify that the selected cell is empty
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    cell = board[i][j];

                    if (move == cell.get_location()){
                        if (cell.get_state() == 0)
                            return true;
                        else
                            // Selected cell is already occupied
                            return false;
                    }
                }
            }
        }
    }
    
    return false;
}
