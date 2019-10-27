#ifndef ACTION_BACK_CLR_H
#define ACTION_BACK_CLR_H

#include "Action.h"

//Add Change Back Color Action class
class ActionBkClr : public Action
{
public:
	ActionBkClr(ApplicationManager *pApp);

	virtual void Execute();

};

#endif