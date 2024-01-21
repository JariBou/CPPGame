#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

// Should be safe to include in headers but if possible please avoid

namespace Entities {
	class Bullet;
	class Foe;
	class UpgradeBox;
}

namespace Utils {

	sf::Vector2f NormalizeVector(sf::Vector2f vector);


	void CheckBulletListLife(std::vector<Entities::Bullet*>& bullets);
	void CheckFoeListLife(std::vector<Entities::Foe*>& foes);
	void CheckUpgradeListLife(std::vector<Entities::UpgradeBox*>& boxes);

	sf::String toString(int integers);
	sf::Vector2f GetShapeCenter(sf::Shape& shape);
	float GetShapeXCenter(sf::Shape& shape);
	float GetShapeYCenter(sf::Shape& shape);
	double DegToRad(float deg);
}
