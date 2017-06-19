#include "Action.hpp"
#include "Player.hpp"
#include <iostream>

void Action::update()
{
  Vect<2u, double> input{0.0, 0.0};

  for (auto &jsCtrld : joystickControlled)
  {
    input = {
      jsCtrld.first->getAxes()[joystickAxe::LEFT_HRZ] / 100.f,
      jsCtrld.first->getAxes()[joystickAxe::LEFT_VRT] / 100.f,
    };
    if (input.length2() <= 0.20f * 0.20f) // Joystick axes are never really at 0
      input = { 0.f, 0.f };
    jsCtrld.second->setInput(input * 0.03 * (1.f + jsCtrld.second->isMounted()));
    try { jsCtrld.second->setMounted((*jsCtrld.first)[joystickState::JS_Y]); }
    catch (std::out_of_range const &) {}
    try { jsCtrld.second->setAttacking(0u, (*jsCtrld.first)[joystickState::JS_X]); }
    catch (std::out_of_range const &) {}
    try { jsCtrld.second->setAttacking(1u, (*jsCtrld.first)[joystickState::JS_A]); }
    catch (std::out_of_range const &) {}
    try { jsCtrld.second->setAttacking(2u, (*jsCtrld.first)[joystickState::JS_B]); }
    catch (std::out_of_range const &) {}
    try { jsCtrld.second->setLocked((*jsCtrld.first)[joystickState::JS_RB]); }
    catch (std::out_of_range const &) {}
  }
  for (auto &kbCtrld : keyboardControlled)
  {
    input = {0.0, 0.0};
    if (Keyboard::getKeys()[kbCtrld.first->keymap[KBACTION::GO_UP]])
      input += {0.0, -1.0};
    if (Keyboard::getKeys()[kbCtrld.first->keymap[KBACTION::GO_LEFT]])
      input += {-1.0, 0.0};
    if (Keyboard::getKeys()[kbCtrld.first->keymap[KBACTION::GO_DOWN]])
      input += {0.0, 1.0};
    if (Keyboard::getKeys()[kbCtrld.first->keymap[KBACTION::GO_RIGHT]])
      input += {1.0, 0.0};
    kbCtrld.second->setInput(input * 0.03 * (1.f + kbCtrld.second->isMounted()));
    kbCtrld.second->setAttacking(0u, Keyboard::getKeys()[kbCtrld.first->keymap[KBACTION::SPELL1]]);
    kbCtrld.second->setAttacking(1u, Keyboard::getKeys()[kbCtrld.first->keymap[KBACTION::SPELL2]]);
    kbCtrld.second->setAttacking(2u, Keyboard::getKeys()[kbCtrld.first->keymap[KBACTION::SPELL3]]);
    kbCtrld.second->setLocked(Keyboard::getKeys()[kbCtrld.first->keymap[KBACTION::LOCK]]);
    kbCtrld.second->setMounted(Keyboard::getKeys()[kbCtrld.first->keymap[KBACTION::MOUNT]]);
  }
}
