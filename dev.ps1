param(
    [ValidateSet("build", "test", "bench", "all")]
    [string]$Action = "all",

    [ValidateSet("Debug", "Release")]
    [string]$Config = "Debug"
)

$buildDir = "build/msvc-$($Config.ToLower())"
$reportDir = "$buildDir/reports"

function Clean-Build {
    if (Test-Path $buildDir) {
        Write-Host "🧹 Removing old build: $buildDir" -ForegroundColor Magenta
        Remove-Item -Recurse -Force $buildDir
    }
}

function Configure-Build {
    Write-Host "🔧 Configuring project ($Config) ..." -ForegroundColor Cyan
    cmake --preset=msvc-$($Config.ToLower())
    if ($LASTEXITCODE -ne 0) { throw "❌ CMake configure failed" }
}

function Build-Project {
    Write-Host "⚙️ Building project ($Config) ..." -ForegroundColor Cyan
    cmake --build $buildDir --config $Config
    if ($LASTEXITCODE -ne 0) { throw "❌ Build failed" }
}

function Run-Tests {
    Write-Host "🧪 Running tests ($Config) ..." -ForegroundColor Cyan
    if (-not (Test-Path $reportDir)) {
        New-Item -ItemType Directory -Force -Path $reportDir | Out-Null
    }

    Push-Location $buildDir

    # Run tests with ctest and export JUnit report
    ctest -C $Config --output-on-failure --no-compress-output --test-dir . `
          --output-junit "$reportDir\junit.xml"

    Pop-Location

    # Generate simple HTML report from JUnit XML (using XSLT or PowerShell formatting)
    if (Test-Path "$reportDir\junit.xml") {
        Write-Host "📄 Converting JUnit XML → HTML report..." -ForegroundColor Cyan

        $xml = [xml](Get-Content "$reportDir\junit.xml")
        $html = "<html><head><title>Test Report</title></head><body>"
        $html += "<h2>DynamicArray Test Report ($Config)</h2>"
        $html += "<table border='1' cellpadding='5' cellspacing='0'>"
        $html += "<tr><th>Test Case</th><th>Status</th><th>Time (s)</th></tr>"

        foreach ($suite in $xml.testsuites.testsuite) {
            foreach ($case in $suite.testcase) {
                $status = if ($case.failure) { "❌ FAIL" } else { "✅ PASS" }
                $time = if ($case.time) { $case.time } else { "0" }
                $html += "<tr><td>$($case.name)</td><td>$status</td><td>$time</td></tr>"
            }
        }

        $html += "</table></body></html>"
        $html | Out-File "$reportDir\report.html" -Encoding UTF8

        Write-Host "✅ Reports generated: $reportDir\junit.xml, $reportDir\report.html" -ForegroundColor Green
    }
}

function Run-Benchmarks {
    Write-Host "⚡ Running benchmarks ($Config) ..." -ForegroundColor Cyan

    if (-not (Test-Path $reportDir)) {
        New-Item -ItemType Directory -Force -Path $reportDir | Out-Null
    }

    $benchmarks = @(
        "bench_dynamic_array.exe"
    )

    foreach ($bench in $benchmarks) {
        $exePath = Join-Path $buildDir "$Config\$bench"
        if (Test-Path $exePath) {
            $benchName = [System.IO.Path]::GetFileNameWithoutExtension($bench)
            Write-Host "`n▶️ $bench" -ForegroundColor Yellow
            & $exePath --benchmark_out="$reportDir\$benchName.json" --benchmark_out_format=json
        } else {
            Write-Warning "⚠️ $bench not found in $Config build."
        }
    }
}


# ---------------- MAIN ----------------
try {
    Clean-Build
    Configure-Build
    Build-Project

    switch ($Action) {
        "build" { }
        "test"  { Run-Tests }
        "bench" { Run-Benchmarks }
        "all"   { Run-Tests; Run-Benchmarks }
    }
}
catch {
    Write-Error $_
    exit 1
}
