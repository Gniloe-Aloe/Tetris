#include <SFML/Graphics.hpp>
#include <ctime>
#include <vector>
//C:\\Users\\Gniloe_Aloe\\Desktop\\Tetris\\block.png

class Block {
public:
	bool available = false;
	sf::Sprite block_sprite;
	int x;
	int y;
	sf::Color color;

	


	Block() {};
	void set_texture(const sf::Texture& texture) {
		block_sprite.setTexture(texture);
	}
	void set_coordinate(const int x, const int y) {
		this->x = x;
		this->y = y;
	}
	void set_position(const int& SIZE) {
		block_sprite.move(x * SIZE, y * SIZE);
	}
	void set_color(int color_number) {
		switch (color_number)
		{
		case 0:
			color = sf::Color::Cyan;
		case 1:
			color = sf::Color::Magenta;
		case 2:
			color = sf::Color::Blue;
		case 3:
			color = sf::Color::Green;
		case 4:
			color = sf::Color::Red;
		case 5:
			color = sf::Color::White;
		case 6:
			color = sf::Color::Yellow;
		}
		block_sprite.setColor(color);
	}

	
};

class Player {
public:
	int x;
	int y;
	Player() {
		x = 10;
		y = 10;
	}

};





int main() {
	//подключение файлов и инициализация констант
	sf::Texture BLOCK_TEXTURE;
	BLOCK_TEXTURE.loadFromFile("C:\\Users\\Gniloe_Aloe\\Desktop\\Tetris\\block.png");
	sf::Sprite block_sprite(BLOCK_TEXTURE);

	//конец игры
	sf::Texture endgane_texture;
	endgane_texture.loadFromFile("C:\\Users\\Gniloe_Aloe\\Desktop\\Tetris\\end.png");
	sf::Sprite endgame_sprite(endgane_texture);

	//начало игры
	sf::Texture startgame_texture;
	startgame_texture.loadFromFile("C:\\Users\\Gniloe_Aloe\\Desktop\\Tetris\\start.png");
	sf::Sprite startgame_sprite(startgame_texture);
	bool start = true;

	const unsigned int CAGE_SIZE = 45;
	const unsigned int FIELD_WIDTH = 11;
	const unsigned int FIELD_HEIGHT = 11;
	const sf::Color background(130, 155, 207);


	srand(time(NULL));


	//создание двумерного массива из блоков под игровое поле
	Block field[FIELD_WIDTH][FIELD_HEIGHT];
	for (int i = 0; i < FIELD_WIDTH; ++i) {
		for (int j = 0; j < FIELD_HEIGHT; ++j) {
			//задаём свойства для каждого блока
			field[i][j].available = false;
			field[i][j].set_texture(BLOCK_TEXTURE);
			field[i][j].set_coordinate(i, j);
			field[i][j].set_position(CAGE_SIZE);
		}

	}
	//создаём окно игры
	sf::RenderWindow window(sf::VideoMode(CAGE_SIZE * FIELD_WIDTH, CAGE_SIZE * FIELD_HEIGHT), "NOT Tetris!");
	window.clear(background);
	Player player;
	bool pressed = true;
	//главный цикл при открытом окне
	while (window.isOpen()) {
		

		//отлавливаем события
		sf::Event event;
		while (window.pollEvent(event)) {

			//если закрыли окно
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (pressed) {
				if (event.type == sf::Event::KeyPressed) {
					pressed = false;
					start = false;
				}

				if (event.key.code == sf::Keyboard::Right) {
					
					if (player.x < FIELD_WIDTH-1) {
						player.x++;
					}
				}
				if (event.key.code == sf::Keyboard::Left) {
					
					if (player.x != 0) {
						player.x--;
					}
				}
				if (event.key.code == sf::Keyboard::Up) {
					
					if (player.y != 0) {
						player.y--;
					}
				}
				if (event.key.code == sf::Keyboard::Down) {
					
					if (player.y < FIELD_HEIGHT - 1) {
						player.y++;
					}
				}
			}
			else {
				pressed = true;
			}

		}
		//проверка начала
		if (start) {
			window.draw(startgame_sprite);
		}
		else {
			window.clear(background);
		}

		

		//соединяем игрока с полем
		field[player.x][player.y].available = true;
		

		//отрисовываем все активные блоки на поле
		for (int i = 0; i < FIELD_WIDTH; ++i) {
			for (int j = 0; j < FIELD_HEIGHT; ++j) {
				if (field[i][j].available) {
					window.draw(field[i][j].block_sprite);
				}
			}
		}
		//проверяем конец игры
		bool end = true;
		for (int i = 0; i < FIELD_WIDTH; ++i) {
			for (int j = 0; j < FIELD_HEIGHT; ++j) {
				if (!field[i][j].available) {
					end = false;
				}
			}
		}
		//если конец
		if (end) {
			window.draw(endgame_sprite);
		}


		window.display();
	}
	return 0;
}