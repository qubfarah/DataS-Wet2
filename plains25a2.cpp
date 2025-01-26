// You can edit anything you want in this file.
// However you need to implement all public Plains function, as provided below as a template

#include "plains25a2.h"

#include <cassert>

#define ERROR_GUARD(x) try {x} catch(...) { return StatusType::ALLOCATION_ERROR; }
#define EXCEPTION_GUARD(code)         \
try {                             \
code                          \
} catch (const std::exception &e) \
{                                 \
std::cerr << "Exception: " << e.what() << std::endl; \
} catch (...) {                   \
std::cerr << "Unknown exception occurred." << std::endl; \
}

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
    utils.add_record_token(recordTokens.search(teamId), 0);

    return StatusType::SUCCESS;
}

StatusType Plains::add_jockey(int jockeyId, int teamId)
{
    if (jockeyId <= 0 || teamId <= 0) return StatusType::INVALID_INPUT;

    if (jockeys.exists(jockeyId)) return StatusType::FAILURE;

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

    utils.updateRecord(victoriousTeam, victoriousTeam->totalRecord + 1);
    utils.updateRecord(losingTeam, losingTeam->totalRecord - 1);

    // assert(records[victoriousTeam->totalRecord + 1] == recordTokens[victoriousTeam->id]);

    auto r1 = records.search(std::abs(victoriousTeam->totalRecord));
    auto r2 = records.search(std::abs(losingTeam->totalRecord));


    return StatusType::SUCCESS;
}

StatusType Plains::merge_teams(int teamId1, int teamId2)
{
    if (teamId1 <= 0 || teamId2 <= 0 || teamId1 == teamId2) return StatusType::INVALID_INPUT;

    const auto team1 = teams.search(teamId1);
    const auto team2 = teams.search(teamId2);

    if (utils.invalid(team1) || utils.invalid(team2)) return StatusType::FAILURE;

    bool mergeToFirst = team1->totalRecord >= team2->totalRecord;

    utils.merge_teams(team1, team2, mergeToFirst, false);

    return StatusType::SUCCESS;
}

#include <stdio.h>

StatusType Plains::unite_by_record(int record)
{
    if (record <= 0) return StatusType::INVALID_INPUT;

    auto recordsList = records.search(record);
    if (recordsList == nullptr) return StatusType::FAILURE;


    for(auto team : teams)
    {
        if(team == nullptr || utils.invalid(team)) continue;
        std::cout << team->id << ": " <<team->totalRecord << std::endl;
    }

    if(commandId==170)
    {
        auto team2 = teams.search(5018);
        auto x = recordTokens.search(5018);
    }

    auto first = recordsList;
    auto second = first->next;

    // has 1 or more than 2:
    // if(second == nullptr) return StatusType::ALLOCATION_ERROR;
    if (second == nullptr || second->next != nullptr) return StatusType::FAILURE;

    auto team1 = teams.search(first->teamId);
    auto team2 = teams.search(second->teamId);

    assert(!(utils.invalid(team1) && utils.invalid(team2)));

    // they must have opposite signs
    if (team1->totalRecord * team2->totalRecord > 0) return StatusType::FAILURE;

    utils.merge_teams(team1, team2, team1->totalRecord > 0, false);


    // No such teams found
    return StatusType::SUCCESS;
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
