#include "game/game.h"

#include "string_ext.h"
#include <map>

namespace stren
{

enum class Faction
{
    Operatives = 0,
    Raiders
};

const std::map<Faction, std::string> kFactionNames = {
    {Faction::Operatives, "The operatives"},
    {Faction::Raiders, "The raiders"},
};

std::string getMoraleStr(const size_t valueCur, const size_t valueMax)
{
    if (valueMax == valueCur)
    {
        return "Great";
    }
    return "Poor";
}

std::string getStaminaStr(const size_t valueCur, const size_t valueMax)
{
    if (valueMax == valueCur)
    {
        return "Great";
    }
    return "Poor";
}

///
/// class Inventory
///
class Inventory
{
private:
public:
    Inventory()
    {
    }
};

///
/// struct UnitStats
///
struct UnitStats
{
    std::string name;
    Faction     faction;
    size_t      moraleMax;
    size_t      moraleCur;
    size_t      staminaMax;
    size_t      staminaCur;
    size_t      healthMax;
    size_t      healthCur;
    size_t      armor;
    size_t      protection;
    size_t      weaponSkill;
    size_t      actinPointsMax;
    size_t      actinPointsCur;

    UnitStats()
        : moraleMax(1)
        , moraleCur(1)
        , staminaMax(1)
        , staminaCur(1)
        , healthMax(1)
        , healthCur(1)
        , armor(0)
        , protection(0)
        , weaponSkill(0)
        , actinPointsMax(0)
        , actinPointsCur(0)
    {
    }
};

///
/// class Unit
///
class Unit
{
private:
    UnitStats   m_stats;
    Inventory   m_inventory;
public:
    ///
    /// Constructor
    ///
    Unit()

    {
    }

    void setName(const std::string & value)
    {
        m_stats.name = value;
    }

    const std::string & getName() const
    {
        return m_stats.name;
    }

    void setFaction(const Faction value)
    {
        m_stats.faction = value;
    }

    Faction getFaction() const
    {
        m_stats.faction;
    }

    void setMoraleMax(const size_t value)
    {
        m_stats.moraleMax = value;
    }

    size_t getMoraleMax() const
    {
        return m_stats.moraleMax;
    }

    void setMoraleCurrent(const size_t value)
    {
        m_stats.moraleCur = value;
    }

    size_t getMoraleCurrent() const
    {
        return m_stats.moraleCur;
    }

    void setStaminaMax(const size_t value)
    {
        m_stats.staminaMax = value;
    }

    size_t getStaminaMax() const
    {
        return m_stats.staminaMax;
    }

    void setStaminaCurrent(const size_t value)
    {
        m_stats.staminaCur = value;
    }

    size_t getStaminaCurrent() const
    {
        return m_stats.staminaCur;
    }

    void setHealthMax(const size_t value)
    {
        m_stats.healthMax = value;
    }

    size_t getHealthMax() const
    {
        return m_stats.healthMax;
    }

    void setHealthCurrent(const size_t value)
    {
        m_stats.healthCur = value;
    }

    size_t getHealthCurrent() const
    {
        return m_stats.healthCur;
    }

    void setArmor(const size_t value)
    {
        m_stats.armor = value;
    }

    size_t getArmor() const
    {
        return m_stats.armor;
    }

    void setProtection(const size_t value)
    {
        m_stats.protection = value;
    }

    size_t getProtection() const
    {
        return m_stats.protection;
    }

    void setWeaponSkill(const size_t value)
    {
        m_stats.weaponSkill = value;
    }

    size_t getWeaponSkill() const
    {
        return m_stats.weaponSkill;
    }

    void setActionPointsMax(const size_t value)
    {
        m_stats.actinPointsMax = value;
    }

    size_t getActionPointsMax() const
    {
        return m_stats.actinPointsMax;
    }

    void setActionPointsCurrent(const size_t value)
    {
        m_stats.actinPointsCur = value;
    }

    size_t getActionPointsCurrent() const
    {
        return m_stats.actinPointsCur;
    }

    void move()
    {
    }

    void shoot()
    {
    }

    void reload()
    {
    }

