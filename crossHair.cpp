#include "stdafx.h"
#include "crossHair.h"

HRESULT crossHair::init()
{
	_img = IMAGEMANAGER->findImage("crossHair_Standard");
	_pos.x = _ptMouse.x;
	_pos.y = _ptMouse.y;
	return S_OK;
}

void crossHair::render()
{
	if (_isReload)
	{
		_img = IMAGEMANAGER->findImage("crossHair_Reload");
		_img->frameRender(getMemDC(), _pos.x , _pos.y , _img->getFrameX(), _img->getFrameY());

		_frameCount++;
		if (_frameCount >= 12)
		{
			_frameCount = 0;
			_img->setFrameX(_img->getFrameX() + 1);
			if (_img->getFrameX() >= _img->getMaxFrameX())
			{
				_isReload = false;
				_img->setFrameX(0);
			}

		}
	}
	else
	{
		_img = IMAGEMANAGER->findImage("crossHair_Standard");
		_img->render(getMemDC(), _pos.x, _pos.y);
	}
}

void crossHair::update()
{
	if (_isReload)
	{
		_pos.x = _ptMouse.x - _img->getFrameWidth() * 0.5f;
		_pos.y = _ptMouse.y - _img->getFrameHeight() * 0.5f;
	}
	else
	{
		_pos.x = _ptMouse.x - _img->getWidth() * 0.5f;
		_pos.y = _ptMouse.y - _img->getHeight() * 0.5f;
	}

}

void crossHair::release()
{
}
