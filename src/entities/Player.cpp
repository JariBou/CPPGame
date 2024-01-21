#include "Player.h"
#include <iostream>
#include "../utils.h"
#include "../enum.h"
#include "Bullet.h"
#include "../GameManager.h"
#include "../particles/ParticleSystem.h"


namespace Entities
{
	using namespace std;


	Player::Player(sf::Shape& shape, GameManager* pGameManager) : DrawableEntity(shape), gameManager(pGameManager) {
		gameManager->SetPlayer(this);
		windowDimension = gameManager->GetWindowDimension();
	}


	void Player::MovePlayer(float deltaTime)
	{
		sf::FloatRect boundingBox = shape.getLocalBounds();
		playerWidth = boundingBox.width + shape.getOutlineThickness() / 2;
		playerHeight = boundingBox.height + shape.getOutlineThickness() / 2;

		//cout << "player Witdh : " << playerHeight << ", player Height : " << playerHeight << endl;
		//cout << "x : " << shape.getPosition().x << ", y :" << shape.getPosition().y << endl;
		//cout << "Window Height : " << windowHeight << ", Window Width : " << windowWidth << endl << endl;
		sf::Vector2f moveVector;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
			if ((shape.getPosition().y - shape.getOutlineThickness()) - 1 > shape.getOutlineThickness()) {
				moveVector.y = -1;
			}
			/*moveVector.y = -1;*/
		}


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			if ((shape.getPosition().y + playerHeight) + 1 < windowDimension.y + shape.getOutlineThickness()) {
				moveVector.y = 1;
			}
			/*moveVector.y = 1;*/
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
			if ((shape.getPosition().x - shape.getOutlineThickness()) - 1 > shape.getOutlineThickness())
			{
				moveVector.x = -1;
			}
			/*moveVector.x = -1;*/
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			if ((shape.getPosition().x + playerWidth) + 1 < windowDimension.x + shape.getOutlineThickness())
			{
				moveVector.x = 1;
			}
			//moveVector.x = 1;
		}

		//std::cout << 1.f / deltaTime << " FPS" << std::endl;
		Move(Utils::NormalizeVector(moveVector) * speed * (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) ? 0.8f : 1), deltaTime);
	}

	void Player::Draw(sf::RenderWindow& window) {
		window.draw(this->shape);

		//Hitbox
		sf::RectangleShape rect;
		rect.setPosition(this->shape.getGlobalBounds().left, this->shape.getGlobalBounds().top);
		rect.setSize(sf::Vector2f(this->shape.getGlobalBounds().width, this->shape.getGlobalBounds().height));
		rect.setOutlineThickness(2);
		rect.setFillColor(sf::Color::Transparent);
		rect.setOutlineColor(sf::Color::White);
		window.draw(rect);
	}

	void Player::Update(float deltaTime)
	{
		bulletClock += deltaTime;
		thrustTimer += deltaTime;
		if (bulletClock >= bulletCooldown) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
				bulletClock = 0;
				// Largeur entre les balles
				float w = (playerWidth-(shape.getOutlineThickness()*2)) / (nbBulletShot + 1);
				for (size_t i = 1; i <= nbBulletShot; i++) {
					sf::RectangleShape* rectangleBullet = new sf::RectangleShape(sf::Vector2f(bulletSize.x, bulletSize.y));
					float bulletSpeed = speed + 250.0 * bulletSpeedLevel / 8;
					float angle;
					// Vérifier le niveau de la mise à niveau des balles
					if (bulletNumberLevel <= 2) {
						// Si le niveau est 1, tirer droit
						angle = 0;
					}
					else {
						float bulletAngleRef = 0.15;
						// Si la boucle est dans la première moitié des balles
						if (i <= (nbBulletShot / 2)) {
						// Si nécessaire, ajouter des angles de référence au vecteur
							if (bulletAngles.size() < nbBulletShot / 2) {
								if (i == nbBulletShot / 2) {
									bulletAngles.insert(bulletAngles.begin(),0);
								}
								else {
									bulletAngles.push_back(bulletAngleRef * i);

								}
							}
							angle = -bulletAngles[bulletAngles.size() - i];
							
						}
						else {
							
							angle = bulletAngles[i - (nbBulletShot / 2) - 1];
							
						}
						
						if (i == nbBulletShot) {
							cout<< angle << endl;
						}
						else {
							cout << angle;
						}
					}
					// Créer une nouvelle balle avec les paramètres calculés
					Bullet* bullet = new Bullet(*rectangleBullet, gameManager, bulletDamage, bulletSpeed, sf::Vector2f(angle, -1.0), windowDimension.x);
					bullet->SetColor(sf::Color::Yellow);
					bullet->SetPosition(sf::Vector2f(shape.getPosition().x + i * w - bulletSize.x / 2, shape.getPosition().y - rectangleBullet->getSize().y * 1.5));
					this->gameManager->AddBullet(bullet);
					bullets.push_back(bullet);
				}
			}
		}

		if (thrustTimer >= 0.05) {
			int randGen = rand() % 5 + 3;
			gameManager->GetParticleSystem()->CreateDirectedExplosionAt(sf::Vector2f(this->shape.getGlobalBounds().left + 3 * (this->shape.getLocalBounds().width / 10), Utils::GetShapeYCenter(this->shape) + this->shape.getLocalBounds().height / 2),
				sf::Color::White, 80, 95, 2.2, randGen, 3, 60);
			randGen = rand() % 5 + 3;
			gameManager->GetParticleSystem()->CreateDirectedExplosionAt(sf::Vector2f(this->shape.getGlobalBounds().left + 7 * (this->shape.getLocalBounds().width / 10), Utils::GetShapeYCenter(this->shape) + this->shape.getLocalBounds().height / 2),
				sf::Color::White, 80, 95, 2.2, randGen, 3, 60);
			thrustTimer = 0;
		}
	}

	void Player::UpgradeLevel(UpgradeType upgrade)
	{
		switch (upgrade)
		{
		case UpgradeSpeed:
			if (movementSpeedLevel < 12) {
				movementSpeedLevel++;
				speed *= 1.1;
				cout << "Speed level : " << movementSpeedLevel << endl;
			}
			break;
		case UpgradeBulletDamage:
			if (bulletDamageLevel < 10) {
				bulletDamageLevel++;
				bulletDamage *= 1.1;
				bulletSize.x *= 1.1;
				bulletSize.y *= 1.1;
				cout << "Bullet damage level : " << bulletDamageLevel << endl;
			}
			break;
		case UpgradeBulletSpeed:
			if (bulletSpeedLevel < 8) {
				bulletSpeedLevel++;
				bulletCooldown -= 0.0325;
				cout << "Bullet speed level : " << bulletSpeedLevel << endl;
			}
			break;
		case UpgradeBulletNumber:
			if (bulletNumberLevel < 4) {
				bulletNumberLevel++;
				nbBulletShot*=2;
				cout << "Bullet number level : " << bulletNumberLevel << endl;
				bulletAngles.clear();
			}
			break;
		default:
			break;
		}
		
		/*if (upgradeLevel < 15) {
			upgradeLevel++;
			upgraded = true;
			cout << "Upgrade level : " << upgradeLevel << endl;
		}*/

	}

	void Player::GetHit(float damage) {
		std::cout << "Player hit" << std::endl;
		chanceCount--;
		if (chanceCount <= 0) {
			lives--;
			chanceCount = 3;
			std::cout << "Player lives : " << lives << std::endl;
		}
	}

	bool Player::CheckLife() {
		return (this->lives > 0);
	}

	GameManager* Player::GetGameManager()
	{
		return gameManager;
	}
	
}
	




	