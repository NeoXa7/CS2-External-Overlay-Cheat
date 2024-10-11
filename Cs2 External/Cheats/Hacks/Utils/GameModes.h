#pragma once
#include <unordered_map>
#include <string>

enum GameMode
{
    Casual = 0,
    Competitive = 1,
    Deathmatch = 2,
    TrainingDay = 4,
};

static const std::unordered_map<int, std::string> GameModeNames = {
    {Casual, "Casual"},
    {Competitive, "Competitive"},
    {Deathmatch, "Deathmatch"},
    {TrainingDay, "Training Day"},
};

