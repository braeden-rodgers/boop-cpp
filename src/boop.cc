/**
 * boop.cc
 * 
 * The implementation file for the boop header file (boop.h).
 * 
 */

#include <array>        // Provides array<string, N>
#include <iostream>     // Provides cin, cout
#include <queue>        // Provides queue<string>
#include <string>       // Provides string
#include <vector>       // Provdies vector<pair<int, int>>
#include "boop.h"       // Provides Game class
#include "colors.h"     // Provides text colors

using namespace std;
using namespace main_savitch_14;

Boop::Boop() {
    empty.fill(string(CELL_WIDTH, ' '));    // *Crickets*

    kitten = {
        "   /\\_/\\    ",
        "  ( o.o )   ",                     // Mew!
        "   > ^ <    ",
        "  /  -  \\   ",
        " (  ---  )  ",
        "   -----    "
    };

    cat = {
        "  /\\____/\\  ",
        " (  o  o  ) ",                     // Meow!
        " (   --   ) ",
        "  \\  __  /  ",
        "   \\____/   ",
        "    ----    "
    };

    for (int i = 0; i < SIZE; i++) 
        for (int j = 0; j < SIZE; j++)
            board[i][j] = Cell();

    p1 = p2 = Player();
}

bool Boop::has_all_pieces(int state) const {
    int pieces = 0;

    // Determine whether or not there are all 8 pieces of the same state on the board
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if ((board[i][j]).get_state() == state)
                pieces++;

    return pieces == 8;
}

void Boop::boop_kitten(int i, int j, int src_state, Cell& src, Cell& dst) {
    // Check if a KITTEN piece will fall off the game board
    if (!is_in_bounds(i, j) && src_state % 2 == 1) {
        src.update(0, empty);

        if (src_state == 1) 
            p1.incr_kittens();
        else if (src_state == 3) 
            p2.incr_kittens();
    }
    else if (dst.get_state() == 0 && src_state % 2 == 1) {
        // Move the adjacent kitten piece to the next cell in its direction
        src.update(0, empty);
        dst.update(src_state, kitten);
    }
    // If neither of the previous statements has been executed, a blocking has occured
    // as there are two pieces in line with the placed piece
}

void Boop::boop_piece(int i, int j, int src_state, Cell& src, Cell& dst) {   
    // Check if ANY piece will fall off the game board
    if (!is_in_bounds(i, j)) {
        src.update(0, empty);

        if (src_state == 1) 
            p1.incr_kittens();
        else if (src_state == 2) 
            p1.incr_cats();
        else if (src_state == 3) 
            p2.incr_kittens();
        else if (src_state == 4)
            p2.incr_cats();
    }
    else if (dst.get_state() == 0) {
        // Move the adjacent piece to the next cell in its direction
        src.update(0, empty);
        dst.set_state(src_state);

        if (src_state % 2 == 1) 
            dst.set_piece(kitten);
        else 
            dst.set_piece(cat);
    }
    // If neither of the previous statements has been executed, a blocking has occured
    // as there are two pieces in line with the placed piece
}

void Boop::boop(int i, int j, bool is_cat) {
    // Scan for all valid moves to boop
    for (int k = 0; k < BOOP_DIRS; k++) {
        // Form an index pair of the direction of an adjacent cell from the placed piece in the center cell
        int r1_idx = i + br_dirs[k];
        int c1_idx = j + bc_dirs[k];

        // Check whether or not the index pair is within the bounds of the game board
        if (!is_in_bounds(r1_idx, c1_idx)) 
            continue;

        Cell& adjacent = board[r1_idx][c1_idx];
        int adj_state = adjacent.get_state();

        // Check if there is a piece in the adjacent cell
        if (adj_state != 0) {
            // Form an index pair of the cell the booped adjacent piece will move to
            int r2_idx = r1_idx + br_dirs[k];
            int c2_idx = c1_idx + bc_dirs[k];
            Cell& next = board[r2_idx][c2_idx];

            // Perform the rest of the booping system depending on the type of the placed piece
            if (!is_cat)
                boop_kitten(r2_idx, c2_idx, adj_state, adjacent, next);
            else
                boop_piece(r2_idx, c2_idx, adj_state, adjacent, next);
        }
    }
}

