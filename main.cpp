﻿#include <SFML/Graphics.hpp>
#include <ctime>
#include <vector>
#include <string>
//C:\\Users\\Gniloe_Aloe\\Desktop\\Tetris\\block.png

//глобальные константы для игрового поля
const unsigned int CAGE_SIZE = 45;// длинна стороны блока в пикселях
const unsigned int FIELD_WIDTH = 10;// ширина поля в блока
const unsigned int FIELD_HEIGHT = 20;// высота поля в блоках
sf::RenderWindow gaming_window(sf::VideoMode(CAGE_SIZE* FIELD_WIDTH, CAGE_SIZE* FIELD_HEIGHT), "Tetris!"); // Окно игры
sf::RenderWindow setting_window(sf::VideoMode(CAGE_SIZE* FIELD_WIDTH, CAGE_SIZE* FIELD_HEIGHT), "Tetris!"); // Окно настроек
//шрифт
sf::Font Arial;
//очки
unsigned int score;


class Block {
public:
	//отображать ли блок
	bool available = false;
	//установлен ли блок на поле (не игроок)
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
	//rand()%5 для перебора всех цветов
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
//создание глобального двумерного массива из блоков под игровое поле
Block field[FIELD_WIDTH][FIELD_HEIGHT];

class Player {
public:
	int x = FIELD_WIDTH/2;
	int y = 0;
	//провека возможности движения вправо если не вышли за пределы поля
	//и справа нет стоящего блока
	bool right_resolution(){
		return (this->x < FIELD_WIDTH - 1)&&(!field[this->x+1][y].available);
	}
	//проверка возможности движения влево
	bool left_resolution() {
		return (this->x > 0)&&(!field[x-1][y].available);
	}
	//проверка наличия свободного места под фигурой игрока
	bool down_resolution() {
		//если не вышли за ганицы поля и под нами нет другого стоящего блока
		return (y < FIELD_HEIGHT - 1) && (!field[x][y + 1].available);
	}
	//установка блока игрока на поле
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

	// Конец игры
	void game_over()
	{
		//Подключение шрифта и работа с текстом
		

		sf::Text endgame_text;
		endgame_text.setFont(Arial);

		endgame_text.setCharacterSize(80);
		endgame_text.setFillColor(sf::Color::White);
		endgame_text.move(15, (FIELD_HEIGHT / 2 * CAGE_SIZE) - CAGE_SIZE * 2);
		
		endgame_text.setString("END GAME");
		gaming_window.draw(endgame_text);

		sf::Text score_text;
		score_text.setFont(Arial);
		score_text.setFillColor(sf::Color::White);
		score_text.move(endgame_text.getPosition());
		score_text.move(2, 100);

		score_text.setString("SCORE: " + std::to_string(score * 100));
		gaming_window.draw(score_text);

		gaming_window.display();
		sf::Clock timer;
		

		sf::Event event;

		while (gaming_window.isOpen()) {
			while (gaming_window.pollEvent(event)) {
				if (event.type == sf::Event::Closed) {
					gaming_window.close();
				}
				if (event.type == sf::Event::KeyPressed && timer.getElapsedTime() > sf::seconds(2)) {
					gaming_window.close();
				}
				
				
			}
		}
	}

