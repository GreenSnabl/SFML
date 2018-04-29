/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Animation.cpp
 * Author: snbl
 * 
 * Created on April 29, 2018, 10:09 PM
 */

#include "Animation.h"

Animation::Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime)

{
    this->imageCount = imageCount;      // Wir benutzen den this-Zeiger, weil der Parameter und das Klassenattribut den gleichen Namen haben (!)
    this->switchTime = switchTime;
    this->totalTime = 0.0f;
    currentImage.x = 0;
    currentImage.y = 0;
    uvRect.width = texture->getSize().x / static_cast<float>(imageCount.x);
    uvRect.height = texture->getSize().y / static_cast<float>(imageCount.y);

}


Animation::~Animation() {
}

void Animation::update(int row, int count, float deltaTime) 
{
    //currentImage.y = row;
    totalTime += deltaTime;
    
    if (totalTime >= switchTime) 
    {
        totalTime -= switchTime;
        currentImage.x++;
        if (currentImage.x >= imageCount.x)
        {
            currentImage.y++;
            currentImage.x = 0;        
        }
        if (currentImage.y *  imageCount.x + currentImage.x >= count)
        {
            currentImage.x = 0;
            currentImage.y = 0;
        }
    }
    
    uvRect.left = currentImage.x * uvRect.width;
    uvRect.top = currentImage.y * uvRect.height;
}

// Ursprüngliche update Funktion
void Animation::update(int row, float deltaTime) 
{
    // currentImage.y = row;
    totalTime += deltaTime;
    
    if (totalTime >= switchTime) 
    {
        totalTime -= switchTime;
        currentImage.x++;
        if (currentImage.x >= imageCount.x)
        {
        
            currentImage.x = 0;        
        }
    }
    
    uvRect.left = currentImage.x * uvRect.width;
    uvRect.top = row * uvRect.height;
}