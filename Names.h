#pragma once
#ifndef NAMES_H
#define NAMES_H
#include <random>
#include <string>

using namespace std;

static mt19937 gen{ random_device{}() };
static double makeRand(double p_floor, double p_ceil)
{
    uniform_real_distribution<> l_distribution(p_floor, p_ceil);
    return l_distribution(gen);
}
static string namesforMonsters[]
{
	"The Rainbow Mutant","The Crying Doll","The Icy Snake","The Night Worm","The Young Babbler","The Bruised Gorilla","The Venom Serpent"
};
const int sizenamesforMonsters = 7;
static string namesforBosses[]
{
	"Baron Nashor","Ender Dragon","Eredin","The Death Reaper","Gregoire De Gorgon"
};
const int sizenamesforBosses = 5;
static string namesForSwords[]
{
        "Vanquisher","Kinslayer","Ashrune","Lightbringer","Mangler","Azurewrath","Spiteblade"
};

static string namesForBows[]
{
        "Meteor","Splintermark","Archangel","Pierce","Windbreaker","Beesting","Whisper"
};
static string namesForMagicSticks[]
{
        "Enigma","Prophecy","Visage","Snowfall","Frostward","Doombinder","Souleater"
};
static string namesForArmors[]
{
        "Leather Jerkin","Curator of Woe","Vest of the Titans","Pact of Hellfire","Visage of Silence","Frost Tunic of Might","Boon of Hate"
};
static string namesForHelmets[]
{
        "Helm of Eternal Fires","Headcover of Silent Worlds","Vengeful Ivory Helmet","Conqueror Golden Helmet","Stormguard Golden Helmet","Casque of the Dragons","Desolation Steel Headguard"
};
static string namesForMagicHats[]
{
        "Bandana of Lost Worlds","Faith's Cloth Cap","Pact of Tears","Tribute of Honor","Dawn of the Fallen","Might of the Night Sky","Fall of Ancient Power"
};
static string namesForTalismans[]
{
        "The Ruby Promise","The Shadow Passion","The Jade Favor","The Faint Core","The Idle Bond","The Austere Soul","The Ruby Twin"
};
static string namesForShields[]
{
        "Primal Tower Shield","Undead Heavy Shield","Wretched Heavy Shield","Ritual Tower Shield","Mercenary Shield","Bandit's Bronzed Shield","Demonic Glass Shield"
};
constexpr int namesTableSize = 7;
static double chance()
{
    return makeRand(1, 100);
}
constexpr double dodge = 33.0;
static char makeBig(char c)
{
    return  std::toupper(c);
}
#endif

