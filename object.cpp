#include "stdafx.h"
#include "object.h"

HRESULT object::init(MYPOINT pos, const char* objectName, bool isFrameRender, OBJECTKIND kind)
{
	_objectName = objectName;
	_pos = pos;
	_img = IMAGEMANAGER->findImage(objectName);
	_kind = kind;
	_isFrameRender = isFrameRender;

	if (_isFrameRender)  _rc.MYRectMake(_pos.x, _pos.y, _img->getFrameWidth(), _img->getFrameHeight() - 50); // 프레임 랜더 O
	else                 _rc.MYRectMake(_pos.x, _pos.y, _img->getWidth(), _img->getHeight());				 // 프레임 랜더 X

	if (_kind == BOX) _damage = 0; // 충돌 가능 
	else _damage = 100;


	return S_OK;
}

void object::render()
{
	if (_isFrameRender)
	{
		_frameCount++;
		CAMERAMANAGER->frameRender(getMemDC(), _img, _rc.left, _rc.top, _frameX, 0);
		if (_frameCount % 7 == 0)
		{
			if (!(_kind == BOX)) // 박스는 총알 충돌 처리 후 랜더링.
			{
				_frameX++;
				if (_frameX >= _img->getMaxFrameX())
					_frameX = 0;

				if (_kind == COLLAPSE)
				{
					_isRemove = true;
				}
	
			}
			else
			{
				if (_damage >= 2)
				{
					_frameX++;
					_damage = 0;
					if (_frameX > 2)
					{
						_img = IMAGEMANAGER->findImage(_objectName + "Collapse");
						_kind = COLLAPSE;
					}
				}
			}
			_frameCount = 0;
		}

	}
	else
	{
		CAMERAMANAGER->render(getMemDC(), _img, _pos.x, _pos.y);
	}
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		CAMERAMANAGER->rectangle(getMemDC(), _rc);
	}
}

void object::update()
{

}

void object::release()
{

}
