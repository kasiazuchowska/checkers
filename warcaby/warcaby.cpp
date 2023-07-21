#include "SFML/Graphics.hpp"
#include <fstream>
#include <iostream>

class Warcaby : public sf::Drawable{
public:
	Warcaby() : iscircle(false){};
	void SetIsCircle(bool);
	void SetLastPos(int, int);
	void SetCircleColor();
	void SetMousePos(int, int, int);
	void SetMap();
	void ChangeMap(int);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void SetDrawParameters(sf::Vector2u draw_area_size);

private:
	int map[8][8];
	sf::Vector2f shift, tile_size, mouse_pos, offset, last_pos;
	sf::Color circle_color;
	bool iscircle;
};

void Warcaby::SetIsCircle(bool s) {
	iscircle = s;
}

void Warcaby::SetCircleColor() {
	int x = (mouse_pos.x - shift.x) / tile_size.x;
	int y = (mouse_pos.y - shift.y) / tile_size.y;
	if (map[y][x] == 2) circle_color = sf::Color::Black;
	if (map[y][x] == 3) circle_color = sf::Color::White;
}

void Warcaby::SetLastPos(int x, int y) {
	last_pos.x = x;
	last_pos.y = y;
}

void Warcaby::SetMousePos(int x, int y, int off) {
	mouse_pos.x = x;
	mouse_pos.y = y;
	if(off == 1) {
		int x = (mouse_pos.x - shift.x) / tile_size.x;
		int y = (mouse_pos.y - shift.y) / tile_size.y;
		offset.x = mouse_pos.x - x * tile_size.x - shift.x;
		offset.y = mouse_pos.y - y * tile_size.y - shift.y;
	}
}


void Warcaby::ChangeMap(int how) {
	int x = (mouse_pos.x - shift.x) / tile_size.x;
	int y = (mouse_pos.y - shift.y) / tile_size.y;
	if (how == 1 && map[y][x] > 1) {
		if ((x ^ y) % 2 == 0)map[y][x] = 0;
		else map[y][x] = 1;
		return;
	}

	if (map[y][x] > 1) {
		x = (last_pos.x - shift.x) / tile_size.x;
		y = (last_pos.y - shift.y) / tile_size.y;
	}

	if (circle_color == sf::Color::Black) {
		if ((x ^ y) % 2 == 0)map[y][x] = 4;
		else map[y][x] = 2;
		return;
	}
	if (circle_color == sf::Color::White) {
		if ((x ^ y) % 2 == 0)map[y][x] = 5;
		else map[y][x] = 3;
		return;
	}
}

void Warcaby::SetMap() {
	for (int i = 0; i < 8; i += 2) {
		map[0][i] = 0;//puste biale
		map[0][i + 1] = 2;//czarny pionek
	}
	for (int i = 0; i < 8; i += 2) {
		map[1][i] = 2;//czarny pionek
		map[1][i + 1] = 0;//puste biale
	}
	for (int i = 0; i < 8; i += 2) {
		map[2][i] = 0;//puste biale
		map[2][i + 1] = 2;//czarny pionek
	}
	for (int i = 0; i < 8; i += 2) {
		map[3][i] = 1;//puste czarne
		map[3][i + 1] = 0;//puste biale
	}
	for (int i = 0; i < 8; i += 2) {
		map[4][i] = 0;//puste biale
		map[4][i + 1] = 1;//puste czarne
	}
	for (int i = 0; i < 8; i += 2) {
		map[5][i] = 3;//bialy pionek
		map[5][i + 1] = 0;//puste biale
	}
	for (int i = 0; i < 8; i += 2) {
		map[6][i] = 0;//puste biale
		map[6][i + 1] = 3;//bialy pionek
	}
	for (int i = 0; i < 8; i += 2) {
		map[7][i] = 3;//bialy pionek
		map[7][i + 1] = 0;//puste biale
	}
	//4 to czarny pionek na bialym
	//5 to bialy pionek na bialym
}

