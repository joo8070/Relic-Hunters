#include "stdafx.h"
#include "weapon.h"

HRESULT weapon::init(GUNTYPE type)
{
	if (type == GUNTYPE::PISTOL)
		setPistol();
	else if (type == GUNTYPE::SHOTGUN)
		setShotgun();
	else
		setHeavy();

	return S_OK;
}


void weapon::update(bool isLeft, MYPOINT pos, GUNTYPE type)
{
	if (isLeft)
	{
		_img->setFrameY(1);
		_img->setFrameX(1);
	}
	else
	{
		_img->setFrameY(0);
		_img->setFrameX(0);
	}

	if (type == GUNTYPE::PISTOL)        pos.x -= (isLeft) ? 40 : 20;   // 총 위치 잡아주기
	else if (type == GUNTYPE::SHOTGUN)	pos.x -= (isLeft) ? 70 : 30;   // 총 위치 잡아주기
	else								pos.x -= (isLeft) ? 40 : 20;   // 총 위치 잡아주기

	pos.y += 15;
	_pos = pos;

	if (_carryBulletCount <= 0 && _currentBulletCount > 0)
	{
		_isReload = true;
	}
	reload();
}

void weapon::render()
{
	CAMERAMANAGER->frameRender(getMemDC(), _img, _pos.x, _pos.y);
}

void weapon::release()
{
}

void weapon::reload()
{
	if (KEYMANAGER->isOnceKeyDown('R') && _carryBulletCount < _reloadBulletCount && _currentBulletCount > 0)
	{
		_isReload = true;
		IMAGEMANAGER->findImage("crossHair_Reload")->setFrameX(0);
	}

	if (_isReload)
	{

		_reloadTime++;


		if (_reloadTime > 132)
		{
			SOUNDMANAGER->play("장전", 0.3f);
			_reloadTime = 0;
			if (_currentBulletCount >= _reloadBulletCount)
			{
				_currentBulletCount -= _reloadBulletCount;
				_carryBulletCount = _reloadBulletCount;
			}
			else if (_currentBulletCount < _reloadBulletCount && _currentBulletCount > 0)
			{
				_carryBulletCount = _currentBulletCount;
				_currentBulletCount = 0;
			}
			else
			{
				_currentBulletCount = 0;
			}
			_isReload = false;

		}
	}

}

void weapon::setPistol()
{
	_img = IMAGEMANAGER->findImage("pistolGun");
	_fireRate = 40;
	_carryBulletCount = 15;
	_currentBulletCount = 180;
	_maxBulletCount = 270;
	_reloadBulletCount = 15;
}

void weapon::setShotgun()
{
	_img = IMAGEMANAGER->findImage("shotGun");
	_fireRate = 30;
	_carryBulletCount = 5;
	_currentBulletCount = 20;
	_maxBulletCount = 30;
	_reloadBulletCount = 5;
}

void weapon::setHeavy()
{
	_img = IMAGEMANAGER->findImage("heavyGun");
	_fireRate = 10;
	_carryBulletCount = 30;
	_currentBulletCount = 300;
	_maxBulletCount = 500;
	_reloadBulletCount = 30;
}
