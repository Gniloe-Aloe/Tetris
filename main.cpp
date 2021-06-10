#include <SFML/Graphics.hpp>
#include <ctime>
#include <chrono>
#include <thread>

//C:\\Users\\Gniloe_Aloe\\Desktop\\Tetris\\block.png

sf::Color random_color() {
	return sf::Color(rand() % 256, rand() % 256, rand() % 256);
}



int main()
{
	srand(time(NULL));

	sf::RenderWindow window(sf::VideoMode(450, 900), "Tetris!");

	sf::Texture block_texture;
	block_texture.loadFromFile("C:\\Users\\Gniloe_Aloe\\Desktop\\Tetris\\block.png");
	sf::Sprite block_sprite(block_texture);
	sf::Sprite block_sprite2(block_texture);
	sf::Sprite block_sprite3(block_texture);
	sf::Sprite block_sprite4(block_texture);
	block_sprite2.move(450, 0);
	block_sprite3.move(90, 0);
	block_sprite4.move(45, 45);

	sf::Color fon;
	fon = sf::Color::Cyan;

	int x = 0;
	int y = 0;


	// Главный цикл приложения: выполняется, пока открыто окно
	while (window.isOpen())
	{
		// Обрабатываем события в цикле
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Пользователь нажал на «крестик» и хочет закрыть окно?
			if (event.type == sf::Event::Closed)
				// тогда закрываем его
				window.close();

			//нажатие любой кнопки
			if (event.type == sf::Event::KeyPressed) {
				
			}

			if (event.key.code == sf::Keyboard::Right) {
				block_sprite.move(45, 0);
			}
			if (event.key.code == sf::Keyboard::Left) {
				block_sprite.move(-45, 0);
			}
			if (event.key.code == sf::Keyboard::Up) {
				block_sprite.move(0, -45);
			}
			if (event.key.code == sf::Keyboard::Down) {
				block_sprite.move(0, 45);
			}
			
		}
		// Установка цвета фона
		window.clear(sf::Color::Blue);

		

		window.draw(block_sprite);
		window.draw(block_sprite4);




		// Отрисовка окна
		window.display();
		
	}

	return 0;
}