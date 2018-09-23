#include <SFML/Graphics.hpp>
#include <time.h>
#include <stdlib.h>
#include <string>
#include <sstream>

const int WIDTH = 900, HEIGHT = 500;

sf::Vector2f RandomDir() {
    srand(time(NULL));
    sf::Vector2f dxdy(5.f, 5.f);

    int dirX = rand()%10 + 1;
    int dirY = rand()%10 + 1;

    if(dirX > 4)
        dxdy.x *= -1.f;
    if(dirY > 4)
        dxdy.y *= -1.f;

    return dxdy;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Pong!");
    window.setFramerateLimit(60);

    //// Paddle declaration ////
    sf::Vector2f paddleDim(20, 100);
    sf::RectangleShape p1(paddleDim);
    sf::RectangleShape p2(paddleDim);
    p1.setPosition(20, HEIGHT/2 - 50);
    p2.setPosition(860, HEIGHT/2 - 50);

    int pointsPlayerOne = 0;
    int pointsPlayerTwo = 0;

    //// Ball declaration ////
    sf::CircleShape ball(10);
    ball.setPosition(WIDTH/2-10, HEIGHT/2-10);
    float dx, dy;

    dx = RandomDir().x;
    dy = RandomDir().y;

    //// GUI ////
    sf::Font font;
    font.loadFromFile("arial.ttf");
    sf::Text points("0", font);

    //// Game loop ////
    while (window.isOpen())
    {
        sf::Event e;
        while (window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
                window.close();
        }
        //// Movement controller ////
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && (p1.getPosition().y > 0))             p1.move(0.f, -8.f);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && (p1.getPosition().y+100 < HEIGHT))    p1.move(0.f, 8.f);

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && (p2.getPosition().y > 0))            p2.move(0.f, -8.f);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && (p2.getPosition().y+100 < HEIGHT)) p2.move(0.f, 8.f);

        //// Ball controller ////
        ball.move(dx, dy);

        if(ball.getPosition().y < 0 || ball.getPosition().y+20 > HEIGHT)
            dy *= -1;
        if(dx < 0 && (ball.getPosition().x < 40 && ball.getPosition().y > p1.getPosition().y && ball.getPosition().y+20 < p1.getPosition().y+100))
            dx *= -1;
        if(dx > 0 && (ball.getPosition().x+20 > 860 && ball.getPosition().y > p2.getPosition().y && ball.getPosition().y+20 < p2.getPosition().y+100))
            dx *= -1;

        if(ball.getPosition().x < 0 || ball.getPosition().x+20 > WIDTH) {
            if(ball.getPosition().x < 0)
                pointsPlayerTwo++;
            else
                pointsPlayerOne++;

            ball.setPosition(WIDTH/2-10, HEIGHT/2-10);
            dx = RandomDir().x;
            dy = RandomDir().y;
        }

        //// Points ////
        std::ostringstream ss;
        ss << pointsPlayerOne << " - " << pointsPlayerTwo;
        points.setString(ss.str());


        //// Render ////
        window.clear();
        window.draw(points);
        window.draw(p1);
        window.draw(p2);
        window.draw(ball);
        window.display();
    }

    return 0;
}
