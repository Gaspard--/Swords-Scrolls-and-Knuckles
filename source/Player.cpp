#include "Player.hpp"
#include "Logic.hpp"

void Player::checkSpells(Logic &logic)
{
  for (auto &spell : spells)
    spell.update(logic, *this);
}

void Player::setAttacking(unsigned int index, bool attacking)
{
  spells[index].active = attacking;
}

void Player::shootArrow(Logic &logic)
{
  logic.spawnArrow(pos, getDir().normalized() * 0.1);
}

int Player::getSpellCooldown(size_t i) const {
  return (spells[i].cooldown / 120);
}

Player Player::makeArcher(Vect<2u, double> pos)
{
  return Player(Vect<3u, Spell>
		(
		 Spell{[](Logic &logic, Player &player) {
		     player.shootArrow(logic);
		   }, 60},
		 Spell{[](Logic &logic, Player &player) {
		     player.shootArrow(logic);
		   }, 60},
		 Spell{[](Logic &logic, Player &player) {
		     player.shootArrow(logic);
		   }, 60}
		 ),
		100u, 0.5, pos);
}
