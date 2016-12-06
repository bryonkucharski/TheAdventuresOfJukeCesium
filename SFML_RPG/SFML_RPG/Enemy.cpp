#include "Enemy.h"

Enemy::Enemy(std::string file, std::string name,int location, int AI_ID, int aiShoot, int health, int level,Vector2f startingPosition, std::vector<RectangleShape> &obstacles) : Creature(name, file) {

	this->sprite.setTextureRect(IntRect(0, 0, 32, 32));
	this->rect.setSize(Vector2f(32, 32));

	this->bOnDeath.loadFromFile("res/Sounds/Attack3.ogg");
	this->bOnHit.loadFromFile("res/Sounds/Attack2.ogg");
	this->soundOnDeath.setBuffer(bOnDeath);
	this->soundOnHit.setBuffer(bOnHit);

	srand(time(NULL));

	this->setCurrentLocation(location);
	this->rect.setPosition(startingPosition);

	this->currentObstacles = obstacles;

	this->setSpeed(1);
	this->setAlive(true);

	this->setAI_ID(AI_ID);
	this->setShootAI(aiShoot);

	this->setMaxHealth(health);
	this->setCurrentHealth(health);
	this->setLevel(level);
	this->setDamage(level * 2);

	font.loadFromFile("res/Fonts/Vecna.otf");
	text.setFont(font);
	text.setCharacterSize(10);
	text.setFillColor(Color::White);
}
Enemy::~Enemy() {

}
void Enemy::updateEnemy(Vector2f playerPos){
	//killing enemies
	if (this->getCurrentHealth() <= 0) {
		this->setAlive(false);
		return;//so you dont update his position.
	}

	this->sprite.setPosition(Vector2f(this->rect.getPosition().x + 10, this->rect.getPosition().y + 10));

	//update text above enemy
	text.setString("Level " + std::to_string(this->getLevel()) + "\n" + this->getName() + "  " + std::to_string(this->getCurrentHealth()) + " / " + std::to_string(this->getMaxHealth()));
	text.setPosition(this->rect.getPosition().x, this->rect.getPosition().y - text.getCharacterSize());

	this->selectMovementAI(this->getAI_ID());
	this->selectShootAI(this->getShootAI(), playerPos);
}//end of update enemy

bool Enemy::isAlive() {
	return this->alive;
}
void Enemy::setAlive(bool a) {
	this->alive = a;
}

//what to do when the enemy is hit by a player bullet
void Enemy::onPlayerBulletIntersect(int damage){
	//loose health
	this->setCurrentHealth(this->getCurrentHealth() - damage);
	this->soundOnHit.play();
	
}

int Enemy::dropExp() {
	this->soundOnDeath.play();
	int exp = this->getMaxHealth() / 20 + this->getLevel();
	return exp;
}

void Enemy::setShootAI(int aiShoot) {
	this->shootAI = aiShoot;
}
int Enemy::getShootAI() {
	return this->shootAI;
}

void Enemy::selectShootAI(int aiShoot, Vector2f playerPos) {
	switch (  2 /*aiShoot*/) {
		case 1: this->shootAI1(playerPos);
			break;
		case 2: this->shootAI2(playerPos);
			break;
		case 3: this->shootAI3(playerPos);
			break;
		case 4: this->shootAI4(playerPos);
			break;
		default:
			//no ai
			break;
	};
 
}

void Enemy::shootAI1(Vector2f playerPos) {
	if (canShoot()) {
		float distX = this->getRect().getPosition().x - playerPos.x;
		float distY = this->getRect().getPosition().y - playerPos.y;
		distX = distX*distX;
		distY = distY*distY;
		float distance = sqrt(distX + distY);
		if (distance < 100) {
			//create new projectile
			Projectile * newProjectile = new Projectile("res/Projectiles/enemyProjectile.png", Vector2f(18, 18),
				Vector2f(this->rect.getPosition().x + (this->rect.getGlobalBounds().width / 2), this->rect.getPosition().y + (this->rect.getGlobalBounds().height / 2))
				, this->getDirection(), 5);
			this->addToBullets(newProjectile);
		}
	}
}//end of shootAI1

void Enemy::shootAI2(Vector2f playerPos) {
	if (canShoot()) {
		float pi = 3.14159;
		float theta;
		float playerX = playerPos.x;
		float playerY = playerPos.y;
		float enemyX = this->getRect().getPosition().x;
		float enemyY = this->getRect().getPosition().y;
		float distX = playerX - enemyX;
		float distY = playerY - enemyY;
		float trackX = distX;
		float trackY = distY;
		distX = distX*distX;
		distY = distY*distY;
		float distance = sqrt(distX + distY);
		if (distance < 150) {
			//create new projectile
			Projectile * newProjectile = new Projectile("res/Projectiles/enemyProjectile.png", Vector2f(18, 18),
				Vector2f(this->rect.getPosition().x + (this->rect.getGlobalBounds().width / 2), this->rect.getPosition().y + (this->rect.getGlobalBounds().height / 2))
				, this->getDirection(), 5);
			//newProjectile->getRect().setRotation(theta);
			float offX = trackX/256;
			float offY = trackY/256;
			newProjectile->setOffSetX(offX);
			newProjectile->setOffSetY(offY);
			this->addToBullets(newProjectile);
		}
	}
}//end of shootAI2

void Enemy::shootAI3(Vector2f playerPos) {
	if (canShoot()) {
		
	}
}//end of shootAI3

void Enemy::shootAI4(Vector2f playerPos) {
	if (canShoot()) {
		
	}
}//end of shootAI4
