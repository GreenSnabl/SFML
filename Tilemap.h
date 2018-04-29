/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Tilemap.h
 * Author: snbl
 *
 * Created on April 29, 2018, 9:48 PM
 */

#ifndef TILEMAP_H
#define TILEMAP_H


#include <SFML/Graphics.hpp>
 
class Tilemap
{
public:
	Tilemap(const std::string& tileset, int tileSize, int* tiles, int width, int height);
	void draw(sf::RenderWindow &window); 
        sf::Texture* getTexture() {return &m_tileset_tex;}
private:
	sf::Texture m_tileset_tex;
	sf::Sprite m_tileset_spr;
 
	int* mp_map;
	int m_mapWidth;
	int m_mapHeight;
	int m_tileSize;
 
};

#endif /* TILEMAP_H */

