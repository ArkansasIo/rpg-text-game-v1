# Repository Audit and Implementation Roadmap

**Repository:** https://github.com/ArkansasIo/rpg-text-game-v1  
**Reviewed:** 2026-10-22  
**Default branch:** `main`

## Executive summary

This repository is a substantial RPG prototype/framework rather than only a small text adventure. It contains C# gameplay and UI systems, SQL Server/Entity Framework database code, Unreal Engine C++ source files, content/design documentation, and an explicit C#-to-UE C++ conversion plan.

The repository tree inspected for this audit contained 187 entries: 48 C# files, 42 C/C++ source/header files, and 10 SQL files. These counts are file-extension counts, not proof that every file is complete or builds.

Recent commit messages show a Phase 1 report of five core systems converted and Phase 2 work beginning on world definition and Aethermoor. The present audit did not run a .NET build or Unreal Build Tool, so compile/runtime status remains unverified.

## Key findings

### 1. Mixed .NET target/version documentation
- `README.md` advertises .NET 8.
- `RPGMenuSystem.csproj` targets `net6.0` and uses Entity Framework Core 6.0.25.
- `DEV_STARTUP_GUIDE.md` references .NET 6 and a developer-specific Windows project path.
- Decision needed: either keep .NET 6 and align documentation, or upgrade project/framework packages together to a currently supported .NET version. Prefer upgrade only after testing API and migration compatibility.

### 2. Unreal Engine integration scaffold appears incomplete
The repository has significant UE-style C++ under `UnrealEngine5/Source/RPGProject`, including character, components, systems, world, shop, dungeon, and UI modules. But the recursive tree inspection did not find:
- `UnrealEngine5/RPGProject.uproject`
- `UnrealEngine5/Source/RPGProject/RPGProject.Build.cs`
- `UnrealEngine5/Source/RPGProject/RPGProject.cpp`
- A GitHub Actions workflow under `.github/workflows/`

These are important gaps for a clean, portable UE project/build. Some files may be intended as export examples rather than a standalone Unreal project; the docs should state that clearly until the project scaffold exists.

### 3. Potential Unreal Header Tool / compile blockers
A source inspection found `DECLARE_DYNAMIC_MULTICAST_DELEGATE_Two` and `DECLARE_DYNAMIC_MULTICAST_DELEGATE_One` in `UnrealEngine5/Source/RPGProject/Systems/CombatSystem.h`. Standard UE delegate macro families commonly use `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams` and `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam`. Verify and correct these declarations before a UE build.

Other likely audit targets:
- Check every reflected header includes its matching `*.generated.h` last among includes.
- Confirm every declared UCLASS/USTRUCT is reflected/compiled by UHT and each implementation is included in the module.
- Eliminate duplicated or incompatible system ownership between `ARPGGameMode`, `ARPGGameSystemsManager`, and player-owned `UObject` systems.
- Ensure required forward declarations/includes are correct.
- Use server authority and replicated state for multiplayer-critical state; client RPCs/UI must not authoritatively mutate inventory, currency, damage, rewards, or quests.

### 4. Database bootstrap is destructive and not truly one-click
`Database/00_CreateDatabase.sql` explicitly switches to master, drops the existing `RPGGame` database if present, recreates it, then instructs the user to run separate schema/item scripts. This is dangerous when data already exists, and the name suggests a complete setup even though it only creates the database and prints next steps.
- Rename/document it as a destructive reset script, or remove automatic database deletion from the normal setup path.
- Make the standard bootstrap idempotent and require explicit opt-in before dropping data.
- Add a disposable local/test database profile and verify schema scripts execute in dependency order.

### 5. Gameplay rules require tests and central validation
The inspected C# `Player.cs` shows level progression, health/mana growth, defense, consumable effects, and equipment-derived stats. The UE combat implementation uses random critical hits/variance and separate defense calculations. These are reasonable prototypes, but parity between the C# reference implementation and UE C++ needs formal test vectors.
- Define shared combat/XP/inventory rules.
- Test edge cases: negative XP/damage/quantity, over-healing, zero/negative cooldowns, overflow, invalid equipment slots, item stack caps, and duplicate reward claims.
- Fix discrepancies with explicit expected outcomes instead of trusting the two implementations to remain equivalent.

