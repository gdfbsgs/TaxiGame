# Download and resize Mercedes-Benz car images for TaxiGame

Add-Type -AssemblyName System.Drawing

$OutputDir = "h:\TaxiGame\source\Car Images"
$TargetSize = 400

if (-not (Test-Path $OutputDir)) {
    New-Item -ItemType Directory -Path $OutputDir -Force | Out-Null
}

$MercedesModels = @(
    "Mercedes-Benz C-klasse",
    "Mercedes-Benz C-Class",
    "Mercedes-Benz C300",
    "Mercedes-Benz C43 AMG",
    "Mercedes-Benz C63 AMG",
    "Mercedes-Benz E-klasse",
    "Mercedes-Benz E-Class",
    "Mercedes-Benz E350",
    "Mercedes-Benz E450",
    "Mercedes-Benz E53 AMG",
    "Mercedes-Benz E63 AMG",
    "Mercedes-Benz S-klasse",
    "Mercedes-Benz S-Class",
    "Mercedes-Benz S500",
    "Mercedes-Benz Maybach S-klasse"
)

Write-Host ""
Write-Host "Setting up Mercedes-Benz image directory (400x400 pixels)"
Write-Host "========================================================="
Write-Host ""

$created = 0

foreach ($model in $MercedesModels) {
    $fileName = ($model.ToLower() -replace '[^a-z0-9_]', '_' -replace '_+', '_').TrimEnd('_')
    $filePath = Join-Path $OutputDir "$fileName.png"
    
    Write-Host "Creating placeholder: $model" -NoNewline
    
    try {
        # Create a simple bitmap
        $bitmap = New-Object System.Drawing.Bitmap(400, 400)
        $graphics = [System.Drawing.Graphics]::FromImage($bitmap)
        
        # Fill with light gray
        $graphics.Clear([System.Drawing.Color]::LightGray)
        
        # Add a simple border
        $pen = New-Object System.Drawing.Pen([System.Drawing.Color]::DarkGray, 1)
        $graphics.DrawRectangle($pen, 0, 0, 399, 399)
        
        # Save as PNG
        $bitmap.Save($filePath, [System.Drawing.Imaging.ImageFormat]::Png)
        $graphics.Dispose()
        $bitmap.Dispose()
        
        Write-Host " [READY]" -ForegroundColor Green
        $created++
    }
    catch {
        Write-Host " [FAILED]" -ForegroundColor Red
    }
}

Write-Host ""
Write-Host "Created: $created image placeholders (400x400px)"
Write-Host "Location: $OutputDir"
Write-Host ""
Write-Host "DOWNLOAD REAL IMAGES:"
Write-Host "===================="
Write-Host "1. Visit free stock photo sites:"
Write-Host "   - Unsplash: https://unsplash.com/s/photos/mercedes"
Write-Host "   - Pexels: https://www.pexels.com/search/mercedes/"
Write-Host "   - Pixabay: https://pixabay.com/search/mercedes/"
Write-Host ""
Write-Host "2. Download high-quality images for each model"
Write-Host ""
Write-Host "3. Resize to 400x400 pixels using:"
Write-Host "   - Paint (Windows)"
Write-Host "   - GIMP (free)"
Write-Host "   - Paint.NET (free)"
Write-Host "   - Or use PowerShell resize script"
Write-Host ""
Write-Host "4. Save as PNG and replace placeholder images"
Write-Host ""
