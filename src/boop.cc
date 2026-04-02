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

void Cell::set_piece(int state) {
    if (state == 1 || state == 3)
        // The cell's piece is set to a kitten piece
        strcpy(piece, " (^o.o^*)/m ");
    else if (state == 2 || state == 4)
        // The cell's piece is set to a cat piece
        strcpy(piece, "(=^0w0^=)==>");
    else
        fill(piece, piece + CELL_WIDTH, ' ');
}

bool Cell::operator == (const Cell& cell) const{
    if((state == 2 && cell.get_state() == 2) || (state == 4 && cell.get_state() == 4))
        return true;
    return false;
}

// *******************************************************************
// BOOP CLASS
// *******************************************************************

Boop::Boop() {
    p1 = p2 = Player();
    char row_num = '1';
    char col_letter = 'A';
    
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            Cell cell;
            string location = string(1, col_letter) + row_num;
            cell.set_location(location);
            cell.set_state(0);
            cell.set_piece(0);
            board[i][j] = cell;
            ++col_letter;
        }
        ++row_num;
        col_letter = 'A';
    }
}

bool Boop::is_inbound(int i, int j) {
    return i >= 0 && i < SIZE && j >= 0 && j < SIZE;
}

void Boop::boop_kpieces(int i, int j) {
    cout << endl;
    cout << "Placed piece: " << "(" << i << ", " << j << ")" << endl;

    // Scan for all valid moves to boop
    for (int k = 0; k < DIRS; k++) {
        // Form an index pair of the direction of an adjacent cell from the placed piece in the center cell
        int r_idx = i + r_dirs[k];
        int c_idx = j + c_dirs[k];

        // Check whether or not the index pair is within the bounds of the game board
        if (!is_inbound(r_idx, c_idx)) continue;
        Cell adj_cell = board[r_idx][c_idx];

        // Check if there is a piece in the adjacent cell
        if (adj_cell.get_state() != 0) {
            // Form an index pair of the cell the booped adjacent piece will move to
            int nr_idx = r_idx + r_dirs[k];
            int nc_idx = c_idx + c_dirs[k];
            Cell new_cell = board[nr_idx][nc_idx];

            // Check if a piece will fall off the game board
            if (!is_inbound(nr_idx, nc_idx)) {
                if (adj_cell.get_state() == 1) p1.incr_kitten_pieces();
                else if (adj_cell.get_state() == 3) p2.incr_kitten_pieces();
                adj_cell.set_state(0);
                adj_cell.set_piece(0);
                board[r_idx][c_idx] = adj_cell;
                board[nr_idx][nc_idx] = new_cell;
            }
            else if ((board[nr_idx][nc_idx]).get_state() == 0) {
                // Move the adjacment piece to the next cell in its direction
                new_cell.set_state(adj_cell.get_state());
                new_cell.set_piece(adj_cell.get_state());
                adj_cell.set_state(0);
                adj_cell.set_piece(0);
                board[r_idx][c_idx] = adj_cell;
                board[nr_idx][nc_idx] = new_cell;
            }
            // If neither of the previous statements has been executed, a blocking has occured
            // as there are two pieces in line with a placed piece
        }
    }

    return;
}

void Boop::boop_pieces(int i, int j) {
    // Notes:
    //  - Cats boop the same as kitten pieces except they can actually boop other cat pieces
    //  - When you line up 3 of your pieces with a combination of Cats and Kittens, you still remove
    //      all three pieces from the board and graduate any Kittens. (fig. 5) The Cats in the group go 
    //      to your pool, as do any newly graduated
}

void Boop::graduate_pieces() {
    // Implement code here
    // Might need to add an argument specifying how many kittens are graduated into cats
    return;
}

void Boop::make_move(const string& move) {
    Cell cell;
    int state;
    bool cat = false;

    // Ask the current player if they want to use an available cat piece
    // ...

    // Scan the game board to find the selected cell
    for(int i = 0; i < SIZE; i++) {
        for(int j = 0; j < SIZE; j++) {
            // Place the upcoming piece on the board
            if (move == (board[i][j]).get_location()){
                // Set player 1's game piece
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
                // Set player 2's game piece
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

                // Trigger the booping mechanism depending on piece type once the new piece has been set
                if (!cat) boop_kpieces(i, j);
                else boop_pieces(i, j);

                // Graduate kitten pieces into cat pieces if necessary
                graduate_pieces();

                break;
            }
        }
    }

    Game::make_move(move);
}

void Boop::restart() {
    // Clear the game board
    
    // Reset the players' game pieces

    Game::restart();
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
                        (board[r][c]).get_piece(w);
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
    // STUB METHOD
    return 0;
}

bool Boop::is_game_over() const {
    // Check if the player has all 8 cat pieces on the board
    if ((next_mover() == HUMAN && p1.get_cat_pieces() == 0) || (next_mover() == COMPUTER && p2.get_cat_pieces() == 0))
        return true;    

    // Scan all 3-piece cat rows
    for (int i = 0; i < SIZE; i++) {
        for (int j = 1; j < SIZE - 1; j++) {
            Cell left = board[i][j - 1];
            Cell middle = board[i][j];
            Cell right = board[i][j + 1];

            // Winning row condition is met
            if (middle == left && middle == right) return true;
        }
    }

    // Scan all 3-piece cat columns
    for (int i = 1; i < SIZE - 1; i++) {
        for (int j = 0; j < SIZE; j++) {
            Cell top = board[i - 1][j];
            Cell middle = board[i][j];
            Cell bottom = board[i + 1][j];

            // Winning column condition is met
            if (middle == top && middle == bottom) return true;
        }
    }

    // Scan all 3-piece cat rising diagonals
    for (int i = 1; i < SIZE - 1; i++) {
        for (int j = 0; j < SIZE - 1; j++) {
            Cell l_bottom = board[i + 1][j - 1];
            Cell middle = board[i][j];
            Cell r_top = board[i - 1][j + 1];

            // Winning diagonal condition is met
            if (middle == l_bottom && middle == r_top) return true;
        }
    }

    // Scan all 3-piece cat falling diagonals
    for (int i = 1; i < SIZE - 1; i++) {
        for (int j = 0; j < SIZE - 1; j++) {
            Cell l_top = board[i - 1][j - 1];
            Cell middle = board[i][j];
            Cell r_bottom = board[i + 1][j + 1];
            
            // Winning diagonal condition is met
            if (middle == l_top && middle == r_bottom) return true;
        }
    }

    return false;
}

bool Boop::is_legal(const string& move) const {
    // Verify the length of the move string
    if (move.length() != 2) return false;

    // Verify the row number and column letter
    char row = move.at(1);
    char col = move.at(0);
    if (row < '1' || row >= '1' + SIZE) return false;
    if (col < 'A' || col >= 'A' + SIZE) return false;

    // Verify that the selected cell is empty
    int r_idx = row - '1';
    int c_idx = col - 'A';

    if (board[r_idx][c_idx].get_state() == 0) return true;

    return false;
}
