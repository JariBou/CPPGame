#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>
#include "DrawableEntity.h"
#include <iostream>
#include <random>
#include "UpgradeBox.h"
#include "../enum.h"
#include "Player.h"
#include "../GameManager.h"

namespace Entities {

	UpgradeBox::UpgradeBox(sf::Shape& shape, GameManager* pGameManager, int UpgradeTypeNb) : DrawableEntity(shape), gameManager(pGameManager), player(*pGameManager->GetPlayer()) {
		speed = 200;
		std::mt19937 rng(std::random_device{}());
		std::uniform_int_distribution<int> type(0, 3);
		int random_number = type(rng);
		upgradeType = UpgradeType(UpgradeTypeNb);
	}

	void UpgradeBox::Update(float deltaTime) {
		Move(sf::Vector2f(0,1), deltaTime*speed);
	}

	bool UpgradeBox::IsColliding() {
		auto selfRect = this->shape.getGlobalBounds();
		auto playerRect = player.shape.getGlobalBounds();

		shouldDestroy = selfRect.intersects(playerRect);
		return shouldDestroy;
	}

	bool UpgradeBox::CheckLife() {

		if (this->shouldDestroy) return false;

		sf::Vector2f windowDimension = gameManager->GetWindowDimension();

		if (shape.getPosition().x < 0 - shape.getLocalBounds().width || shape.getPosition().y < 0 - shape.getLocalBounds().height
			|| shape.getPosition().x > windowDimension.x + shape.getLocalBounds().width || shape.getPosition().y > windowDimension.y + shape.getLocalBounds().height) {
			return false;
		}
		return true;

	}

	UpgradeType UpgradeBox::GetUpgradeType() {
		return upgradeType;
	}
		

}



