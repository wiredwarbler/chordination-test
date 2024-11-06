// implementation file
// where function declarations go
// #pragma once
#include "./headers/chordinate.h"
#include <string>
#include <iostream>

// constructors, mutator functions, battle functions, etc.

// https://www.youtube.com/watch?v=Yr2LNtrRIUs
// https://stackoverflow.com/questions/7449817/where-do-i-include-the-string-library-in-my-c-header-file
// https://www.w3schools.com/cpp/cpp_constructors.asp

/* STAT */
Stat::Stat(StatType st, int m)
{
    type = st;
    max = m;
    current = m;
};
int Stat::getMax()
{
    return max;
};
int Stat::getCurrent()
{
    return current;
};
std::string Stat::getDisplay()
{
    return std::to_string(current) + " / " + std::to_string(max);
};
void Stat::reset()
{
    current = max;
};
void Stat::delta(int n)
{
    // 1 (are there better ways to make a floor/ceiling function?)
    // n is expected to be the value, positive or negative, to add to the current property.
    int sum = current + n;
    current = (sum > max)
                  ? max
              : (sum < 0)
                  ? 0
                  : sum;
};

/* ACTOR */
Actor::Actor(int i, int lvl, std::string n, int h, int a, int d, int s, int l) : hp(StatType::HitPoints, h), // otherwise these will be initialized before the constructor code runs
                                                                                 attack(StatType::Attack, a),
                                                                                 defense(StatType::Defense, d),
                                                                                 speed(StatType::Speed, s),
                                                                                 luck(StatType::Luck, l)
{
    id = i;
    name = n;
    level = l;
    state = ActorState::Normal;
};
int Actor::getCurrentHP()
{
    return hp.getCurrent();
}
void Actor::deltaHP(int n)
{
    hp.delta(n);
}

/* HERO */
Hero::Hero(int i, int lvl, int ps, std::string n, Voice v, int h, int a, int d, int s, int l) : Actor(i, lvl, n, h, a, d, s, l)
{
    voice = v;
    partySequence = ps;
};
std::string Hero::displayInfo()
{
    std::string newline = "\r\n";
    std::string tab = "\t";
    // return "NAME:" + tab + name + newline;

    // this is a lambda function declaration
    auto format = [tab, newline](std::string val)
    {
        return tab + val + newline;
    };

    return "NAME:" + format(name) +
           "LEVEL:" + format(std::to_string(level)) +
           "HP:" + format(hp.getDisplay()) +
           "ATK:" + format(attack.getDisplay()) +
           "DEF:" + format(defense.getDisplay()) +
           "SPD:" + format(speed.getDisplay()) +
           "LUCK:" + format(luck.getDisplay());
};
std::string Hero::getName()
{
    return name;
}
int Hero::getSpeed()
{
    return speed.getCurrent();
}
void Hero::deltaHP(int n) 
{
    Actor::deltaHP(n);
}
bool Hero::operator<(const Hero &other) const
{
    return id > other.id;
}

/* ACTIONS, CHORDS, AND NOTES */
BasicAction::BasicAction(std::string n, std::string aat, ActionType t, ActionTargetType att)
{
    name = n;
    actorActionText = aat;
    type = t;
    allowedTargetType = att;
}
std::string BasicAction::getActionText()
{
    return actorActionText;
}

Note::Note(Hero &heroRef, BasicAction &actionRef)
    : hero(heroRef), action(actionRef)
{
    attempted = false;
    success = false;
}
void Note::setAttempted(bool a = true)
{
    attempted = a;
}
void Note::setSuccess(bool s = false)
{
    success = s;
}
int Note::getHeroSpeed()
{
    return hero.getSpeed();
}
std::string Note::getConsoleDisplay()
{
    return hero.getName() + " " + action.getActionText();
}
void Note::testHeroMod()
{
    hero.deltaHP(-1);
}
// bool Note::speedSort(Note &other)
// {
//     return getHeroSpeed() >= other.getHeroSpeed();
// }