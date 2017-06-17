#include "Player.hpp"
#include "Logic.hpp"
#include "ProjectileList.hpp"

void Player::checkSpells(Logic &logic)
{
  for (auto &spell : spells)
    spell.update(logic, *this);
}

void Player::setAttacking(unsigned int index, bool attacking)
{
  spells[index].active = attacking;
}

Player Player::makeArcher(Vect<2u, double> pos)
{
  return Player(Vect<3u, Spell>
		(
		 Spell{[](Logic &logic, Player &player, unsigned int time) {
		     if (time == 9)
		       logic.spawnProjectile(player.getPos(), player.getDir().normalized() * 0.12, ProjectileList::ARROW);
		   }, 60, 10},
		 Spell{[](Logic &, Player &player, unsigned int time) {
		     if (!time)
		       player.dash(3.0, 30);
		     player.invulnerable = time != 29;
		   }, 240, 30},
		 Spell{[](Logic &logic, Player &player, unsigned int time) {
		     if (!(time % 20))
		       logic.spawnProjectile(player.getPos(), player.getDir().normalized() * 0.18, ProjectileList::BOUNCY_ARROW);
		   }, 2400, 480}
		 ),
		100u, 0.5, pos);
}

int Player::getSpellTimeleft(size_t i) const {
  return (spells[i].timeLeft / 12);
}

Player Player::makeMage(Vect<2u, double> pos)
{
  return Player(Vect<3u, Spell>
		(
		 Spell{[](Logic &logic, Player &player, unsigned int time) {
		     if (time == 9)
		       logic.spawnProjectile(player.getPos(), player.getDir().normalized() * 0.08, ProjectileList::ARROW);
		   }, 90, 10},
		 Spell{[](Logic &, Player &, unsigned int time) {
		     // if (!time)
		     //   player.dash(3.0, 30);
		     // player.invulnerable = time != 29;
		     std::cout << "[Player] TODO: mage spell 2" << std::endl;
		   }, 240, 30},
		 Spell{[](Logic &logic, Player &player, unsigned int time) {
		     if (!(time % 20))
		       logic.spawnProjectile(player.getPos(), {0.0, 0.0}, ProjectileList::ICE_PILLAR);
		     player.invulnerable = time != 480;
		   }, 2400, 480}
		 ),
		100u, 0.5, pos);
}

Player Player::makeTank(Vect<2u, double> pos)
{
  return Player(Vect<3u, Spell>
		(
		 Spell{[](Logic &logic, Player &player, unsigned int time) {
		     if (time == 9)
		       logic.spawnProjectile(player.getPos(), player.getDir().normalized() * 0.12, ProjectileList::ARROW);
		   }, 60, 10},
		 Spell{[](Logic &, Player &player, unsigned int time) {
		     if (!time)
		       player.dash(3.0, 30);
		     player.invulnerable = time != 29;
		   }, 240, 30},
		 Spell{[](Logic &logic, Player &player, unsigned int time) {
		     if (!(time % 20))
		       logic.spawnProjectile(player.getPos(), player.getDir().normalized() * 0.18, ProjectileList::BOUNCY_ARROW);
		   }, 2400, 480}
		 ),
		100u, 0.5, pos);
}

Player Player::makeWarrior(Vect<2u, double> pos)
{
  return Player(Vect<3u, Spell>
		(
		 Spell{[](Logic &logic, Player &player, unsigned int time) {
		     if (time == 9)
		       logic.spawnProjectile(player.getPos(), player.getDir().normalized() * 0.12, ProjectileList::ARROW);
		   }, 60, 10},
		 Spell{[](Logic &, Player &player, unsigned int time) {
		     if (!time)
		       player.dash(3.0, 30);
		     player.invulnerable = time != 29;
		   }, 240, 30},
		 Spell{[](Logic &logic, Player &player, unsigned int time) {
		     if (!(time % 20))
		       logic.spawnProjectile(player.getPos(), player.getDir().normalized() * 0.18, ProjectileList::BOUNCY_ARROW);
		   }, 2400, 480}
		 ),
		100u, 0.5, pos);
}
