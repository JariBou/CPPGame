#include "ParticleSystem.h"
#include <cmath>
#include "Particle.h"
#include "ParticleCompound.h"
#include "../utils.h"

namespace SFX {

	/// <summary>
	/// Creates a Particle system
	/// Cascading style:
	/// -> ParticleSystem Manages ParticleCompounds (basically a list of Particles that together create an effect)
	/// -> ParticleCompound manages individual Particles
	/// </summary>
	ParticleSystem::ParticleSystem()
	{

	}

	void ParticleSystem::Update(float deltaTime)
	{
		for (ParticleCompound* pParticleCompound : this->particleCompoundList) {
			pParticleCompound->Update(deltaTime);
		}
	}

	void ParticleSystem::Draw(sf::RenderWindow& window)
	{
		for (ParticleCompound* pParticleCompound : this->particleCompoundList) {
			pParticleCompound->Draw(window);
		}
	}

	void ParticleSystem::CheckLifetimes()
	{
		auto it = this->particleCompoundList.begin();
		while (it != this->particleCompoundList.end())
		{
			if ((*it)->IsActive()) {
				it++;
			}
			else {
				it = this->particleCompoundList.erase(it);
			}
		}
	}

	void ParticleSystem::AddParticleCompound(ParticleCompound* compound)
	{
		this->particleCompoundList.push_back(compound);
	}

	void ParticleSystem::Reset()
	{
		auto it = this->particleCompoundList.begin();
		while (it != this->particleCompoundList.end())
		{
			(*it)->Delete();
			it = this->particleCompoundList.erase(it);
		}
	}

#pragma region Prefabs

	void ParticleSystem::CreateExplosionAt(sf::Vector2f position, sf::Color color, float size, int numberOfParticles, float distanceFromOrigin, float minSpeed)
	{
		CreateDirectedExplosionAt(position, color, 360, 180, size, numberOfParticles, distanceFromOrigin, minSpeed);
	}

	void ParticleSystem::CreateDirectedExplosionAt(sf::Vector2f position, sf::Color color, float angle, float directionAngle, float size, int numberOfParticles, float distanceFromOrigin, float minSpeed)
	{
		ParticleCompound* explosionCompound = new ParticleCompound();

		float angleDelta = angle / numberOfParticles;
		int randomAngleModVal = angle / numberOfParticles;

		float testingAngle = directionAngle - angle/2;

		for (int i = 0; i < numberOfParticles; i++)
		{
			float angle = Utils::DegToRad(testingAngle + (rand() % randomAngleModVal) - randomAngleModVal / 2.);

			float x = cos(angle) * distanceFromOrigin;
			float y = sin(angle) * distanceFromOrigin;

			sf::RectangleShape* particleShape = new sf::RectangleShape(sf::Vector2f(size, size));
			particleShape->setPosition(position);
			particleShape->setFillColor(color);

			float speed = ((rand() % 1000) / 100.) + minSpeed;
			Particle* pNewParticle = new Particle(*particleShape, 0.6, sf::Vector2f(x, y), speed);

			explosionCompound->AddParticle(pNewParticle);

			testingAngle += angleDelta;
		}

		AddParticleCompound(explosionCompound);
	}

#pragma endregion

}
