#ifndef ACTION_INFO_H
#define ACTION_INFO_H

#include "Action.h"


//Add Save Action class
class ActionInfo : public Action
{
public:
	ActionInfo(ApplicationManager *pApp);

	virtual void Execute();

};

#endif