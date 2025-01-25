//
// Created by Farah Qub on 16/01/2025.
//

#ifndef DS_WET2_WINTER_2024_2025_TEAM_H
#define DS_WET2_WINTER_2024_2025_TEAM_H

#include "UnionFind.h"

class Team {
public:
    int id;
    int totalRecord;
    Jockey* head;
    Team* parent;    // Parent in the up-tree
    int rank;          // Rank for union-find


    explicit Team(int teamId) : id(teamId), parent(this), rank(0), totalRecord(0);

    void updateTotalRecord(int rec){
        totalRecord += rec;
    }
};

#endif //DS_WET2_WINTER_2024_2025_TEAM_H
