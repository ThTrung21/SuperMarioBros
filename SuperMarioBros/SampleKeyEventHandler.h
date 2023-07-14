#pragma once

#include "Scene.h"

class CSampleKeyHandler: public CSceneKeyHandler
{
public:
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	CSampleKeyHandler(LPSCENE s) :CSceneKeyHandler(s) {};
};
class CSampleKeyHandlerMap : public CSceneKeyHandler {
public:
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	CSampleKeyHandlerMap(LPSCENE s) :CSceneKeyHandler(s) {};
};