### 6. No automated test or CI pipeline found
No test source files matched the inspected tree and no `.github/workflows/` workflow exists.
- Add .NET build and unit-test CI immediately.
- Add static checks for generated Unreal project structure and source conventions.
- Run Unreal compilation only on a properly provisioned Unreal runner or document a local build script; do not claim a UE build succeeds without one.

## Recommended implementation order

### P0 — Establish a trustworthy baseline
1. Add a root-level audit/status page and clarify whether this repository is a playable C# console game, UE source export, or both.
2. Make the .NET framework/package target consistent.
3. Add .NET build/test workflow and a minimal automated test project.
4. Make database setup safe and reproducible; keep destructive reset separate and clearly named.
5. Fix the combat delegate macro declarations and inspect all UHT/build prerequisites.

### P1 — Deliver a playable vertical slice
1. New game / character setup.
2. Explore Aethermoor zones and inspect NPCs.
3. Encounter enemies and run turn-based or explicitly specified real-time combat.
4. Gain XP, level up, earn loot/gold.
5. Inventory, equip/unequip, consume items, shop.
6. Complete and claim one quest.
7. Save/load and resume.
8. A repeatable smoke test for the entire loop.

Choose a single source of truth for game rules. If C# remains a runnable text RPG and UE5 is a separate target, specify shared rules/data contracts rather than maintaining two unsynchronized copies.

### P2 — Complete Unreal Engine scaffold
Create/verify:
- `UnrealEngine5/RPGProject.uproject`
- `UnrealEngine5/Source/RPGProject/RPGProject.Build.cs`
- `UnrealEngine5/Source/RPGProject/RPGProject.cpp`
- `RPGProjectEditor.Target.cs` and `RPGProject.Target.cs`
- Required GameMode, PlayerController, Pawn/Character, and module config.
- Input assets or documented setup for Enhanced Input.
- Data assets/data tables for items, enemies, quests, zones, and balance values.
- Packaging/launch instructions without machine-specific paths.

### P3 — Content pipeline and assets
Build content as original, data-driven fantasy RPG assets:
- Character races/classes, classes/specs, equipment and weapons.
- Item rarity, affixes, icons and tooltips.
- Enemy families, boss variants and loot tables.
- Biomes/zones, settlements, NPC dialogue.
- Dungeons, encounter tables, quest chains, achievements.
- Main menu, character sheet, inventory, map, quest log, merchant and combat HUD.
Use original names/art rather than copying protected assets from commercial games.

### P4 — Multiplayer readiness (only after vertical slice works)
- Dedicated-server authority model and explicit replication policy.
- Authentication/session ownership and secure persistence.
- Server validation for damage, movement, inventory, trade, crafting, currency and quest rewards.
- Idempotent reward/trade requests, audit logs, reconnect and recovery tests.
- Load-test targets and a documented service boundary. A single-player prototype is not an MMO server just because it contains guild/social classes.

## Acceptance checklist

- [ ] Clean checkout restores and builds on a fresh machine.
- [ ] Automated tests pass in CI.
- [ ] A full new-game → combat → loot → quest → save/load loop works.
- [ ] Database setup does not destroy an existing database by default.
- [ ] UE project opens/compiles using documented engine version and modules, or files are clearly labeled as reference/export source.
- [ ] No critical gameplay state is client-authoritative in multiplayer.
- [ ] Documentation separates implemented, partially implemented, planned, and unverified features.
- [ ] README feature counts are generated from the repository or explicitly labeled as design targets.

## Scope and limitation of this audit

This was a remote repository/tree/source inspection. It did not execute `dotnet restore`, `dotnet build`, SQL Server setup, Unreal Build Tool, Unreal Header Tool, packaged builds, or gameplay sessions. Items above marked as potential issues require toolchain validation before they can be called confirmed compile failures.
