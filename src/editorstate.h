#ifndef EDITORSTATE_H
#define EDITORSTATE_H

#include <memory>
#include "../externals/json/json.h"
#include "state.h"
#include "timer.h"
#include "map.h"
#include "uiobjectmanager.h"

class EditorState : public State{
	EditorState();
	~EditorState();
};

#endif