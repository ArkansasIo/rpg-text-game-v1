# Organize Blueprint Documentation
# Moves all blueprint-related files to Documentation/Blueprints folder

Write-Host "??? Organizing Blueprint Documentation..." -ForegroundColor Cyan

# Create Documentation structure
$docRoot = "Documentation"
$blueprintFolder = "$docRoot/Blueprints"
$setupFolder = "$docRoot/Setup"
$worldFolder = "$docRoot/WorldSystem"

New-Item -ItemType Directory -Force -Path $blueprintFolder | Out-Null
New-Item -ItemType Directory -Force -Path $setupFolder | Out-Null
New-Item -ItemType Directory -Force -Path $worldFolder | Out-Null

Write-Host "? Created folder structure" -ForegroundColor Green

# Blueprint Framework Files
$blueprintFiles = @(
    "UE5_UNIVERSAL_BLUEPRINT_FRAMEWORK.md",
    "UE5_UNIVERSAL_BLUEPRINT_FRAMEWORK_IMPLEMENTATION.md",
    "UE5_BLUEPRINT_FRAMEWORK_QUICK_START.md",
    "UE5_BLUEPRINT_FRAMEWORK_MASTER_INDEX.md",
    "README_BLUEPRINT_FRAMEWORK.md",
    "BLUEPRINT_FRAMEWORK_FILE_INDEX.md",
    "BLUEPRINT_FRAMEWORK_COMPLETION_SUMMARY.md",
    "BLUEPRINT_DOCUMENTATION_INDEX.md",
    "UE5_BLUEPRINT_FOLDER_STRUCTURE.md",
    "UE5_BLUEPRINT_QUICK_START_TODAY.md",
    "UE5_BLUEPRINT_COMPLETE_MASTER_GUIDE.md",
    "UE5_BLUEPRINT_TEMPLATES.md",
    "UE5_BLUEPRINT_IMPLEMENTATION_GUIDE.md",
    "UE5_BLUEPRINT_CHECKLIST_AND_SAVE_ORGANIZATION.md",
    "UE5_3D_MMORPG_COMPLETE_GUIDE.md",
    "UE5_3D_MMORPG_MASTER_INDEX.md",
    "UE5_3D_MMORPG_SUMMARY.md"
)

# Setup/Installation Files
$setupFiles = @(
    "HOW_TO_OPEN_IN_UNREAL_ENGINE_5.md",
    "UNREAL_ENGINE_5_QUICK_START_15MIN.md",
    "UNREAL_ENGINE_5_SETUP_VISUAL_GUIDE.md",
    "UNREAL_ENGINE_5_SETUP_MASTER_INDEX.md",
    "UNREAL_ENGINE_5_SETUP_COMPLETE.md"
)

# World System Files
$worldFiles = @(
    "WORLD_DOCUMENTATION.md",
    "WORLD_SYSTEM_README.md",
    "WORLD_SYSTEM_MASTER_INDEX.md",
    "WORLD_CREATION_SUMMARY.md",
    "AethermoorWorldDisplay.cs"
)

# Summary/Completion Files
$summaryFiles = @(
    "COMPLETION_SUMMARY.md",
    "COMPLETE_DOCUMENTATION_MASTER_LIST.md",
    "GITHUB_PUSH_SUCCESS.md",
    "GITHUB_PUSH_GUIDE.md"
)

Write-Host "`n?? Moving Blueprint files..." -ForegroundColor Yellow
foreach ($file in $blueprintFiles) {
    if (Test-Path $file) {
        Move-Item -Path $file -Destination $blueprintFolder -Force
        Write-Host "  ? Moved: $file" -ForegroundColor Green
    }
}

Write-Host "`n?? Moving Setup files..." -ForegroundColor Yellow
foreach ($file in $setupFiles) {
    if (Test-Path $file) {
        Move-Item -Path $file -Destination $setupFolder -Force
        Write-Host "  ? Moved: $file" -ForegroundColor Green
    }
}

Write-Host "`n?? Moving World System files..." -ForegroundColor Yellow
foreach ($file in $worldFiles) {
    if (Test-Path $file) {
        Move-Item -Path $file -Destination $worldFolder -Force
        Write-Host "  ? Moved: $file" -ForegroundColor Green
    }
}

Write-Host "`n?? Moving Summary files to Documentation root..." -ForegroundColor Yellow
foreach ($file in $summaryFiles) {
    if (Test-Path $file) {
        Move-Item -Path $file -Destination $docRoot -Force
        Write-Host "  ? Moved: $file" -ForegroundColor Green
    }
}

Write-Host "`n? Organization Complete!" -ForegroundColor Green
Write-Host "`nNew Structure:" -ForegroundColor Cyan
Write-Host "Documentation/" -ForegroundColor White
Write-Host "  ??? Blueprints/ (17 files)" -ForegroundColor Gray
Write-Host "  ??? Setup/ (5 files)" -ForegroundColor Gray
Write-Host "  ??? WorldSystem/ (5 files)" -ForegroundColor Gray
Write-Host "  ??? *.md (4 summary files)" -ForegroundColor Gray

Write-Host "`nRoot folder now contains:" -ForegroundColor Cyan
Write-Host "  ??? README.md" -ForegroundColor Gray
Write-Host "  ??? LICENSE" -ForegroundColor Gray
Write-Host "  ??? .gitignore" -ForegroundColor Gray
Write-Host "  ??? Documentation/" -ForegroundColor Gray
Write-Host "  ??? UnrealEngine5/" -ForegroundColor Gray
Write-Host "  ??? Database/" -ForegroundColor Gray
Write-Host "  ??? Game/" -ForegroundColor Gray
Write-Host "  ??? UI/" -ForegroundColor Gray
Write-Host "  ??? SaveSystem/" -ForegroundColor Gray
Write-Host "  ??? MenuSystem/" -ForegroundColor Gray
