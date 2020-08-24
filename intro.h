#pragma once
#include "gameNode.h"
class intro : public gameNode
{
private:
	image*     _img;
	animation* _anim;

public:
	intro() {}
	~intro() {}

	HRESULT init();
	void render();
	void update();
	void release();

};

