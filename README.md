# boop.
A remake of the 2022 C++ implementation based on a deceptively cute but deceivingly challenging abstract strategy game for two players.

## Game Description
*boop.* is an abstract strategy board game where you place a kitten on the board and boops every other kitten next to the placed piece on the board one space away. Line up three kittens in a row on the board to graduate them into cat pieces, and then line up three cats in a row to win the game.

However, that isn't easy as you and the opponent are constantly "booping" kittens around. Can you “boop” your cats into position to win? Or will you just get "booped" right off the board?

### Rules:
#### Contents & Set-Up
Two players begin the game with 8 Kittens of their color (blue for Player 1 and yellow for player 2). The 8 Cats of their color begin “out of play” to the far side of the board. If playing with an AI opponent, the human player will be the first to play-- or choose the first player if playing a round of human vs. human.
#### "Booping"
Lining up a row of three pieces isn't easy because whenever a piece is added to the board, that piece will "boop" all of its adjacent pieces by pushing them one space away, including diagonally.

It is possible for a piece to be "booped" right off the board, in which case it is returned to its player's pool of pieces.

A piece that was "booped" does NOT cause a chain reaction once it moves into a new space. The other pieces it moves towards do not move away in reaction.

A blocking will occur if there are any two pieces already in line with a placed piece. This is true regardless of the colors of the pieces. 

Setting up a line of two and defending against it is an important strategy. So, breaking up or blocking your opponent's line of two is cruical to winning the game!

#### Graduating Kittens into Cats
After the "booping" process, the board will be scanned to see if you have 3 kittens in a row. Getting 3 kittens in a horizontally, vertically, or diagonally will result in graduating those pieces into cats.

Once the kittens are graduated into cats, those pieces are then removed from the board and are permanately out of the game as those pieces are replaced with now available cat pieces from the reserve. Remember that you will ALWAYS have 8 active pieces in the game.

Alternatively, if all 8 of your pieces are on the board, you may graduate any one kitten into a cat by removing it from the game and putting a reserved cat into your pool. You could place a cat back into your pool, instead of graduating a kitten.

In a rare case of lining up more than three in a row, or multiple connected 3's, choose which group of 3 to graduate, leaving the remaining pieces on the board. Likewise, if you have both a three in a row and eight pieces on the board, choose which you would activate.

#### Cats
Once cats are in your active pool, you may choose to play either a cat or kitten on your turn. Cats behave the same way as kittens in all respect, expect that **cats CANNOT be booped by kittens**. However, cats can "boop" other cats as well as kittens.

When you line up 3 of your pieces with a combination of cats and kittens, you still remove all three pieces from the board and graduate any kittens. The cats in the group will go back into the pool, as do any newly graduated cats.

#### Winning
When you line up three of your cats in a row horizontally, vertically, or diagonally, you win the game. Alternatively, a player can win the game by having all 8 of their cat pieces on the board at the end of a turn.

## Features:
* "Booping" Mechanism 
* Kitten Graduation (Kitten -> Cat)
* Human VS. Human
* Human VS. AI

## Project Structure:
```
boop/
├── app/
│   └── main.cc
├── docs/
│   └── Boop_Rules.pdf
├── include/
│   ├── boop.h
│   ├── colors.h
│   └── game.h
├── src/
│   ├── boop.cc
│   ├── game.cc
├── Makefile
└── README.md
```

## Installation & Setup :
### Prerequisites
* C++17 or later
* CMake
* GCC
### Installation
```
git clone git@github.com:braeden-rodgers/boop.git
cd boop
make
```
### Running the Game
```
make run
```
or 
```
./build/boop
```

## Usage:
* Launch the executable 
* Follow the prompts on-screen to start a game
* Players alternate turns placing pieces
* The game ends when a win condition is met
### Controls
* User input is handled via terminal (e.g., row/column selection)
* Invalid moves are rejected

## AI
WIP

## Testing:
WIP
### Running the Tests
`make test`

## Screenshots
WIP

## Concepts & Learning Goals:
* Object-Oriented Programming (OOP) in C++
* Game loop design and state management
* Board representation and data structures
* Algorithmic thinking
* Clean, modular code organization

## Known Issues/TODO:
* Implement an AI opponent

## Acknowledgements:
* Original *boop.* game designers for the game concept
* Developers at Ohio Univeristy for the base version of the class Game files
