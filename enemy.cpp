#include "stdafx.h"
#include "enemy.h"

HRESULT enemy::init(string enemyName, MYPOINT pos)
{
	_enemyName = enemyName;
	_img = IMAGEMANAGER->findImage(_enemyName + "_WALK");
	_hp = _maxHp = 100;
	_pos = pos;
	_speed = 2;
	_state = ENEMYSTATE::WALK;
	_rayCastLength = 100;
	_rayCast.x = _pos.x + cosf(_angle) * _rayCastLength;
	_rayCast.y = _pos.y - sinf(_angle) * _rayCastLength;
	_rc.MYRectMakeCenter(_pos.x, _pos.y, _img->getFrameWidth() * 0.5f, _img->getFrameHeight() * 0.6f);

	_isDead = false;
	_bullet = new bullet;
	return S_OK;
}

void enemy::render()
{
	_bullet->render();
	CAMERAMANAGER->frameRender(getMemDC(), _img, _rc.left - _img->getFrameWidth() * 0.5f * 0.5f, _rc.top - _img->getFrameHeight() * 0.6f * 0.5f, _frameIndexX, _frameIndexY);
	//
	
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		CAMERAMANAGER->rectangle(getMemDC(), _rc);
	}
}

void enemy::update(string nowStageName, MYPOINT playerPos)
{
	_bullet->update(nowStageName);
	if (_state != ENEMYSTATE::EGG && _state != ENEMYSTATE::EGGDESTROY && _state != ENEMYSTATE::DEATH)
	{
		raycast(nowStageName, playerPos);
		//think(); // 안써야겠다
	}
	frameRender();
}

void enemy::release()
{

}

void enemy::raycast(string nowStageName, MYPOINT playerPos)
{
	_rayCast.x = _pos.x + cosf(_angle) * _rayCastLength;
	_rayCast.y = _pos.y - sinf(_angle) * _rayCastLength;

	COLORREF color = GetPixel(IMAGEMANAGER->findImage(nowStageName + "_COLLISION")->getMemDC(), _rayCast.x, _rayCast.y);

	int r = GetRValue(color);
	int g = GetGValue(color);
	int b = GetBValue(color);

	_isBlock = false;

	if ((r == 255 && g == 0 && b == 255))
	{
		_speed = 0;
		_state = ENEMYSTATE::IDLE;
		_isBlock = true;

	}
}

//void enemy::think()
//{
//	if (_isFollowPlayer) return;
//	_thinkCount++;
//
//	if (_thinkCount % 100 == 0)
//	{
//		if (_state != ENEMYSTATE::HIT)
//			_state = (ENEMYSTATE)(RND->getInt(2));
//		_angle = RND->getFromFloatTo(0, PI2);
//		_thinkCount = 0;
//	}
//
//	if (!_isFollowPlayer && !_isBlock)
//	{
//		if (_state == ENEMYSTATE::WALK)
//		{
//			_speed = 2;
//		}
//		else if (_state == ENEMYSTATE::IDLE)
//		{
//			_speed = 0;
//		}
//		_pos.x += cosf(_angle) * _speed;
//		_pos.y += -sinf(_angle) * _speed;
//	}
//	_rc.MYRectMakeCenter(_pos.x, _pos.y, _img->getFrameWidth() * 0.5f, _img->getFrameHeight() * 0.6f);
//}

