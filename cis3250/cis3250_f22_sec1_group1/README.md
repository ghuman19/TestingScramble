# BOGGLE (CIS3250_F22_Sec1_Group1)

## Purpose
This program will be a fully working and efficient version of the popular game BOGGLE
by the end of the FALL 2022 semester at UoG.

## Functionality
As of Oct 20, 2022, this program now has a Main Menu with these options
    
    - Singleplayer (play game)
    - View Rules
    - View User Scores
    - View Highscores
    - Exit

As of Sept 29, 2022, this program can run a very basic, terminal text-based version of boggle.
Enter in your guesses like you would on any other version of boggle, and the game will give
you points based on your performance!


## Contributions
There were three groups of pairs that each worked to update and evolve the current code base.
### GROUP ONE (Nathan Starkman, Nathan Feenstra):
- Created Rule Printing Fuction, which takes a custom written rules documents and prints it for the user if desired. 
- Began development on AllPossibleWords Function, still work in progress
- Created PrintTops function, which shows the highest scoring player in each scoring category (Game Amounts, Overall Scores, current game score)
### GROUP TWO (Harry Ghuman, Nitin Satishbabu):
- Removed testing code functions
- Found all redundant and unneccary code and removed it
- Major bug testing 
### GROUP THREE (Mahad Asif, Michael Janeway):
- Refactored boggle.c
- Added User and User File functionality (Added capability to save a user and maintain that user for multiple times the code is run)
- Added main Menu file and functionality


## How to run
To run our boggle game, simply run:

```
make
./boggle
```

in a terminal in the folder of this repo.

Ensure that your terminal supports the **make** command to make sure that 
the above instructions work.

Also, run:
```
make clean
```
to clear the files produced by the make command to free up space in your repo!