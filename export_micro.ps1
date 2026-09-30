param (
    [Parameter(Mandatory=$true)]
    [string]$DestDir
)

Write-Host "--- Starting export for microprocessed use ---"

if (!(Test-Path "Source") -or !(Test-Path "CMakeLists.txt")) {
    Write-Host "Error: This script must be executed at the root of the GamepadCore project." -ForegroundColor Red
    exit 1
}

if (!(Test-Path $DestDir)) {
    Write-Host "Creating destination directory: $DestDir"
    New-Item -ItemType Directory -Force -Path $DestDir | Out-Null
}

$ItemsToCopy = @("Source", "CMakeLists.txt", "LICENSE")

foreach ($Item in $ItemsToCopy) {
    if (Test-Path $Item) {
        Write-Host "Copying $Item to $DestDir..."
        if ((Get-Item $Item) -is [System.IO.DirectoryInfo]) {
            Copy-Item -Path $Item -Destination (Join-Path $DestDir (Split-Path $Item -Leaf)) -Recurse -Force
        } else {
            Copy-Item -Path $Item -Destination $DestDir -Force
        }
    } else {
        Write-Host "Warning: $Item not found, skipping." -ForegroundColor Yellow
    }
}

Write-Host "--- Export completed! ---"
Write-Host "Files exported to: $DestDir"
Get-ChildItem -Path $DestDir
