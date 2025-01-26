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
    RecordToken() = default;

    RecordToken(int teamId) : teamId(teamId), next(nullptr)
    {
        clearPrevious();
    }

    shared_ptr<RecordToken> next;
    weak_ptr<RecordToken> previous;


    bool operator==(const RecordToken& other)
    {
        return &other == this;
    }

    void clearPrevious()
    {
        previous = std::shared_ptr<RecordToken>(nullptr);
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
    // UnionFind jockeysTeamMembership;
    UnionFind teamMembership;

    // teamId->token
    HashTable<int, RecordToken> recordTokens;

    // record->token
    HashTable<int, RecordToken> records;

    class PlainsUtils
    {
        Plains* p;

    private:
        void removeTeamFromRecord(const shared_ptr<Team>& team) ;

    public:
        PlainsUtils(Plains* _p);

        bool inSameTeamMembership(const shared_ptr<Jockey>& a, const shared_ptr<Jockey>& b) const;

        // O(log(m))
        shared_ptr<Team> team(const shared_ptr<Jockey>& a) const;

        static bool invalid(const shared_ptr<Team> &team);

        void updateRecord(const shared_ptr<Team>& team, const int& record);

        void add_record_token(const shared_ptr<RecordToken>& token, const int& record) const;

        void merge_teams(shared_ptr<Team> team1, shared_ptr<Team> team2, bool mergeToFirst, bool dryMerge);

        static int recordKey(const int& record);
    };

    PlainsUtils utils;

    //TODO: remove
public:
    int commandId = 0;

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
