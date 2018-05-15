/*
** EPITECH PROJECT, 2018
** MyEventReceiver
** File description:
** MyEventReceiver
*/

#ifndef MYEVENTRECEIVER_HPP_
	#define MYEVENTRECEIVER_HPP_

#include <irrlicht.h>

class MyEventReceiver : public irr::IEventReceiver
{
public:
	MyEventReceiver();
	~MyEventReceiver();
	// This is the one method that we have to implement
	virtual bool OnEvent(const irr::SEvent& event);

	// This is used to check whether a key is being held down
	virtual bool IsKeyDown(irr::EKEY_CODE keyCode) const;

private:
	// We use this array to store the current state of each key
	bool KeyIsDown[irr::KEY_KEY_CODES_COUNT];
};


#endif /* !MYEVENTRECEIVER_HPP_ */
