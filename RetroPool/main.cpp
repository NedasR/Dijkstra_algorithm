#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <queue>


enum class Direction
{
    NONE,
    Right,
    Down,
    Left,
    Up
};

int main()
{
    
    const int map[][22] = {  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                             {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0},
                             {0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0},
                             {0,0,0,0,0,0,1,0,0,1,0,0,0,1,0,0,0,1,1,1,1,1},
                             {0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,0,1,0,0,0},
                             {0,1,0,1,0,0,1,0,0,1,1,1,0,0,0,1,0,0,1,0,0,0},
                             {0,1,0,1,0,1,1,0,1,1,1,0,0,1,0,1,0,0,1,0,0,0},
                             {0,1,0,1,0,1,1,0,0,0,1,0,1,0,0,1,0,0,0,0,0,0},
                             {0,0,0,1,0,1,1,0,1,0,0,0,1,0,1,1,0,0,1,0,0,0},
                             {0,1,0,0,0,1,1,0,1,1,1,1,1,0,1,1,0,0,1,1,1,0}};

    Direction directionMap[10][22];
    for (int y = 0; y < 10; y++)
    {
        for (int x = 0; x < 22; x++)
        {
            directionMap[y][x] = Direction::NONE;
        }
    }

    int distMap[10][22];
    for (int y = 0; y < 10; y++)
    {
        for (int x = 0; x < 22; x++)
        {
            distMap[y][x] =99999999;
        }
    }
    distMap[0][0] = 0;

    bool vistedMap[10][22];
    for (int y = 0; y < 10; y++)
    {
        for (int x = 0; x < 22; x++)
        {
            vistedMap[y][x] = false;
        }
    }
    vistedMap[0][0] = true;

    std::queue<sf::Vector2i> myQueue;
    myQueue.push(sf::Vector2i(0, 0));
    sf::Vector2i current;
    sf::Vector2i left;
    sf::Vector2i down;
    sf::Vector2i right;
    sf::Vector2i up;

    while (!myQueue.empty())
    {
        current = myQueue.front();
        int num;
        num = distMap[current.y][current.x];
        num++;
        left = current;
        left.x++;
        down = current;
        down.y++;
        right = current;
        right.x--;
        up = current;
        up.y--;
        if (left.x >= 0 && left.x < 22 && left.y >= 0 && left.y < 10)
        {
            if (!vistedMap[left.y][left.x])
            {
                if (map[left.y][left.x] == 0)
                {
                    directionMap[left.y][left.x] = Direction::Left;
                    distMap[left.y][left.x] = num;
                    myQueue.push(left);
                }
            }
        }

        if (down.x >= 0 && down.x < 22 && down.y >= 0 && down.y < 10)
        {
            if (!vistedMap[down.y][down.x])
            {
                if (map[down.y][down.x] == 0)
                {
                    directionMap[down.y][down.x] = Direction::Up;
                    distMap[down.y][down.x] = num;
                    myQueue.push(down);

                }
            }
        }

        if (right.x >= 0 && right.x < 22 && right.y >= 0 && right.y < 10)
        {
            if (!vistedMap[right.y][right.x])
            {
                if (map[right.y][right.x] == 0)
                {
                    directionMap[right.y][right.x] = Direction::Right;
                    distMap[right.y][right.x] = num;
                    myQueue.push(right);

                }
            }
        }

        if (up.x >= 0 && up.x < 22 && up.y >= 0 && up.y < 10)
        {
            if (!vistedMap[up.y][up.x])
            {
                if (map[up.y][up.x] == 0)
                {
                    directionMap[up.y][up.x] = Direction::Down;
                    distMap[up.y][up.x] = num;
                    myQueue.push(up);

                }
            }
        }

        if (current.x >= 0 && current.x < 22 && current.y >= 0 && current.y < 10)
        {
            vistedMap[current.y][current.x] = true;
        }
        myQueue.pop();
    }
    for (int y = 0; y < 10; y++)
    {
        for (int x = 0; x < 22; x++)
        {
            std::cout << static_cast<int>(directionMap[y][x]) << " ";
        }
        std::cout << std::endl;
    }

    sf::Text distanceNumbers;
    sf::Font textFont;
    if (!(textFont.loadFromFile("assets/arial.ttf")))
    {
        std::cout << "Failed to load font";
    }
    distanceNumbers.setFont(textFont);
    distanceNumbers.setCharacterSize(16);
    sf::Vector2i player(13, 9);
    sf::RenderWindow window(sf::VideoMode(800, 800), "Coffee's game");
    sf::RectangleShape cells(sf::Vector2f(20, 20));
    sf::RectangleShape Dplayer(sf::Vector2f(20, 20));
    Dplayer.setFillColor(sf::Color::Yellow);
    //both of these variables make sure the maze is centered in the midel of the game screen
    int xOffset = window.getSize().x / 2 - cells.getSize().x * 11;
    int yOffset = window.getSize().x / 2 - cells.getSize().x * 5;
    sf::Clock clock;
    bool start = false;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == event.Closed) {
                window.close();
            }
            if (event.type == event.KeyPressed)
            {
                if (event.key.code  == sf::Keyboard::A)
                {
                    if (!(start))
                    {
                        start = true;
                    }
                    else {
                        start = false;
                    }
                }
            }
        }
        
        // instead of zero it's -1 because an array starts from index 0
        if (player.x != -1 && player.y != -1 && clock.getElapsedTime() >= sf::milliseconds(200) && start)
        {
            clock.restart();
            switch (static_cast<Direction>(directionMap[player.y][player.x]))
            {
            case Direction::Left :
                {
                    player.x--;
                    break;
                }
            case Direction::Right :
                {
                    player.x++;
                    break;
                }
            case Direction::Up :
                {
                    player.y --;
                    break;
                }
            case Direction::Down :
                {
                    player.y++;
                    break;
                }
            }
        }

        window.clear();
        for (int y = 0; y < 10; y++)
        {
            for (int x = 0; x < 22; x++)
            {
                distanceNumbers.setString(std::to_string(distMap[y][x]));
                distanceNumbers.setPosition(xOffset + (cells.getSize().x * x), yOffset + (cells.getSize().y * y));
                cells.setPosition(xOffset +(cells.getSize().x * x), yOffset +(cells.getSize().y * y));
                cells.setFillColor(sf::Color((distMap[y][x]+10)*3, 0, 0));
                window.draw(cells);

                if (distMap[y][x] < 9999)
                {
                    window.draw(distanceNumbers);
                }
            }
        }
        Dplayer.setPosition(xOffset + (Dplayer.getSize().x * player.x), yOffset + (Dplayer.getSize().x * player.y));
        window.draw(Dplayer);
        window.display();
    }
    return 0;
}

