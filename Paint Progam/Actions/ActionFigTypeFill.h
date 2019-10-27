#ifndef ACTION_FIG_TYPE_FILL_H
#define ACTION_FIG_TYPE_FILL_H

#include "Action.h"

//Add Action class
class ActionFigTypeFill : public Action
{
public:
	ActionFigTypeFill(ApplicationManager *pApp);

	//Add to the ApplicationManager
	virtual void Execute();

};

#endif