#pragma once
#include "DungeonTriggers.h"
#include "GenericTriggers.h"

namespace ai
{
    class ZulGurubEnterDungeonTrigger : public EnterDungeonTrigger
    {
    public:
        ZulGurubEnterDungeonTrigger(PlayerbotAI* ai) : EnterDungeonTrigger(ai, "enter zul'gurub", "zul'gurub", 309) {}
    };

    class ZulGurubLeaveDungeonTrigger : public LeaveDungeonTrigger
    {
    public:
        ZulGurubLeaveDungeonTrigger(PlayerbotAI* ai) : LeaveDungeonTrigger(ai, "leave zul'gurub", "zul'gurub", 309) {}
    };

    class JeklikStartFightTrigger : public StartBossFightTrigger
    {
    public:
        JeklikStartFightTrigger(PlayerbotAI* ai) : StartBossFightTrigger(ai, "start jeklik fight", "jeklik", 14517) {}
    };

    class JeklikEndFightTrigger : public EndBossFightTrigger
    {
    public:
        JeklikEndFightTrigger(PlayerbotAI* ai) : EndBossFightTrigger(ai, "end jeklik fight", "jeklik", 14517) {}
    };

    class JeklikTooCloseTrigger : public CloseToCreatureTrigger
    {
    public:
        JeklikTooCloseTrigger(PlayerbotAI* ai) : CloseToCreatureTrigger(ai, "jeklik too close", 14517, 20.0f) {}
    };

    class JeklikMeleeStackedTrigger : public ValueTrigger
    {
    public:
        JeklikMeleeStackedTrigger(PlayerbotAI* ai) : ValueTrigger(ai, "jeklik melee stacked", 1)
        {
            qualifier = "and::{"
                "melee range,"
                "friendly count::5y>3"
                "}";
        }
    };

    class JeklikCastingHealTrigger : public ValueTrigger
    {
    public:
        JeklikCastingHealTrigger(PlayerbotAI* ai) : ValueTrigger(ai, "jeklik casting heal", 1)
        {
            qualifier = "and::{"
                "enemy casting::23860,"
                "interrupt possible"
                "}";
        }
    };

    class MindFlayOnFriendTrigger : public HasAuraTrigger
    {
    public:
        MindFlayOnFriendTrigger(PlayerbotAI* ai) : HasAuraTrigger(ai, "mind flay on friend", 24633)
        {
            qualifier = "friend";
        }
    };

    class BatAddsPresentTrigger : public ValueTrigger
    {
    public:
        BatAddsPresentTrigger(PlayerbotAI* ai) : ValueTrigger(ai, "bat adds present", 1)
        {
            qualifier = "enemy count::10y>3";
        }
    };
}
