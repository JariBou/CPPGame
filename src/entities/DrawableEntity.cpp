#include "DrawableEntity.h"

namespace Entities
{
	DrawableEntity::DrawableEntity(sf::Shape& shape) : shape(shape){}

	void DrawableEntity::Draw(sf::RenderWindow& Window) {
		Window.draw(this->shape);
	}

	void DrawableEntity::SetWindowDimension(sf::Vector2f windowDimension) {
		this->windowDimension = windowDimension;
	}

	void DrawableEntity::Move(sf::Vector2f vectorMove, float deltaTime) {
		sf::Vector2f pos = shape.getPosition();
		pos += vectorMove * deltaTime;
		shape.setPosition(pos);
	}

	void DrawableEntity::SetPosition(sf::Vector2f pos) {
		shape.setPosition(pos);
	}

	void DrawableEntity::SetColor(sf::Color color, sf::Color color2) {
		shape.setFillColor(color);
		if (color2 != sf::Color::Transparent) {
			shape.setOutlineThickness(5);
			shape.setOutlineColor(color2);
		}
	}
	
	void DrawableEntity::SetColor(sf::Color color) {
		shape.setFillColor(color);
		shape.setOutlineThickness(0);
		shape.setOutlineColor(sf::Color::Transparent);
	}

	
}
