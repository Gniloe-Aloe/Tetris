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

int main() {
	//подключение файлов и инициализация констант
	sf::Texture BLOCK_TEXTURE;
	BLOCK_TEXTURE.loadFromFile("pic/block.png");
	sf::Sprite block_sprite(BLOCK_TEXTURE);

	const unsigned int CAGE_SIZE = 45;
	const unsigned int FIELD_WIDTH = 10;
	const unsigned int FIELD_HEIGHT = 20;
	const sf::Color background(130, 155, 207);

	srand(time(NULL));
	//создание двумерного массива из блоков под игровое поле
	Block field[FIELD_WIDTH][FIELD_HEIGHT];
	for (int i = 0; i < FIELD_WIDTH; ++i) {
		for (int j = 0; j < FIELD_HEIGHT; ++j) {
			//задаём свойства для каждого блока
			field[i][j].available = true;
			field[i][j].set_texture(BLOCK_TEXTURE);
			field[i][j].set_coordinate(i, j);
			field[i][j].set_position(CAGE_SIZE);


		}

	}

	//тестирую цвет


	//создаём окно игры
	sf::RenderWindow window(sf::VideoMode(CAGE_SIZE * FIELD_WIDTH, CAGE_SIZE * FIELD_HEIGHT), "Tetris!");
	window.clear(background);
	//главный цикл при открытом окне
	while (window.isOpen()) {

		//отлавливаем события
		sf::Event event;
		while (window.pollEvent(event)) {

			//если закрыли окно
			if (event.type == sf::Event::Closed) {
				window.close();
			}

		}


		//отрисовываем все активные блоки на поле
		for (int i = 0; i < FIELD_WIDTH; ++i) {
			for (int j = 0; j < FIELD_HEIGHT; ++j) {
				if (field[i][j].available) {
					window.draw(field[i][j].block_sprite);
				}
			}
		}

		window.display();
	}
	return 0;
}