$fontPath = "c:/Users/Toshiba/Desktop/LionX-Engine/fa-solid-900.ttf"
$outputPath = "c:/Users/Toshiba/Desktop/LionX-Engine/app/src/main/jni/include/font_fontawesome.h"

if (!(Test-Path $fontPath)) {
    Write-Host "Error: Font not found at $fontPath!"
    exit 1
}

Write-Host "Reading bytes from $fontPath..."
$bytes = [System.IO.File]::ReadAllBytes($fontPath)
$len = $bytes.Length
Write-Host "Read $len bytes. Formatting to C++ array..."

$sb = New-Object System.Text.StringBuilder
[void]$sb.AppendLine("// Auto-generated font header from $fontPath")
[void]$sb.AppendLine("#pragma once")
[void]$sb.AppendLine("const unsigned char font_awesome_ttf[] = {")

$chunkSize = 16
for ($i = 0; $i -lt $len; $i += $chunkSize) {
    $chunk = @()
    $limit = [Math]::Min($i + $chunkSize, $len)
    for ($j = $i; $j -lt $limit; $j++) {
        $chunk += "0x{0:x2}" -f $bytes[$j]
    }
    $line = "    " + ($chunk -join ", ")
    if ($limit -lt $len) {
        $line += ","
    }
    [void]$sb.AppendLine($line)
}

[void]$sb.AppendLine("};")
[void]$sb.AppendLine("const unsigned int font_awesome_ttf_len = $len;")

Write-Host "Writing to $outputPath..."
[System.IO.File]::WriteAllText($outputPath, $sb.ToString())
Write-Host "Successfully generated FontAwesome header at $outputPath!"
