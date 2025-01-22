//
// 234218 Data Structures 1.
// Semester: 2025A (Winter).
// Wet Exercise #1.
//
// The following header file contains all methods we expect you to implement.
// You MAY add private methods and fields of your own.
// DO NOT erase or modify the signatures of the public methods.
// DO NOT modify the preprocessors in this file.
// DO NOT use the preprocessors in your other code files.
//

#ifndef PLAINS25WINTER_WET1_H_
#define PLAINS25WINTER_WET1_H_

#include "wet2util.h"

#include <iostream>
#include <cstring>
#include <memory>

#include "HashTable.h"
#include "UnionFind.h"

#include "Jockey.h"
#include "Team.h"

using namespace std;

// double linked list
class RecordToken
{

public:
    int teamId;

    RecordToken(int teamId) : teamId(teamId) {}

    RecordToken *next;
    RecordToken *previous;

    bool operator==(const RecordToken &other)
    {
        return &other == this;
    }
};

class Plains
{
private:
    HashTable<int, Team> teams;
    HashTable<int, Jockey> jockeys;

    // for every jockey added, a set by it's id is created
    // if the team the jockey is added to empty, then the teams set id is this jockey id,
    // if not, then the jockey is merged with the team's set id.
    // therefore, in terms of length of hashtable, it's O(n)
    // but in terms of active sets, it's O(m).
    UnionFind<Jockey> jockeysTeamMembership;

    HashTable<int, RecordToken> recordTokens;
    HashTable<int, RecordToken *> records;

    class PlainsUtils
    {
        shared_ptr<Plains> p;

    public:
        bool inSameTeamMembership(const shared_ptr<Jockey> &a, const shared_ptr<Jockey> &b) const
        {
            return p->jockeysTeamMembership.find(a->id) == p->jockeysTeamMembership.find(b->id);
        }

        Team &team(const shared_ptr<Jockey> &a) const
        {
            const auto teamSet = p->jockeysTeamMembership.find(a->id);
            auto teamId = teamSet.identifier;

            return p->teams[teamId];
        }

        static bool invalid(const shared_ptr<Team> &team)
        {
            return team == nullptr || !team->isMerged;
        }

        auto set(const shared_ptr<Team> &team) const
        {
            return p->jockeysTeamMembership.find(team->firstJockey);
        }

        void updateRecord(Team &team, int record)
        {
            auto &teamToken = p->recordTokens[team.id];

            if (team.totalRecord == 0)
            {
                auto nextRecord = p->records.search(record);
                if (nextRecord == nullptr)
                {
                    p->records.insert(record, &teamToken);
                }
            }

            // if the team token is the first in the double linked list.
            removeTeamFromRecord(team);

            add_record_token(teamToken, record);

            team.totalRecord = record;
        }

        void removeTeamFromRecord(Team &team)
        {
            auto &teamToken = p->recordTokens[team.id];

            if (p->records[team.totalRecord] == &teamToken)
            {
                auto next = teamToken.next;

                p->records[team.totalRecord] = next;
                // remove this node from link
                next->previous = nullptr;

                teamToken.previous = nullptr;
                teamToken.next = nullptr;
            }
            else
            {
                if (teamToken.previous != nullptr)
                {
                    teamToken.previous->next = teamToken.next;
                }
            }
        }

        void add_record_token(RecordToken &token, int record)
        {
            auto currentHead = p->records[record];

            currentHead->previous = &token;
            token.next = currentHead;

            p->records[record] = &token;
        }

        void merge_teams(const int &teamId1, const int &teamId2, bool mergeToFirst)
        {
            auto team1 = p->teams.search(teamId1);
            auto team2 = p->teams.search(teamId2);

            return merge_teams(team1, team2, mergeToFirst);
        }

        void merge_teams(shared_ptr<Team> team1, shared_ptr<Team> team2, bool mergeToFirst)
        {
            auto toTeam = mergeToFirst ? team1 : team2;
            auto fromTeam = mergeToFirst ? team2 : team1;

            removeTeamFromRecord(*fromTeam);

            updateRecord(*toTeam, toTeam->totalRecord + fromTeam->totalRecord);

            p->jockeysTeamMembership.unite(set(toTeam), set(toTeam));

            //
            fromTeam->deactivate();
        }


        void verifyJockey() {

        }

        void addJockeyMembership() {}
    };

    PlainsUtils utils;

public:
    // <DO-NOT-MODIFY> {
    Plains();

    ~Plains();

    StatusType add_team(int teamId);

    StatusType add_jockey(int jockeyId, int teamId);

    StatusType update_match(int victoriousJockeyId, int losingJockeyId);

    StatusType merge_teams(int teamId1, int teamId2);

    StatusType unite_by_record(int record);

    output_t<int> get_jockey_record(int jockeyId);

    output_t<int> get_team_record(int teamId);

    // } </DO-NOT-MODIFY>
};

#endif // PLAINS25WINTER_WET1_H_
