// You can edit anything you want in this file.
// However you need to implement all public Plains function, as provided below as a template

#include "plains25a2.h"


static const int HASH_TABLE_SIZE = 1011; // prime num for hash table size



Plains::Plains()
{

}

Plains::~Plains()
{

}

StatusType Plains::add_team(int teamId)
{
    if (teamId <= 0) return StatusType::INVALID_INPUT;

    if(teams.exists(teamId)) return StatusType::FAILURE;

    teams[teamId] = move(Team(teamId));

    return StatusType::SUCCESS;
}

StatusType Plains::add_jockey(int jockeyId, int teamId)
{
    if (jockeyId <= 0 || teamId <= 0) return StatusType::INVALID_INPUT;

    auto team = teams.search(teamId);

    if(team == nullptr) return StatusType::FAILURE;

    jockeys[jockeyId] = move(Jockey(jockeyId, team));

    return StatusType::SUCCESS;
}

StatusType Plains::update_match(int victoriousJockeyId, int losingJockeyId)
{
    if (victoriousJockeyId <= 0 || losingJockeyId <= 0 || victoriousJockeyId == losingJockeyId) {
        return StatusType::INVALID_INPUT;
    }

    Jockey* victorious;
    Jockey* losing;
    if (!jockeys.find(victoriousJockeyId, victorious) || !jockeys.find(losingJockeyId, losing)) {
        return StatusType::FAILURE; // One or both jockeys do not exist
    }

    if (victorious->teamId == losing->teamId) {
        return StatusType::FAILURE; // Jockeys are on the same team
    }

    victorious->record += 1;
    losing->record -= 1;
    return StatusType::SUCCESS;
}

StatusType Plains::merge_teams(int teamId1, int teamId2)
{
    if (teamId1 <= 0 || teamId2 <= 0 || teamId1 == teamId2) return StatusType::INVALID_INPUT;

    Team* team1;
    Team* team2;
    if (!teams.find(teamId1, team1) || !teams.find(teamId2, team2)) {
        return StatusType::FAILURE; // One or both teams do not exist
    }

    unionFind.unite(teamId1, teamId2);

    if (team1->totalRecord < team2->totalRecord) {
        team1->id = team2->id;
    } else {
        team2->id = team1->id;
    }

    return StatusType::SUCCESS;
}

StatusType Plains::unite_by_record(int record)
{
    if (record <= 0) return StatusType::INVALID_INPUT;

    Team* positiveRecordTeam = nullptr;
    Team* negativeRecordTeam = nullptr;

    for (int i = 0; i < teams.get_capacity(); ++i) {
        Team* team;
        if (teams.find(i, team)) {
            if (team->totalRecord == record) {
                positiveRecordTeam = team;
            } else if (team->totalRecord == -record) {
                negativeRecordTeam = team;
            }

            if (positiveRecordTeam && negativeRecordTeam) {
                return merge_teams(positiveRecordTeam->id, negativeRecordTeam->id);
            }
        }
    }
    // No such teams found
    return StatusType::FAILURE;
}

output_t<int> Plains::get_jockey_record(int jockeyId)
{
    if (jockeyId <= 0) return INVALID_INPUT;

    Jockey* jockey;
    if (!jockeys.find(jockeyId, jockey)) {
        return StatusType::FAILURE; // Jockey does not exist
    }

    return jockey->record;
    return StatusType::SUCCESS;
    return 0;
}

output_t<int> Plains::get_team_record(int teamId)
{
    if (teamId <= 0) return INVALID_INPUT;

    Team* team;
    if (!teams.find(teamId, team)) {
        return FAILURE; // Team does not exist
    }

     return team->totalRecord;
    return 0;
}
