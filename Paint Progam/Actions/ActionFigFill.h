#ifndef ACTION_FIG_FILL_H
#define ACTION_FIG_FILL_H

#include "Action.h"

//Add Action class
class ActionFigFill : public Action
{
public:
	ActionFigFill(ApplicationManager *pApp);

	//Add to the ApplicationManager
	virtual void Execute();

};

#endif