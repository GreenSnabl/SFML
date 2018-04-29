#include <SFML/Graphics.hpp>
#include <iostream>
#include <unistd.h>

class TileMap : public sf::Drawable, public sf::Transformable
{
public:

    bool load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height)
    {
        // load the tileset texture
        if (!m_tileset.loadFromFile(tileset))
            return false;

        // resize the vertex array to fit the level size
        m_vertices.setPrimitiveType(sf::Quads);
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
    }

    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
};


using std::cout;
using std::endl;


int main()
{
/*
    sf::VertexArray triangle(sf::TrianglesFan, 3);

    triangle[0].position = sf::Vector2f(200, 0);
    triangle[1].position = sf::Vector2f(390, 250);
    triangle[2].position = sf::Vector2f(20, 250);

    sf::Texture texture;

    if (!texture.loadFromFile("bike400x256.jpg"))
    {
        cout << "Error loading texture" << endl;
    }

    triangle[0].texCoords = sf::Vector2f(100, 0);
    triangle[1].texCoords = sf::Vector2f(0, 250);
    triangle[2].texCoords = sf::Vector2f(250, 250);
    
    
    
    sf::VertexArray quad(sf::Quads, 4);
    quad[0].position = sf::Vector2f(0,0);
    quad[1].position = sf::Vector2f(400,0);
    quad[2].position = sf::Vector2f(400,256);
    quad[3].position = sf::Vector2f(50,256);
    
    quad[0].texCoords = sf::Vector2f(0,0);
    quad[1].texCoords = sf::Vector2f(400,0);
    quad[2].texCoords = sf::Vector2f(400,256);
    quad[3].texCoords = sf::Vector2f(0,256);
    
    
    
    sf::RenderWindow window(sf::VideoMode(400, 256), "SFML WORKS!");

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();

                break;
            }
        }
        window.clear();

        window.draw(quad, &texture); 

        window.display();
    }
    
    */

    // create the window
    sf::RenderWindow window(sf::VideoMode(100, 100), "Tilemap");

    // define the level with an array of tile indices
    const int level[] =
    {
        2,3,3,3,2,3,3,2,3,3,
        3,1,0,1,0,1,1,6,1,3,
        3,1,0,1,0,1,1,3,3,3,
        3,1,0,1,0,1,1,0,1,3,
        2,1,0,1,0,1,1,3,1,3,
        3,1,0,1,0,1,1,3,1,3,
        2,1,0,1,0,4,1,3,1,3,
        3,3,3,1,3,1,2,3,1,3,
        3,1,0,1,0,1,1,1,1,3,
        2,3,3,3,3,3,3,2,3,3
             
    };

    // create the tilemap from the level definition
    TileMap map;
    if (!map.load("tileset.png", sf::Vector2u(10, 10), level, 10, 10))
        return -1;

    sf::Texture texture;
    texture.loadFromFile("player.png");
    
    sf::RectangleShape rect;
    rect.setPosition(sf::Vector2f(60, 60));
    rect.setSize(sf::Vector2f(10,10));
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
            rect.move(-10, 0);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            rect.move(0, 10);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            rect.move(10, 0);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            rect.move(0, -10);
        }
        
        usleep(1000000);
        // draw the map
        window.clear();
        window.draw(map);
        window.draw(rect);
        window.draw(quad, &texture);
        window.display();
        usleep(1000000);
        
        
    }

    return 0;
}