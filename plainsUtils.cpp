//
// Created by jamal on 26/01/2025.
//

#include <cassert>

#include "plains25a2.h"


Plains::PlainsUtils::PlainsUtils(Plains *_p) : p(_p) {
}

bool Plains::PlainsUtils::inSameTeamMembership(const shared_ptr<Jockey> &a, const shared_ptr<Jockey> &b) const {
    return p->teamMembership.find(a->originalTeamId) == p->teamMembership.find(b->originalTeamId);
}

shared_ptr<Team> Plains::PlainsUtils::team(const shared_ptr<Jockey> &a) const {
    const auto &teamSetMembership = p->teamMembership.find(a->originalTeamId);
    int teamSet = p->membershipIdentifier[teamSetMembership];

    return p->teams.search(teamSet);
}

bool Plains::PlainsUtils::invalid(const shared_ptr<Team> &team) {
    return team == nullptr || team->isMerged;
}


int Plains::PlainsUtils::recordKey(const int &record) {
    return std::abs(record);
}

void Plains::PlainsUtils::add_record_token(const shared_ptr<RecordToken> &token, const int &record) const {
    const shared_ptr<RecordToken> result = p->records.search(record);

    // must be removed before added
    assert(token->previous.lock() == nullptr && token->next == nullptr);

    if (result != nullptr) {
        assert(result->previous.lock() == nullptr);

        result->previous = token;
        token->next = result;
    }

    p->records.upsert(record, token);

    assert(p->records.search(record) == token);
}


void Plains::PlainsUtils::updateRecord(const shared_ptr<Team> &team, const int &record) {
    auto teamToken = p->recordTokens.search(team->id);

    removeTeamFromRecord(team);

    add_record_token(teamToken, recordKey(record));

    team->totalRecord = record;
}


void Plains::PlainsUtils::removeTeamFromRecord(const shared_ptr<Team> &team) {
    auto teamToken = p->recordTokens.search(team->id);

    const int teamRecord = recordKey(team->totalRecord);
    auto next = teamToken->next;

    // if the team is the first at the head
    if (
        p->records.search(
            teamRecord
        ) == teamToken) {
        // updates head of list
        p->records.upsert(teamRecord, next);

        // remove this node from link
        if (next != nullptr) {
            next->clearPrevious();
        }
    } else {
        if (auto previous = teamToken->previous.lock()) {
            previous->next = next;
            if (next != nullptr) {
                next->previous = previous;
            }
        }
    }
    teamToken->clearPrevious();
    teamToken->next = nullptr;
}


void Plains::PlainsUtils::merge_teams(shared_ptr<Team> team1, shared_ptr<Team> team2, bool mergeToFirst,
                                      bool dryMerge) {
    auto toTeam = mergeToFirst ? team1 : team2;
    auto fromTeam = mergeToFirst ? team2 : team1;

    assert(!(invalid(toTeam)&&invalid(fromTeam)));

    removeTeamFromRecord(fromTeam);

    updateRecord(toTeam, toTeam->totalRecord + fromTeam->totalRecord);

    p->teamMembership.unite(toTeam->id, fromTeam->id);

    int resultSet = p->teamMembership.find(toTeam->id);

    p->membershipIdentifier.upsert(resultSet, toTeam->id);


    fromTeam->deactivate();
}

//     bool inSameTeamMembership(const shared_ptr<Jockey> &a, const shared_ptr<Jockey> &b) const {
//     }
//
//     // O(log(m))
//     Team &team(const shared_ptr<Jockey> &a) const {
//         const auto &teamSet = p->teamMembership.find(a->id);
//
//         return p->teams[teamSet];
//     }
//
//     static bool invalid(const shared_ptr<Team> &team) {
//         return team == nullptr || team->isMerged;
//     }
//
//     void updateRecord(Team &team, int record) {
//         auto &teamToken = p->recordTokens[team.id];
//
//         const auto nextRecord = p->records.search(record);
//         if (nextRecord == nullptr) {
//             p->records.insert(record, &teamToken);
//         }
//
//         // if the team token is the first in the double linked list.
//         removeTeamFromRecord(team);
//
//         add_record_token(teamToken, record);
//
//         team.totalRecord = record;
//     }
//
//     void removeTeamFromRecord(Team &team) {
//         auto &teamToken = p->recordTokens[team.id];
//
//         // if the team is the first at the head
//         if (p->records[team.totalRecord] == &teamToken) {
//             auto next = teamToken.next;
//
//             p->records[team.totalRecord] = next;
//             // remove this node from link
//             if (next != nullptr) {
//                 next->previous = nullptr;
//             }
//
//             teamToken.previous = nullptr;
//             teamToken.next = nullptr;
//         } else {
//             if (teamToken.previous != nullptr) {
//                 teamToken.previous->next = teamToken.next;
//             }
//         }
//     }
//
//     void add_record_token(RecordToken &token, int record) {
//         RecordToken *currentHead = p->records[record];
//         if (currentHead != nullptr) {
//             currentHead->previous = &token;
//             token.next = currentHead;
//         }
//
//         p->records[record] = &token;
//     }
//
//     void merge_teams(const int &teamId1, const int &teamId2, bool mergeToFirst) {
//         auto team1 = p->teams.search(teamId1);
//         auto team2 = p->teams.search(teamId2);
//
//         return merge_teams(team1, team2, mergeToFirst);
//     }
//
//     void merge_teams(shared_ptr<Team> team1, shared_ptr<Team> team2, bool mergeToFirst) {
//         auto toTeam = mergeToFirst ? team1 : team2;
//         auto fromTeam = mergeToFirst ? team2 : team1;
//
//         removeTeamFromRecord(*fromTeam);
//
//         updateRecord(*toTeam, toTeam->totalRecord + fromTeam->totalRecord);
//
//         p->teamMembership.unite(toTeam->id, fromTeam->id);
//
//         fromTeam->deactivate();
//     }
// };
