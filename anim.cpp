/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <SFML/Graphics.hpp>

using namespace sf;

void animation_Window() {
	RenderWindow window(VideoMode(640, 480), "Animate this!");
	Sprite pad;
	Texture padtex;
	Time tempClock;
	Clock clock;
	int frame = 0, frames = 20, frameWidth = 53;
 
	padtex.loadFromFile("sheet.png");
	pad.setTexture(padtex);
	pad.setTextureRect(IntRect(0, 0, 53, 192));
 
	while (window.isOpen())
	{
		Time elapsed = clock.restart();
		tempClock += elapsed;
 
		if (tempClock.asSeconds() >= 0.05)
		{
			if (frame < frames - 1)
			{
				frame++;
			}
			else
			{
				frame = 0;
			}
 
			tempClock = tempClock.Zero;
			pad.setTextureRect(IntRect(frameWidth * frame, 0, frameWidth, 196));
		}
 
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
 
		window.clear();
		window.draw(pad);
		window.display();
	}
}