bool Boop::validate_selection(string move, Player& player) {
    // Verify the length of the move string
    if (move.length() != 2)
        return false;
    
    char col = (char)toupper(move[0]);
    char row = move.at(1);

    // Verify the row number and column letter
    if (row < '1' || row >= '1' + SIZE) 
        return false;
    if (col < 'A' || col >= 'A' + SIZE) 
        return false;

    int r_idx = get_row_idx(row);
    int c_idx = get_col_idx(col);
    bool is_human = (next_mover() == HUMAN) ? true : false;
    Cell& selected = board[r_idx][c_idx];

    // Check if the current player tries to select an invalid cell to graduate a kitten
    if ((is_human && selected.get_state() != 1) || (!is_human && selected.get_state() != 3))
        return false;

    // Update the selected cell as an empty cell and graduate its kitten into a cat
    selected.update(0, empty);
    player.incr_cats();

    return true;
}

void Boop::select_kitten(Player& player) {
    string move;

    cout << MENU << "Select one kitten to graduate into a cat." << RESET << endl;
    move = get_user_move();

    // Verify the selected move before graduating a kitten
    while (!validate_selection(move, player)) {
        cout << RED << "Invalid selection." << RESET << endl;
        move = get_user_move();
    }
}

Graduation Boop::select_graduation(const vector<Graduation> groups) {
    const int G_SIZE = groups.size();
    int i = 1;
    int choice;
    string ans;

    cout << MENU << "Select one of the following groups of pieces to graduate into cats:" << RESET << endl;

    // Display all options
    for (auto& group : groups) {
        cout << i << ".) ";
        
        for (auto& [i, j] : group.cells) {
            string cell = string(1, get_col(j)) + string(1, get_row(i));
            cout << cell << " ";
        }

        cout << endl;
        i++;
    }

    cout << endl;

    // Prompt the current player to select one group to graduate
    while (true) {        
        cout << "Enter your choice: ";
        getline(cin, ans);

        try {
            choice = stoi(ans);
            if (choice > 0 && choice <= G_SIZE)
                break;
        }
        catch (...) {}

        cout << RED << "Invalid choice." << RESET << endl;
    }

    return groups[choice - 1];
}

void Boop::find_graduations(std::vector<Graduation>& groups) {
    const int PLAYER1 = 0;
    const int PLAYER2 = 1;

    // Search for all possible groups of 3 pieces to graduate
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            int c1_state = (board[i][j]).get_state();
            int c1_owner = (c1_state > 0 && c1_state <= 2) ? PLAYER1 : PLAYER2;

            // Check if the current cell is empty
            if (c1_state == 0)
                continue;

            for (int k = 0; k < DIRS; k++) {
                // Form two index pairs to find 3 pieces in line of same type
                int r1_idx = i + r_dirs[k];
                int c1_idx = j + c_dirs[k];
                int r2_idx = i + 2 * r_dirs[k];
                int c2_idx = j + 2 * c_dirs[k];

                // Check whether the last index pair is in bounds of the game board
                if (!is_in_bounds(r2_idx, c2_idx))
                    continue;
                
                int c2_state = (board[r1_idx][c1_idx]).get_state();
                int c3_state = (board[r2_idx][c2_idx]).get_state();
                
                // Check if either of the adjacent cells is empty
                if (c2_state == 0 || c3_state == 0) 
                    continue;

                int c2_owner = (c2_state <= 2) ? PLAYER1 : PLAYER2;
                int c3_owner = (c3_state <= 2) ? PLAYER1 : PLAYER2;

                // Check if the pieces share the same owner (All player 1's pieces or all player 2's pieces)
                if (c1_owner != c2_owner || c1_owner != c3_owner) 
                    continue;

                Graduation group;
                group.cells = {
                                {i, j},
                                {r1_idx, c1_idx},
                                {r2_idx, c2_idx}
                            };
                group.owner = c1_owner;

                bool is_kitten1 = (c1_state % 2 == 1);
                bool is_kitten2 = (c2_state % 2 == 1);
                bool is_kitten3 = (c3_state % 2 == 1);

                // Determine whether the pieces are all kittens or a combination of kittens and cats
                group.all_kittens = (is_kitten1 && is_kitten2 && is_kitten3);
                group.is_mixed = !(is_kitten1 && is_kitten2 && is_kitten3) && (is_kitten1 || is_kitten2 || is_kitten3);
                
                // Add the graduation group to a vector of all potential groups to graduate
                groups.push_back(group);
            }
        }
    }
}

