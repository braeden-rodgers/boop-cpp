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

void Cell::update(int val, char p[CELL_HEIGHT][CELL_WIDTH]) {
    state = val;
    for (int i = 0; i < CELL_HEIGHT; i++)
        for (int j = 0; j < CELL_WIDTH; j++)
            piece[i][j] = p[i][j];
}


// *******************************************************************
// BOOP CLASS
// *******************************************************************

Boop::Boop() {
    p1 = p2 = Player();

    for (int i = 0; i < CELL_HEIGHT; i++)   // *Crickets*
        strcpy(empty[i], "            ");

    strcpy(kitten[0], "   /\\_/\\    ");
    strcpy(kitten[1], "  ( o.o )   ");      // Mew!
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
    for (int k = 0; k < BOOP_DIRS; k++) {
        // Form an index pair of the direction of an adjacent cell from the placed piece in the center cell
        int r_idx = i + br_dirs[k];
        int c_idx = j + bc_dirs[k];

        // Check whether or not the index pair is within the bounds of the game board
        if (!is_inbound(r_idx, c_idx)) 
            continue;

        Cell& adj_cell = board[r_idx][c_idx];
        int adj_cell_state = adj_cell.get_state();

        // Check if there is a piece in the adjacent cell
        if (adj_cell_state != 0) {
            // Form an index pair of the cell the booped adjacent piece will move to
            int nr_idx = r_idx + br_dirs[k];
            int nc_idx = c_idx + bc_dirs[k];
            Cell& new_cell = board[nr_idx][nc_idx];

            // Check if a KITTEN piece will fall off the game board
            if (!is_inbound(nr_idx, nc_idx) && adj_cell_state % 2 != 0) {
                // Update the kitten counter
                if (adj_cell_state == 1) 
                    p1.incr_kittens();
                else if (adj_cell_state == 3) 
                    p2.incr_kittens();

                // Update the adjacent cell as a now empty cell 
                adj_cell.update(0, empty);
            }
            else if (new_cell.get_state() == 0 && adj_cell_state % 2 != 0) {
                // Move the adjacent kitten piece to the next cell in its direction
                new_cell.update(adj_cell_state, kitten);

                // Update the adjacent cell as a now empty cell 
                adj_cell.update(0, empty);
            }
            // If neither of the previous statements has been executed, a blocking has occured
            // as there are two pieces in line with the placed piece
        }
    }
}

void Boop::boop_pieces(int i, int j) {    
    // Scan for all valid moves to boop
    for (int k = 0; k < BOOP_DIRS; k++) {
        // Form an index pair of the direction of an adjacent cell from the placed piece in the center cell
        int r_idx = i + br_dirs[k];
        int c_idx = j + bc_dirs[k];

        // Check whether or not the index pair is within the bounds of the game board
        if (!is_inbound(r_idx, c_idx)) 
            continue;

        Cell& adj_cell = board[r_idx][c_idx];
        int adj_cell_state = adj_cell.get_state();

        // Check if there is a piece in the adjacent cell
        if (adj_cell_state != 0) {
            // Form an index pair of the cell the booped adjacent piece will move to
            int nr_idx = r_idx + br_dirs[k];
            int nc_idx = c_idx + bc_dirs[k];
            Cell& new_cell = board[nr_idx][nc_idx];

            // Check if ANY piece will fall off the game board
            if (!is_inbound(nr_idx, nc_idx)) {
                // Update the kitten counter
                if (adj_cell_state == 1) 
                    p1.incr_kittens();
                else if (adj_cell_state == 2) 
                    p1.incr_cats();
                else if (adj_cell_state == 3) 
                    p2.incr_kittens();
                else 
                    p2.incr_cats();

                // Update the adjacent cell as a now empty cell 
                adj_cell.update(0, empty);
            }
            else if (new_cell.get_state() == 0) {
                // Move the adjacent piece to the next cell in its direction
                new_cell.set_state(adj_cell_state);
                if (adj_cell_state % 2 != 0) 
                    new_cell.set_piece(kitten);
                else 
                    new_cell.set_piece(cat);

                // Update the adjacent cell as a now empty cell 
                adj_cell.update(0, empty);
            }
            // If neither of the previous statements has been executed, a blocking has occured
            // as there are two pieces in line with the placed piece
        }
    }
}

