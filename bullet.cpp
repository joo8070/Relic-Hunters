#include "stdafx.h"
#include "bullet.h"

HRESULT bullet::init()
{
	return S_OK;
}

void bullet::render()
{
	// =============================================== _viPlayerBullet =============================================================== //
	for (int i = 0; i < _vPlayerBullet.size(); i++)
	{
		if (_vPlayerBullet[i]->isFrameRender)
		{
			CAMERAMANAGER->frameRender(getMemDC(), _vPlayerBullet[i]->img, _vPlayerBullet[i]->rc.left, _vPlayerBullet[i]->rc.top, _vPlayerBullet[i]->img->getFrameX(), _vPlayerBullet[i]->img->getFrameY());
			_vPlayerBullet[i]->frameCount++;
			if (_vPlayerBullet[i]->frameCount % 20 == 0)
			{
				_vPlayerBullet[i]->frameCount = 0;
				_vPlayerBullet[i]->img->setFrameX(_vPlayerBullet[i]->img->getFrameX() + 1);

				if (_vPlayerBullet[i]->img->getFrameX() >= _vPlayerBullet[i]->img->getMaxFrameX())
				{
					_vPlayerBullet[i]->img->setFrameX(0);
				}
			}
		}
		else
		{

			CAMERAMANAGER->render(getMemDC(), _vPlayerBullet[i]->img, _vPlayerBullet[i]->rc.left, _vPlayerBullet[i]->rc.top);

		}
		if (KEYMANAGER->isToggleKey(VK_TAB))
		{
			CAMERAMANAGER->rectangle(getMemDC(), _vPlayerBullet[i]->rc);
		}
	}
	// =============================================== _viPlayerBullet =============================================================== //

	// =============================================== _vEnemyBullet =============================================================== //
	for (int i = 0; i < _vEnemyBullet.size(); i++)
	{
		if (_vEnemyBullet[i]->isFrameRender)
		{
			CAMERAMANAGER->frameRender(getMemDC(), _vEnemyBullet[i]->img, _vEnemyBullet[i]->rc.left, _vEnemyBullet[i]->rc.top, _vEnemyBullet[i]->img->getFrameX(), _vEnemyBullet[i]->img->getFrameY());
			_vEnemyBullet[i]->frameCount++;
			if (_vEnemyBullet[i]->frameCount % 20 == 0)
			{
				_vEnemyBullet[i]->frameCount = 0;
				_vEnemyBullet[i]->img->setFrameX(_vEnemyBullet[i]->img->getFrameX() + 1);

				if (_vEnemyBullet[i]->img->getFrameX() >= _vEnemyBullet[i]->img->getMaxFrameX())
				{
					_vEnemyBullet[i]->img->setFrameX(0);
				}
			}
		}
		else
		{

			CAMERAMANAGER->render(getMemDC(), _vEnemyBullet[i]->img, _vEnemyBullet[i]->rc.left, _vEnemyBullet[i]->rc.top);

		}
		if (KEYMANAGER->isToggleKey(VK_TAB))
		{
			CAMERAMANAGER->rectangle(getMemDC(), _vEnemyBullet[i]->rc);
		}
	}
	// =============================================== _vEnemyBullet =============================================================== //

	// =============================================== _vBossBullet =============================================================== //
	for (int i = 0; i < _vBossBullet.size(); i++)
	{
		if (_vBossBullet[i]->isFrameRender)
		{
			CAMERAMANAGER->frameRender(getMemDC(), _vBossBullet[i]->img, _vBossBullet[i]->rc.left, _vBossBullet[i]->rc.top, _vBossBullet[i]->img->getFrameX(), _vBossBullet[i]->img->getFrameY());
			_vBossBullet[i]->frameCount++;
			if (_vBossBullet[i]->frameCount % 20 == 0)
			{
				_vBossBullet[i]->frameCount = 0;
				_vBossBullet[i]->img->setFrameX(_vBossBullet[i]->img->getFrameX() + 1);

				if (_vBossBullet[i]->img->getFrameX() >= _vBossBullet[i]->img->getMaxFrameX())
				{
					_vBossBullet[i]->img->setFrameX(0);
				}
			}
		}
		else
		{

			CAMERAMANAGER->render(getMemDC(), _vBossBullet[i]->img, _vBossBullet[i]->rc.left, _vBossBullet[i]->rc.top);

		}
		if (KEYMANAGER->isToggleKey(VK_TAB))
		{
			CAMERAMANAGER->rectangle(getMemDC(), _vBossBullet[i]->rc);
		}
	}
	// =============================================== _vBossBullet =============================================================== //

}

