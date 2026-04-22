#include "playerbot/playerbot.h"
#include "ZulGurubDungeonActions.h"
#include "playerbot/strategy/values/PositionValue.h"
#include "playerbot/strategy/AiObjectContext.h"
#include "Grids/GridNotifiers.h"
#include "Grids/GridNotifiersImpl.h"

using namespace ai;

bool SpreadFromMeleeAction::Execute(Event& event)
{
    Unit* boss = AI_VALUE2(Unit*, "find target", "jeklik");
    if (!boss)
        return false;

    // Get nearby melee bots
    std::list<Unit*> units;
    MaNGOS::AnyFriendlyUnitInObjectRangeCheck u_check(bot, 10.0f);
    MaNGOS::UnitListSearcher<MaNGOS::AnyFriendlyUnitInObjectRangeCheck> searcher(units, u_check);
    Cell::VisitAllObjects(bot, searcher, 10.0f);

    // Count melee bots (within 5yd of boss)
    int meleeCount = 0;
    for (Unit* unit : units)
    {
        if (unit->GetTypeId() == TYPEID_PLAYER && unit->GetDistance(boss) < 5.0f)
            meleeCount++;
    }

    // If too many melee stacked, move away
    if (meleeCount > 3)
    {
        float angle = frand(0, M_PI_F * 2.0f);
        float distance = frand(5.0f, 8.0f);
        WorldPosition bossPos(boss);
        WorldPosition newPos = bossPos + WorldPosition(0, distance * cos(angle), distance * sin(angle), 0);
        newPos.setZ(newPos.getHeight());

        if (bot->IsWithinLOS(newPos.getX(), newPos.getY(), newPos.getZ() + bot->GetCollisionHeight()))
        {
            if (MoveTo(bot->GetMapId(), newPos.getX(), newPos.getY(), newPos.getZ(), false, false, false, true))
                return true;
        }
    }

    return false;
}
