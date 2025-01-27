//
// Created by jamal on 27/01/2025.
//

#ifndef PLAINSDEBUG_H
#define PLAINSDEBUG_H
#include <map>

#include "Jockey.h"
#include "Team.h"
#include "UnionFind.h"
#include "wet2util.h"

class PlainsDebug {
private:
    std::map<int, Team> teams;
    std::map<int, Jockey> jockeys;


    std::map<int, int> jockyRecord;
    std::map<int, int> teamRecord;
    std::map<int, int> setIdentifier;


    // for every jockey added, a set by it's id is created
    // if the team the jockey is added to empty, then the teams set id is this jockey id,
    // if not, then the jockey is merged with the team's set id.
    // therefore, in terms of length of hashtable, it's O(n)
    // but in terms of active sets, it's O(m).
    // UnionFind jockeysTeamMembership;
    UnionFind teamMembership;

    template<typename T>
    bool exists(std::map<int, T> &map, int id) {
        return map.find(id) == map.end();
    }

    bool invalid_team(int teamId) {
        return !exists(teams, teamId) || teams[teamId].isMerged;
    }

    //TODO: remove
public:
    int commandId = 0;

public:
    // <DO-NOT-MODIFY> {
    Plains();

    ~Plains();


    StatusType add_team(int teamId) {
        if (teamId <= 0) return StatusType::INVALID_INPUT;

        if (exists(teams, teamId)) return StatusType::FAILURE;

        teams[teamId] = Team(teamId);

        setIdentifier[teamMembership.makeset(teamId)]= teamId;

        teamRecord[teamId] = 0;

        return StatusType::SUCCESS;
    }

    StatusType add_jockey(int jockeyId, int teamId) {
        if (jockeyId <= 0 || teamId <= 0) return StatusType::INVALID_INPUT;

        if (exists(jockeys, jockeyId)) return StatusType::FAILURE;

        if (invalid_team(teamId)) return StatusType::FAILURE;

        jockeys[jockeyId] = Jockey(jockeyId, teamId);

        return StatusType::SUCCESS;
    }

    StatusType update_match(int victoriousJockeyId, int losingJockeyId) {
        if (victoriousJockeyId <= 0 || losingJockeyId <= 0 || victoriousJockeyId == losingJockeyId) {
            return StatusType::INVALID_INPUT;
        }

        if (!exists(jockeys, victoriousJockeyId) || !exists(jockeys, losingJockeyId)) return StatusType::FAILURE;

        Jockey &victorious = jockeys[victoriousJockeyId];

        Jockey &losing = jockeys[losingJockeyId];

        auto victoriousTeamId = teamMembership.find(victorious.originalTeamId);
        auto losingTeamId = teamMembership.find(losing.originalTeamId);;

        if (victoriousTeamId == losingTeamId) {
            return StatusType::FAILURE;
        }


        victorious.record += 1;
        losing.record -= 1;

        teamRecord[victoriousTeamId] += 1;
        teamRecord[losingTeamId] -= 1;

        // utils.updateRecord(victoriousTeam, victoriousTeam->totalRecord + 1);
        // utils.updateRecord(losingTeam, losingTeam->totalRecord - 1);
        //
        // // assert(records[victoriousTeam->totalRecord + 1] == recordTokens[victoriousTeam->id]);
        //
        // auto r1 = records.search(std::abs(victoriousTeam->totalRecord));
        // auto r2 = records.search(std::abs(losingTeam->totalRecord));


        return StatusType::SUCCESS;
    }

    StatusType merge_teams(int teamId1, int teamId2) {
        if (teamId1 <= 0 || teamId2 <= 0 || teamId1 == teamId2) return StatusType::INVALID_INPUT;

        if (invalid_team(teamId1) || invalid_team(teamId2)) return StatusType::FAILURE;

        auto team1 = teams[teamId1];
        auto team2 = teams[teamId2];

        bool mergeToFirst = teamRecord[teamId1] >= teamRecord[teamId2];

        if (mergeToFirst) {
            team2.deactivate();
        } else {
            team1.deactivate();
        }

        teamMembership.unite(teamId1, teamId2);

        return StatusType::SUCCESS;
    }

    StatusType unite_by_record(int record);

    output_t<int> get_jockey_record(int jockeyId);

    output_t<int> get_team_record(int teamId);

    // } </DO-NOT-MODIFY>
};

#endif //PLAINSDEBUG_H