void Warcaby::draw(sf::RenderTarget & target, sf::RenderStates states) const{
	sf::Texture White_texture, Black_texture;
	sf::Sprite White_sprite, Black_sprite;

	White_texture.loadFromFile("White.jpg");
	Black_texture.loadFromFile("Black.jpg");

	White_sprite.setTexture(White_texture);
	Black_sprite.setTexture(Black_texture);

	White_sprite.setScale(this->tile_size.x / White_texture.getSize().x, this->tile_size.y / White_texture.getSize().y);
	Black_sprite.setScale(this->tile_size.x / Black_texture.getSize().x, this->tile_size.y / Black_texture.getSize().y);

	sf::CircleShape circle_w, circle_b;
	circle_w.setRadius(tile_size.x / 2);
	circle_w.setFillColor(sf::Color::White);
	circle_w.setOutlineColor(sf::Color::White);
	circle_b.setRadius(tile_size.x / 2);
	circle_b.setFillColor(sf::Color::Black);
	circle_b.setOutlineColor(sf::Color::Black);

	for (int y = 0; y < 8; ++y)
		for (int x = 0; x < 8; ++x)
		{
			switch (map[y][x])
			{
			case 0:
			{
				White_sprite.setPosition(shift.x + x * this->tile_size.x, shift.y + y * this->tile_size.y);
				target.draw(White_sprite);
				break;
			}
			case 1:
			{
				Black_sprite.setPosition(shift.x + x * this->tile_size.x, shift.y + y * this->tile_size.y);
				target.draw(Black_sprite);
				break;
			}
			case 2:
			{
				Black_sprite.setPosition(shift.x + x * this->tile_size.x, shift.y + y * this->tile_size.y);
				target.draw(Black_sprite);
				circle_b.setPosition(shift.x + x * this->tile_size.x, shift.y + y * this->tile_size.y);
				target.draw(circle_b);
				break;
			}
			case 3:
			{
				Black_sprite.setPosition(shift.x + x * this->tile_size.x, shift.y + y * this->tile_size.y);
				target.draw(Black_sprite);
				circle_w.setPosition(shift.x + x * this->tile_size.x, shift.y + y * this->tile_size.y);
				target.draw(circle_w);
				break;
			}
			case 4:
			{
				White_sprite.setPosition(shift.x + x * this->tile_size.x, shift.y + y * this->tile_size.y);
				target.draw(White_sprite);
				circle_b.setPosition(shift.x + x * this->tile_size.x, shift.y + y * this->tile_size.y);
				target.draw(circle_b);
				break;
			}
			case 5:
			{
				White_sprite.setPosition(shift.x + x * this->tile_size.x, shift.y + y * this->tile_size.y);
				target.draw(White_sprite);
				circle_w.setPosition(shift.x + x * this->tile_size.x, shift.y + y * this->tile_size.y);
				target.draw(circle_w);
				break;
			}
			}

		}
	if (iscircle) {
		if (circle_color == sf::Color::Black) {
			circle_b.setPosition(mouse_pos.x - offset.x, mouse_pos.y - offset.y);
			target.draw(circle_b);
		}
		if (circle_color == sf::Color::White) {
			circle_w.setPosition(mouse_pos.x - offset.x, mouse_pos.y - offset.y);
			target.draw(circle_w);
		}
	}

	

}

void Warcaby::SetDrawParameters(sf::Vector2u draw_area_size)
{
	this->tile_size = sf::Vector2f(
		std::min(std::floor((float)draw_area_size.x / (float)8), std::floor((float)draw_area_size.y / (float)8)),
		std::min(std::floor((float)draw_area_size.x / (float)8), std::floor((float)draw_area_size.y / (float)8))
	);
	this->shift = sf::Vector2f(
		((float)draw_area_size.x - this->tile_size.x * 8) / 2.0f,
		((float)draw_area_size.y - this->tile_size.y * 8) / 2.0f
	);
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "WARCABY", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
	Warcaby warcaby;

	warcaby.SetMap();
	warcaby.SetDrawParameters(window.getSize());



	while (window.isOpen())
	{
		window.clear(sf::Color::Black);
		sf::Event event;

		while (window.pollEvent(event))
		{

			if (event.type == sf::Event::Resized)
			{
				float width = static_cast<float>(event.size.width);
				float height = static_cast<float>(event.size.height);
				window.setView(sf::View(sf::FloatRect(0, 0, width, height)));
				warcaby.SetDrawParameters(window.getSize());
			}

			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				warcaby.SetMousePos(event.mouseButton.x, event.mouseButton.y,1);//set offset
				warcaby.SetLastPos(event.mouseButton.x, event.mouseButton.y);
				warcaby.SetCircleColor();
				warcaby.ChangeMap(1);//how = 1 czyli zabierz pionek
				warcaby.SetIsCircle(true);
				
			}

			if (event.type == sf::Event::MouseMoved && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				warcaby.SetMousePos(event.mouseMove.x, event.mouseMove.y,0);//dont set offset
			}

			if (event.type == sf::Event::MouseButtonReleased) {
				warcaby.SetMousePos(event.mouseButton.x, event.mouseButton.y, 1);//set offset
				warcaby.ChangeMap(2);//how = 2 czyli postaw pionek
				warcaby.SetIsCircle(false);
			}
		}

		window.draw(warcaby);
		window.display();
	}

	return 0;
}