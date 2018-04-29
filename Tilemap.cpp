/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Tilemap.cpp
 * Author: snbl
 * 
 * Created on April 29, 2018, 9:48 PM
 */

#include "Tilemap.h"

Tilemap::Tilemap(const std::string& tileset, int tileSize, int* tiles, int width, int height)
	: mp_map(tiles), m_mapWidth(width), m_mapHeight(height), m_tileSize(tileSize)
{
	m_tileset_tex.loadFromFile(tileset);
	m_tileset_spr.setTexture(m_tileset_tex);
}
 
void Tilemap::draw(sf::RenderWindow &window)
{
	for (unsigned int y = 0; y < m_mapHeight; ++y) {
		for (unsigned int x = 0; x < m_mapWidth; ++x)
		{
			int tilecount = x + y * 10;
 
			m_tileset_spr.setPosition(x * m_tileSize, y * m_tileSize);
 
			int tu = mp_map[tilecount] % (48 / 16);
			int tv = mp_map[tilecount] / (48 / 16);
 
			m_tileset_spr.setTextureRect(sf::IntRect(tu * 16, tv * 16, 16, 16));
 
			window.draw(m_tileset_spr);
 
		}
	}
}
