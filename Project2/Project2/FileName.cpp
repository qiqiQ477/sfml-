//#include <D:/SFML-2.6.1/include/SFML/Graphics.hpp>
//#include <D:/SFML-2.6.1/include/SFML/Audio.hpp>
//#include <D:/SFML-2.6.1/include/SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>
#include <random>
using namespace std;

int main()
{
	//创建窗口
	sf::RenderWindow window(sf::VideoMode(640, 640), "窗口");
	//限制帧率为60
	window.setFramerateLimit(60);

	//加载纹理和精灵
	sf::Texture texture,texture01;
	if (!
		texture.loadFromFile("图片/漫画边框-小图_爱给网_aigei_com.png")
		|| !texture01.loadFromFile("图片/125253063_p0_master1200(2).jpg")
		)
	{
		cout << "无法加载" << endl;
		return -1;
	}
	/*if (!
		texture01.loadFromFile("图片/125253063_p0_master1200(2).jpg")
		)
	{
		cout << "无法加载" << endl;
		return -1;
	}*/

	sf::Sprite sprite(texture),sprite01(texture01);
	sprite.setPosition(0, 0);
	sprite01.setPosition(200, 100);

	//创建图形
	sf::CircleShape circle(50);
	circle.setFillColor(sf::Color::Green);
	circle.setPosition(100, 100);

	sf::RectangleShape rectang(sf::Vector2f(120, 60)),re_rectang(sf::Vector2f(60,30));
	rectang.setFillColor(sf::Color::Blue);
	rectang.setPosition(500, 400);
	re_rectang.setFillColor(sf::Color::Red);
	re_rectang.setPosition(60, 10);


	//加载字体和文字
	sf::Font font;
	if (!
		font.loadFromFile("Fonts/Inkfree.ttf")
		)
	{
		cout << "无法加载" << endl;
		return -1;
	}
	sf::Text text("0",font, 20);
	text.setFillColor(sf::Color::Yellow);
	text.setPosition(10, 10);
	
	sf::Text re_text("清零",font, 20);
	re_text.setFillColor(sf::Color::White);
	re_text.setPosition(65, 10);

	sf::Text time_text("剩余时间：", font, 30);
	time_text.setFillColor(sf::Color::Red);
	time_text.setPosition(400, 10);

	//时间
	sf::Clock clock;
	sf::Time limtTime = sf::seconds(60);
	bool isLimtTime = false;

	//创建随机数生成器
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> disx(0, texture.getSize().x - texture01.getSize().x);
	uniform_int_distribution<> disy(0, texture.getSize().y - texture01.getSize().y);

	//游戏变量
	int score = 0;
	bool isRuning = true;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			window.close();
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
			{
				sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
				if ((sprite01.getGlobalBounds().contains(mousePos)
					|| rectang.getGlobalBounds().contains(mousePos)) && isRuning)
				{
					score++;
					text.setString(" " + to_string(score));

					circle.setPosition(disx(gen), disy(gen));
					sprite01.setPosition(disx(gen), disy(gen));
				}
				if (re_rectang.getGlobalBounds().contains(mousePos))
				{
					score = 0;
					text.setString(" " + to_string(score));
					clock.restart();
					isRuning = true;
					isLimtTime = false;
				}

			}
		}
		if (!isLimtTime)
		{
			sf::Time elapsedTime = clock.getElapsedTime();
			if (elapsedTime >= limtTime)
			{
				time_text.setString("时间到！");
				isLimtTime = true;
				isRuning = false;
			}
			else
			{
				int remaining = static_cast<int>(limtTime.asSeconds()) - static_cast<int>(elapsedTime.asSeconds());
				time_text.setString("剩余时间：" + to_string(remaining));
			}
		}

		window.clear();
		window.draw(sprite);
		//window.draw(circle);
		//window.draw(rectang);
		window.draw(sprite01);
		window.draw(text);
		window.draw(re_rectang);
		window.draw(re_text);
		window.draw(time_text);

		window.display();
	}
	

	return 0;
}