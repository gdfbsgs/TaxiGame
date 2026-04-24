// Обновление позиции прокрутки и ограничение сверху (не выше 0)
scrollY += scroll;
    if (scrollY < 0) {
        scrollY = 0;
        return;
    }

    // Подсчет видимых машин по текущему уровню для расчета высоты списка
    int visibleCount = 0;
    for (const auto& car : cars) {
        if (currentTier == "All" || car.getTier() == currentTier) {
            visibleCount++;
        }
    }

    // Calculate total content height
    long long totalHeight = 50 + visibleCount * 30LL;
    // Determine max scroll based on tier
    long long maxScroll = 0;
    if (currentTier == "All") {
        maxScroll = totalHeight - 1800;
    } 
    if (currentTier == "Economy" || currentTier == "Comfort" || currentTier == "Comfort+") {
        maxScroll = totalHeight - 1200;
    } // Business, Premier, Elite, Minivan have maxScroll = 0 (no scrolling needed)
    // Clamp scrollY to valid range
    if (maxScroll < 0){
        maxScroll = 0;
    }
    if (scrollY > maxScroll){
        scrollY = maxScroll;
    }