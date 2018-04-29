/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Animation.h
 * Author: snbl
 *
 * Created on April 29, 2018, 10:09 PM
 */

#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>

class Animation {
public:
    Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);
    ~Animation();
    
    sf::IntRect uvRect;
    
    void update(int row, int count, float deltaTime);
    void update(int row, float deltaTime);
    
private:
    sf::Vector2u imageCount;
    sf::Vector2u currentImage;
    
    float totalTime;
    float switchTime;
};

#endif /* ANIMATION_H */

