/*
** EPITECH PROJECT, 2018
** MyEventReceiver
** File description:
** MyEventReceiver
*/

#ifndef MYEVENTRECEIVER_HPP_
	#define MYEVENTRECEIVER_HPP_

#include <irrlicht.h>
#include <iostream>

class MyEventReceiver : public irr::IEventReceiver
{
public:
	MyEventReceiver();
	~MyEventReceiver();
	// This is the one method that we have to implement
	virtual bool 						OnEvent(const irr::SEvent& event);

	// This is used to check whether a key is being held down
	virtual bool 						IsKeyDown(irr::EKEY_CODE keyCode) const;
	virtual bool 						IsKeyUp(irr::EKEY_CODE keyCode) const;
	int 								getIdButtonPressed() const;
	void 								resetIdButtonPressed();
	const irr::SEvent::SJoystickEvent	&GetJoystickState(void) const;

private:
	struct SMouseState
	{
		irr::core::position2di Position;
		bool LeftButtonDown;
		SMouseState() : LeftButtonDown(false) { }
	} MouseState;
	// We use this array to store the current state of each key
	bool						KeyIsDown[irr::KEY_KEY_CODES_COUNT];
	bool 						KeyIsUp[irr::KEY_KEY_CODES_COUNT];
	int 						_idButtonPressed = -1;
	irr::SEvent::SJoystickEvent JoystickState;
};


#endif /* !MYEVENTRECEIVER_HPP_ */
