#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <cstdlib>
#include <iostream>
using namespace sf;
int main()
{
	//sf::RenderWindow window(sf::VideoMode(640, 480), "SFML works!");
	srand(time(NULL));
	sf::RenderWindow app(sf::VideoMode(640, 480), "Illusive,evasive,persistent");
	app.setFramerateLimit(60);
	
	//Adding sound
	SoundBuffer buffer;
	if (!buffer.loadFromFile("C:\\Trash\\punch.wav"))
		return -1;
	Sound sound;
	sound.setBuffer(buffer);
	//sound.play();
	//session
	// Game text
	Font font;

	//Load and check the availability of the font file
	if (!font.loadFromFile("C:\\Trash\\OpenSans-Bold.ttf"))
	{
		std::cout << "can't load font" << std::endl;
	}

	

	//font.loadFromFile("arial.ttf");
	Text gameOvertext;
	gameOvertext.setFont(font);
	gameOvertext.setCharacterSize(20);
	gameOvertext.setFillColor(Color::Red);
	gameOvertext.setPosition(20.f, 20.f);
	gameOvertext.setString("GAME OVER");


	// enemy!
	sf::Texture sessTex;
	sf::Sprite session;
	sessTex.loadFromFile("C:\\Trash\\zalikova.jpg");
	session.setTexture(sessTex);
	session.setScale(sf::Vector2f(0.1f,0.1f));
	int sessionSpawnTimer = 15;
	std::vector<sf::Sprite> sessions;
	sessions.push_back(Sprite(session));

	// player

	Texture playerTex;
	Sprite player;
	playerTex.loadFromFile("C:\\Trash\\meme2.png");
	player.setTexture(playerTex);
	player.setScale(Vector2f(0.17f, 0.17f));

	// hp + hp bar status

	int hp = 10;
	RectangleShape hpBar;
	hpBar.setFillColor(Color::Red);
	hpBar.setSize(Vector2f((float)hp*20.f,20.f));
	hpBar.setPosition(200.f,10.f);
	
	
	/////////
	while (app.isOpen() )
	{
		sf::Event event;
		
		
		while (app.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				app.close();
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
				app.close();
		}
	
		if (hp > 0)
		{
			player.setPosition(player.getPosition().x, Mouse::getPosition(app).y);
			//out of bounds
			//top
			if (player.getPosition().y > app.getSize().y - player.getGlobalBounds().height)
			{
				player.setPosition(player.getPosition().x, app.getSize().y - player.getGlobalBounds().height);
			}
			//bottom
			if (player.getPosition().y < 0)
			{
				player.setPosition(player.getPosition().x, 0);
			}
			// SPAM SESSIONS (ENEMY) 
			for (size_t i = 0; i < sessions.size(); i++)
			{
				sessions[i].move(-6.f, 0.f);
				if (sessions[i].getPosition().x < 0 - session.getGlobalBounds().width)
					sessions.erase(sessions.begin() + i);
			}
			if (sessionSpawnTimer < 40)
			{
				sessionSpawnTimer++;
			}
			if (sessionSpawnTimer >= 40)
			{
				session.setPosition(app.getSize().x, rand() % int(app.getSize().y - session.getGlobalBounds().height));
				sessions.push_back(Sprite(session));
				sessionSpawnTimer = 0;
			}

			// collision
			for (size_t i = 0; i < sessions.size(); i++)
			{
				if (player.getGlobalBounds().intersects(sessions[i].getGlobalBounds()))
				{

					hp--;
					
					sessions.erase(sessions.begin() + i);
					sound.play();
					

				}

			}
			hpBar.setSize(Vector2f((float)hp * 20.f, 20.f));
			
		}
		app.clear();
		app.draw(player);
		

		for (int i = 0; i < sessions.size(); i++)
		{
			app.draw(sessions[i]);
		}
		
		app.draw(hpBar);
		if (hp <= 0)
		app.draw(gameOvertext);
		app.display();
	}
	return 0;
}