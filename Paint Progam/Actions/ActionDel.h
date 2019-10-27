#ifndef ACTION_DELETE_H
#define ACTION_DELETE_H

#include "Action.h"

//Add Delete Action class
class ActionDel : public Action
{
public:
	ActionDel(ApplicationManager *pApp);

	virtual void Execute();

};

#endif