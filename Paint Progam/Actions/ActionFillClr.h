#ifndef ACTION_FILL_CLR_H
#define ACTION_FILL_CLR_H

#include "Action.h"

//Add Change Fill Color Action class
class ActionFillClr : public Action
{
public:
	ActionFillClr(ApplicationManager *pApp);

	virtual void Execute();

};

#endif