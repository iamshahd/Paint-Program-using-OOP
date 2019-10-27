#ifndef ACTION_MOVE_H
#define ACTION_MOVE_H

#include "Action.h"

//Add Action class
class ActionMove : public Action
{
public:
	ActionMove(ApplicationManager *pApp);

	virtual void Execute();

};

#endif