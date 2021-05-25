#include <SFML/Graphics.hpp>



int main()
{
	// Объект, который, собственно, является главным окном приложения
	sf::RenderWindow window(sf::VideoMode(800, 400), "Tetris");

	// Главный цикл приложения. Выполняется, пока открыто окно
	while (window.isOpen())
	{
		// Обрабатываем очередь событий в цикле
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Пользователь нажал на «крестик» и хочет закрыть окно?
			if (event.type == sf::Event::Closed)
				// тогда закрываем его
				window.close();
		}
		//цвет окна
		window.clear(sf::Color(189, 162, 162, 0));

		//создание и отрисовка круга
		sf::CircleShape circle(50.f);
		circle.move(15, 15);
		circle.setFillColor(sf::Color(100, 142, 227));
		circle.setOutlineThickness(15.f);
		circle.setOutlineColor(sf::Color(230, 0, 230));
		window.draw(circle);

		//треугольник
		sf::CircleShape triangle(65.0f, 3);
		triangle.move(150, 15);
		triangle.setFillColor(sf::Color::Yellow);
		window.draw(triangle);

		//квадрат
		sf::CircleShape square(60, 4);
		square.move(300, 15);
		square.setFillColor(sf::Color::Blue);
		window.draw(square);

		//октагон
		sf::CircleShape octagon(60, 8);
		octagon.move(450, 15);
		octagon.setFillColor(sf::Color::Cyan);
		window.draw(octagon);

		//задаём вершины многоугольника
		sf::ConvexShape figure;
		figure.setPointCount(4);
		figure.setPoint(0, sf::Vector2f(500, 15));
		figure.setPoint(1, sf::Vector2f(600, 15));
		figure.setPoint(2, sf::Vector2f(600, 150));
		figure.setPoint(3, sf::Vector2f(500, 150));
		figure.setFillColor(sf::Color::Green);
		figure.move(120, 0);
		window.draw(figure);


		// Отрисовка окна	
		window.display();
	}

	return 0;
}