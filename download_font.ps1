$url = "https://cdnjs.cloudflare.com/ajax/libs/font-awesome/5.15.4/webfonts/fa-solid-900.ttf"
$out = "c:/Users/Toshiba/Desktop/LionX-Engine/fa-solid-900.ttf"

Write-Host "Downloading $url..."
try {
    [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.SecurityProtocolType]::Tls12
    $webclient = New-Object System.Net.WebClient
    $webclient.DownloadFile($url, $out)
    Write-Host "Success! File size: $((Get-Item $out).Length) bytes"
} catch {
    Write-Host "Failed: $_"
}
