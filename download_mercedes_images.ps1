Add-Type -AssemblyName System.Drawing

$OutputDir = "h:\TaxiGame\source\Car Images"
$TargetSize = 400

if (-not (Test-Path $OutputDir)) {
    New-Item -ItemType Directory -Path $OutputDir -Force | Out-Null
}

$MercedesModels = @(
    @{model="Mercedes-Benz C-klasse"; file="mercedes_c_klasse"},
    @{model="Mercedes-Benz C-Class"; file="mercedes_c_class"},
    @{model="Mercedes-Benz C300"; file="mercedes_c300"},
    @{model="Mercedes-Benz C43 AMG"; file="mercedes_c43_amg"},
    @{model="Mercedes-Benz C63 AMG"; file="mercedes_c63_amg"},
    @{model="Mercedes-Benz E-klasse"; file="mercedes_e_klasse"},
    @{model="Mercedes-Benz E-Class"; file="mercedes_e_class"},
    @{model="Mercedes-Benz E350"; file="mercedes_e350"},
    @{model="Mercedes-Benz E450"; file="mercedes_e450"},
    @{model="Mercedes-Benz E53 AMG"; file="mercedes_e53_amg"},
    @{model="Mercedes-Benz E63 AMG"; file="mercedes_e63_amg"},
    @{model="Mercedes-Benz S-klasse"; file="mercedes_s_klasse"},
    @{model="Mercedes-Benz S-Class"; file="mercedes_s_class"},
    @{model="Mercedes-Benz S500"; file="mercedes_s500"},
    @{model="Mercedes-Benz Maybach S-klasse"; file="mercedes_maybach_s_klasse"}
)

function Download-And-Resize {
    param([string]$ModelName, [string]$FileName)
    
    Write-Host "Downloading: $ModelName..." -NoNewline
    
    try {
        $searchQuery = [System.Uri]::EscapeDataString($ModelName)
        $url = "https://source.unsplash.com/featured/?$searchQuery"
        
        $webClient = New-Object System.Net.WebClient
        $webClient.Headers.Add("User-Agent", "Mozilla/5.0")
        
        $tempFile = [System.IO.Path]::GetTempFileName()
        $webClient.DownloadFile($url, $tempFile)
        
        $image = [System.Drawing.Image]::FromFile($tempFile)
        $resized = New-Object System.Drawing.Bitmap($TargetSize, $TargetSize)
        $graphics = [System.Drawing.Graphics]::FromImage($resized)
        $graphics.InterpolationMode = [System.Drawing.Drawing2D.InterpolationMode]::HighQualityBicubic
        $graphics.DrawImage($image, 0, 0, $TargetSize, $TargetSize)
        
        $outputPath = Join-Path $OutputDir "$FileName.png"
        $resized.Save($outputPath, [System.Drawing.Imaging.ImageFormat]::Png)
        
        $graphics.Dispose()
        $resized.Dispose()
        $image.Dispose()
        $webClient.Dispose()
        Remove-Item $tempFile -Force -ErrorAction SilentlyContinue
        
        Write-Host " OK" -ForegroundColor Green
        return $true
    }
    catch {
        Write-Host " FAILED" -ForegroundColor Red
        return $false
    }
}

Write-Host "Downloading Mercedes-Benz images"
Write-Host "Target size: 400x400 pixels"
Write-Host ""

$successful = 0
$failed = 0

foreach ($item in $MercedesModels) {
    if (Download-And-Resize -ModelName $item.model -FileName $item.file) {
        $successful++
    }
    else {
        $failed++
    }
    Start-Sleep -Milliseconds 500
}

Write-Host ""
Write-Host "Complete!"
Write-Host "Successful: $successful"
Write-Host "Failed: $failed"
Write-Host "Output: $OutputDir"
