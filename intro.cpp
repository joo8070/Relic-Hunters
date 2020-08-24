#include "stdafx.h"
#include "intro.h"

HRESULT intro::init()
{
	_img = IMAGEMANAGER->findImage("intro");
	_anim = new animation;
	_anim->init(_img->getWidth(), _img->getHeight(), _img->getFrameWidth(), _img->getFrameHeight());
	_anim->setDefPlayFrame(false, true);
	_anim->setFPS(1);

	_anim->start();
	return S_OK;
}

void intro::render()
{
	_img->aniRender(getMemDC(), 0, 0, _anim);
}

void intro::update()
{
	_anim->frameUpdate(TIMEMANAGER->getElapsedTime() * 6);
}

void intro::release()
{
}