void enemy::frameRender()
{
	_frameCount++;

	if (_frameCount % 10 == 0)
	{
		switch (_state)
		{
		case ENEMYSTATE::IDLE:
			_img = IMAGEMANAGER->findImage(_enemyName + "_IDLE");
			if (_isLeft)
			{
				_frameIndexY = 1;
				_frameIndexX--;

				if (_frameIndexX <= 0)
				{
					_frameIndexX = _img->getMaxFrameX();
				}
			}
			else
			{
				_frameIndexY = 0;
				_frameIndexX++;

				if (_frameIndexX >= _img->getMaxFrameX())
				{
					_frameIndexX = 0;
				}
			}
			break;
		case ENEMYSTATE::WALK:
			_img = IMAGEMANAGER->findImage(_enemyName + "_WALK");
			if (_isLeft)
			{
				_frameIndexY = 1;
				_frameIndexX--;

				if (_frameIndexX < 2)
				{
					_frameIndexX = _img->getMaxFrameX();
				}
			}
			else
			{
				_frameIndexY = 0;
				_frameIndexX++;

				if (_frameIndexX >= _img->getMaxFrameX())
				{
					_frameIndexX = 1;
				}
			}

			break;
		case ENEMYSTATE::ATTACK:
			_img = IMAGEMANAGER->findImage(_enemyName + "_IDLE");
			if (_isLeft)
			{		
				if (_enemyName == "boss")
				{
					_frameIndexY = 1;
					_frameIndexX--;
					if (_frameIndexX < 0)
					{
						_frameIndexX = _img->getMaxFrameX();
					}
				}
				else
				{
					_frameIndexY = 1;
					_frameIndexX = 5;
				}
			}
			else
			{
				_frameIndexY = 0;
				_frameIndexX++;

				if (_frameIndexX >= _img->getMaxFrameX())
				{
					_frameIndexX = 1;
				}
			}

			break;
		case ENEMYSTATE::HIT:
			_img = IMAGEMANAGER->findImage(_enemyName + "_HIT");
			if (_isLeft)
			{
				_frameIndexY = 1;
				if (_enemyName == "tutle1" || _enemyName == "tutle2" || _enemyName == "tutle1")
				{
					if (_frameIndexX == 0)
						_frameIndexX = 1;
					else
						_frameIndexX = 0;
				}
				else if(_enemyName == "boss")
				{
					if (_frameIndexX == 1)
						_frameIndexX = 0;
					else
						_frameIndexX = 1;
				}
				else
				{
					if (_frameIndexX == 0)
						_frameIndexX = 1;
					else
						_frameIndexX = 0;
				}

				_state = ENEMYSTATE::IDLE;
			}

			else
			{
				_frameIndexY = 0;
				if (_enemyName == "duck1" || _enemyName == "duck2" || _enemyName == "duck1")
				{
					if (_frameIndexX == 0)
						_frameIndexX = 1;
					else
						_frameIndexX = 0;
				}
				else if(_enemyName == "boss")
				{
					if (_frameIndexX == 0)
						_frameIndexX = 1;
					else
						_frameIndexX = 0;
				}
				else
				{
					if (_frameIndexX == 0)
						_frameIndexX = 1;
					else
						_frameIndexX = 0;
				}
				_state = ENEMYSTATE::IDLE;

			}
			break;
		case ENEMYSTATE::DEATH:

			_img = IMAGEMANAGER->findImage(_enemyName + "_DEATH");
			if (_isLeft)
			{
				_frameIndexY = 1;
				_frameIndexX--;

				if (_frameIndexX < 0)
				{
					_isDead = true;
					_frameIndexX = 0;
				}
			}
			else
			{
				_frameIndexY = 0;
				_frameIndexX++;

				if (_frameIndexX > _img->getMaxFrameX())
				{
					_isDead = true;
					_frameIndexX = _img->getMaxFrameX();
				}
			}
			_state = ENEMYSTATE::DEATH;
			break;
		case ENEMYSTATE::EGG:
			_img = IMAGEMANAGER->findImage(_enemyName + "_EGG");

			_frameIndexX++;

			if (_frameIndexX >= _img->getMaxFrameX() || _frameIndexX < 22)
			{
				_frameIndexX = 22;
			}
			break;
		case ENEMYSTATE::EGGDESTROY:
			_img = IMAGEMANAGER->findImage(_enemyName + "_EGG");
			_frameIndexX++;
			if (_frameIndexX >= 21)
			{
				_frameIndexX = 0;
				_state = ENEMYSTATE::IDLE;
			}
			break;
		}
		_frameCount = 0;
	}
}
