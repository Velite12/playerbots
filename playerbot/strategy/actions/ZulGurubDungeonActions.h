#pragma once
#include "DungeonActions.h"
#include "ChangeStrategyAction.h"

namespace ai
{
    class ZulGurubEnableDungeonStrategyAction : public ChangeAllStrategyAction
    {
    public:
        ZulGurubEnableDungeonStrategyAction(PlayerbotAI* ai) : ChangeAllStrategyAction(ai, "enable zul'gurub strategy", "+zul'gurub") {}
    };

    class ZulGurubDisableDungeonStrategyAction : public ChangeAllStrategyAction
    {
    public:
        ZulGurubDisableDungeonStrategyAction(PlayerbotAI* ai) : ChangeAllStrategyAction(ai, "disable zul'gurub strategy", "-zul'gurub") {}
    };

    class JeklikEnableFightStrategyAction : public ChangeAllStrategyAction
    {
    public:
        JeklikEnableFightStrategyAction(PlayerbotAI* ai) : ChangeAllStrategyAction(ai, "enable jeklik fight strategy", "+jeklik") {}
    };

    class JeklikDisableFightStrategyAction : public ChangeAllStrategyAction
    {
    public:
        JeklikDisableFightStrategyAction(PlayerbotAI* ai) : ChangeAllStrategyAction(ai, "disable jeklik fight strategy", "-jeklik") {}
    };

    class MoveAwayFromJeklikAction : public MoveAwayFromCreature
    {
    public:
        MoveAwayFromJeklikAction(PlayerbotAI* ai) : MoveAwayFromCreature(ai, "move away from jeklik", 14517, 20.0f) {}
    };

    class SpreadFromMeleeAction : public MovementAction
    {
    public:
        SpreadFromMeleeAction(PlayerbotAI* ai) : MovementAction(ai, "spread from melee") {}
        bool Execute(Event& event) override;
        bool isPossible() override { return ai->CanMove(); }

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "spread from melee"; }
        virtual std::string GetHelpDescription()
        {
            return "This action makes melee bots spread out to avoid Sonic Blast chain.\n";
        }
        virtual std::vector<std::string> GetUsedActions() { return {}; }
        virtual std::vector<std::string> GetUsedValues() { return {}; }
#endif
    };
}
