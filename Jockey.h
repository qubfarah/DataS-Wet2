//
// Created by Farah Qub on 16/01/2025.
//

#ifndef DS_WET2_WINTER_2024_2025_JOCKEY_H
#define DS_WET2_WINTER_2024_2025_JOCKEY_H

#include "Team.h"

class Jockey {
public:
    int id;
    int originalTeamId;
    int record;

Jockey() = default;

    Jockey(int jockeyId, int teamId)
            : id(jockeyId), originalTeamId(teamId), record(0) {}
};


#endif //DS_WET2_WINTER_2024_2025_JOCKEY_H