#ifndef ACTION_UNDO_H
#define ACTION_UNDO_H

#include "Action.h"

//Add Action class
class ActionUndo : public Action
{
public:
	ActionUndo(ApplicationManager *pApp);

	virtual void Execute();

};

#endif