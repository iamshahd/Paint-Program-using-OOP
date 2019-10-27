#ifndef ACTION_RESTART_H
#define ACTION_RESTART_H

#include "Action.h"

//Add Action class
class ActionRestart : public Action
{
public:
	ActionRestart(ApplicationManager *pApp);

	//Add to the ApplicationManager
	virtual void Execute();

};

#endif