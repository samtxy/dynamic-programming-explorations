///////////////////////////////////////////////////////////////////////////////
// poly_exp.cpp
//
// Definitions for two algorithms:
//
// soccer_exhaustive
// soccer_dyn_prog
//
///////////////////////////////////////////////////////////////////////////////

#include "poly_exp.hpp"
#include <iostream>
#include <stdexcept>
#include<list>
#include<vector>
#include<cmath>
using namespace std;

int algorithms::soccer_exhaustive(const std::vector<std::string> field) {
    if (field.size() == 0) {
        throw invalid_argument("ERROR: the input matrix cannot be empty.");
    }

    int len, counter, bit, templ;
    const int r = field.size();
    const int c = field.at(0).size();
    len = r + c - 2;
    counter = 0;
    string rightmove = "RIGHT";
    string downmove = "DOWN";
    bool at_destination = false;
    bool basecase = false;

    vector <string> candidate;
    int temp_r, temp_c, blocked;
    blocked = 0;
    temp_r = 0;
    temp_c = 0;
    int p = 2;
    templ = pow(len, p) - 1;

    if (r == 0 || c == 0 || len > 31) {
        throw invalid_argument("ERROR: Zero rows or zero columns in the input matrix.");
    }

    else {
        for (int i = 0; i < r; ++i) {
            if (field[i].size() != c) throw invalid_argument("ERROR: one row may be too short or one row may be too long.");

            for (int j = 0; j < c; ++j) {
                if (field[i][j] != '.' && field[i][j] != 'X') throw invalid_argument("ERROR: Only '.' and 'X' are allowed in the input matrix. Try again with only these characters.");
            }
        }
    }

    if (r == 1 && c == 1 && field[0][0] == '.') {
        counter = 1;
    }

    if (field.size() == 1 && field[0][0] == '.' && candidate.size() == 0 && c == 0) {

        basecase = true;

    }
    for (int bits = 0; bits <= pow(p, len) - 1; bits++)
    {
        for (int k = 0; k <= len - 1; k++)
        {

            bit = (bits >> k) & 1;
            if (bit == 1) {
                candidate.push_back(rightmove);
                temp_c++;
                if (temp_r < r && temp_c < c)
                    if (field[temp_r][temp_c] == 'X') {

                        blocked++;

                    }
                if (temp_r == (r - 1) && temp_c == (c - 1)) {
                    at_destination = true;
                }
            }

            else {
                candidate.push_back(downmove);
                temp_r++;
                if (temp_r < r && temp_c < c)
                {
                    if (field[temp_r][temp_c] == 'X') {

                        blocked++;

                    }
                    if (temp_r == (r - 1) && temp_c == (c - 1)) {
                        at_destination = true;
                    }
                }
            }
        }

        if ((temp_r < r && temp_c < c && blocked == 0 && at_destination == true) || basecase == true) {
            counter++;
        }
        candidate.clear();
        temp_r = 0;
        temp_c = 0;
        blocked = 0;
        at_destination = false;
    }
    return counter;
}
 
int algorithms::soccer_dyn_prog(const std::vector<std::string> field) {
    if (field.size() == 0){
        throw invalid_argument("ERROR: the input matrix cannot be empty.");
    }

    // GENERAL ERROR-HANDLING CASES:
    const int rowSize = field.size();
    const int colSize = field.at(0).size();

    if (rowSize == 0 || colSize == 0){
        throw invalid_argument("ERROR: Zero rows or zero columns in the input matrix.");
    }else{
        for (int i = 0 ; i < rowSize; ++i){
            if (field[i].size() != colSize) throw invalid_argument("ERROR: one row may be too short or one row may be too long.");

            for (int j = 0; j < colSize; ++j){
                if (field[i][j] != '.' & field[i][j] != 'X') throw invalid_argument("ERROR: Only '.' and 'X' are allowed in the input matrix. Try again with only these characters.");
            } // ^ Only one '&' condition checks both parts of the condition, while '&&' checks one to see if it's true and if it's not then it doesn't bother to check the rest. (CHECK TO CONFIRM if you really want to know if this is correct.)
        }
    }
    // New r⨉c matrix initialized to zeroes (which is the default for this template stuff):
    std::vector<std::vector<int> > A(rowSize, std::vector<int>(colSize));
    // BASE CASE:
    A[0][0] = 1;
    // GENERAL CASES:
    for (int i = 0; i < rowSize; ++i){
        for (int j = 0; j < colSize; ++j){
            if (field[i][j] == 'X'){
                A[i][j] = 0;
                continue;
            }
            int above = 0, from_left = 0;
            
            if (i > 0 && field[i-1][j] == '.') above = A[i-1][j];
            if (j > 0 && field[i][j-1] == '.') from_left = A[i][j-1];
            A[i][j] += above + from_left;
        }
    }

    return A[rowSize-1][colSize-1];
}