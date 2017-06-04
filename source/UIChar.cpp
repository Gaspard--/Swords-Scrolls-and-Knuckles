#include "UIChar.hpp"

UIChar::UIChar(std::string const &name)
	: name(name), score(0), health(0)
{
}

std::string UIChar::getName(void) const {

	return name;
}

void UIChar::setScore(int s) {

	score = s;
}

int UIChar::getScore(void) const {

	return score;
}

void UIChar::setHealth(int h) {

	health = h;
}

int UIChar::getHealth(void) const {

	return health;
}