void bullet::update(string nowStage)
{
	for (int i = 0; i < _vPlayerBullet.size(); i++)
	{
		_vPlayerBullet[i]->pos.x += cosf(_vPlayerBullet[i]->angle) * _vPlayerBullet[i]->speed;
		_vPlayerBullet[i]->pos.y += -sinf(_vPlayerBullet[i]->angle) * _vPlayerBullet[i]->speed;

		if (_vPlayerBullet[i]->isFrameRender) // 랜더에 따라서 렉트 크기 다르게
		{
			_vPlayerBullet[i]->rc.MYRectMakeCenter(_vPlayerBullet[i]->pos.x, _vPlayerBullet[i]->pos.y,
				_vPlayerBullet[i]->img->getFrameWidth(),
				_vPlayerBullet[i]->img->getFrameHeight());
		}
		else
		{
			_vPlayerBullet[i]->rc.MYRectMakeCenter(_vPlayerBullet[i]->pos.x, _vPlayerBullet[i]->pos.y,
				_vPlayerBullet[i]->img->getWidth(),
				_vPlayerBullet[i]->img->getHeight());
		}
		color = GetPixel(IMAGEMANAGER->findImage(nowStage + "_COLLISION")->getMemDC(), _vPlayerBullet[i]->pos.x, _vPlayerBullet[i]->pos.y);
		r = GetRValue(color);
		g = GetGValue(color);
		b = GetBValue(color);

		if (_vPlayerBullet[i]->range < getDistance(_vPlayerBullet[i]->pos.x, _vPlayerBullet[i]->pos.y,
			_vPlayerBullet[i]->firePos.x, _vPlayerBullet[i]->firePos.y) || (r == 255 && g == 0 && b == 255)) // 거리 넘어가면 지워 지게 && 픽셀 충돌
		{
			removeBullet(i);
		}
		// 픽셀 충돌
		if (r == 0 && g == 255 && b == 255)
		{
			EllipseMakeCenter(IMAGEMANAGER->findImage(nowStage + "_COLLISION")->getMemDC(), _vPlayerBullet[i]->pos.x, _vPlayerBullet[i]->pos.y,
				100, 100);

			_hbrush = CreateSolidBrush(RGB(16, 151, 181));
			_hPen = CreatePen(PS_SOLID, 1, RGB(16, 151, 181));
			_hOldbrush = (HBRUSH)SelectObject(IMAGEMANAGER->findImage(nowStage)->getMemDC(), _hbrush);
			_hOldPen = (HPEN)SelectObject(IMAGEMANAGER->findImage(nowStage)->getMemDC(), _hPen);

			EllipseMakeCenter(IMAGEMANAGER->findImage(nowStage)->getMemDC(), _vPlayerBullet[i]->pos.x, _vPlayerBullet[i]->pos.y,
				100, 100);

			SelectObject(IMAGEMANAGER->findImage(nowStage)->getMemDC(), _hOldbrush);
			SelectObject(IMAGEMANAGER->findImage(nowStage)->getMemDC(), _hOldPen);
			DeleteObject(_hPen);
			DeleteObject(_hbrush);
			removeBullet(i);
		}
	}
	// =============================================== _vPlayerBullet =============================================================== //

	// =============================================== _vEnemyBullet =============================================================== //
	for (int i = 0; i < _vEnemyBullet.size(); i++)
	{
		_vEnemyBullet[i]->pos.x += cosf(_vEnemyBullet[i]->angle) * _vEnemyBullet[i]->speed;
		_vEnemyBullet[i]->pos.y += -sinf(_vEnemyBullet[i]->angle) * _vEnemyBullet[i]->speed;

		if (_vEnemyBullet[i]->isFrameRender) // 랜더에 따라서 렉트 크기 다르게
		{
			_vEnemyBullet[i]->rc.MYRectMakeCenter(_vEnemyBullet[i]->pos.x, _vEnemyBullet[i]->pos.y,
				_vEnemyBullet[i]->img->getFrameWidth(),
				_vEnemyBullet[i]->img->getFrameHeight());
		}
		else
		{
			_vEnemyBullet[i]->rc.MYRectMakeCenter(_vEnemyBullet[i]->pos.x, _vEnemyBullet[i]->pos.y,
				_vEnemyBullet[i]->img->getWidth(),
				_vEnemyBullet[i]->img->getHeight());
		}
		color = GetPixel(IMAGEMANAGER->findImage(nowStage + "_COLLISION")->getMemDC(), _vEnemyBullet[i]->pos.x, _vEnemyBullet[i]->pos.y);
		r = GetRValue(color);
		g = GetGValue(color);
		b = GetBValue(color);

		if (_vEnemyBullet[i]->range < getDistance(_vEnemyBullet[i]->pos.x, _vEnemyBullet[i]->pos.y,
			_vEnemyBullet[i]->firePos.x, _vEnemyBullet[i]->firePos.y) || (r == 255 && g == 0 && b == 255)) // 거리 넘어가면 지워 지게 && 픽셀 충돌시
		{
			removeEnemuBullet(i);
		}

		// 픽셀 충돌

	}
	// =============================================== _vEnemyBullet =============================================================== //



	// =============================================== _vBossBullet =============================================================== //

	for (int i = 0; i < _vBossBullet.size(); i++)
	{
		_vBossBullet[i]->pos.x += cosf(_vBossBullet[i]->angle) * _vBossBullet[i]->speed;
		_vBossBullet[i]->pos.y += -sinf(_vBossBullet[i]->angle) * _vBossBullet[i]->speed;

		if (_vBossBullet[i]->isFrameRender) // 랜더에 따라서 렉트 크기 다르게
		{
			_vBossBullet[i]->rc.MYRectMakeCenter(_vBossBullet[i]->pos.x, _vBossBullet[i]->pos.y,
				_vBossBullet[i]->img->getFrameWidth(),
				_vBossBullet[i]->img->getFrameHeight());
		}
		else
		{
			_vBossBullet[i]->rc.MYRectMakeCenter(_vBossBullet[i]->pos.x, _vBossBullet[i]->pos.y,
				_vBossBullet[i]->img->getWidth(),
				_vBossBullet[i]->img->getHeight());
		}
		color = GetPixel(IMAGEMANAGER->findImage(nowStage + "_COLLISION")->getMemDC(), _vBossBullet[i]->pos.x, _vBossBullet[i]->pos.y);
		r = GetRValue(color);
		g = GetGValue(color);
		b = GetBValue(color);

		if (_vBossBullet[i]->range < getDistance(_vBossBullet[i]->pos.x, _vBossBullet[i]->pos.y,
			_vBossBullet[i]->firePos.x, _vBossBullet[i]->firePos.y) || (r == 255 && g == 0 && b == 255)) // 거리 넘어가면 지워 지게 && 픽셀 충돌시
		{
			removeBossBullet(i);
		}






		// 픽셀 충돌
	}

	// =============================================== _vBossBullet =============================================================== //

}

