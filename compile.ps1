# PowerShell compile helper (requires g++ available in PATH)
# Collect all .cpp files recursively and compile to main.exe
$files = Get-ChildItem -Path . -Recurse -Filter *.cpp | ForEach-Object { $_.FullName }
if ($files.Count -eq 0) {
  Write-Error "No .cpp files found"
  exit 1
}
& g++ -fdiagnostics-color=always -g $files -Iinclude -o main.exe
if ($LASTEXITCODE -ne 0) {
  Write-Error "g++ returned exit code $LASTEXITCODE"
  exit $LASTEXITCODE
}
Write-Output "Compiled to main.exe"
