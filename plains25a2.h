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

class Plains
{
private:
    HashTable<Team> teams;
    HashTable<Jockey> jockeys;

    // universe: teams
    UnionFind teamMembership; // Size => O(m)
    // setId->teamId
    HashTable<int> membershipIdentifier; // Size => O(m)

    // teamId->token
    HashTable<Team::RecordToken> recordTokens; // Size => O(m)

    // record->token
    HashTable<Team::RecordToken> records; // Size => O(m) (requires resizing)



    class PlainsUtils
    {
        Plains* p;

    private:
        // O(1)
        void removeTeamFromRecord(const shared_ptr<Team>& team) ;

        static int recordKey(const int& record);

    public:
        PlainsUtils(Plains* _p);

        // O(log(m))
        bool inSameTeamMembership(const shared_ptr<Jockey>& a, const shared_ptr<Jockey>& b) const;

        // O(log(m))
        shared_ptr<Team> team(const shared_ptr<Jockey>& a) const;
     
        // O(1)
        static bool invalid_team(const shared_ptr<Team> &team);

        // O(1)
        void update_record(const shared_ptr<Team>& team, const int& record);

        // O(1)
        void add_record_token(const shared_ptr<Team::RecordToken>& token, const int& record) const;

        // O(log(m))
        void merge_teams(shared_ptr<Team> team1, shared_ptr<Team> team2, bool mergeToFirst);
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
