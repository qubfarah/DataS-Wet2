//
// Created by Farah Qub on 16/01/2025.
//

#ifndef DS_WET2_WINTER_2024_2025_JOCKEY_H
#define DS_WET2_WINTER_2024_2025_JOCKEY_H

#include "Team.h"

class Jockey
{
private:
    int id;
    int originalTeamId;
    int record;

    void updateRecord(const int &);

public:
    Jockey();

    Jockey(int jockeyId, int teamId);

    int getId() const;
    int getOriginalTeamId() const;

    void increase_record();
    void decrease_record();

    int getRecord() const;
};

#endif // DS_WET2_WINTER_2024_2025_JOCKEY_H