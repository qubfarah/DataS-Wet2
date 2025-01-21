//
// Created by Farah Qub on 16/01/2025.
//

#ifndef DS_WET2_WINTER_2024_2025_JOCKEY_H
#define DS_WET2_WINTER_2024_2025_JOCKEY_H

class Jockey {
public:
    int id;
    int teamId;
    int record;

    Jockey(int jockeyId, shared_ptr<Team>); 

    Jockey(int jockeyId, int teamId)
            : id(jockeyId), teamId(teamId), record(0) {}
};


#endif //DS_WET2_WINTER_2024_2025_JOCKEY_H