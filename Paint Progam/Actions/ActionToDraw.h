#ifndef ACTION_TO_DRAW_H
#define ACTION_TO_DRAW_H

#include "Action.h"

//Add Switch to Play Action class
class ActionToDraw : public Action
{
public:
	ActionToDraw(ApplicationManager *pApp);

	virtual void Execute();

};

#endif