#ifndef ACTION_ADD_HEX_H
#define ACTION_ADD_HEX_H

#include "Action.h"

//Add Hexagon Action class
class ActionAddHex : public Action
{
public:
	ActionAddHex(ApplicationManager *pApp);

	//Add Hexagon to the ApplicationManager
	virtual void Execute();

};

#endif