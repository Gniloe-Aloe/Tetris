#include <SFML/Graphics.hpp>
#include <ctime>
#include <vector>
//C:\\Users\\Gniloe_Aloe\\Desktop\\Tetris\\block.png

//���������� ��������� ��� �������� ����
const unsigned int CAGE_SIZE = 45;// ������ ������� ����� � ��������
const unsigned int FIELD_WIDTH = 10;// ������ ���� � �����
const unsigned int FIELD_HEIGHT = 20;// ������ ���� � ������
sf::RenderWindow window(sf::VideoMode(CAGE_SIZE* FIELD_WIDTH, CAGE_SIZE* FIELD_HEIGHT), "Tetris!"); // ���� ����


class Block {
public:
	//���������� �� ����
	bool available = false;
	//���������� �� ���� �� ���� (�� ������)
	bool set_on_field = false;
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
//�������� ����������� ���������� ������� �� ������ ��� ������� ����
Block field[FIELD_WIDTH][FIELD_HEIGHT];

class Player {
public:
	int x = FIELD_WIDTH/2;
	int y = 0;
	//������� ����������� �������� ������ ���� �� ����� �� ������� ����
	//� ������ ��� �������� �����
	bool right_resolution(){
		return (this->x < FIELD_WIDTH - 1)&&(!field[this->x+1][y].available);
	}
	//�������� ����������� �������� �����
	bool left_resolution() {
		return (this->x > 0)&&(!field[x-1][y].available);
	}
	//�������� ������� ���������� ����� ��� ������� ������
	bool down_resolution() {
		//���� �� ����� �� ������ ���� � ��� ���� ��� ������� �������� �����
		return (y < FIELD_HEIGHT - 1) && (!field[x][y + 1].available);
	}
	//��������� ����� ������ �� ����
	void set_on_field(){
		field[this->x][this->y].set_on_field = true;
		//field[this->x][this->y].available = true;
		this->x = FIELD_WIDTH/2;
		this->y = 0;
		if (!down_resolution())
		{
			game_over();
		}

	}

	// ����� ����
	void game_over()
	{
		
		window.close();
	}

	//�������
	void fall() {
		if (down_resolution()) {
			++y;
		}
		
	}
};

// ��������� ����� �� �������������
bool check_line(const int& y){
	for (int i = 0; i < FIELD_WIDTH; ++i){
		if (!field[i][y].available){
			return false;	
		}
	}
	return true;
}

// ������� �����
void delete_line(const int& y){
	for (int i = 0; i < FIELD_WIDTH; ++i){
		field[i][y].available = false;
		field[i][y].set_on_field = false;
	}
}

// ����� ����� ����
void fall_line(const int& y){
	// �������� �����������, �������� �� set_on_field
	for (int i = y - 1; i > 0; --i){
		for (int j = 0; j < FIELD_WIDTH; ++j){

			if (field[j][i].set_on_field){

				field[j][i].available = false;
				field[j][i].set_on_field = false;
				field[j][i + 1].available = true;
				field[j][i + 1].set_on_field = true;

			}
		}
	}
}

int main() {

	//����������� ������ � ������������� ��������
	sf::Texture BLOCK_TEXTURE;
	//�������� ������ 3 - 5
	BLOCK_TEXTURE.loadFromFile("C:\\Users\\Gniloe_Aloe\\Desktop\\Tetris\\pic\\block5_o.png");
	//BLOCK_TEXTURE.loadFromFile("D:\\IfoLabs\\GitTest\\Tetris1\\Tetris\\pic\\block2.png");

	sf::Sprite block_sprite(BLOCK_TEXTURE);

	//���� ����
	const sf::Color background(130, 155, 207);

	//�������� ������� ����
	sf::Texture BACKGROUND_TEXTURE;
	//�������� ����� 1-4
	BACKGROUND_TEXTURE.loadFromFile("C:\\Users\\Gniloe_Aloe\\Desktop\\Tetris\\pic\\background3.png");
	sf::Sprite background_sprite(BACKGROUND_TEXTURE);

	//�������� ������� �����
	sf::Texture CAGE_TEXTURE;
	CAGE_TEXTURE.loadFromFile("C:\\Users\\Gniloe_Aloe\\Desktop\\Tetris\\pic\\gaming_cage.png");
	sf::Sprite gaming_cage(CAGE_TEXTURE);
	
	srand(time(NULL));
	
	//����������� ������� ����
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
	
	window.clear(background);

	//���������� �������� �����
	int score = 0;

	//�������� ������� � ���������� �������� ��� ������� �� �������
	sf::Clock pressing_timer;
	sf::Time pressing_delay = sf::seconds(0.01);

	//������ �������
	sf::Clock falling_timer;
	const sf::Time difficulty_level = sf::seconds(1);
	sf::Time falling_delay = difficulty_level;

	//����� ������� ������
	bool left_was_pressed = false;
	bool right_was_pressed = false;
	bool up = false;
	bool down_was_pressed = false;

	//������� ���� ��� �������� ����
	while (window.isOpen()) {

		window.draw(background_sprite);

		field[player.x][player.y].available = false;

		//����������� �������
		sf::Event event;
		while (window.pollEvent(event)) {

			//���� ������� ����
			if (event.type == sf::Event::Closed) {
				window.close();
			}

			//��������
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == (sf::Keyboard::D)) {
					right_was_pressed = true;
				}
				if (event.key.code == (sf::Keyboard::A)) {
					left_was_pressed = true;
				}
				//���������� �������
				if (event.key.code == (sf::Keyboard::S)) {
					down_was_pressed = true;
				}
				
				//��������� ������
				if (event.key.code == (sf::Keyboard::W)) {
					
				}
			}
			//���������, ������ �� ���� �������� ������� �������
			if (pressing_timer.getElapsedTime() > pressing_delay) {
				//������� ������

				//�������� ������ ������
				if (right_was_pressed) {
					if (player.right_resolution()) {
						player.x++;
					}
					right_was_pressed = false;
				}
				//�������� ������ �����
				if (left_was_pressed) {
					if (player.left_resolution()) {
						player.x--;
					}
					left_was_pressed = false;
				}
				//���� ���� ������ ������ ��� ����������� �������
				if (down_was_pressed) {
					falling_delay = sf::seconds(0.05);
					down_was_pressed = false;
				}
				else {
					falling_delay = difficulty_level;
				}
				
					
				
				
				pressing_timer.restart();
			}
			
		}

		
		
		//������� 
		if (falling_timer.getElapsedTime() > falling_delay) {
			player.fall();
			falling_timer.restart();
		}

		//������ ��������� ����� ������
		field[player.x][player.y].available = true;

		//��������� ����� �� ����, ���� ������ �� ����� ��������� ����
		if (!player.down_resolution()) {
			if (check_line(player.y))
			{
				delete_line(player.y);
				fall_line(player.y);
			}
			player.set_on_field();
		}


		//������������ ��� �������� ����� �� ����
		for (int i = 0; i < FIELD_WIDTH; ++i) {
			for (int j = 0; j < FIELD_HEIGHT; ++j) {
				if (field[i][j].available) {
					window.draw(field[i][j].block_sprite);
				}
			}
		}
		window.draw(gaming_cage);

		window.display();
	}
	return 0;
}
