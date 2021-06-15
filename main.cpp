#include <SFML/Graphics.hpp>
#include <ctime>
#include <vector>
//C:\\Users\\Gniloe_Aloe\\Desktop\\Tetris\\block.png

//���������� ��������� ��� �������� ����
const unsigned int CAGE_SIZE = 50;// ������ ������� ����� � ��������
const unsigned int FIELD_WIDTH = 10;// ������ ���� � �����
const unsigned int FIELD_HEIGHT = 20;// ������ ���� � ������

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
	//rand()%5 ��� �������� ���� ������
	void set_color(int color_index) {
		switch (color_index) {
		case 0:
			this->block_sprite.setColor(sf::Color::Red);
			break;
		case 1:
			this->block_sprite.setColor(sf::Color::Cyan);
			break;
		case 2:
			this->block_sprite.setColor(sf::Color::Blue);
			break;
		case 3:
			this->block_sprite.setColor(sf::Color::Yellow);
			break;
		case 4:
			this->block_sprite.setColor(sf::Color::Magenta);
			break;
		}
	}

};

class Player {
public:
	int x = 0;
	int y = 0;
	//������� ����������� �������� ������ 
	bool right_resolution(){
		return this->x < FIELD_WIDTH - 1;
	}
	bool left_resolution() {
		return this->x > 0;
	}

};

int main() {
	//����������� ������ � ������������� ��������
	sf::Texture BLOCK_TEXTURE;
	BLOCK_TEXTURE.loadFromFile("C:\\Users\\Gniloe_Aloe\\Desktop\\Tetris\\pic\\block2.png");
	sf::Sprite block_sprite(BLOCK_TEXTURE);

	
	const sf::Color background(130, 155, 207);

	srand(time(NULL));
	//�������� ���������� ������� �� ������ ��� ������� ����
	Block field[FIELD_WIDTH][FIELD_HEIGHT];
	for (int i = 0; i < FIELD_WIDTH; ++i) {
		for (int j = 0; j < FIELD_HEIGHT; ++j) {
			//����� �������� ��� ������� �����
			field[i][j].available = false;
			field[i][j].set_texture(BLOCK_TEXTURE);
			field[i][j].set_coordinate(i, j);
			field[i][j].set_position(CAGE_SIZE);
			field[i][j].set_color(rand()%5);
		}
	}

	//������ ������
	Player player;




	//������ ���� ����
	sf::RenderWindow window(sf::VideoMode(CAGE_SIZE * FIELD_WIDTH, CAGE_SIZE * FIELD_HEIGHT), "Tetris!");
	window.clear(background);

	//�������� ������� � ���������� �������� ��� ������� �� �������
	sf::Clock pressing_timer;
	sf::Time pressing_delay = sf::seconds(0.01);

	//������� ���� ��� �������� ����
	while (window.isOpen()) {

		
		

		//����������� �������
		sf::Event event;
		while (window.pollEvent(event)) {

			//���� ������� ����
			if (event.type == sf::Event::Closed) {
				window.close();
			}

			//���������, ������ �� ���� �������� ������� �������
			if (pressing_timer.getElapsedTime() > pressing_delay) {
				//������� ������
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
					if (player.right_resolution()) {
						player.x++;
					}
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
					if (player.left_resolution()) {
						player.x--;
					}
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
					player.y--;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
					player.y++;
				}
				
				pressing_timer.restart();
			}

		}
		//������ ��������� ����� ������
		field[player.x][player.y].available = true;


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