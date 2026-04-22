#include "playerbot/playerbot.h"
#include "ZulGurubDungeonStrategies.h"

using namespace ai;

void ZulGurubDungeonStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "start jeklik fight",
        NextAction::array(0, new NextAction("enable jeklik fight strategy", 100.0f), NULL)));
}

void ZulGurubDungeonStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    // No non-combat triggers for ZG dungeon strategy
}

void JeklikFightStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    Player* bot = ai->GetBot();
    
    // Ranged/healers move out for Sonar Pulse (10yd pulse)
    if (ai->IsRanged(bot) || ai->IsHeal(bot))
    {
        triggers.push_back(new TriggerNode(
            "jeklik too close",
            NextAction::array(0, new NextAction("move away from jeklik", 100.0f), NULL)));
    }

    // Melee spread to avoid Sonic Blast chain
    if (ai->IsRanged(bot))
    {
        triggers.push_back(new TriggerNode(
            "jeklik melee stacked",
            NextAction::array(0, new NextAction("spread from melee", 80.0f), NULL)));
    }

    // Interrupt heal
    triggers.push_back(new TriggerNode(
        "jeklik casting heal",
        NextAction::array(0, new NextAction("interrupt spell", 100.0f), NULL)));

    // Dispel Mind Flay
    triggers.push_back(new TriggerNode(
        "mind flay on friend",
        NextAction::array(0, new NextAction("dispel magic", 90.0f), NULL)));

    // AoE bat adds
    triggers.push_back(new TriggerNode(
        "bat adds present",
        NextAction::array(0, new NextAction("aoe", 85.0f), NULL)));
}

void JeklikFightStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "end jeklik fight",
        NextAction::array(0, new NextAction("disable jeklik fight strategy", 100.0f), NULL)));
}

void JeklikFightStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "end jeklik fight",
        NextAction::array(0, new NextAction("disable jeklik fight strategy", 100.0f), NULL)));
}

void JeklikFightStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    // No reaction triggers for Jeklik
}
