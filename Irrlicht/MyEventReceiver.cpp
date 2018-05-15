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
	for (irr::u32 i = 0; i < irr::KEY_KEY_CODES_COUNT; ++i)
		KeyIsDown[i] = false;
}

bool MyEventReceiver::IsKeyDown(irr::EKEY_CODE keyCode) const
{
	return KeyIsDown[keyCode];
}

bool MyEventReceiver::IsKeyUp(irr::EKEY_CODE keyCode) const
{
	return KeyIsDown[keyCode];
}

int MyEventReceiver::getIdButtonPressed() const
{
	return _idButtonPressed;
}

bool MyEventReceiver::OnEvent(const irr::SEvent& event)
{
	// Remember whether each key is down or up
	if (event.EventType == irr::EET_KEY_INPUT_EVENT) {
		KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
		KeyIsUp[event.KeyInput.Key] = !event.KeyInput.PressedDown;
	}
	if (event.EventType == irr::EET_MOUSE_INPUT_EVENT) {
		if (event.MouseInput.Event == irr::EMIE_LMOUSE_PRESSED_DOWN) {
			std::cout << "x =" << MouseState.Position.X;
			std::cout << "y =" << MouseState.Position.Y << std::endl;
		}
		if (event.MouseInput.Event == irr::EMIE_MOUSE_MOVED) {
			MouseState.Position.X = event.MouseInput.X;
			MouseState.Position.Y = event.MouseInput.Y;
		}

	}
	if (event.EventType == irr::EET_GUI_EVENT) {
		int id = event.GUIEvent.Caller->getID();
		if (event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED)
			_idButtonPressed = id;
	}
	return false;
}

MyEventReceiver::~MyEventReceiver()
{
}
