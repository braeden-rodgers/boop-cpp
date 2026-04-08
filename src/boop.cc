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
    for (int i = 0; i < CELL_HEIGHT; i++) 
        strcpy(piece[i], "            ");
}

void Cell::get_piece(int i, int j) const {
    switch (state) {
        case 0:
            cout << piece[i][j];
            break;
        case 1:
            cout << YELLOW << piece[i][j] << RESET;
            break;
        case 2:
            cout << H_YELLOW << piece[i][j] << RESET;
            break;
        case 3:
            cout << BLUE << piece[i][j] << RESET;
            break;
        case 4:
            cout << H_BLUE << piece[i][j] << RESET; 
            break;
    }
}

void Cell::set_piece(char p[CELL_HEIGHT][CELL_WIDTH]) {
    for (int i = 0; i < CELL_HEIGHT; i++)
        for (int j = 0; j < CELL_WIDTH; j++)
            piece[i][j] = p[i][j];
}

// *******************************************************************
// BOOP CLASS
// *******************************************************************

Boop::Boop() {
    p1 = p2 = Player();

    for (int i = 0; i < CELL_HEIGHT; i++)
        strcpy(empty[i], "            ");

    strcpy(kitten[0], "   /\\_/\\    ");
    strcpy(kitten[1], "  ( o.o )   ");      // Meow!
    strcpy(kitten[2], "   > ^ <    ");
    strcpy(kitten[3], "  /  -  \\   ");
    strcpy(kitten[4], " (  ---  )  ");
    strcpy(kitten[5], "   -----    ");

    strcpy(cat[0], "  /\\____/\\  ");
    strcpy(cat[1], " (  o  o  ) ");         // Meow!
    strcpy(cat[2], " (   --   ) ");
    strcpy(cat[3], "  \\  __  /  ");
    strcpy(cat[4], "   \\____/   ");
    strcpy(cat[5], "    ----    ");
}

void Boop::boop_kpieces(int i, int j) {
    // Scan for all valid moves to boop
    for (int k = 0; k < DIRS; k++) {
        // Form an index pair of the direction of an adjacent cell from the placed piece in the center cell
        int r_idx = i + r_dirs[k];
        int c_idx = j + c_dirs[k];

        // Check whether or not the index pair is within the bounds of the game board
        if (!is_inbound(r_idx, c_idx)) 
            continue;

        Cell adj_cell = board[r_idx][c_idx];
        int adj_cell_state = adj_cell.get_state();

        // Check if there is a piece in the adjacent cell
        if (adj_cell_state != 0) {
            // Form an index pair of the cell the booped adjacent piece will move to
            int nr_idx = r_idx + r_dirs[k];
            int nc_idx = c_idx + c_dirs[k];
            Cell new_cell = board[nr_idx][nc_idx];

            // Check if a KITTEN piece will fall off the game board
            if (!is_inbound(nr_idx, nc_idx) && adj_cell_state % 2 != 0) {
                // Update the kitten counter
                if (adj_cell_state == 1) 
                    p1.incr_kitten_pieces();
                else if (adj_cell_state == 3) 
                    p2.incr_kitten_pieces();

                // Update the adjacent cell as a now empty cell 
                adj_cell.set_state(0);
                adj_cell.set_piece(empty);

                board[r_idx][c_idx] = adj_cell;
            }
            else if (new_cell.get_state() == 0) {
                // Move the adjacent kitten piece to the next cell in its direction
                if (adj_cell_state % 2 != 0) {
                    new_cell.set_state(adj_cell_state);
                    new_cell.set_piece(kitten);

                    // Update the adjacent cell as a now empty cell 
                    adj_cell.set_state(0);
                    adj_cell.set_piece(empty);

                    board[r_idx][c_idx] = adj_cell;
                    board[nr_idx][nc_idx] = new_cell;
                }
            }
            // If neither of the previous statements has been executed, a blocking has occured
            // as there are two pieces in line with the placed piece
        }
    }
}

void Boop::boop_pieces(int i, int j) {    
    // Scan for all valid moves to boop
    for (int k = 0; k < DIRS; k++) {
        // Form an index pair of the direction of an adjacent cell from the placed piece in the center cell
        int r_idx = i + r_dirs[k];
        int c_idx = j + c_dirs[k];

        // Check whether or not the index pair is within the bounds of the game board
        if (!is_inbound(r_idx, c_idx)) 
            continue;

        Cell adj_cell = board[r_idx][c_idx];
        int adj_cell_state = adj_cell.get_state();

        // Check if there is a piece in the adjacent cell
        if (adj_cell_state != 0) {
            // Form an index pair of the cell the booped adjacent piece will move to
            int nr_idx = r_idx + r_dirs[k];
            int nc_idx = c_idx + c_dirs[k];
            Cell new_cell = board[nr_idx][nc_idx];

            // Check if ANY piece will fall off the game board
            if (!is_inbound(nr_idx, nc_idx)) {
                // Update the kitten counter
                if (adj_cell_state == 1) 
                    p1.incr_kitten_pieces();
                else if (adj_cell_state == 2) 
                    p1.incr_cat_pieces();
                else if (adj_cell_state == 3) 
                    p2.incr_kitten_pieces();
                else 
                    p2.incr_cat_pieces();

                // Update the adjacent cell as a now empty cell 
                adj_cell.set_state(0);
                adj_cell.set_piece(empty);

                board[r_idx][c_idx] = adj_cell;
            }
            else if (new_cell.get_state() == 0) {
                // Move the adjacent piece to the next cell in its direction
                new_cell.set_state(adj_cell_state);
                if (adj_cell_state % 2 != 0) 
                    new_cell.set_piece(kitten);
                else 
                    new_cell.set_piece(cat);

                // Update the adjacent cell as a now empty cell 
                adj_cell.set_state(0);
                adj_cell.set_piece(empty);

                board[r_idx][c_idx] = adj_cell;
                board[nr_idx][nc_idx] = new_cell;
            }
            // If neither of the previous statements has been executed, a blocking has occured
            // as there are two pieces in line with the placed piece
        }
    }
}

