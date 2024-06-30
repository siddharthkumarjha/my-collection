/*
Simulation of card movement on a 2D grid

Description:
    Given an application that organizes info by arranging cards with notes on them into lists on a 2d-grid.
    These notes can be moved across multiple lists.

    eg include billboard-based task management such as Trello and Jira

        Board1            Board 2          Board 3
    --------------    --------------    --------------
    | ---------- |    | ---------- |    | ---------- |
    | | Task 1 | |    | | Task 3 | |    | | Task 4 | |
    | ---------- |    | ---------- |    | ---------- |
    | ---------- |    |            |    | ---------- |
    | | Task 2 |-|--->|            |    | | Task 5 | |
    | ---------- |    |            |    | ---------- |
    |____________|    |____________|    |____________|

    The first argument, cards, is given a value indicating the initial position of all cards in the board,
    each as a 2d array, with the following rules
            [CardID, RowIndex, ColumnIndex]
    Here, the row and column indexes are assumed to be zero based indexed.

    The second argument, moves, is a 2d array of values indicating the movement of the cards,
    each with the following rules,
            [CardID, Row index before move, Column index before move, Dest. Row index, Dest. Column index]
    
    Here, the row and column indexes are 0 based valid values(you don't have to assume every index is not valid)

    The 3rd arg., query is an int type value indicating the ID of the card to be moved.
    Based on the given cards and moves, 
    implement a function that returns the final position of the card specified in the 3rd arg. as,
        [row index, col index]

    Note the following rules are said to exist for moving cards,
        - When a card is moved and if there is another card at the destination, the existing card is moved down one row
        - Also, when a card is moved, other cards in the original column move up one.
        - Cards can be moved to the same row and column as before
        - There shall be no gaps in initial placement
        - We can assume that the coordinates before a move is correct.
*/

#include "2d-grid.hpp"
#include <iostream>

void move(
    std::map<std::pair<int, int>, int> &pos,
    std::pair<int, int> oldCord,
    std::pair<int, int> newCord
    )
{
    std::printf("DBG: oldCord: [%d, %d] | newCord: [%d, %d]\n", oldCord.first, oldCord.second, newCord.first, newCord.second);
    
    auto newCordItr = pos.find(newCord);
    auto oldCordItr = pos.find(oldCord);

    if(newCordItr == pos.end())
    {
        pos[newCord] = oldCordItr->second;
        oldCordItr->second = -1;
    }
    else
    {
        move(pos, newCord, std::make_pair(newCord.first + 1, newCord.second));
        newCordItr->second = oldCordItr->second;
        oldCordItr->second = -1;

        for(auto &[key, value] : pos)
        {
            if(key.second == oldCord.second && oldCord.first < key.first && value > -1)
            {
                pos[std::make_pair(key.first - 1, key.second)] = value;
                value = -1;
            }
        }
    }

}

std::vector<int> solution(
    std::vector<std::vector<int>> &cards, 
    std::vector<std::vector<int>> &moves, 
    int &query
    )
{
    std::vector<int> ans;
    ans.reserve(2);

    std::map<std::pair<int, int>, int> pos;
    for(const auto &cRef : cards)
    {
        std::pair<int, int> cord = std::make_pair(cRef[1], cRef[2]);
        pos[cord] = cRef[0];
    }

    for(const auto &mRef : moves)
    {
        std::pair<int, int> oldCord = std::make_pair(mRef[1], mRef[2]);
        std::pair<int, int> newCord = std::make_pair(mRef[3], mRef[4]);

        std::printf("Pos Map:\n");
        move(pos, oldCord, newCord);

        for(const auto &[key, value] : pos)
            std::printf("x: %d y: %d | %d\n", key.first, key.second, value);
    }

    std::printf("Cards: [CardID, x, y]\n");
    for(const auto &cRef : cards)
    {
        std::printf("[%d, %d, %d], ", cRef[0], cRef[1], cRef[2]);
    }
    std::printf("\nMoves: [CardID, Xold, Yold, Xnew, Ynew]\n");
    for(const auto &mRef : moves)
    {
        std::printf("[%d, %d, %d, %d, %d] ", mRef[0], mRef[1], mRef[2], mRef[3], mRef[4]);
    }
    std::printf("\nquery: %d\n", query);

    for(const auto &[key, value] : pos)
    {
        if(value == query)
        {
            ans.push_back(key.first);
            ans.push_back(key.second);
        }
    }
    return ans;
}