#ifndef STREN_UNIT_H
#define STREN_UNIT_H

#include "string_ext.h"

///
/// class Inventory
///
class Inventory
{
public:
    ///
    /// Constructor
    ///
    Inventory()
    {
    }
    ///
    ///
    ///
    void removeItem() {}
    ///
    ///
    ///
    void addItem() {}
    ///
    ///
    ///
};
///
/// class Unit
///
class Unit
{
private:
    std::string m_id;
    std::string m_name;
    std::string m_faction;
    int         m_weaponSkill;
    int         m_armour;
    int         m_protection;
    int         m_moraleCur;
    int         m_moraleMax;
    int         m_staminaCur;
    int         m_staminaMax;
    int         m_healthCur;
    int         m_healthMax;
    int         m_actionPointsCur;
    int         m_actionPointsMax;
    bool        m_isAi;
    Inventory   m_inventory;
public:
    ///
    /// Constructor
    ///
    Unit()
        : m_weaponSkill(0)
        , m_armour(0)
        , m_protection(0)
        , m_moraleCur(0)
        , m_moraleMax(0)
        , m_staminaCur(0)
        , m_staminaMax(0)
        , m_healthCur(0)
        , m_healthMax(0)
        , m_actionPointsCur(0)
        , m_actionPointsMax(0)
    {
    }
    ///
    /// @todo
    ///
    void move() {}
    ///
    /// @todo
    ///
    void fire() {}
    ///
    /// @todo
    ///
    void changeFireMode() {}
    ///
    /// @todo
    ///
    void reload() {}
    ///
    /// @todo
    ///
    void dropItem()
    {
        m_inventory.removeItem();
    }
    ///
    /// @todo
    ///
    void pickupItem()
    {
        m_inventory.addItem();
    }
};

#endif //STREN_UNIT_H
