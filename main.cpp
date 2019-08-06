#include <iostream>
#include <vector>
#include <string>
#include <algorithm>


//Its just bubble sort.
void sort(std::vector<int>& vect){
    for(unsigned int i = 0; i < vect.size(); i++){
        for(unsigned int j = 0; j < vect.size() - 1; j++){
            if(vect[j] > vect[j + 1]){
                int temp = vect[j];
                vect[j] = vect[j + 1];
                vect[j+1] = temp;
            }
        }
    }
}

bool checkVect(std::vector<std::vector<int>>& vect){
    for(unsigned int i = 0; i < vect.size(); i++){
        //sort the current tracker
        sort(vect[i]);
        for(unsigned int j = 0; j < vect[i].size() - 1; j++){
            //if a duplicate is found, it is not a valid board
            if(vect[i][j] == vect[i][j + 1]) return false;
        }
    }
    return true;
}

bool validate(const std::vector<std::vector<int>>& board){
    //check if there is the correct number of rows
    if(board.size() != 9) return false;

    //check if there is the correct number of columns
    for(unsigned int i = 0; i < board.size(); i++){
        if(board[i].size() != 9) return false;
    }

    //vector of vectors to keep track of numbers
    //Size of 27 for 9 rows + 9 columns + 9 nonets
    std::vector<std::vector<int>> values(27);

    for(unsigned int i = 0; i < board.size(); i++){
        for(unsigned int j = 0; j < board[i].size(); j++){
            //if a number outside the range 1 - 9 is found, it is not a valid board
            if(board[i][j] > 9 || board[i][j] < 1) return false;
            //put the value at i,j into the current row tracker
            values[i].push_back(board[i][j]);
            //put the value at j,i into the current column tracker
            values[i + 9].push_back(board[j][i]);

            //value for current nonet
            unsigned int nonet;

            //determain the current nonet row
            if(i < 3) nonet = 0;
            else if (i < 6) nonet = 3;
            else nonet = 6;

            //offset current nonet row with current nonet column
            if(j < 3) nonet += 0;
            else if (j < 6) nonet += 1;
            else nonet += 2;

            //put the value of i,j into the current nonet tracker
            values[nonet + 18].push_back(board[i][j]);
        }
    }
    return checkVect(values);
}

int main() {

    //A valid test board
    std::vector<std::vector<int>> table1 =
            {
                    {1,2,3,4,5,6,7,8,9},
                    {4,5,6,7,8,9,1,2,3},
                    {7,8,9,1,2,3,4,5,6},
                    {2,3,4,5,6,7,8,9,1},
                    {5,6,7,8,9,1,2,3,4},
                    {8,9,1,2,3,4,5,6,7},
                    {9,1,2,3,4,5,6,7,8},
                    {3,4,5,6,7,8,9,1,2},
                    {6,7,8,9,1,2,3,4,5}
            };


    if(validate(table1)) std::cout << "Valid sudoku table" << std::endl;
    else std::cout << "Invalid sudoku table" << std::endl;

    //An invalid test board
    std::vector<std::vector<int>> table2 =
            {
                    {7,2,3,4,5,6,7,8,9},
                    {4,5,6,7,8,9,1,2,3},
                    {7,8,9,1,2,3,4,5,6},
                    {2,3,4,5,6,7,8,9,1},
                    {5,6,7,8,9,1,2,3,4},
                    {8,9,1,2,3,4,5,6,7},
                    {9,1,2,3,4,5,6,7,8},
                    {3,4,5,6,7,8,9,1,2},
                    {6,7,8,9,1,2,3,4,5}
            };


    if(validate(table2)) std::cout << "Valid sudoku table" << std::endl;
    else std::cout << "Invalid sudoku table" << std::endl;

    return 0;
}