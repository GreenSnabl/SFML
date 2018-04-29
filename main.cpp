#include <SFML/Graphics.hpp>
#include <iostream>
#include <unistd.h>

class TileMap : public sf::Drawable, public sf::Transformable
{
public:

    TileMap();
    TileMap(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height) : m_tileSize{tileSize}, m_width{width}, m_height{height}
    {
        load(tileset, tileSize, tiles, width, height);
    }
    
    sf::VertexArray& getVertexMap() {
        return m_vertices;
    }
    
    bool addDynamicTile(unsigned int pos_x,unsigned  int pos_y,unsigned  int tex_x,unsigned  int tex_y) {
        m_dynamicVertices.resize(m_dynamicVertices.getVertexCount() + 4);
        m_dynamicVertices[m_dynamicVertices.getVertexCount() - 4].position = sf::Vector2f(pos_x * m_tileSize.x, pos_y * m_tileSize.y);
        m_dynamicVertices[m_dynamicVertices.getVertexCount() - 3].position = sf::Vector2f(pos_x * m_tileSize.x + m_tileSize.x, pos_y * m_tileSize.y);
        m_dynamicVertices[m_dynamicVertices.getVertexCount() - 2].position = sf::Vector2f(pos_x * m_tileSize.x + m_tileSize.x, pos_y * m_tileSize.y + m_tileSize.y);
        m_dynamicVertices[m_dynamicVertices.getVertexCount() - 1].position = sf::Vector2f(pos_x * m_tileSize.x, pos_y * m_tileSize.y + m_tileSize.y);
        
        m_dynamicVertices[m_dynamicVertices.getVertexCount() - 4].texCoords = sf::Vector2f(tex_x * m_tileSize.x, tex_y * m_tileSize.y);
        m_dynamicVertices[m_dynamicVertices.getVertexCount() - 3].texCoords = sf::Vector2f(tex_x * m_tileSize.x + m_tileSize.x, tex_y * m_tileSize.y);
        m_dynamicVertices[m_dynamicVertices.getVertexCount() - 2].texCoords = sf::Vector2f(tex_x * m_tileSize.x + m_tileSize.x, tex_y * m_tileSize.y + m_tileSize.y);
        m_dynamicVertices[m_dynamicVertices.getVertexCount() - 1].texCoords = sf::Vector2f(tex_x * m_tileSize.x, tex_y * m_tileSize.y + m_tileSize.y);
        
    }
    
    
    
    bool load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height)
    {
        // load the tileset texture
        if (!m_tileset.loadFromFile(tileset))
            return false;

        // resize the vertex array to fit the level size
        m_vertices.setPrimitiveType(sf::Quads);
        m_dynamicVertices.setPrimitiveType(sf::Quads);
        m_vertices.resize(width * height * 4);

        // populate the vertex array, with one quad per tile
        for (unsigned int i = 0; i < width; ++i)
            for (unsigned int j = 0; j < height; ++j)
            {
                // get the current tile number
                int tileNumber = tiles[i + j * width];

                // find its position in the tileset texture
                int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
                int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

                // get a pointer to the current tile's quad
                sf::Vertex* quad = &m_vertices[(i + j * width) * 4];

                // define its 4 corners
                quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
                quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
                quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
                quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

                // define its 4 texture coordinates
                quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
                quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
                quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
                quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
            }

        return true;
    }

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // apply the transform
        states.transform *= getTransform();

        // apply the tileset texture
        states.texture = &m_tileset;

        // draw the vertex array
        target.draw(m_vertices, states);
        target.draw(m_dynamicVertices, states);
    }

    sf::VertexArray m_vertices;
    sf::VertexArray m_dynamicVertices;
    
    
    sf::Texture m_tileset;
    
    sf::Vector2f m_tileSize;
    const unsigned int m_height;
    const unsigned int m_width;
    
};

using namespace sf;
using std::cout;
using std::endl;

