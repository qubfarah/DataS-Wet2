//
// Created by Farah Qub on 16/01/2025.
//

#ifndef DS_WET2_WINTER_2024_2025_JOCKEY_H
#define DS_WET2_WINTER_2024_2025_JOCKEY_H

#endif //DS_WET2_WINTER_2024_2025_JOCKEY_H
class Jockey {
public:
    int id;            // Unique ID
    Jockey* parent;    // Parent in the up-tree
    int rank;          // Rank for union-find
    int record;  // record
    int teamId;

    // Constructor
    explicit Jockey(int id, int teamId)
            : id(id), parent(this), rank(0), record(0), teamId(teamId) {}
};

