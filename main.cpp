#include <SFML/Graphics.hpp>



int main()
{
	// Устанавливаем 8-й уровень сглаживания
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	// Объект, который, собственно, является главным окном приложения
	sf::RenderWindow window(sf::VideoMode(800, 400), "Tetris", sf::Style::Default, settings);

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
		figure.setPoint(0, sf::Vector2f(0, 0));
		figure.setPoint(1, sf::Vector2f(100, 30));
		figure.setPoint(2, sf::Vector2f(100, 130));
		figure.setPoint(3, sf::Vector2f(0, 100));
		figure.setFillColor(sf::Color::Black);
		figure.move(600, 15);
		window.draw(figure);

		//прямоугольник
		sf::RectangleShape rectangle (sf::Vector2f(200, 150));
		rectangle.setFillColor(sf::Color::Magenta);
		rectangle.move(30, 150);
		window.draw(rectangle);

		//текстуры
		sf::Texture brick_texture;
		//тут нужно указать своё расположение картинки и не забыть про два слэша
		//второй аргумент для загрузки части изображения, начиная с координат (0;0)
		brick_texture.loadFromFile("C:\\Users\\Gniloe_Aloe\\Desktop\\Tetris\\brick.jpg", sf::IntRect(0, 0, 1000, 1000));
		sf::Sprite brick_sprite(brick_texture, sf::IntRect(0, 0, 200, 200));
		brick_texture.setSmooth(true);
		brick_sprite.move(300, 150);
		window.draw(brick_sprite);

		//синий спрайт
		sf::Sprite blue_brick(brick_texture, sf::IntRect(0, 0, 200, 200));
		blue_brick.setColor(sf::Color::Blue);
		blue_brick.move(520, 150);

		blue_brick.move(100, 0);
		blue_brick.setRotation(45.0f);
		blue_brick.setScale(0.5, 0.5);
		window.draw(blue_brick);
		
		

		// Отрисовка окна	
		window.display();
	}

	return 0;
}