/*  Der alte Code mit pimaldaumen gecodeter Tilemap im Stil des DungeonCrawlers
int main()
{    
    
    // create the window
    sf::RenderWindow window(sf::VideoMode(320, 320), "Tilemap");

    // define the level with an array of tile indices
    const int level[] =
    {
        135,136,137,138,139,137,139,140,141,138,
        137,202,203,204,203,205,206,205,206,136,
        138,202,203,204,202,205,206,202,206,138,
        136,203,202,202,202,205,202,202,202,138,
        138,202,202,204,202,205,202,204,202,139,
        137,202,202,204,203,202,202,202,202,135,
        142,202,203,202,202,202,202,202,202,139,
        141,202,202,202,205,202,202,202,202,137,
        139,202,203,204,202,202,202,202,206,141,
        135,136,137,138,139,137,139,140,141,138,
             
    };

    // create the tilemap from the level definition
    TileMap map("ProjectUtumno_full.png", sf::Vector2u(32, 32), level, 10, 10);
    
    map.addDynamicTile(7, 6, 56, 12);
    
    sf::Texture texture;
    texture.loadFromFile("player.png");
    
    sf::RectangleShape rect;
    rect.setPosition(sf::Vector2f(64, 64));
    rect.setSize(sf::Vector2f(32,32));
    rect.setTexture(&texture);
    
    sf::VertexArray quad(sf::Quads, 4);
    quad[0].position = sf::Vector2f(40,40);
    quad[1].position = sf::Vector2f(50,40);
    quad[2].position = sf::Vector2f(50,50);
    quad[3].position = sf::Vector2f(40,50);
    
    quad[0].texCoords = sf::Vector2f(0,0);
    quad[1].texCoords = sf::Vector2f(10,0);
    quad[2].texCoords = sf::Vector2f(10,10);
    quad[3].texCoords = sf::Vector2f(0,10);

    
    // run the main loop
    while (window.isOpen())
    {
        // handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            rect.move(-32, 0);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            rect.move(0, 32);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            rect.move(32, 0);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            rect.move(0, -32);
        }
        
        usleep(500000);
        // draw the map
        window.clear();
        window.draw(map);
        window.draw(rect);
        window.draw(quad, &texture);
        window.display();
        usleep(200000);
        
        
    }
 
    return 0;
} 
 */
    

// Die Main der Tilemap von Codebreaker
    
#include "Tilemap.h"
#include "Animation.h"


int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Tilemap");
 
	int map[] = {
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	};
 
	Tilemap themap("Tileset.png", 16, map, 10, 10);
        
        Sprite sprite;
        sprite.setTexture(*themap.getTexture());    // Setze die Textur an der sich der sprite bedient
        sprite.setTextureRect(IntRect(0,0,16,16));  // Setze den Texturausschnitt an der sich der Sprite bedient
        sprite.setPosition(Vector2f(200.f,200.f));  // Setze absolute Position
        sprite.move(Vector2f(50.f,50.f));           // Relative Bewegung / Offsetbewegung
        
        Texture playerTexture;
        playerTexture.loadFromFile("explosion_3_40_128.png");
        
        sf::RectangleShape player(sf::Vector2f(128, 128));
        sf::RectangleShape player2(sf::Vector2f(128,128));
        
        
        player.setPosition(150,150);
        player.setTexture(&playerTexture);
        
        player2.setPosition(300, 300);
        player2.setTexture(&playerTexture);
        
        Animation animation(&playerTexture, sf::Vector2u(8,8), 0.1f);
        Animation animation2(&playerTexture, sf::Vector2u(8,8), 0.1f);
       
        float deltaTime = 0.0f;

        sf::Clock clock;
        
        
	while (window.isOpen())
	{
                deltaTime = clock.restart().asSeconds();

                
                
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
                        if (event.type == sf::Event::KeyPressed)                        // Konstruiert man die Animation auf die Art, wie sie hier angewendet wird
                        {                                                               // blockiert man den Mainloop und die Bewegung verzögert sich
                            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))       // CyberPong realisiert eine fließende Bewegung + Animation der Paddle-Sprites (How?)
                            {
                                player.move(-10.f, 0.f);                            
                            }
                            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
                            {
                                player.move(10.f, 0.f);                            
                            } 
                            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
                            {
                                player.move(0.f, -10.f);                            
                            }
                            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
                            {
                                player.move(0.f, 10.f);                            
                            }
                        }
		}
 
                animation.update(3, 38, deltaTime);
                animation2.update(0,deltaTime);
                
                player.setTextureRect(animation.uvRect);
                player2.setTextureRect(animation2.uvRect);
                
		window.clear();
 
		themap.draw(window);
                
                window.draw(player);
                window.draw(player2);
                window.draw(sprite);
 
		window.display();
	}
 
	return 0;
}

