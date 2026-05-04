#!/usr/bin/env python3
"""
Download and resize Mercedes-Benz car images for TaxiGame
Requires: requests, Pillow libraries
Install with: pip install requests Pillow
"""

import os
import requests
from PIL import Image
from io import BytesIO
import time

# Output directory
OUTPUT_DIR = r"h:\TaxiGame\source\Car Images"
os.makedirs(OUTPUT_DIR, exist_ok=True)

# Mercedes models to download
MERCEDES_MODELS = {
    "Mercedes-Benz C-klasse": "mercedes_c_klasse",
    "Mercedes-Benz C-Class": "mercedes_c_class",
    "Mercedes-Benz C300": "mercedes_c300",
    "Mercedes-Benz C43 AMG": "mercedes_c43_amg",
    "Mercedes-Benz C63 AMG": "mercedes_c63_amg",
    "Mercedes-Benz E-klasse": "mercedes_e_klasse",
    "Mercedes-Benz E-Class": "mercedes_e_class",
    "Mercedes-Benz E350": "mercedes_e350",
    "Mercedes-Benz E450": "mercedes_e450",
    "Mercedes-Benz E53 AMG": "mercedes_e53_amg",
    "Mercedes-Benz E63 AMG": "mercedes_e63_amg",
    "Mercedes-Benz S-klasse": "mercedes_s_klasse",
    "Mercedes-Benz S-Class": "mercedes_s_class",
    "Mercedes-Benz S500": "mercedes_s500",
    "Mercedes-Benz Maybach S-klasse": "mercedes_maybach_s_klasse",
}

# Unsplash API endpoint (free, no key needed for basic usage)
UNSPLASH_API_URL = "https://api.unsplash.com/search/photos"
UNSPLASH_PARAMS = {
    "query": "",
    "per_page": 1,
    "order_by": "popular",
    "orientation": "landscape"
}

# Target image size
TARGET_SIZE = (400, 400)

def download_and_resize_image(search_query, output_filename):
    """Download image from Unsplash and resize to 400x400"""
    try:
        params = UNSPLASH_PARAMS.copy()
        params["query"] = search_query
        
        print(f"Downloading: {search_query}...", end=" ")
        
        # Using direct image download without API key (works for basic usage)
        # Fallback to a direct search query approach
        response = requests.get(
            f"https://source.unsplash.com/featured/?{search_query}",
            timeout=10,
            allow_redirects=True
        )
        
        if response.status_code == 200:
            # Open image and resize
            img = Image.open(BytesIO(response.content))
            
            # Convert RGBA to RGB if necessary
            if img.mode == 'RGBA':
                rgb_img = Image.new('RGB', img.size, (255, 255, 255))
                rgb_img.paste(img, mask=img.split()[3])
                img = rgb_img
            elif img.mode != 'RGB':
                img = img.convert('RGB')
            
            # Resize to 400x400 with high quality
            img_resized = img.resize(TARGET_SIZE, Image.Resampling.LANCZOS)
            
            # Save with high quality
            output_path = os.path.join(OUTPUT_DIR, f"{output_filename}.png")
            img_resized.save(output_path, "PNG", quality=95, optimize=False)
            
            print(f"✓ Saved as {output_filename}.png")
            return True
        else:
            print(f"✗ Failed (HTTP {response.status_code})")
            return False
            
    except Exception as e:
        print(f"✗ Error: {str(e)}")
        return False

def main():
    print(f"Downloading Mercedes-Benz car images to: {OUTPUT_DIR}\n")
    print(f"Target size: {TARGET_SIZE[0]}x{TARGET_SIZE[1]} pixels\n")
    
    successful = 0
    failed = 0
    
    for model_name, filename in MERCEDES_MODELS.items():
        # Extract model type for better search
        search_query = model_name
        if download_and_resize_image(search_query, filename):
            successful += 1
        else:
            failed += 1
        
        # Rate limiting to avoid overwhelming the server
        time.sleep(1)
    
    print(f"\n{'='*50}")
    print(f"Download complete!")
    print(f"Successful: {successful}")
    print(f"Failed: {failed}")
    print(f"Output directory: {OUTPUT_DIR}")

if __name__ == "__main__":
    # Check if requests library is installed
    try:
        import requests
        from PIL import Image
    except ImportError:
        print("Error: Required libraries not found!")
        print("Please install them with:")
        print("pip install requests Pillow")
        exit(1)
    
    main()
