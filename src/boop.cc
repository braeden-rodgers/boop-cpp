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

    for (int i = 0; i < CELL_HEIGHT; i++)
        strcpy(empty[i], "            ");   // *Crickets*

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

void Boop::boop_kpieces(int i, int j, Cell& src, Cell& dst) {
    int src_state = src.get_state();

    // Check if a KITTEN piece will fall off the game board
    if (!is_inbounds(i, j) && src_state % 2 != 0) {
        // Update the kitten counter
        if (src_state == 1) 
            p1.incr_kittens();
        else if (src_state == 3) 
            p2.incr_kittens();

        // Update the adjacent cell as a now empty cell 
        src.update(0, empty);
    }
    else if (dst.get_state() == 0 && src_state % 2 != 0) {
        // Move the adjacent kitten piece to the next cell in its direction
        dst.update(src_state, kitten);

        // Update the adjacent cell as a now empty cell 
        src.update(0, empty);
    }
    // If neither of the previous statements has been executed, a blocking has occured
    // as there are two pieces in line with the placed piece
}

void Boop::boop_pieces(int i, int j, Cell& src, Cell& dst) {   
    int src_state = src.get_state();

    // Check if ANY piece will fall off the game board
    if (!is_inbounds(i, j)) {
        // Update the counter
        if (src_state == 1) 
            p1.incr_kittens();
        else if (src_state == 2) 
            p1.incr_cats();
        else if (src_state == 3) 
            p2.incr_kittens();
        else if (src_state == 4)
            p2.incr_cats();

        // Update the adjacent cell as a now empty cell 
        src.update(0, empty);
    }
    else if (dst.get_state() == 0) {
        // Move the adjacent piece to the next cell in its direction
        dst.set_state(src_state);
        if (src_state % 2 != 0) 
            dst.set_piece(kitten);
        else 
            dst.set_piece(cat);

        // Update the adjacent cell as a now empty cell 
        src.update(0, empty);
    }
    // If neither of the previous statements has been executed, a blocking has occured
    // as there are two pieces in line with the placed piece
}

void Boop::boop(int i, int j, bool is_cat) {
    // Scan for all valid moves to boop
    for (int k = 0; k < BOOP_DIRS; k++) {
        // Form an index pair of the direction of an adjacent cell from the placed piece in the center cell
        int r_idx = i + br_dirs[k];
        int c_idx = j + bc_dirs[k];

        // Check whether or not the index pair is within the bounds of the game board
        if (!is_inbounds(r_idx, c_idx)) 
            continue;

        Cell& adj_cell = board[r_idx][c_idx];
        int adj_cell_state = adj_cell.get_state();

        // Check if there is a piece in the adjacent cell
        if (adj_cell_state != 0) {
            // Form an index pair of the cell the booped adjacent piece will move to
            int nr_idx = r_idx + br_dirs[k];
            int nc_idx = c_idx + bc_dirs[k];
            Cell& new_cell = board[nr_idx][nc_idx];

            // Perform the rest of the booping system depending on the type of the placed piece
            if (!is_cat)
                boop_kpieces(nr_idx, nc_idx, adj_cell, new_cell);
            else
                boop_pieces(nr_idx, nc_idx, adj_cell, new_cell);
        }
    }
}

void Boop::graduate() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            Cell& c1 = board[i][j];
            int state = c1.get_state();

            // Check if the current cell contains a kitten piece or not
            if (state % 2 == 0)
                continue;

            for (int k = 0; k < DIRS; k++) {
                // Form two index pairs to find 3 kitten pieces in line of same type
                int r_idx = i + r_dirs[k];
                int c_idx = j + c_dirs[k];
                int nr_idx = i + 2 * r_dirs[k];
                int nc_idx = j + 2 * c_dirs[k];

                // Check whether the last index pair is in bounds of the game board
                if (!is_inbounds(nr_idx, nc_idx))
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
    char col = (char)toupper(move[0]);
    int r_idx = get_row_idx(row);
    int c_idx = get_col_idx(col);
    Cell& sel_cell = board[r_idx][c_idx];

    if (player.get_cats() > 0) {
        string ans;
        
        cout << "You have " << player.get_cats() << " piece(s) available. Would you like to use one?" << endl;
        while (true) {
            cout << "Y/N: ";
            getline(cin, ans);
            transform(ans.begin(), ans.end(), ans.begin(), ::toupper);

            if (ans == "Y" || ans == "YES") {
                is_cat = true;
                break;
            }
            else if (ans == "N" || ans == "NO")
                break;
        }
    }

    if (!is_cat) {
        // Set the current player's kitten piece
        sel_cell.update(state, kitten);
        player.decr_kittens();
    } else {
        // Set the current player's cat piece
        sel_cell.update(state + 1, cat);
        player.decr_cats();
    }

    // Boop!
    boop(r_idx, c_idx, is_cat);

    // Graduate kitten pieces into cat pieces if necessary
    graduate();

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
    string eql_str = string(82, '=');
    string plus_str = string(82, '+');
    string spacing = "\t\t\t\t";
    string kpieces_str = "Kitten Pieces:";
    string cpieces_str = "Cat Pieces:";

    // Print a block for better distinction when printing the board every turn
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
    // Scan through the entire board to find 3 matching cat pieces in line
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            int c1_state = board[i][j].get_state();

            // Ignore the current cell if it does not contain a cat piece
            if (c1_state != 2 && c1_state != 4) 
                continue;

            // Form two index pairs to determine whether there's a line of 3 cat pieces
            for (int k = 0; k < DIRS; k++) {
                int r_idx = i + r_dirs[k];
                int c_idx = j + c_dirs[k];
                int nr_idx = i + 2 * r_dirs[k];
                int nc_idx = j + 2 * c_dirs[k];

                // Check whether the last index pair is in bounds of the game board
                if (!is_inbounds(nr_idx, nc_idx)) 
                    continue;

                int c2_state = (board[r_idx][c_idx]).get_state();
                int c3_state = (board[nr_idx][nc_idx]).get_state();

                // A winning condition is met when all 3 cat pieces in line are matching
                if (c2_state == c1_state && c3_state == c1_state)
                    return true;
            }
        }
    }

    return false;
}

bool Boop::is_legal(const string& move) const {
    // Verify the length of the move string
    if (move.length() != 2) 
        return false;
    
    char row = move.at(1);
    char col = (char)toupper(move[0]);

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
