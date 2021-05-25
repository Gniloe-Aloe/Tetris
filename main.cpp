#include <SFML/Graphics.hpp>

const int M = 20; // ������ �������� ����
const int N = 10; // ������ �������� ����

int field[M][N] = { 0 }; // ������� ����

// ������ �������-���������
int figures[7][4] =
{
	1,3,5,7, // I
	2,4,5,7, // S
	3,5,4,6, // Z
	3,5,4,7, // T
	2,3,5,7, // L
	3,5,7,6, // J
	2,3,4,5, // O
};

class Point {
public:
	int x;
	int y;

};

Point a[4];
Point b[4];


int main()
{
	//����������� �� ��� ���
	int dx = 0;

	sf::RenderWindow window(sf::VideoMode(320, 480), "Tetris");
	//include texture
	sf::Texture brick_texture;
	brick_texture.loadFromFile("C:\\Users\\Gniloe_Aloe\\Desktop\\Tetris\\brick_texture.png");

	sf::Sprite brick_sprite(brick_texture);
	brick_sprite.setTextureRect(sf::IntRect(0, 0, 18, 18));

	// ������� ���� ����������: �����������, ���� ������� ����
	while (window.isOpen())
	{
		// ������������ ������� � �����
		sf::Event event;
		while (window.pollEvent(event))
		{
			// ������������ ����� �� �������� � ����� ������� ����?
			if (event.type == sf::Event::Closed) {
				// ����� ��������� ���
				window.close();
			}
							
		}

		int n = 1; // ������ ��� ���������
		for (int i = 0; i < 4; i++)
		{
			a[i].x = figures[n][i] % 2;
			a[i].y = figures[n][i] / 2;
		}

		// ��������� ����� ���� - �����
		window.clear(sf::Color(175, 213, 252));

		for (int i = 0; i < 4; i++)
		{
			// ������������� ������� ������� ������� ���������
			brick_sprite.setPosition(a[i].x * 18, a[i].y * 18);
			// ��������� �������
			window.draw(brick_sprite);
		}

		window.draw(brick_sprite);



		// ��������� ����
		window.display();
	}

	return 0;
}