void Boop::graduate_pieces() {
    return;
}

void Boop::make_move(const string& move) {
    bool is_cat = false;

    char row = move.at(1);
    char col = move.at(0);
    int r_idx = get_row_idx(row);
    int c_idx = get_col_idx(col);
    Cell sel_cell = board[r_idx][c_idx];

    if (next_mover() == HUMAN){
        // Set player 1's game piece
        if (!is_cat) {
            sel_cell.set_state(1);
            sel_cell.set_piece(kitten);
            p1.decr_kitten_pieces();
        }
        else {
            sel_cell.set_state(2);
            sel_cell.set_piece(cat);
            p1.decr_cat_pieces();
        }
    }
    else {
        // Set player 2's game piece
        if (!is_cat) {
            sel_cell.set_state(3);
            sel_cell.set_piece(kitten);
            p2.decr_kitten_pieces();
        }
        else {
            sel_cell.set_state(4);
            sel_cell.set_piece(cat);
            p2.decr_cat_pieces();
        }
    }
    board[r_idx][c_idx] = sel_cell;

    // Boop!
    if (!is_cat) boop_kpieces(r_idx, c_idx);    // Only move adjacent kitten pieces as a kitten
    else boop_pieces(r_idx, c_idx);             // Move any adjacent pieces as a cat 

    // Graduate kitten pieces into cat pieces if necessary
    graduate_pieces();

    Game::make_move(move);
}

void Boop::restart() {
    // Clear the game board
    
    // Reset the players' game pieces

    Game::restart();
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
                    // Print the piece
                    (board[r][c]).get_piece(h, w);
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
    int eval = 0;
    int state;

    // Evaluate each cell on the board
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            state = (board[i][j]).get_state();

            if (state == 1 || state == 2) 
                eval--;
            else if (state == 3 || state == 4) 
                eval++;
        }   
    }

    return eval;    
}

bool Boop::is_game_over() const {
    // Scan all 3-piece cat rows
    for (int i = 0; i < SIZE; i++) {
        for (int j = 1; j < SIZE - 1; j++) {
            Cell middle = board[i][j];
            Cell left = board[i][j - 1];
            Cell right = board[i][j + 1];

            // Winning row condition is met
            if (middle == left && middle == right) 
                return true;
        }
    }

    // Scan all 3-piece cat columns
    for (int i = 1; i < SIZE - 1; i++) {
        for (int j = 0; j < SIZE; j++) {
            Cell middle = board[i][j];
            Cell top = board[i - 1][j];
            Cell bottom = board[i + 1][j];

            // Winning column condition is met
            if (middle == top && middle == bottom) 
                return true;
        }
    }

    // Scan all 3-piece cat rising diagonals
    for (int i = 1; i < SIZE - 1; i++) {
        for (int j = 0; j < SIZE - 1; j++) {
            Cell middle = board[i][j];
            Cell l_bottom = board[i + 1][j - 1];
            Cell r_top = board[i - 1][j + 1];

            // Winning diagonal condition is met
            if (middle == l_bottom && middle == r_top) 
                return true;
        }
    }

    // Scan all 3-piece cat falling diagonals
    for (int i = 1; i < SIZE - 1; i++) {
        for (int j = 0; j < SIZE - 1; j++) {
            Cell middle = board[i][j];
            Cell l_top = board[i - 1][j - 1];
            Cell r_bottom = board[i + 1][j + 1];
            
            // Winning diagonal condition is met
            if (middle == l_top && middle == r_bottom) 
                return true;
        }
    }

    return false;
}

bool Boop::is_legal(const string& move) const {
    // Verify the length of the move string
    if (move.length() != 2) 
        return false;

    char row = move.at(1);
    char col = move.at(0);

    // Verify the row number and column letter
    if (row < '1' || row >= '1' + SIZE) 
        return false;
    if (col < 'A' || col >= 'A' + SIZE) 
        return false;

    int r_idx = get_row_idx(row);
    int c_idx = get_col_idx(col);

    // Verify that the selected cell is empty
    if (board[r_idx][c_idx].get_state() == 0) 
        return true;

    return false;
}
