#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>
#include "DrawableEntity.h"

class GameManager;

namespace Entities {
    class Player; // Assurez-vous que la classe Player est d�clar�e avant Bullet

    class Bullet : public DrawableEntity {
        public:
            int damage;
            float speed;
            bool shouldDestroy = false;
            Bullet(sf::Shape& shape, Player& player); // Utilisation d'une r�f�rence constante
            Bullet(sf::Shape& shape, GameManager* pGameManager, int damage, float speed, sf::Vector2f Direction, int WindowWidth); // Utilisation d'une r�f�rence constante
            virtual ~Bullet() = default;
            virtual bool MoveBullet(float deltaTime);
            virtual void Update(float deltaTime);
            virtual bool CheckLife();
            virtual bool CheckHit();
            void ShotByEnemy() {
                shotByPlayer = false;
            }
            GameManager* gameManager;
            Player* player; // Utilisation d'une r�f�rence constante
    private :
			sf::Vector2f direction;
            bool shotByPlayer = true;
            int windowWidth;
            /*int windowHeight;*/
       
};
}