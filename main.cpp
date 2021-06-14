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
	//����������� ������ � ������������� ��������
	sf::Texture BLOCK_TEXTURE;
	BLOCK_TEXTURE.loadFromFile("pic/block.png");
	sf::Sprite block_sprite(BLOCK_TEXTURE);

	const unsigned int CAGE_SIZE = 45;
	const unsigned int FIELD_WIDTH = 10;
	const unsigned int FIELD_HEIGHT = 20;
	const sf::Color background(130, 155, 207);

	srand(time(NULL));
	//�������� ���������� ������� �� ������ ��� ������� ����
	Block field[FIELD_WIDTH][FIELD_HEIGHT];
	for (int i = 0; i < FIELD_WIDTH; ++i) {
		for (int j = 0; j < FIELD_HEIGHT; ++j) {
			//����� �������� ��� ������� �����
			field[i][j].available = true;
			field[i][j].set_texture(BLOCK_TEXTURE);
			field[i][j].set_coordinate(i, j);
			field[i][j].set_position(CAGE_SIZE);


		}

	}

	//�������� ����


	//������ ���� ����
	sf::RenderWindow window(sf::VideoMode(CAGE_SIZE * FIELD_WIDTH, CAGE_SIZE * FIELD_HEIGHT), "Tetris!");
	window.clear(background);
	//������� ���� ��� �������� ����
	while (window.isOpen()) {

		//����������� �������
		sf::Event event;
		while (window.pollEvent(event)) {

			//���� ������� ����
			if (event.type == sf::Event::Closed) {
				window.close();
			}

		}


		//������������ ��� �������� ����� �� ����
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