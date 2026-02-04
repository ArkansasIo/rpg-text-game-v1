#!/usr/bin/env pwsh
<#
.SYNOPSIS
    RPG Development Environment Startup Script
    
.DESCRIPTION
    Initializes and launches the complete RPG development environment
    including Unreal Engine 5, database, and C# systems.
    
.PARAMETER Mode
    dev-ue5    - Launch UE5 Editor with RPG systems
    dev-cs     - Launch C# game development
    dev-all    - Launch both (parallel)
    dev-setup  - Setup and verify environment
    
.EXAMPLE
    .\dev-startup.ps1 -Mode dev-ue5
    .\dev-startup.ps1 -Mode dev-all
#>

param(
    [Parameter(Mandatory=$false)]
    [ValidateSet("dev-ue5", "dev-cs", "dev-all", "dev-setup")]
    [string]$Mode = "dev-setup"
)

$ProjectRoot = "C:\Users\Shadow\source\repos\Solution1"
$UE5Path = "C:\Program Files\Epic Games\UE_5.3\Engine\Binaries\Win64"
$UE5Editor = "$UE5Path\UE4Editor.exe"
$ProjectFile = "$ProjectRoot\AethermoorRPG.uproject"
$CSharpProject = "$ProjectRoot\RPGMenuSystem.csproj"

Write-Host "================================" -ForegroundColor Cyan
Write-Host "?? RPG DEV ENVIRONMENT STARTUP" -ForegroundColor Cyan
Write-Host "================================" -ForegroundColor Cyan
Write-Host ""

# Function to check file existence
function Test-FileExists($Path) {
    if (Test-Path $Path) {
        Write-Host "? Found: $Path" -ForegroundColor Green
        return $true
    } else {
        Write-Host "? Missing: $Path" -ForegroundColor Red
        return $false
    }
}

# Function to setup environment
function Setup-Environment {
    Write-Host ""
    Write-Host "?? VERIFYING ENVIRONMENT..." -ForegroundColor Yellow
    Write-Host ""
    
    $AllGood = $true
    
    # Check UE5
    if (Test-FileExists $UE5Editor) {
        Write-Host "   UE5 Editor ready" -ForegroundColor Green
    } else {
        Write-Host "   ??  UE5 not found at $UE5Editor" -ForegroundColor Yellow
        $AllGood = $false
    }
    
    # Check UE5 Project
    if (Test-FileExists $ProjectFile) {
        Write-Host "   Unreal project ready" -ForegroundColor Green
    } else {
        Write-Host "   ??  Project file not found" -ForegroundColor Yellow
    }
    
    # Check C# Project
    if (Test-FileExists $CSharpProject) {
        Write-Host "   C# project ready" -ForegroundColor Green
    } else {
        Write-Host "   ??  C# project not found" -ForegroundColor Yellow
    }
    
    # Check systems
    $SystemsPath = "$ProjectRoot\UnrealEngine5\Source\RPGProject\Systems"
    $SystemFiles = Get-ChildItem "$SystemsPath\*.h" 2>/dev/null | Measure-Object | Select-Object -ExpandProperty Count
    Write-Host "   Systems created: $SystemFiles files" -ForegroundColor Green
    
    # Check documentation
    $DocFiles = Get-ChildItem "$ProjectRoot\*.md" 2>/dev/null | Measure-Object | Select-Object -ExpandProperty Count
    Write-Host "   Documentation: $DocFiles files" -ForegroundColor Green
    
    Write-Host ""
    
    if ($AllGood) {
        Write-Host "? ENVIRONMENT VERIFIED - READY TO DEVELOP!" -ForegroundColor Green
    } else {
        Write-Host "??  Some components missing - setup may be required" -ForegroundColor Yellow
    }
    
    Write-Host ""
}

