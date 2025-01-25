// You can edit anything you want in this file.
// However you need to implement all public Plains function, as provided below as a template

#include "plains25a2.h"


static const int HASH_TABLE_SIZE = 1011; // prime num for hash table size



Plains::Plains() {

}

Plains::~Plains() {

}

StatusType Plains::add_team(int teamId) {

    if (teamId <= 0) return StatusType::INVALID_INPUT;

    if (teams.find(teamId) != nullptr) {
        return StatusType::FAILURE; // team already exists
    }else{
        teams.insert(teamId, new Team(teamId));
    }
    Team* team1 = new Team(1);
    team1->parent = team1; // Points to itself
    team1->rank = 1;
    return StatusType::SUCCESS;

}

StatusType Plains::add_jockey(int jockeyId, int teamId) {
    if (jockeyId <= 0 || teamId <= 0) return StatusType::INVALID_INPUT;

    if ((jockeys.find(jockeyId) != nullptr) || teams.find(teamId) == nullptr) {
        return StatusType::FAILURE; // Jockey already exists or team doesn't exist
    }

    Jockey *newjockey = new Jockey(jockeyId, teamId);
    jockeys.insert(jockeyId, newjockey);

    unite(newjockey ,teams.find(teamId)->head);

    return StatusType::SUCCESS;
}

StatusType Plains::update_match(int victoriousJockeyId, int losingJockeyId) {
    if (victoriousJockeyId <= 0 || losingJockeyId <= 0 || victoriousJockeyId == losingJockeyId) {
        return StatusType::INVALID_INPUT;
    }

    Jockey *victorious;
    Jockey *losing;
    if (jockeys.find(victoriousJockeyId, victorious) == nullptr || jockeys.find(losingJockeyId, losing) == nullptr) {
        return StatusType::FAILURE; // One or both jockeys do not exist
    }

    if (victorious->teamId == losing->teamId) {
        return StatusType::FAILURE; // Jockeys are on the same team
    }

    victorious->record += 1;
    teams.find(victorious->teamId, new Team(victorious->teamId)) -> updateTotalRecord(1);

    losing->record -= 1;
    teams.find(losing->teamId, new Team(losing->teamId)) -> updateTotalRecord(-1);

    records.insert(victorious->teamId, new Team(victorious->teamId));
    records.insert(losing->teamId, new Team(losing->teamId));

    return StatusType::SUCCESS;
}

StatusType Plains::merge_teams(int teamId1, int teamId2) {
    if (teamId1 <= 0 || teamId2 <= 0 || teamId1 == teamId2) return StatusType::INVALID_INPUT;

    Jockey *newjockey = new Jockey(jockeyId, teamId);
    Team *team1 = new Team(teamId1);
    Team *team2 = new Team(teamId2);
    if (teams.find(teamId1, team1) == nullptr || teams.find(teamId2, team2) == nullptr) {
        return StatusType::FAILURE; // One or both teams do not exist
    }

    Uptree_teams.unite(team1, team2);

    if (team1->totalRecord < team2->totalRecord) {
        team1->id = team2->id;
    } else {
        team2->id = team1->id;
    }

    return StatusType::SUCCESS;
}

StatusType Plains::unite_by_record(int record) {
    if (record <= 0) return StatusType::INVALID_INPUT;

    if (records.find(teamId1, team1) == nullptr || teams.find(teamId2, team2) == nullptr) {
        return StatusType::FAILURE; // One or both teams do not exist
    }

    Team *positiveRecordTeam = nullptr;
    Team *negativeRecordTeam = nullptr;

    for (int i = 0; i < teams.get_capacity(); ++i) {
        Team *team;
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

output_t<int> Plains::get_jockey_record(int jockeyId) {
    if (jockeyId <= 0) return INVALID_INPUT;

    Jockey *jockey;
    if (jockeys.find(jockeyId, jockey) == nullptr) {
        return StatusType::FAILURE; // Jockey does not exist
    }

    return jockey->record;
    return StatusType::SUCCESS;
    return 0;
}

output_t<int> Plains::get_team_record(int teamId) {
    if (teamId <= 0) return INVALID_INPUT;

    Team *team;
    if (teams.find(teamId, team) == nullptr) {
        return StatusType::FAILURE; // Team does not exist
    }

    return team->totalRecord;
    return 0;
}
