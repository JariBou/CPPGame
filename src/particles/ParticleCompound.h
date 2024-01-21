#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

namespace SFX{

	class Particle;

	class ParticleCompound {
	public:
		ParticleCompound();
		void Update(float deltaTime);
		void Draw(sf::RenderWindow& window);
		void CheckLifetimes();

		void AddParticle(Particle* pParticle);

		void Delete();

		/// <summary>
		/// Returns true if the compound has active Particles
		/// </summary>
		/// <returns></returns>
		bool IsActive();
	private:
		std::vector<Particle*> particlesList;

	};

}