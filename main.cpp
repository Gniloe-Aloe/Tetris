#include <SFML/Graphics.hpp>



int main()
{
	// ������, �������, ����������, �������� ������� ����� ����������
	sf::RenderWindow window(sf::VideoMode(800, 400), "Tetris");

	// ������� ���� ����������. �����������, ���� ������� ����
	while (window.isOpen())
	{
		// ������������ ������� ������� � �����
		sf::Event event;
		while (window.pollEvent(event))
		{
			// ������������ ����� �� �������� � ����� ������� ����?
			if (event.type == sf::Event::Closed)
				// ����� ��������� ���
				window.close();
		}
		//���� ����
		window.clear(sf::Color(189, 162, 162, 0));

		//�������� � ��������� �����
		sf::CircleShape circle(50.f);
		circle.move(15, 15);
		circle.setFillColor(sf::Color(100, 142, 227));
		circle.setOutlineThickness(15.f);
		circle.setOutlineColor(sf::Color(230, 0, 230));
		window.draw(circle);

		//�����������
		sf::CircleShape triangle(65.0f, 3);
		triangle.move(150, 15);
		triangle.setFillColor(sf::Color::Yellow);
		window.draw(triangle);

		//�������
		sf::CircleShape square(60, 4);
		square.move(300, 15);
		square.setFillColor(sf::Color::Blue);
		window.draw(square);

		//�������
		sf::CircleShape octagon(60, 8);
		octagon.move(450, 15);
		octagon.setFillColor(sf::Color::Cyan);
		window.draw(octagon);

		//����� ������� ��������������
		sf::ConvexShape figure;
		figure.setPointCount(4);
		figure.setPoint(0, sf::Vector2f(500, 15));
		figure.setPoint(1, sf::Vector2f(600, 15));
		figure.setPoint(2, sf::Vector2f(600, 150));
		figure.setPoint(3, sf::Vector2f(500, 150));
		figure.setFillColor(sf::Color::Green);
		figure.move(120, 0);
		window.draw(figure);


		// ��������� ����	
		window.display();
	}

	return 0;
}