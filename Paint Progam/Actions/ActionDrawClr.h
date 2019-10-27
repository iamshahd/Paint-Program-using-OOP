#ifndef ACTION_DRAW_CLR_H
#define ACTION_DRAW_CLR_H

#include "Action.h"

//Add Change Draw Color Action class
class ActionDrawClr : public Action
{
public:
	ActionDrawClr(ApplicationManager *pApp);

	virtual void Execute();
	
};

#endif