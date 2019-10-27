#ifndef ACTION_TO_PLAY_H
#define ACTION_TO_PLAY_H

#include "Action.h"

//Add Switch to Play Action class
class ActionToPlay : public Action
{
public:
	ActionToPlay(ApplicationManager *pApp);

	virtual void Execute();

};

#endif