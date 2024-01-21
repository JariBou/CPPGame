#include "utils.h"
#include <cmath>
#include <iostream>
#include <sstream>

#include "entities/Bullet.h"
#include "entities/Foe.h"
#include "entities/UpgradeBox.h"
using namespace std;


namespace Utils {

	sf::Vector2f NormalizeVector(sf::Vector2f vector) {
		float magnitude = sqrt(vector.x * vector.x + vector.y * vector.y);

		if (magnitude == 0) {
			return sf::Vector2f(0, 0);
		}

		return sf::Vector2f(vector.x / magnitude, vector.y / magnitude);

	}

	void CheckBulletListLife(std::vector<Entities::Bullet*>& bullets) {
		auto bulletVectorIterator = bullets.begin();
		while (bulletVectorIterator != bullets.end()) {
			if ((*bulletVectorIterator)->CheckLife()) {
				bulletVectorIterator++;
			}
			else {
				bulletVectorIterator = bullets.erase(bulletVectorIterator);
				/*std::cout << "Bullet deleted" << std::endl;*/
			}
		}
	}

	void CheckFoeListLife(std::vector<Entities::Foe*>& foes) {
		auto foeVectorIterator = foes.begin();
		while (foeVectorIterator != foes.end()) {
			if ((*foeVectorIterator)->CheckLife()) {
				foeVectorIterator++;
			}
			else {
				if ((*foeVectorIterator)->isDead()) {
					(*foeVectorIterator)->OnKilledByPlayer();
				}
				(*foeVectorIterator)->OnDestroyed();
				foeVectorIterator = foes.erase(foeVectorIterator);
				std::cout << "Foe deleted" << std::endl;
			}
		}
	}

	void CheckUpgradeListLife(std::vector<Entities::UpgradeBox*>& boxes) {
		auto upgradeVectorIterator = boxes.begin();
		while (upgradeVectorIterator != boxes.end()) {
			if ((*upgradeVectorIterator)->CheckLife()) {
				upgradeVectorIterator++;
			}
			else {
				upgradeVectorIterator = boxes.erase(upgradeVectorIterator);
				std::cout << "Upgrade deleted" << std::endl;
			}
		}
	}

	// Omg, can't stress how much I HATE this nonsense of "gngngn no you can't use parent class as parameter"
	void CheckEntityListLife(std::vector<Entities::DrawableEntity*>* boxes) {
		auto upgradeVectorIterator = boxes->begin();
		while (upgradeVectorIterator != boxes->end()) {
			if ((*upgradeVectorIterator)->CheckLife()) {
				upgradeVectorIterator++;
			}
			else {
				upgradeVectorIterator = boxes->erase(upgradeVectorIterator);
				std::cout << "Upgrade deleted" << std::endl;
			}
		}
	}

	sf::String toString(int integer)
	{
		std::ostringstream os;
		os << integer;
		return os.str();
	}

	sf::Vector2f GetShapeCenter(sf::Shape& shape)
	{
		return sf::Vector2f(GetShapeXCenter(shape),
			GetShapeYCenter(shape));
	}

	float GetShapeXCenter(sf::Shape& shape)
	{
		return shape.getPosition().x + shape.getLocalBounds().width / 2;
	}

	float GetShapeYCenter(sf::Shape& shape)
	{
		return shape.getPosition().y + shape.getLocalBounds().height / 2;
	}

	double DegToRad(float deg) {
		double pi = 3.14159265359;
		return (deg * (pi / 180));
		
	}

}