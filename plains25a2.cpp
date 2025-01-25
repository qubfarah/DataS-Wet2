// You can edit anything you want in this file.
// However you need to implement all public Plains function, as provided below as a template

#include "plains25a2.h"


Plains::Plains() : utils(this)
{
}

Plains::~Plains()
{
}

StatusType Plains::add_team(int teamId)
{
    if (teamId <= 0) return StatusType::INVALID_INPUT;

    if (teams.exists(teamId)) return StatusType::FAILURE;

    teams.insert(teamId, Team(teamId));

    recordTokens.insert(teamId, RecordToken(teamId));;

    teamMembership.makeset(teamId);

    // starting at 0
    utils.add_record_token(recordTokens[teamId], 0);

    return StatusType::SUCCESS;
}

StatusType Plains::add_jockey(int jockeyId, int teamId)
{
    if (jockeyId <= 0 || teamId <= 0) return StatusType::INVALID_INPUT;

    const auto team = teams.search(teamId);

    if (utils.invalid(team)) return StatusType::FAILURE;

    jockeys.insert(jockeyId, Jockey(jockeyId, team->id));

    return StatusType::SUCCESS;
}

StatusType Plains::update_match(int victoriousJockeyId, int losingJockeyId)
{
    if (victoriousJockeyId <= 0 || losingJockeyId <= 0 || victoriousJockeyId == losingJockeyId)
    {
        return StatusType::INVALID_INPUT;
    }

    const shared_ptr<Jockey> victorious = jockeys.search(victoriousJockeyId);
    const shared_ptr<Jockey> losing = jockeys.search(losingJockeyId);

    if (victorious == nullptr || losing == nullptr) return StatusType::FAILURE;

    if (utils.inSameTeamMembership(victorious, losing))
    {
        return StatusType::FAILURE;
    }

    auto victoriousTeam = utils.team(victorious);
    auto losingTeam = utils.team(losing);


    victorious->record += 1;
    losing->record -= 1;

    utils.updateRecord(victoriousTeam, victoriousTeam.totalRecord + 1);
    utils.updateRecord(losingTeam, losingTeam.totalRecord - 1);

    return StatusType::SUCCESS;
}

StatusType Plains::merge_teams(int teamId1, int teamId2)
{
    if (teamId1 <= 0 || teamId2 <= 0 || teamId1 == teamId2) return StatusType::INVALID_INPUT;

    const auto team1 = teams.search(teamId1);
    const auto team2 = teams.search(teamId2);

    if (team1 == nullptr || team2 == nullptr) return StatusType::FAILURE;

    bool mergeToFirst = team1->totalRecord >= team2->totalRecord;

    utils.merge_teams(team1, team2, mergeToFirst);

    return StatusType::SUCCESS;
}

StatusType Plains::unite_by_record(int record)
{
    if (record <= 0) return StatusType::INVALID_INPUT;

    auto recordsList1 = records.search(record);

    if (recordsList1 == nullptr) return StatusType::FAILURE;

    RecordToken* record1 = *recordsList1;

    // we want exactly 1 in the list.
    if (record1->next != nullptr) return StatusType::FAILURE;


    auto recordsList2 = records.search(-record);

    if (recordsList2 == nullptr) return StatusType::FAILURE;

    RecordToken* record2 = *recordsList2;

    // we want exactly 2 in the list.
    if (record2->next != nullptr) return StatusType::FAILURE;


    utils.merge_teams(record1->teamId, record2->teamId, true);


    // No such teams found
    return StatusType::FAILURE;
}

output_t<int> Plains::get_jockey_record(int jockeyId)
{
    if (jockeyId <= 0) return StatusType::INVALID_INPUT;

    const auto jockey = jockeys.search(jockeyId);
    if (jockey == nullptr) return StatusType::FAILURE;

    return jockey->record;
}

output_t<int> Plains::get_team_record(int teamId)
{
    if (teamId <= 0) return StatusType::INVALID_INPUT;

    const auto team = teams.search(teamId);

    if (utils.invalid(team)) return StatusType::FAILURE;

    return team->totalRecord;
}
