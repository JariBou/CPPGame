#include "ParticleCompound.h"
#include "Particle.h"


namespace SFX {

	ParticleCompound::ParticleCompound()
	{
	}

	void ParticleCompound::Update(float deltaTime) {

		this->CheckLifetimes();

		for (Particle* pParticle : this->particlesList) {
			pParticle->Update(deltaTime);
		}
	}

	void ParticleCompound::Draw(sf::RenderWindow& window) {
		for (Particle* pParticle : this->particlesList) {
			float newAlpha = 1 - pParticle->GetLifePercentage();
			pParticle->UpdateAlpha(newAlpha);
			pParticle->Draw(window);
		}
	}

	void ParticleCompound::CheckLifetimes()
	{
		auto it = this->particlesList.begin();
		while (it != this->particlesList.end())
		{
			if ((*it)->CheckLife()) {
				it++;
			}
			else {
				it = this->particlesList.erase(it);
			}
		}
	}

	void ParticleCompound::AddParticle(Particle* pParticle)
	{
		this->particlesList.push_back(pParticle);
	}

	void ParticleCompound::Delete()
	{
		auto it = this->particlesList.begin();
		while (it != this->particlesList.end())
		{
			it = this->particlesList.erase(it);
		}
	}

	bool ParticleCompound::IsActive()
	{
		return this->particlesList.size() > 0;
	}

}