void bullet::release()
{
}

void bullet::playerFire(const char* imgName, int range, bool isFrameRender, MYPOINT pos, float angle, float speed, int damege)
{
	tagBullet* tempBullet = new tagBullet;
	tempBullet->imgName = imgName;
	tempBullet->isFrameRender = isFrameRender;
	tempBullet->img = IMAGEMANAGER->findImage(imgName);
	tempBullet->pos = tempBullet->firePos = pos;
	tempBullet->range = range;
	tempBullet->angle = angle;
	tempBullet->damage = damege; // (isFrameRender) ? 
	tempBullet->speed = speed;

	if (isFrameRender)
		tempBullet->rc.MYRectMakeCenter(tempBullet->pos.x, tempBullet->pos.y, tempBullet->img->getFrameWidth(), tempBullet->img->getFrameHeight());
	else
		tempBullet->rc.MYRectMakeCenter(tempBullet->pos.x, tempBullet->pos.y, tempBullet->img->getWidth(), tempBullet->img->getHeight());

	_vPlayerBullet.push_back(tempBullet);
}

void bullet::enemyFire(const char * imgName, int range, bool isFrameRender, MYPOINT pos, float angle, float speed)
{
	tagBullet* tempBullet = new tagBullet;
	tempBullet->imgName = imgName;
	tempBullet->isFrameRender = isFrameRender;
	tempBullet->img = IMAGEMANAGER->findImage(imgName);
	tempBullet->pos = tempBullet->firePos = pos;
	tempBullet->range = range;
	tempBullet->angle = angle;
	tempBullet->damage = (isFrameRender) ? RND->getFromIntTo(15, 30) : RND->getFromIntTo(8, 20);
	tempBullet->speed = speed;

	if (isFrameRender)
		tempBullet->rc.MYRectMakeCenter(tempBullet->pos.x, tempBullet->pos.y, tempBullet->img->getFrameWidth(), tempBullet->img->getFrameHeight());
	else
		tempBullet->rc.MYRectMakeCenter(tempBullet->pos.x, tempBullet->pos.y, tempBullet->img->getWidth(), tempBullet->img->getHeight());

	_vEnemyBullet.push_back(tempBullet);
}

