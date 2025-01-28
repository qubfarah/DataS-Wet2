//
// Created by Farah Qub on 16/01/2025.
//
#include "Jockey.h"

Jockey::Jockey() = default;

Jockey::Jockey(int jockeyId, int teamId) : id(jockeyId), originalTeamId(teamId), record(0)
{
}

int Jockey::getId() const
{
    return id;
}

int Jockey::getOriginalTeamId() const
{
    return originalTeamId;
}

void Jockey::increase_record()
{
    updateRecord(record + 1);
}

void Jockey::decrease_record()
{
    updateRecord(record - 1);
}

int Jockey::getRecord() const
{
    return record;
}

void Jockey::updateRecord(const int &val)
{
    record = val;
}