	//падение
	void fall() {
		if (down_resolution()) {
			++y;
		}
		
	}
};

// Проверяем линию на заполненность
bool check_line(const int& y){
	for (int i = 0; i < FIELD_WIDTH; ++i){
		if (!field[i][y].available){
			return false;	
		}
	}
	return true;
}

// Удаляем линию
void delete_line(const int& y){
	for (int i = 0; i < FIELD_WIDTH; ++i){
		field[i][y].available = false;
		field[i][y].set_on_field = false;
	}
	score++;
}

// Сдвиг линий вниз
void fall_line(const int& y){
	// Сдвигаем изображения, опираясь на set_on_field
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

//для настроек
void demonsration_setting_block(sf::Sprite* set_blocks_sprites, int size, sf::Texture& set_block) {
	for (int i = 0; i < 5; ++i) {
		set_blocks_sprites[i].setPosition(75 + (5 * 30), 15 + ((19 - i) * 30));
		set_blocks_sprites[i].setTexture(set_block);

		switch (i) {
		case 0:
			set_blocks_sprites[i].setColor(sf::Color::Red);
			break;
		case 1:
			set_blocks_sprites[i].setColor(sf::Color::Cyan);
			break;
		case 2:
			set_blocks_sprites[i].setColor(sf::Color::Blue);
			break;
		case 3:
			set_blocks_sprites[i].setColor(sf::Color::Yellow);
			break;
		case 4:
			set_blocks_sprites[i].setColor(sf::Color::Magenta);
			break;
		}
	}
}


int main() {

	//подключение файлов и инициализация констант
	sf::Texture BLOCK_TEXTURE;
	//диапозон блоков 3 - 5

	BLOCK_TEXTURE.loadFromFile("pic//block5_o.png");
	

	sf::Sprite block_sprite(BLOCK_TEXTURE);

	//цвет фона
	const sf::Color background(130, 155, 207);

	//текстура заднего фона
	sf::Texture BACKGROUND_TEXTURE;
	//диапозон фонов 1-4
	
	BACKGROUND_TEXTURE.loadFromFile("pic//background3.png");
	sf::Sprite background_sprite(BACKGROUND_TEXTURE);

	//текстура игровой сетки
	sf::Texture CAGE_TEXTURE;
	
	CAGE_TEXTURE.loadFromFile("pic//gaming_cage.png");
	sf::Sprite gaming_cage(CAGE_TEXTURE);

	//Подключение шрифта и работа с текстом
	Arial.loadFromFile("arial.ttf");

	
	srand(time(NULL));
	
	//настраиваем игровое поле
	for (int i = 0; i < FIELD_WIDTH; ++i) {
		for (int j = 0; j < FIELD_HEIGHT; ++j) {
			//задаём свойства для каждого блока
			field[i][j].available = false;
			field[i][j].set_texture(BLOCK_TEXTURE);
			field[i][j].set_coordinate(i, j);
			field[i][j].set_position(CAGE_SIZE);
			field[i][j].set_color(rand()%5);
		}
	}

	//создаём игрока
	Player player;




	//создаём окно игры
	
	gaming_window.clear(background);

	//количество убранных линий
	score = 0;

	//создание таймера и переменной задержки для нажатия на клавиши
	sf::Clock pressing_timer;
	sf::Time pressing_delay = sf::seconds(0.01);

	//таймер падения
	sf::Clock falling_timer;
	const sf::Time difficulty_level = sf::seconds(0.5);
	sf::Time falling_delay = difficulty_level;

	//флаги нажатия кнопок
	bool left_was_pressed = false;
	bool right_was_pressed = false;
	bool up = false;
	bool down_was_pressed = false;

	//текстуры для окна настроек
	sf::Texture start_background;
	start_background.loadFromFile("pic//start_back.png");
	sf::Sprite start_background_sprite(start_background);
	
	sf::Texture set_color;
	set_color.loadFromFile("pic//set_color.png");
	sf::Sprite set_color_sprite(set_color);
	set_color_sprite.move(75, 15);

	sf::Texture set_cage;
	set_cage.loadFromFile("pic//set_cage.png");
	sf::Sprite set_cage_sprite(set_cage);
	set_cage_sprite.move(75, 15);

	sf::Texture set_block;
	set_block.loadFromFile("pic//set_block.png");
	

	sf::Sprite set_blocks_sprites[5];
	
	demonsration_setting_block(set_blocks_sprites, 5, set_block);

	//главный цикл при открытом окне настроек************************************************************************
	while (setting_window.isOpen()){
		
		setting_window.draw(start_background_sprite);
		setting_window.draw(set_color_sprite);

		for (int i = 0; i < 5; ++i) {
			setting_window.draw(set_blocks_sprites[i]);
		}
		
		setting_window.draw(set_cage_sprite);
		sf::Event event;
		//отлавливаем слбытия
		while (setting_window.pollEvent(event)) {

			//если закрыли окно
			if (event.type == sf::Event::Closed) {
				background_sprite.setColor(set_color_sprite.getColor());
				setting_window.close();
			}
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == (sf::Keyboard::D)) {
					set_color_sprite.setColor(sf::Color(rand()%240, rand()%240, rand()%240));
				}
				if (event.key.code == (sf::Keyboard::A)) {
					set_color_sprite.setColor(sf::Color(rand() % 240, rand() % 240, rand() % 240));
				}
				if (event.key.code == (sf::Keyboard::S)) {
					
				}
				if (event.key.code == (sf::Keyboard::W)) {
				
				}
				//выбор
				if (event.key.code == sf::Keyboard::Enter) {
					background_sprite.setColor(set_color_sprite.getColor());
					setting_window.close();
				}
			}
		}
		





		setting_window.display();
	}

	//главный цикл при открытом игровом окне**********************************************************************
	while (gaming_window.isOpen()) {

		gaming_window.draw(background_sprite);

		field[player.x][player.y].available = false;

		//отлавливаем события
		sf::Event event;
		while (gaming_window.pollEvent(event)) {

			//если закрыли окно
			if (event.type == sf::Event::Closed) {
				gaming_window.close();
			}

			//движение
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == (sf::Keyboard::D)) {
					right_was_pressed = true;
				}
				if (event.key.code == (sf::Keyboard::A)) {
					left_was_pressed = true;
				}
				//ускоренное падение
				if (event.key.code == (sf::Keyboard::S)) {
					down_was_pressed = true;
				}
				
				//переворот фигуры
				if (event.key.code == (sf::Keyboard::W)) {
					
				}
			}
			//проверяем, прошла ли наша задержка времени отклика
			if (pressing_timer.getElapsedTime() > pressing_delay) {
				//нажатие клавиш

				//движение фигуры вправо
				if (right_was_pressed) {
					if (player.right_resolution()) {
						player.x++;
					}
					right_was_pressed = false;
				}
				//двидение фигуры влево
				if (left_was_pressed) {
					if (player.left_resolution()) {
						player.x--;
					}
					left_was_pressed = false;
				}
				//если была нажата кнопка для ускоренного падения
				if (down_was_pressed) {
					falling_delay = sf::seconds(0.03);
					down_was_pressed = false;
				}
				else {
					falling_delay = difficulty_level;
				}
				
					
				
				
				pressing_timer.restart();
			}
			
		}

		
		
		//падение 
		if (falling_timer.getElapsedTime() > falling_delay) {
			player.fall();
			falling_timer.restart();
		}

		//делаем активными блоки игрока
		field[player.x][player.y].available = true;

		//установка блока на поле, если больше не можем двигаться вниз
		if (!player.down_resolution()) {
			if (check_line(player.y))
			{
				delete_line(player.y);
				fall_line(player.y);
			}
			player.set_on_field();
		}


		//отрисовываем все активные блоки на поле
		for (int i = 0; i < FIELD_WIDTH; ++i) {
			for (int j = 0; j < FIELD_HEIGHT; ++j) {
				if (field[i][j].available) {
					gaming_window.draw(field[i][j].block_sprite);
				}
			}
		}
		gaming_window.draw(gaming_cage);
		
		gaming_window.display();
	}
	return 0;
}
