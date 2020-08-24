#include "stdafx.h"
#include "item.h"

HRESULT item::init(string imgName, MYPOINT pos, ITEMTYPE type, string nowStageName)
{
	_imgName = imgName;
	_stageName = nowStageName;
	_pos = _dropStartPos = pos;
	_type = type;
	_angle = RND->getFromFloatTo(PI * 0.5f - 0.09f, PI * 0.5f + 0.09f);
	_gravity = 0.01f;
	if (_type == ITEM_GUN)
	{
		_rc.MYRectMakeCenter(_pos.x, _pos.y, IMAGEMANAGER->findImage(_imgName)->getFrameX(), IMAGEMANAGER->findImage(_imgName)->getHeight());
		_isFrameImg = false;
	}
	else
	{
		_isFrameImg = true;
		_rc.MYRectMakeCenter(_pos.x, _pos.y, IMAGEMANAGER->findImage(_imgName)->getFrameWidth(), IMAGEMANAGER->findImage(_imgName)->getFrameHeight());
	}
	return S_OK;
}

void item::render()
{
	if (_isFrameImg)
	{
		CAMERAMANAGER->frameRender(getMemDC(), IMAGEMANAGER->findImage(_imgName), _rc.left, _rc.top, _frameX, 0);
	}
	else
	{
		CAMERAMANAGER->render(getMemDC(), IMAGEMANAGER->findImage(_imgName), _rc.left, _rc.top);
	}
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		CAMERAMANAGER->rectangle(getMemDC(), _rc);
	}
}

void item::update()
{
	switch (_type)
	{
	case ITEM_GUN:
		break;
	case ITEM_COIN:
		updateCoinItem();
		break;
	case ITEM_HP:
		updateHPItem();
		break;
	case ITEM_BULLET:
		updateBulletItem();
		break;
	case ITEM_RELIC:
		break;
	}
}

void item::release()
{

}

void item::updateCoinItem()
{
	_count++;
	if (_count % 5 == 0)
	{
		_frameX++;

		if (_frameX >= IMAGEMANAGER->findImage(_imgName)->getMaxFrameX())
			_frameX = 0;
	}
	if (getDistance(_dropStartPos.x, _dropStartPos.y, _pos.x, _pos.y) <= 100)
	{
		_gravity -= 0.003f;
		_pos.x += cosf(_angle) * 10.0f;
		_pos.y += -sinf(_angle) *10.0f * _gravity;
	}

	_rc.MYRectMakeCenter(_pos.x, _pos.y, IMAGEMANAGER->findImage(_imgName)->getFrameWidth(), IMAGEMANAGER->findImage(_imgName)->getFrameHeight());

}

void item::updateHPItem()
{
	if (_isPlayerGet)
	{
		_count++;

		if (_count % 10 == 0)
		{
			_frameX++;
			if (_frameX >= IMAGEMANAGER->findImage(_imgName)->getMaxFrameX())
			{
				_frameX = IMAGEMANAGER->findImage(_imgName)->getMaxFrameX();
				_isDisappear = true;
			}
		}
	}
}

void item::updateBulletItem()
{
	if (_isPlayerGet)
	{
		_count++;

		if (_count % 10 == 0)
		{
			_frameX++;
			if (_frameX >= IMAGEMANAGER->findImage(_imgName)->getMaxFrameX())
			{
				_frameX = IMAGEMANAGER->findImage(_imgName)->getMaxFrameX();
				_isDisappear = true;
			}
			
		}
	}
}
