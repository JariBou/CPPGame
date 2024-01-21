#include "Particle.h"


namespace SFX {

	Particle::Particle(sf::Shape& shape, float maxLifetime, sf::Vector2f direction) : Entities::DrawableEntity(shape), maxLifetime(maxLifetime), direction(direction) {
		this->currColor = shape.getFillColor();
	}

	Particle::Particle(sf::Shape& shape, float maxLifetime, sf::Vector2f direction, float speed) : Particle::Particle(shape, maxLifetime, direction)
	{
		this->speed = speed;
	}

	bool Particle::CheckLife() {
		return lifetime < maxLifetime;
	}

	void Particle::Update(float deltaTime)
	{
		lifetime += deltaTime;
		this->SetPosition(shape.getPosition() + (this->direction * deltaTime * this->speed));
		// TODO
	}

	void Particle::UpdateAlpha(float alpha)
	{
		sf::Color oldFillColor = shape.getFillColor();
		this->currColor = sf::Color(oldFillColor.r, oldFillColor.g, oldFillColor.b, alpha * 255);
		//sf::Color oldOutlineColor = shape.getOutlineColor();
		//sf::Color newOutlineColor(oldOutlineColor.r, oldOutlineColor.g, oldOutlineColor.b, alpha);

		shape.setFillColor(this->currColor);
		//shape.setOutlineColor(newOutlineColor);
	}

	float Particle::GetLifePercentage()
	{
		float percent = lifetime / maxLifetime;
		if (percent > 1) {
			return 1;
		}
		else if (percent < 0) {
			return 0;
		}
		return lifetime / maxLifetime;
	}

}
