// You can edit anything you want in this file.
// However you need to implement all public Plains function, as provided below as a template

#include "plains25a2.h"

#include <cassert>

#define ERROR_GUARD(x)                       \
    try                                      \
    {                                        \
        x                                    \
    }                                        \
    catch (...)                              \
    {                                        \
        return StatusType::ALLOCATION_ERROR; \
    }

Plains::Plains() : utils(this)
{
}

// all memory is managed
Plains::~Plains() = default;

StatusType Plains::add_team(int teamId)
{
    if (teamId <= 0)
        return StatusType::INVALID_INPUT;

    if (teams.exists(teamId))
        return StatusType::FAILURE;

    ERROR_GUARD({
        teams.insert(teamId, Team(teamId));

        recordTokens.insert(teamId, Team::RecordToken(teamId));

        membershipIdentifier.insert(teamMembership.makeset(teamId), teamId);

        // starting at 0, search after insert to ensure copy is not affecting result.
        utils.add_record_token(recordTokens.search(teamId), 0);
    });

    return StatusType::SUCCESS;
}

StatusType Plains::add_jockey(int jockeyId, int teamId)
{
    if (jockeyId <= 0 || teamId <= 0)
        return StatusType::INVALID_INPUT;

    if (jockeys.exists(jockeyId))
        return StatusType::FAILURE;

    const auto team = teams.search(teamId);

    if (utils.invalid_team(team))
        return StatusType::FAILURE;

    ERROR_GUARD({
        jockeys.insert(jockeyId, Jockey(jockeyId, team->getId()));
    });

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

    if (victorious == nullptr || losing == nullptr)
        return StatusType::FAILURE;

    if (utils.inSameTeamMembership(victorious, losing))
    {
        return StatusType::FAILURE;
    }

    auto victoriousTeam = utils.team(victorious);
    auto losingTeam = utils.team(losing);

    ERROR_GUARD({
        victorious->increase_record();
        losing->decrease_record();

        utils.update_record(victoriousTeam, victoriousTeam->getTotalRecord() + 1);
        utils.update_record(losingTeam, losingTeam->getTotalRecord() - 1);
    });

    return StatusType::SUCCESS;
}

StatusType Plains::merge_teams(int teamId1, int teamId2)
{
    if (teamId1 <= 0 || teamId2 <= 0 || teamId1 == teamId2)
        return StatusType::INVALID_INPUT;

    const auto team1 = teams.search(teamId1);
    const auto team2 = teams.search(teamId2);

    if (utils.invalid_team(team1) || utils.invalid_team(team2))
        return StatusType::FAILURE;

    bool mergeToFirst = team1->getTotalRecord() >= team2->getTotalRecord();

    ERROR_GUARD({
        utils.merge_teams(team1, team2, mergeToFirst);
    });

    return StatusType::SUCCESS;
}

#include <stdio.h>

StatusType Plains::unite_by_record(int record)
{
    if (record <= 0)
        return StatusType::INVALID_INPUT;

    auto recordsList = records.search(record);
    if (recordsList == nullptr)
        return StatusType::FAILURE;

    auto first = recordsList;
    auto second = first->getNext();

    // has 1 or more than 2:
    // if(second == nullptr) return StatusType::ALLOCATION_ERROR;
    if (second == nullptr || second->getNext() != nullptr)
        return StatusType::FAILURE;

    auto team1 = teams.search(first->getTeamId());
    auto team2 = teams.search(second->getTeamId());

    assert(!(utils.invalid_team(team1) && utils.invalid_team(team2)));

    // they must have opposite signs
    if (team1->getTotalRecord() * team2->getTotalRecord() > 0)
        return StatusType::FAILURE;

    ERROR_GUARD({
        utils.merge_teams(team1, team2, team1->getTotalRecord() > 0);
    });

    return StatusType::SUCCESS;
}

output_t<int> Plains::get_jockey_record(int jockeyId)
{
    if (jockeyId <= 0)
        return StatusType::INVALID_INPUT;

    const auto jockey = jockeys.search(jockeyId);

    if (jockey == nullptr)
        return StatusType::FAILURE;

    return jockey->getRecord();
}

output_t<int> Plains::get_team_record(int teamId)
{
    if (teamId <= 0)
        return StatusType::INVALID_INPUT;

    const auto team = teams.search(teamId);

    if (utils.invalid_team(team))
        return StatusType::FAILURE;

    return team->getTotalRecord();
}