void bullet::setBossBullet(const char * imgName, int range, bool isFrameRender, MYPOINT pos, float angle, float speed)
{
	tagBullet* tempBullet = new tagBullet;
	tempBullet->imgName = imgName;
	tempBullet->isFrameRender = isFrameRender;
	tempBullet->img = IMAGEMANAGER->findImage(imgName);
	tempBullet->pos = tempBullet->firePos = pos;
	tempBullet->range = range;
	tempBullet->angle = angle;
	tempBullet->damage = (isFrameRender) ? RND->getFromIntTo(15, 30) : RND->getFromIntTo(8, 20);
	tempBullet->speed = speed;

	if (isFrameRender)
		tempBullet->rc.MYRectMakeCenter(tempBullet->pos.x, tempBullet->pos.y, tempBullet->img->getFrameWidth(), tempBullet->img->getFrameHeight());
	else
		tempBullet->rc.MYRectMakeCenter(tempBullet->pos.x, tempBullet->pos.y, tempBullet->img->getWidth(), tempBullet->img->getHeight());

	_vBossBullet.push_back(tempBullet);
}


void bullet::removeBullet(int arrNum)
{
	if (_vPlayerBullet[arrNum]->imgName == "pistolBullet")
		EFFECTMANAGER->play("pistol_effect", _vPlayerBullet[arrNum]->pos.x, _vPlayerBullet[arrNum]->pos.y, 50, 50);
	else if (_vPlayerBullet[arrNum]->imgName == "shotgunBullet")
		EFFECTMANAGER->play("shotgun_effect", _vPlayerBullet[arrNum]->pos.x, _vPlayerBullet[arrNum]->pos.y, 50, 50);
	else
		EFFECTMANAGER->play("heavygun_effect", _vPlayerBullet[arrNum]->pos.x, _vPlayerBullet[arrNum]->pos.y, 50, 50);


	_vPlayerBullet.erase(_vPlayerBullet.begin() + arrNum);
}

void bullet::removeEnemuBullet(int arrNum)
{
	if (_vEnemyBullet[arrNum]->imgName == "pistolBullet")
		EFFECTMANAGER->play("pistol_effect", _vEnemyBullet[arrNum]->pos.x, _vEnemyBullet[arrNum]->pos.y, 50, 50);
	else if (_vEnemyBullet[arrNum]->imgName == "shotgunBullet")
		EFFECTMANAGER->play("shotgun_effect", _vEnemyBullet[arrNum]->pos.x, _vEnemyBullet[arrNum]->pos.y, 50, 50);
	else
		EFFECTMANAGER->play("heavygun_effect", _vEnemyBullet[arrNum]->pos.x, _vEnemyBullet[arrNum]->pos.y, 50, 50);

	_vEnemyBullet.erase(_vEnemyBullet.begin() + arrNum);
}

void bullet::removeBossBullet(int arrNum)
{
	if (_vBossBullet[arrNum]->imgName == "bossBullet1")
		EFFECTMANAGER->play("pistol_effect", _vBossBullet[arrNum]->pos.x, _vBossBullet[arrNum]->pos.y, 100, 100);
	else if (_vBossBullet[arrNum]->imgName == "bossBullet2")
		EFFECTMANAGER->play("shotgun_effect", _vBossBullet[arrNum]->pos.x, _vBossBullet[arrNum]->pos.y, 100, 100);
	else
		EFFECTMANAGER->play("heavygun_effect", _vBossBullet[arrNum]->pos.x, _vBossBullet[arrNum]->pos.y, 100, 100);

	_vBossBullet.erase(_vBossBullet.begin() + arrNum);
}

