param([string]$OutputDirectory = (Join-Path $env:TEMP "mybooks-build-x64"))
$ErrorActionPreference = "Stop"
$repo = Split-Path -Parent $PSScriptRoot
$roots = @("windows-c-programming", "malware-analysis/code/windows-c", "windows-stack-safety", "windows-heap-safety")
New-Item -ItemType Directory -Force -Path $OutputDirectory | Out-Null
$sources = foreach ($root in $roots) { Get-ChildItem -LiteralPath (Join-Path $repo $root) -Recurse -File -Filter "*.c" }
$failures = 0
foreach ($source in $sources) {
    $relative = $source.FullName.Substring($repo.Length).TrimStart('\')
    $name = $relative -replace '[\\/: ]', '_'
    Write-Host "Compiling $relative"
    & cl.exe /nologo /W4 /TC $source.FullName "/Fo$(Join-Path $OutputDirectory "$name.obj")" "/Fe$(Join-Path $OutputDirectory "$name.exe")"
    if ($LASTEXITCODE -ne 0) { $failures++ }
}
if ($failures -gt 0) { throw "$failures of $($sources.Count) x64 examples failed to compile." }
Write-Host "Compiled $($sources.Count) x64 examples successfully."
