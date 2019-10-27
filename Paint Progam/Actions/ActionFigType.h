#ifndef ACTION_FIG_TYPE_H
#define ACTION_FIG_TYPE_H

#include "Action.h"

//Add Action class
class ActionFigType : public Action
{
public:
	ActionFigType(ApplicationManager *pApp);

	//Add to the ApplicationManager
	virtual void Execute();

};

#endif