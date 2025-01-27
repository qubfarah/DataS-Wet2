//
// Created by Farah Qub on 16/01/2025.
//

#include "Team.h"

using namespace std;

Team::Team() = default;

Team::Team(int teamId) : id(teamId), totalRecord(0), hasBeenMerged(false)
{
}

void Team::deactivate()
{
    hasBeenMerged = true;
}

int Team::getId() const
{
    return id;
}

int Team::getTotalRecord() const
{
    return totalRecord;
}

bool Team::isValid() const
{
    return !hasBeenMerged;
}

void Team::updateRecord(const int &val)
{
    totalRecord = val;
}

Team::RecordToken::RecordToken() = default;

Team::RecordToken::RecordToken(int teamId) : teamId(teamId), next(nullptr)
{
    clearPrevious();
}

bool Team::RecordToken::operator==(const RecordToken &other)
{
    return &other == this;
}

void Team::RecordToken::clearPrevious()
{
    // previous = std::shared_ptr<Team::RecordToken>(nullptr);
    setPrevious(nullptr);
}
void Team::RecordToken::clearNext()
{
    // previous = std::shared_ptr<Team::RecordToken>(nullptr);
    setNext(nullptr);
}

void Team::RecordToken::setNext(shared_ptr<RecordToken> next)
{
    this->next = next;
}

shared_ptr<Team::RecordToken> Team::RecordToken::getNext()
{
    return next;
}

void Team::RecordToken::setPrevious(shared_ptr<RecordToken> previous)
{
    this->previous = previous;
}

weak_ptr<Team::RecordToken> Team::RecordToken::getPrevious()
{
    return previous;
}

int Team::RecordToken::getTeamId() const
{
    return teamId;
}