// the code below is an implementation of bucket fill algorithm it's very similar to BFS
/*
int main()
{
   const int Input[10][22] ={
                      {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                      {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0},
                      {0,0,0,0,1,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0},
                      {0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1},
                      {0,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,0,0,1,0,0,0},
                      {0,1,0,1,0,0,1,0,1,1,1,1,1,1,1,1,0,0,1,0,0,0},
                      {0,1,0,1,0,1,1,0,1,1,1,1,1,1,1,1,0,0,1,0,0,0},
                      {0,1,0,1,1,1,1,0,0,0,1,0,0,0,1,1,0,0,1,0,0,0},
                      {0,0,0,1,0,1,1,0,1,0,0,0,1,0,1,1,0,0,1,0,0,0},
                      {0,1,0,0,0,1,1,0,1,1,1,1,1,0,1,1,0,0,1,1,1,0}};
int Output[10][22] = {
                      {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
                      {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,2},
                      {2,2,2,2,1,2,2,2,2,2,1,1,1,1,1,1,2,2,2,2,2,2},
                      {2,2,1,2,2,2,1,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1},
                      {2,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,2,2,1,0,0,0},
                      {2,1,2,1,0,0,1,2,1,1,1,1,1,1,1,1,2,2,1,0,0,0},
                      {2,1,2,1,0,1,1,2,1,1,1,1,1,1,1,1,2,2,1,0,0,0},
                      {2,1,2,1,1,1,1,2,2,2,1,2,2,2,1,1,2,2,1,0,0,0},
                      {2,2,2,1,2,1,1,2,1,2,2,2,1,2,1,1,2,2,1,0,0,0},
                      {2,1,2,2,2,1,1,2,1,1,1,1,1,2,1,1,2,2,1,1,1,0}};

int Output[11][23] = {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                      {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0},
                      {0,0,0,0,1,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0},
                      {0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1},
                      {0,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,0,0,1,0,0,0},
                      {0,1,0,1,0,0,1,0,1,1,1,1,1,1,1,1,0,0,1,0,0,0},
                      {0,1,0,1,0,1,1,0,1,1,1,1,1,1,1,1,0,0,1,0,0,0},
                      {0,1,0,1,1,1,1,0,0,0,1,0,0,0,1,1,0,0,1,0,0,0},
                      {0,0,0,1,0,1,1,0,1,0,0,0,1,0,1,1,0,0,1,0,0,0},
                      {0,1,0,0,0,1,1,0,1,1,1,1,1,0,1,1,0,0,1,1,1,0} };
bool vistedMap[10][22];
for (int y = 0; y < 10; y++)
{
    for (int x = 0; x < 22; x++)
    {
        vistedMap[y][x] = false;
    }
}

std::queue<sf::Vector2i> myQueue;
myQueue.push(sf::Vector2i(0, 0));
sf::Vector2i current;
sf::Vector2i left;
sf::Vector2i down;
sf::Vector2i right;
sf::Vector2i up;
while (!myQueue.empty())
{
    current = myQueue.front();
    Output[current.y][current.x] = 2;
    left = current;
    left.x++;
    down = current;
    down.y++;
    right = current;
    right.x--;
    up = current;
    up.y--;
    
    if (left.x >= 0 && left.x < 22 && left.y >= 0 && left.y < 10)
    {
        if (!vistedMap[left.y][left.x])
        {
            if (Input[left.y][left.x] == 0)
            {
                myQueue.push(left);
                
            }
        }
    }

    if (down.x >= 0 && down.x < 22 && down.y >= 0 && down.y < 10)
    {
        if (!vistedMap[down.y][down.x])
        {
            if (Input[down.y][down.x] == 0)
            {
                myQueue.push(down);
                
            }
        }
    }

    if (right.x >= 0 && right.x < 22 && right.y >= 0 && right.y < 10)
    {
        if (!vistedMap[right.y][right.x])
        {
            if (Input[right.y][right.x] == 0)
            {
                myQueue.push(right);

            }
        }
    }

    if (up.x >= 0 && up.x < 22 && up.y >= 0 && up.y < 10)
    {
        if (!vistedMap[up.y][up.x])
        {
            if (Input[up.y][up.x] == 0)
            {
                myQueue.push(up);

            }
        }
    }

    if (current.x >= 0 && current.x < 22 && current.y >= 0 && current.y < 10)
    {
        vistedMap[current.y][current.x] = true;
    }
    myQueue.pop();
}

int count = 0;
int zeroCount = 0;
for (int y = 0; y < 10; y++)
{
    for (int x = 0; x < 22; x++)
    {
        if (Output[y][x] == 2)
        {
            count++;
        }
        if (Input[y][x] == 0)
        {
            zeroCount++;
        }
        std::cout << Output[y][x] << " ";
    }
    std::cout << std::endl;
}
std::cout << count << " " << zeroCount;



}
*/