void Boop::graduate_pieces() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            Cell& c1 = board[i][j];
            int state = c1.get_state();

            // Check if the current cell contains a kitten piece or not
            if (state % 2 == 0)
                continue;

            for (int k = 0; k < GRAD_DIRS; k++) {
                // Form two index pairs to find 3 kitten pieces in line of same type
                int r_idx = i + gr_dirs[k];
                int c_idx = j + gc_dirs[k];
                int nr_idx = i + 2 * gr_dirs[k];
                int nc_idx = j + 2 * gc_dirs[k];

                // Check whether the last index pair is in bound of the game board
                if (!is_inbound(nr_idx, nc_idx))
                    continue;

                Cell& c2 = board[r_idx][c_idx];
                Cell& c3 = board[nr_idx][nc_idx];

                // Check if all 3 pieces in line are matching
                if (c2.get_state() == state && c3.get_state() == state) {
                    Player& player = (state == 1) ? p1 : p2;

                    // Remove the 3 matching kittens from the game board
                    c1.update(0, empty);
                    c2.update(0, empty);
                    c3.update(0, empty);

                    // Update the current player's pool
                    player.add_cats(3);
                }
            }
        }
    }    
}

void Boop::make_move(const string& move) {
    bool is_cat = false;
    bool human = next_mover() == HUMAN;
    int state = human ? 1 : 3;
    Player& player = human ? p1 : p2;

    // Get the selected cell of the board to manipulate it
    char row = move.at(1);
    char col = move.at(0);
    int r_idx = get_row_idx(row);
    int c_idx = get_col_idx(col);
    Cell& sel_cell = board[r_idx][c_idx];

    if (player.get_cats() > 0) {
        string ans;
        
        cout << "You have a cat piece available. Would you like to use one? (Y/N): ";
        getline(cin, ans);

        if (ans == "Y" || ans == "YES" || ans == "y" || ans == "yes")
            is_cat = true;
    }

    if (!is_cat) {
        // Set the current player's kitten piece
        sel_cell.update(state, kitten);
        player.decr_kittens();

        // Boop!
        boop_kpieces(r_idx, c_idx);
    } else {
        // Set the current player's cat piece
        sel_cell.update(state + 1, cat);
        player.decr_cats();

        // Boop!
        boop_pieces(r_idx, c_idx);
    }

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
    string eql_str = string(82, '=');
    string plus_str = string(82, '+');

    cout << endl << eql_str << endl;
    cout << plus_str << endl;
    cout << eql_str << endl << endl;

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
                // Print the piece
                for (int w = 0; w < CELL_WIDTH; w++)
                    (board[r][c]).get_piece(h, w);
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
    cout << YELLOW << "\t  " << kpieces_str << " " << RESET << p1.get_kittens()
         << BLUE << spacing << kpieces_str << " " << RESET << p2.get_kittens() << endl;
    cout << YELLOW << "\t     " << cpieces_str << " " <<  RESET << p1.get_cats()
         << BLUE << spacing << cpieces_str << "    " << RESET << p2.get_cats() << endl;
    cout << endl;
}

int Boop::evaluate() const {
    int eval = 0;

    // Evaluate each cell on the board
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            int state = (board[i][j]).get_state();

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
            if (left == middle && right == middle) 
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
            if (top == middle && bottom == middle) 
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
            if (l_bottom == middle && r_top == middle) 
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
            if (l_top == middle && r_bottom == middle) 
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
    if ((board[r_idx][c_idx]).get_state() == 0) 
        return true;

    return false;
}
