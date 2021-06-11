#include <SFML/Graphics.hpp>
#include <ctime>
#include <vector>

class blok {
public:
	int x = 0;
	int y = 0;
	blok() {};
	blok(int x, int y) :x(x), y(y) {};
	bool out_field_right() {
		if (x == 9 )
			return true;
		else
			return false;	
	}
	bool out_field_left() {
		if (x == 0)
			return true;
		else
			return false;
	}
};

class tetramino {
public:
	blok bloks[4];

	void set_figure(int value) {
		// ��������� I
		if (value == 0) {
			for (int i = 0; i < 4; ++i) {
				bloks[i].x = 5;
				bloks[i].y = i;
			}
		}
	}
	bool tetramino_out_of_field() {
		for (int i = 0; i < 4; ++i) {
			if (bloks[i].out_field_right() == true || bloks[i].out_field_left() == true) {
				return true;
			}
		}
		return false;
	}

	void move_right() {
		for (int i = 0; i < 4; ++i) {
			++bloks[i].x;
		}
	}

		
		
	
};



//C:\\Users\\Gniloe_Aloe\\Desktop\\Tetris\\block.png

sf::Color random_color() {
	return sf::Color(rand() % 256, rand() % 256, rand() % 256);
}



int main()
{
	const int CELLS_SIZE = 45;
	bool presed = true;
	
	

	srand(time(NULL));

	sf::RenderWindow window(sf::VideoMode(450, 900), "Tetris!");
	sf::Color fon;
	fon = sf::Color::Magenta;


	//������ ����������, �� ������� ������� ���������
	sf::Texture block_texture;
	block_texture.loadFromFile("C:\\Users\\Gniloe_Aloe\\Desktop\\Tetris\\block.png");
	

	

	
	
	

	std::vector<sf::Sprite> test;
	for (int i = 0; i < 4; ++i) {
		test.emplace_back(block_texture);
	}
	//��������� � ������������ ���������
	tetramino tetramino;
	//����� ����� ��� ���������
	tetramino.set_figure(0);
	//���� ����� �������������� ������������ � ����� ������
	for (int i = 0; i < 4; ++i) {
		test[i].move(tetramino.bloks[i].x * CELLS_SIZE, tetramino.bloks[i].y * CELLS_SIZE);
	}

	// ������� ���� ����������: �����������, ���� ������� ����
	while (window.isOpen())
	{
		// ������������ ������� � �����
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (presed) {
				// ������������ ����� �� �������� � ����� ������� ����?
				if (event.type == sf::Event::Closed) {
					// ����� ��������� ���
					window.close();
				}
				//������� ����� ������
				if (event.type == sf::Event::KeyPressed) {
					presed = false;
				}
				
				if (event.key.code == sf::Keyboard::Right) {
					if (!tetramino.tetramino_out_of_field()) {
						tetramino.move_right();
					}
				}
				if (event.key.code == sf::Keyboard::Left) {
					
				}
				if (event.key.code == sf::Keyboard::Up) {
					
					
				}
				if (event.key.code == sf::Keyboard::Down) {
					
				}
			}
			else {
				presed = true;
			}
		}
		// ��������� ����� ����
		window.clear(fon);



		//������������ ��� ����� � ���������
		for (int i = 0; i < 4; ++i) {
			window.draw(test[i]);
		}
		




		// ��������� ����
		window.display();
		
	}

	return 0;
}