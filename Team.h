//
// Created by Farah Qub on 16/01/2025.
//

#ifndef DS_WET2_WINTER_2024_2025_TEAM_H
#define DS_WET2_WINTER_2024_2025_TEAM_H

#include <memory>

class Team
{
private:
    int id;
    int totalRecord;

    // when this team has been merged, and no longer considered an active record.
    bool hasBeenMerged;

public:

    // acts like double linked list node.
    class RecordToken
    {
    private:
        int teamId;
        shared_ptr<RecordToken> next;
        weak_ptr<RecordToken> previous;

    public:
        RecordToken();

        RecordToken(int teamId);

        bool operator==(const RecordToken &other);

        void clearPrevious();
        void clearNext();

        void setNext(shared_ptr<RecordToken> next);
        shared_ptr<RecordToken> getNext();

        void setPrevious(shared_ptr<RecordToken> previous);
        weak_ptr<RecordToken> getPrevious();

        int getTeamId() const;
    };

public:
    Team();

    Team(int teamId);

    void deactivate();

    int getId() const;
    int getTotalRecord() const;

    bool isValid() const;

    void updateRecord(const int &);
};

#endif // DS_WET2_WINTER_2024_2025_TEAM_H