    void pickup()
    {
    }
};

Game::Game()
{
    createBoard();
    createTerrain();
    createObjects();
    createUnits();
    createItems();
}

Game::~Game()
{
}

void Game::update(const size_t dt)
{
}

void Game::createBoard()
{
}

void Game::createTerrain()
{
}

void Game::createObjects()
{
}

void Game::createUnits()
{
    std::vector<UnitStats> statsList;

    UnitStats stats;
    stats.name = "Jasper Prune";
    stats.faction = Faction::Raiders;
    stats.moraleMax = 230;
    stats.moraleCur = 230;
    stats.staminaMax = 170;
    stats.staminaCur = 170;
    stats.healthMax = 27;
    stats.healthCur = 27;
    stats.armor = 0;
    stats.protection = 0;
    stats.actinPointsMax = 19;
    stats.actinPointsCur = 19;
    stats.weaponSkill = 2;
    statsList.push_back(stats);

    stats.name = "Nelson Smith";
    stats.faction = Faction::Raiders;
    stats.moraleMax = 200;
    stats.moraleCur = 200;
    stats.staminaMax = 190;
    stats.staminaCur = 190;
    stats.healthMax = 19;
    stats.healthCur = 19;
    stats.armor = 0;
    stats.protection = 0;
    stats.actinPointsMax = 21;
    stats.actinPointsCur = 21;
    stats.weaponSkill = 0;
    statsList.push_back(stats);

    stats.name = "Combat Droid";
    stats.faction = Faction::Raiders;
    stats.moraleMax = 255;
    stats.moraleCur = 255;
    stats.staminaMax = 190;
    stats.staminaCur = 190;
    stats.healthMax = 50;
    stats.healthCur = 50;
    stats.armor = 12;
    stats.protection = 0;
    stats.actinPointsMax = 20;
    stats.actinPointsCur = 20;
    stats.weaponSkill = 0;
    statsList.push_back(stats);
    // one more combat droid
    statsList.push_back(stats);

    stats.name = "Leeder Kreenon";
    stats.faction = Faction::Raiders;
    stats.moraleMax = 250;
    stats.moraleCur = 250;
    stats.staminaMax = 250;
    stats.staminaCur = 250;
    stats.healthMax = 36;
    stats.healthCur = 36;
    stats.armor = 0;
    stats.protection = 0;
    stats.actinPointsMax = 22;
    stats.actinPointsCur = 22;
    stats.weaponSkill = 6;
    statsList.push_back(stats);

    stats.name = "Elane Freuyh";
    stats.faction = Faction::Raiders;
    stats.moraleMax = 250;
    stats.moraleCur = 250;
    stats.staminaMax = 175;
    stats.staminaCur = 175;
    stats.healthMax = 26;
    stats.healthCur = 26;
    stats.armor = 0;
    stats.protection = 0;
    stats.actinPointsMax = 18;
    stats.actinPointsCur = 18;
    stats.weaponSkill = 4;
    statsList.push_back(stats);

    stats.name = "Billy Bragg";
    stats.faction = Faction::Raiders;
    stats.moraleMax = 220;
    stats.moraleCur = 220;
    stats.staminaMax = 220;
    stats.staminaCur = 220;
    stats.healthMax = 29;
    stats.healthCur = 29;
    stats.armor = 0;
    stats.protection = 0;
    stats.actinPointsMax = 17;
    stats.actinPointsCur = 17;
    stats.weaponSkill = 1;
    statsList.push_back(stats);

    stats.name = "Leon Trotsky";
    stats.faction = Faction::Raiders;
    stats.moraleMax = 230;
    stats.moraleCur = 230;
    stats.staminaMax = 180;
    stats.staminaCur = 180;
    stats.healthMax = 32;
    stats.healthCur = 32;
    stats.armor = 0;
    stats.protection = 0;
    stats.actinPointsMax = 19;
    stats.actinPointsCur = 19;
    stats.weaponSkill = 2;
    statsList.push_back(stats);

    stats.name = "Slarty Bartfast";
    stats.faction = Faction::Raiders;
    stats.moraleMax = 175;
    stats.moraleCur = 175;
    stats.staminaMax = 165;
    stats.staminaCur = 165;
    stats.healthMax = 29;
    stats.healthCur = 29;
    stats.armor = 0;
    stats.protection = 0;
    stats.actinPointsMax = 17;
    stats.actinPointsCur = 17;
    stats.weaponSkill = 0;
    statsList.push_back(stats);

    stats.name = "Combat Droid";
    stats.faction = Faction::Raiders;
    stats.moraleMax = 255;
    stats.moraleCur = 255;
    stats.staminaMax = 190;
    stats.staminaCur = 190;
    stats.healthMax = 50;
    stats.healthCur = 50;
    stats.armor = 12;
    stats.protection = 0;
    stats.actinPointsMax = 20;
    stats.actinPointsCur = 20;
    stats.weaponSkill = 0;
    statsList.push_back(stats);

    stats.name = "Don Caloni";
    stats.faction = Faction::Raiders;
    stats.moraleMax = 230;
    stats.moraleCur = 230;
    stats.staminaMax = 195;
    stats.staminaCur = 195;
    stats.healthMax = 27;
    stats.healthCur = 27;
    stats.armor = 0;
    stats.protection = 0;
    stats.actinPointsMax = 23;
    stats.actinPointsCur = 23;
    stats.weaponSkill = 1;
    statsList.push_back(stats);

    stats.name = "Combat Droid";
    stats.faction = Faction::Raiders;
    stats.moraleMax = 255;
    stats.moraleCur = 255;
    stats.staminaMax = 190;
    stats.staminaCur = 190;
    stats.healthMax = 50;
    stats.healthCur = 50;
    stats.armor = 12;
    stats.protection = 0;
    stats.actinPointsMax = 20;
    stats.actinPointsCur = 20;
    stats.weaponSkill = 0;
    statsList.push_back(stats);

    stats.name = "Joey";
    stats.faction = Faction::Raiders;
    stats.moraleMax = 240;
    stats.moraleCur = 240;
    stats.staminaMax = 200;
    stats.staminaCur = 200;
    stats.healthMax = 25;
    stats.healthCur = 25;
    stats.armor = 0;
    stats.protection = 0;
    stats.actinPointsMax = 17;
    stats.actinPointsCur = 17;
    stats.weaponSkill = 1;
    statsList.push_back(stats);

    stats.name = "Rita Rumpole";
    stats.faction = Faction::Raiders;
    stats.moraleMax = 205;
    stats.moraleCur = 205;
    stats.staminaMax = 195;
    stats.staminaCur = 195;
    stats.healthMax = 26;
    stats.healthCur = 26;
    stats.armor = 0;
    stats.protection = 0;
    stats.actinPointsMax = 24;
    stats.actinPointsCur = 24;
    stats.weaponSkill = 2;
    statsList.push_back(stats);

    stats.name = "Jim Digriz";
    stats.faction = Faction::Raiders;
    stats.moraleMax = 200;
    stats.moraleCur = 200;
    stats.staminaMax = 190;
    stats.staminaCur = 190;
    stats.healthMax = 27;
    stats.healthCur = 27;
    stats.armor = 0;
    stats.protection = 0;
    stats.actinPointsMax = 20;
    stats.actinPointsCur = 20;
    stats.weaponSkill = 3;
    statsList.push_back(stats);

    stats.name = "Kurt Levine";
    stats.faction = Faction::Raiders;
    stats.moraleMax = 250;
    stats.moraleCur = 250;
    stats.staminaMax = 240;
    stats.staminaCur = 240;
    stats.healthMax = 33;
    stats.healthCur = 33;
    stats.armor = 0;
    stats.protection = 0;
    stats.actinPointsMax = 18;
    stats.actinPointsCur = 18;
    stats.weaponSkill = 5;
    statsList.push_back(stats);

    stats.name = "Jill";
    stats.faction = Faction::Raiders;
    stats.moraleMax = 180;
    stats.moraleCur = 180;
    stats.staminaMax = 170;
    stats.staminaCur = 170;
    stats.healthMax = 26;
    stats.healthCur = 26;
    stats.armor = 0;
    stats.protection = 0;
    stats.actinPointsMax = 21;
    stats.actinPointsCur = 21;
    stats.weaponSkill = 1;
    statsList.push_back(stats);

    for (const UnitStats & stats : statsList)
    {
        addUnit(stats);
    }
}

void Game::addUnit(const UnitStats & stats)
{
    Unit unit;
    unit.setName(stats.name);
    unit.setFaction(stats.faction);
    unit.setMoraleMax(stats.moraleMax);
    unit.setMoraleCurrent(stats.moraleCur);
    unit.setStaminaMax(stats.staminaMax);
    unit.setStaminaCurrent(stats.staminaCur);
    unit.setHealthMax(stats.healthMax);
    unit.setHealthCurrent(stats.healthCur);
    unit.setArmor(stats.armor);
    unit.setProtection(stats.protection);
    unit.setWeaponSkill(stats.weaponSkill);
    unit.setActionPointsMax(stats.actinPointsMax);
    unit.setActionPointsCurrent(stats.actinPointsCur);
    m_units.push_back(unit);
}

void Game::createItems()
{
}
} // stren