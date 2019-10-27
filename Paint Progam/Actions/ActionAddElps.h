#ifndef ACTION_ADD_ELPS_H
#define ACTION_ADD_ELPS_H

#include "Action.h"

//Add Elipse Action class
class ActionAddElps : public Action
{
public:
	ActionAddElps(ApplicationManager *pApp);

	//Add Elipse to the ApplicationManager
	virtual void Execute();

};

#endif