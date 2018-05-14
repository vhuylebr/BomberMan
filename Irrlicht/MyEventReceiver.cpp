/*
** EPITECH PROJECT, 2018
** MyEventReceiver
** File description:
** MyEventReceiver
*/

#include "MyEventReceiver.hpp"

MyEventReceiver::MyEventReceiver()
{
	for (irr::u32 i = 0; i < irr::KEY_KEY_CODES_COUNT; ++i)
		KeyIsDown[i] = false;
}

bool MyEventReceiver::IsKeyDown(irr::EKEY_CODE keyCode) const
{
	return KeyIsDown[keyCode];
}

bool MyEventReceiver::OnEvent(const irr::SEvent& event)
{
	// Remember whether each key is down or up
	if (event.EventType == irr::EET_KEY_INPUT_EVENT) {
		KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
	}
	return false;
}

MyEventReceiver::~MyEventReceiver()
{
}
