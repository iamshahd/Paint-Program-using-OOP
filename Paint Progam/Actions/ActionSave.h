#ifndef ACTION_SAVE_H
#define ACTION_SAVE_H

#include "Action.h"

#include <fstream>
using namespace std;

//Add Save Action class
class ActionSave : public Action
{
public:
	ActionSave(ApplicationManager *pApp);

	virtual void Execute();

};

#endif