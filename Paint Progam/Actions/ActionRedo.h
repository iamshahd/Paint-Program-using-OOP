#ifndef ACTION_REDO_H
#define ACTION_REDO_H

#include "Action.h"

//Add Action class
class ActionRedo : public Action
{
public:
	ActionRedo(ApplicationManager *pApp);

	virtual void Execute();

};

#endif