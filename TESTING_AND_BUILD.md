# Build and Testing Baseline

## Current .NET build

The application project currently declares `net6.0` in `RPGMenuSystem.csproj`, while the main README advertises .NET 8. The workflow uses the .NET 8 SDK, which can build a net6.0 target when the corresponding targeting pack is available, but it does not by itself migrate the app to .NET 8. See `AUDIT_AND_IMPLEMENTATION_ROADMAP.md` and resolve this mismatch before release.

Run locally:

```bash
dotnet --info
dotnet restore RPGMenuSystem.csproj
dotnet build RPGMenuSystem.csproj --configuration Release
dotnet run --project RPGMenuSystem.csproj
```

The console app may attempt SQL Server initialization first and falls back to file-based saves when database initialization fails. Use a local disposable database when evaluating database setup. Never run the destructive reset SQL against a database containing wanted data.

## Unreal Engine

The current repository includes UE-style C++ source, but at the time of the audit the recursive tree did not contain a project descriptor or module build file at the conventional paths. The Unreal C++ files therefore have not been validated by this workflow. Do not treat a successful .NET build as evidence that Unreal code compiles.

## Test policy

- Keep pure game rules testable without a SQL Server or Unreal Editor.
- Cover player level progression, damage/defense, consumable use, item stacks, equipment changes, quest rewards, and save/load.
- Use a separate test database and deterministic fixtures for persistence tests.
- Record engine/version, build command, and result for each claimed release.
