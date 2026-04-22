#pragma once
#include "playerbot/strategy/Strategy.h"

namespace ai
{
    class ZulGurubDungeonStrategy : public Strategy
    {
    public:
        ZulGurubDungeonStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        std::string getName() override { return "zul'gurub"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    class JeklikFightStrategy : public Strategy
    {
    public:
        JeklikFightStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        std::string getName() override { return "jeklik"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
    };
}