# Function to launch UE5
function Launch-UE5 {
    Write-Host ""
    Write-Host "?? LAUNCHING UNREAL ENGINE 5..." -ForegroundColor Cyan
    Write-Host ""
    
    if (Test-Path $UE5Editor) {
        Write-Host "Starting UE5 Editor..." -ForegroundColor Yellow
        Write-Host "Path: $UE5Editor" -ForegroundColor Gray
        Write-Host "Project: $ProjectFile" -ForegroundColor Gray
        Write-Host ""
        
        try {
            Start-Process $UE5Editor -ArgumentList "-project=$ProjectFile -game" -NoNewWindow
            Write-Host "? UE5 Editor launched!" -ForegroundColor Green
            Write-Host ""
            Write-Host "?? What to do next:" -ForegroundColor Yellow
            Write-Host "   1. Wait for editor to fully load (5-10 minutes first time)" -ForegroundColor Gray
            Write-Host "   2. Create Blueprint children of the systems" -ForegroundColor Gray
            Write-Host "   3. Set up your game content" -ForegroundColor Gray
            Write-Host "   4. Design your levels and NPCs" -ForegroundColor Gray
            Write-Host ""
        } catch {
            Write-Host "? Failed to launch UE5: $_" -ForegroundColor Red
        }
    } else {
        Write-Host "? UE5 Editor not found!" -ForegroundColor Red
        Write-Host "   Expected at: $UE5Editor" -ForegroundColor Red
    }
}

# Function to launch C# game
function Launch-CSharp {
    Write-Host ""
    Write-Host "???  LAUNCHING C# GAME..." -ForegroundColor Cyan
    Write-Host ""
    
    if (Test-Path $CSharpProject) {
        Write-Host "Building C# project..." -ForegroundColor Yellow
        
        try {
            Push-Location $ProjectRoot
            dotnet build --configuration Release
            
            if ($LASTEXITCODE -eq 0) {
                Write-Host "? Build successful!" -ForegroundColor Green
                Write-Host ""
                Write-Host "Starting game..." -ForegroundColor Yellow
                dotnet run
            } else {
                Write-Host "? Build failed" -ForegroundColor Red
            }
            Pop-Location
        } catch {
            Write-Host "? Error: $_" -ForegroundColor Red
        }
    } else {
        Write-Host "? C# project not found!" -ForegroundColor Red
    }
}

# Function to launch both
function Launch-All {
    Write-Host ""
    Write-Host "?? LAUNCHING BOTH ENVIRONMENTS..." -ForegroundColor Cyan
    Write-Host ""
    
    # Launch UE5 in background
    Write-Host "Starting UE5..." -ForegroundColor Yellow
    Launch-UE5
    
    # Give it a moment
    Start-Sleep -Seconds 3
    
    # Launch C# in new window
    Write-Host ""
    Write-Host "Starting C# game in new window..." -ForegroundColor Yellow
    $PSFile = "$ProjectRoot\launch-csharp.ps1"
    
    # Create temp launcher script
    @"
cd "$ProjectRoot"
dotnet build --configuration Release
if (`$LASTEXITCODE -eq 0) {
    dotnet run
} else {
    Write-Host "Build failed - check errors above" -ForegroundColor Red
}
Read-Host "Press Enter to close"
"@ | Out-File $PSFile -Encoding UTF8
    
    Start-Process powershell -ArgumentList "-NoExit", "-File", $PSFile
    
    Write-Host ""
    Write-Host "? Both environments launching!" -ForegroundColor Green
    Write-Host ""
    Write-Host "?? Open windows:" -ForegroundColor Yellow
    Write-Host "   • Unreal Engine 5 (main window)" -ForegroundColor Gray
    Write-Host "   • C# Game (new PowerShell window)" -ForegroundColor Gray
}

# Main execution
Write-Host "Mode: $Mode" -ForegroundColor Gray
Write-Host ""

switch ($Mode) {
    "dev-setup" {
        Setup-Environment
    }
    "dev-ue5" {
        Setup-Environment
        Launch-UE5
    }
    "dev-cs" {
        Setup-Environment
        Launch-CSharp
    }
    "dev-all" {
        Setup-Environment
        Launch-All
    }
}

Write-Host ""
Write-Host "================================" -ForegroundColor Cyan
Write-Host "Ready for development! ??" -ForegroundColor Cyan
Write-Host "================================" -ForegroundColor Cyan