void Boop::graduate(Player& player) {
    vector<Graduation> groups;
    int kitten_state = (next_mover() == HUMAN) ? 1 : 3;

    // Scan the game board to find all possible groups of 3 pieces for graduation
    find_graduations(groups);

    bool can_graduate = !groups.empty();
    bool all_kittens = has_all_pieces(kitten_state);
    
    if (all_kittens) {
        display_status();
        
        // Check for the rare case of having a 3-in-a-row AND 8 kitten pieces on the board
        if (can_graduate) {
            int choice;
            string ans;

            cout << MENU << "Select one of the following options to activate:" << RESET << endl;
            cout << "1.) Graduate a 3-in-a-row" << endl;
            cout << "2.) Select one kitten on the board to graduate into a cat" << endl << endl;

            while (true) {        
                cout << "Enter your choice: ";
                getline(cin, ans);

                try {
                    choice = stoi(ans);
                    if (choice > 0 && choice <= 2)
                        break;
                }
                catch (...) {}

                cout << RED << "Invalid choice." << RESET << endl;
            }

            // If the current player selects the second option, allow them to graduate one kitten
            if (choice == 2) {
                select_kitten(player);
                return;
            }
        }
        else {
            select_kitten(player);
            return;
        }
    }

    // Check for the rare case of lining up more than 3 pieces in a row OR overlapping 3’s
    if (groups.size() > 1) {
        display_status();

        // Choose which group of 3 pieces to graduate
        Graduation selected = select_graduation(groups);
        groups.clear();
        groups.push_back(selected);
    }

    // Perform kitten graduation
    for (auto& group : groups) {
        // Check for the rare case of detecting a line of 3 pieces with a combination of cats and kittens
        if (group.is_mixed) {
            // Remove them from the board and graduate the kittens into cats
            for (auto& [i, j] : group.cells) {
                (board[i][j]).update(0, empty);

                if (group.owner == 0)
                    p1.incr_cats();
                else
                    p2.incr_cats();
            }
        }
        // Otherwise, graduate all 3 kittens into cats
        else if (group.all_kittens) {
            for (auto& [i, j] : group.cells)
                (board[i][j]).update(0, empty);

            if (group.owner == 0)
                p1.add_cats(3);
            else
                p2.add_cats(3);
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
    Cell& selected = board[r_idx][c_idx];

    // Allow the current player to place a cat piece
    if (player.get_cats() > 0) {
        // Automatically set to true if the current player doesn't have kitten pieces from their pool
        if (player.get_kittens() == 0)
            is_cat = true;
        else {
            string ans;
            
            cout << MENU << "You have " << player.get_cats() << " cat piece(s) available. Would you like to use one?" << RESET << endl;
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
    }

    // Set the current player's piece on the board
    if (!is_cat) {
        selected.update(state, kitten);
        player.decr_kittens();
    } else {
        selected.update(state + 1, cat);
        player.decr_cats();
    }

    // Boop!
    boop(r_idx, c_idx, is_cat);

    // Perform kitten graduation
    graduate(player);

    Game::make_move(move);
}

void Boop::restart() {
    // Implement code here

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
                for (int w = 0; w < CELL_WIDTH; w++) {
                    int state = (board[r][c]).get_state();
                    char piece = (board[r][c]).get_piece(h, w);

                    if (state == 1 || state == 2)
                        cout << YELLOW << piece << RESET;
                    else if (state == 3 || state == 4) 
                        cout << BLUE << piece << RESET;
                    else
                        cout << piece;
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
    int cat_state = (next_mover() == HUMAN) ? 2 : 4;

    // Check if the current player wins by having all 8 of their cat pieces on the board at the end of a turn
    if (has_all_pieces(cat_state))
        return true;
    
    // Scan through the entire board to find 3 matching cat pieces in line
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            int c1_state = (board[i][j]).get_state();

            // Ignore the current cell if it does not contain a cat piece
            if (c1_state != 2 && c1_state != 4) 
                continue;

            // Form two index pairs to determine whether there's a line of 3 cat pieces
            for (int k = 0; k < DIRS; k++) {
                int r1_idx = i + r_dirs[k];
                int c1_idx = j + c_dirs[k];
                int r2_idx = i + 2 * r_dirs[k];
                int c2_idx = j + 2 * c_dirs[k];

                // Check whether the last index pair is in bounds of the game board
                if (!is_in_bounds(r2_idx, c2_idx)) 
                    continue;

                int c2_state = (board[r1_idx][c1_idx]).get_state();
                int c3_state = (board[r2_idx][c2_idx]).get_state();

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
    
    char col = (char)toupper(move[0]);
    char row = move.at(1);

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
