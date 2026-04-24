void TaxiGame::initializeTierButtons(sf::Font& font) {
    string Mode = getCurrentMode();
    if(Mode == "YandexGo"){
        tierButtons.emplace_back(925, 45, 70,  30, "All",      font);  
        tierButtons.emplace_back(915, 80, 80,  30, "Economy",  font);  
        tierButtons.emplace_back(915, 115, 80,  30, "Comfort",  font);  
        tierButtons.emplace_back(915, 150, 90,  30, "Comfort+", font);  
        tierButtons.emplace_back(915, 185, 80,  30, "Business", font);
        tierButtons.emplace_back(915, 220, 80,  30, "Premier",  font); 
        tierButtons.emplace_back(915, 255, 80,  30, "Elite",   font); 
        tierButtons.emplace_back(915, 290, 80,  30, "Minivan", font); 
    }
    if(Mode == "Uber"){
        tierButtons.emplace_back(925, 45, 70,  30, "All",      font);   
        tierButtons.emplace_back(915, 80, 80,  30, "UberX",  font);   
        tierButtons.emplace_back(915, 115, 80,  30, "UberXL",  font);  
        tierButtons.emplace_back(915, 150, 80,  30, "Electric",  font);  
        tierButtons.emplace_back(915, 185, 80,  30, "VanXL",  font);
        tierButtons.emplace_back(915, 220, 80,  30, "Black",  font);    
        tierButtons.emplace_back(915, 255, 80,  30, "Luxury",  font);          

    }
   
}