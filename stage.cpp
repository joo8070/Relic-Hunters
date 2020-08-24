#include "stdafx.h"
#include "stage.h"

HRESULT stage::init()
{
	return S_OK;
}

HRESULT stage::init(string imgName, MYPOINT spawnPoint, string animName)
{

	_img = IMAGEMANAGER->findImage(imgName);
	_imgName = imgName;
	_spawnPoint = spawnPoint;
	_animName = animName;

	if (animName != "")
	{
		_animImg = IMAGEMANAGER->findImage(animName);
		_anim = new animation;
		_anim->init(_animImg->getWidth(), _animImg->getHeight(), _animImg->getFrameWidth(), _animImg->getFrameHeight());
		_anim->setDefPlayFrame(false, false);
		_anim->setFPS(1);
	}

	return S_OK;
}

void stage::render()
{

	_img = IMAGEMANAGER->findImage(_imgName);

	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		_img = IMAGEMANAGER->findImage(_imgName + "_COLLISION");

	}
	CAMERAMANAGER->render(getMemDC(), _img);
	if (_animName != "")
	{
		if (!_anim->isPlay()) return;
		CAMERAMANAGER->aniRender(getMemDC(), _animImg, CAMERAMANAGER->getX() - 400, CAMERAMANAGER->getY() - 300, _anim, false);
		_anim->frameUpdate(TIMEMANAGER->getElapsedTime() * 6);
	}

}

void stage::update()
{
}

void stage::release()
{
}
