//
// Created by Farah Qub on 16/01/2025.
//

#ifndef DS_WET2_WINTER_2024_2025_TEAM_H
#define DS_WET2_WINTER_2024_2025_TEAM_H



class Team {
public:
    int id;
    int totalRecord;

    // when this team has been merged, and no longer considered an active record.
    bool isMerged;

    Team() = default;


    Team(int teamId) : id(teamId), totalRecord(0), isMerged(false) {}

    void deactivate() {
        isMerged = true;
    }
};


#endif //DS_WET2_WINTER_2024_2025_TEAM_H

