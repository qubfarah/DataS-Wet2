//
// Created by jamal on 26/01/2025.
//

#include <cassert>

#include "plains25a2.h"

Plains::PlainsUtils::PlainsUtils(Plains *_p) : p(_p)
{
}

// O(log(m))
bool Plains::PlainsUtils::inSameTeamMembership(const shared_ptr<Jockey> &a, const shared_ptr<Jockey> &b) const
{
    return p->teamMembership.find(a->getOriginalTeamId()) == p->teamMembership.find(b->getOriginalTeamId());
}

// O(log(m))
shared_ptr<Team> Plains::PlainsUtils::team(const shared_ptr<Jockey> &a) const
{
    const auto &teamSetMembership = p->teamMembership.find(a->getOriginalTeamId());
    int teamSet = p->membershipIdentifier[teamSetMembership];

    return p->teams.search(teamSet);
}

// O(1)
bool Plains::PlainsUtils::invalid_team(const shared_ptr<Team> &team)
{
    return team == nullptr || !team->isValid();
}

// O(1)
int Plains::PlainsUtils::recordKey(const int &record)
{
    return std::abs(record);
}

// O(1)
void Plains::PlainsUtils::add_record_token(const shared_ptr<Team::RecordToken> &token, const int &record) const
{
    const shared_ptr<Team::RecordToken> result = p->records.search(record);

    // must be removed before added
    assert(token->getPrevious().lock() == nullptr && token->getNext() == nullptr);

    if (result != nullptr)
    {
        assert(result->getPrevious().lock() == nullptr);

        result->setPrevious(token);

        token->setNext(result);
    }

    p->records.upsert(record, token);

    assert(p->records.search(record) == token);
}

// O(1)
void Plains::PlainsUtils::update_record(const shared_ptr<Team> &team, const int &record)
{
    auto teamToken = p->recordTokens.search(team->getId());

    removeTeamFromRecord(team);

    add_record_token(teamToken, recordKey(record));

    team->updateRecord(record);
}

// O(1)
void Plains::PlainsUtils::removeTeamFromRecord(const shared_ptr<Team> &team)
{
    auto teamToken = p->recordTokens.search(team->getId());

    const int teamRecord = recordKey(team->getTotalRecord());
    auto next = teamToken->getNext();

    // if the team is the first at the head
    if (
        p->records.search(
            teamRecord) == teamToken)
    {
        // updates head of list
        p->records.upsert(teamRecord, next);

        // remove this node from link
        if (next != nullptr)
        {
            next->clearPrevious();
        }
    }
    else
    {
        if (auto previous = teamToken->getPrevious().lock())
        {
            previous->setNext(next);
            if (next != nullptr)
            {
                next->setPrevious(previous);
            }
        }
    }

    teamToken->clearPrevious();
    teamToken->clearNext();
}

// O(log(m))
void Plains::PlainsUtils::merge_teams(shared_ptr<Team> team1, shared_ptr<Team> team2, bool mergeToFirst)
{
    auto toTeam = mergeToFirst ? team1 : team2;
    auto fromTeam = mergeToFirst ? team2 : team1;

    assert(!(invalid_team(toTeam) && invalid_team(fromTeam)));

    removeTeamFromRecord(fromTeam);

    update_record(toTeam, toTeam->getTotalRecord() + fromTeam->getTotalRecord());

    p->teamMembership.unite(toTeam->getId(), fromTeam->getId());

    int resultSet = p->teamMembership.find(toTeam->getId());

    // it's always update since both sets existed before.
    p->membershipIdentifier.upsert(resultSet, toTeam->getId());

    fromTeam->deactivate();
}