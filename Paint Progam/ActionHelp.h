#ifndef ACTION_HELP_H
#define ACTION_HELP_H

#include "Action.h"

class ActionHelp : public Action
{
public:

	ActionHelp(ApplicationManager *pApp);

	virtual void Execute();
};
#endif
