# PlayerBots Live Integration Test Framework

## Overview

The test framework allows bots to execute self-testing scripts that verify bot behavior in real-time. Tests are activated via qualified strategies (e.g., `+test:walk_to_ironforge`) and run scripted scenarios with monitoring.

## Quick Start

```bash
# Activate a test
.bot mybot strategy +test:walk_to_ironforge

# Or use the test command directly
.bot mybot test walk_to_ironforge
```

## Architecture

### Two Execution Modes

1. **Scripted Mode** (blocking): Execute DSL commands one per tick, preventing other actions
2. **Observe Mode** (yielding): Normal AI runs while monitors check conditions each tick

### Test Lifecycle

```
1. Strategy activated (+test:<name>)
2. Script loaded from registry
3. Scripted phase: execute commands
4. Observe phase: AI runs, monitors check
5. Monitor triggers → result set
6. Report result (console + file)
7. Strategy deactivated
```

## DSL Reference

### Scripted Commands

| Command | Description |
|---------|-------------|
| `teleport <location>` | Teleport to named location or coords |
| `set destination <loc>` | Set AI navigation target |
| `spawn bot <class> <spec> at <loc>` | Spawn test bot |
| `despawn bot <guid>` | Remove spawned bots |
| `clear mobs radius <yards>` | Clear hostile mobs |
| `form party` | Form party |
| `give item <itemId>` | Give item to bot |
| `equip item <itemId>` | Equip item |
| `observe` | Switch to observe mode |
| `cleanup` | End test and cleanup |
| `assert <condition>` | Verify condition (fails immediately if false) |
| `monitor <condition>` | Register monitor for observe mode |

**Fallthrough**: Any unrecognized command is passed to the bot's chat command handler with a debug log.

### Monitor Commands

Monitors are declared in scripted mode, checked every tick during observe:

```
monitor time > <seconds> => fail "<message>"
monitor time > <seconds> => pass "<message>"
monitor hp < <percent> => fail "<message>"
monitor distance to <location> < <yards> => pass "<message>"
monitor distance to <location> > <yards> => fail "<message>"
monitor mob <entryId> is dead => pass "<message>"
monitor party wiped => fail "<message>"
```

### Assert Commands

Asserts are evaluated immediately and fail the test if condition is not met:

```
assert distance to <location> < <yards>
assert distance to <location> > <yards>
assert mob <entryId> is dead
assert hp > <percent>
assert time < <seconds>
```

## Named Locations

Built-in location lookup:

| Name | Map | Coordinates |
|------|-----|-------------|
| `ironforge` | 0 | -4981.25, -881.54, 502.62 |
| `ironforge_outside` | 0 | -5144.0, -866.0, 501.0 |
| `stormwind` | 0 | -8833.0, 628.0, 97.0 |
| `orgrimmar` | 1 | 1676.35, -4315.77, 61.84 |
| `ratchet_dock` | 1 | -1016.0, -3754.0, 5.5 |
| `ratchet_flightmaster` | 1 | -1003.0, -3754.0, 6.0 |
| `booty_bay_dock` | 0 | -14285.0, 532.0, 23.0 |
| `zg_entrance` | 309 | -11917.0, -1233.0, 92.0 |

**Raw coordinates**: Use `m <map> <x> <y> <z>` format:
```
teleport m 0 -4981.25 -881.54 502.62
```

## Available Tests

### walk_to_ironforge
Tests basic navigation to Ironforge.

```
teleport ironforge_outside
monitor time > 120 => fail "Timeout: bot did not reach Ironforge gate"
monitor distance to ironforge < 50 => pass "Bot reached Ironforge gate"
observe
```

### flight_ratchet_to_booty_bay
Tests flight path navigation.

```
teleport ratchet_flightmaster
monitor time > 300 => fail "Timeout: flight took too long"
monitor distance to booty_bay_dock < 100 => pass "Bot arrived at Booty Bay"
observe
```

## Usage

### Via Strategy (Recommended)

```bash
# Start test
.bot mybot strategy +test:walk_to_ironforge

# Check status
.bot mybot strategy

# Cancel test
.bot mybot strategy -test:walk_to_ironforge
```

### Via Command

```bash
.bot mybot test walk_to_ironforge
```

## Output

### Chat Output
```
[TEST] Starting test: walk_to_ironforge
[TEST] Teleported to ironforge_outside
[TEST] Entering observe mode
[TEST] TEST PASS: Bot reached Ironforge gate
[TEST] Test complete: PASS
```

### Console Output
```
[BOTTEST] 2026-04-18 14:32:15 | mybot | walk_to_ironforge | PASS | Bot reached Ironforge gate
```

### File Output
Results are appended to `bot_test_results.log` in the server working directory:
```
[BOTTEST] 2026-04-18 14:32:15 | mybot | walk_to_ironforge | PASS | Bot reached Ironforge gate
```

## Adding Custom Tests

Register tests in `TestAction.cpp`:

```cpp
TestAction::RegisterTest("my_test", {
    "teleport stormwind",
    "monitor time > 60 => fail \"Timeout\"",
    "observe"
});
```

## Adding Named Locations

Add to `sTestLocations` map in `TestAction.cpp`:

```cpp
{"my_location", {mapId, x, y, z}},
```

## Debugging

Enable debug output:
```
.bot mybot strategy +debug
```

Watch for `[TestAction]` prefixed messages in console.

## Implementation Notes

- **Assert behavior**: Fails immediately if condition not met
- **Fallthrough**: Unknown commands passed to bot command handler
- **Priority**: Test action runs at priority 10 (higher than normal actions)
- **No triggers**: Strategy runs test action every tick while active
- **Auto-deactivate**: Strategy removed after test completes
