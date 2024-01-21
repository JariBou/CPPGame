#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>

namespace Entities
{

	enum class ShapeType   
	{
		FILLED = 0,
		OUTLINED = 1,
	};
	

	class DrawableEntity {

		public:
			DrawableEntity(sf::Shape& shape);

			virtual ~DrawableEntity() = default;

			virtual void Draw(sf::RenderWindow& window);

			virtual void Move(sf::Vector2f vectorMove, float deltaTime);
			virtual void Update(float deltaTime) = 0;

			virtual void SetPosition(sf::Vector2f pos);

			virtual void SetColor(sf::Color color, sf::Color color2);
			virtual void SetColor(sf::Color color);

			/// <summary>
			/// Returns False if the entity should be removed
			/// </summary>
			/// <returns></returns>
			virtual bool CheckLife() = 0;

			void SetWindowDimension(sf::Vector2f windowDimension);

			sf::Shape& shape;
			sf::Vector2f windowDimension;

	};
}

