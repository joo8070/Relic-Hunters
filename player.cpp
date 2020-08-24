#include "stdafx.h"
#include "player.h"
#include "stageManager.h"

HRESULT player::init()
{
	// ------------------- 임시 변수 삭제 ------------------- //

	_pos.x = 1000;
	_pos.y = 1050;
	_img = IMAGEMANAGER->findImage("jimmy_IDLE");
	_rc.MYRectMakeCenter(_pos.x, _pos.y, 40, 50);
	_staus.speed = 5;
	_staus.hp = _staus.maxHp = 200;
	// ------------------- 임시 변수 삭제 ------------------- //
	_name = "jimmy";
	_coin = 1000;
	_ptMouse.x += _pos.x;
	_ptMouse.y += _pos.y;
	_img = IMAGEMANAGER->findImage(_name + "_IDLE");

	// 픽셀충돌 변수
	_probeYTop = _pos.y - _img->getFrameHeight() * 0.2f;
	_probeYBottom = _pos.y + _img->getFrameHeight() / 2;
	_probeXLeft = _pos.x - _img->getFrameWidth() * 0.3f;
	_probeXRight = _pos.x + _img->getFrameWidth() * 0.3f;
	// 픽셀충돌 변수

	gunSetting();
	_bullet = new bullet;
	_bullet->init();

	_crossHair = new crossHair;
	_crossHair->init();


	return S_OK;
}

void player::update()
{
	if (_staus.hp >= _staus.maxHp)
	{
		_staus.hp = _staus.maxHp;
	}

	//if (_staus.hp > 0)
	{
		move();
		collision();
		_weapon[_myWeaponType]->update(_isLeft, _pos, _myWeaponType);
	}

	



	playerFrameRender();

	_bullet->update(_stageManager->getNowStage());
	_crossHair->update();
	CAMERAMANAGER->setX(_pos.x); // 카메라 셋팅
	CAMERAMANAGER->setY(_pos.y);
	_rc.MYRectMakeCenter(_pos.x, _pos.y, 40, 50);


	if (_staus.hp <= 0)
	{
		_staus.hp = 0;
		//_state = STATE::DEATH;

	}



}

void player::render()
{
	if (_isAiming)
	{
		POINT ptPos;
		ptPos.x = _ptMouse.x + CAMERAMANAGER->getL();
		ptPos.y = _ptMouse.y + CAMERAMANAGER->getT();
	}
	_bullet->render();
	CAMERAMANAGER->frameRender(getMemDC(), _img, _rc.left - 33, _rc.top - 50, _img->getFrameX(), _img->getFrameY());
	if (!_isDead)
	{
		_weapon[_myWeaponType]->render();
	}
	_crossHair->render();
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		CAMERAMANAGER->rectangle(getMemDC(), _rc);
	}
	//CAMERAMANAGER->ellipse(getMemDC(), _pos.x, _probeYTop, 10, 10);
	//CAMERAMANAGER->ellipse(getMemDC(), _pos.x, _probeYBottom, 10, 10);

	if (_isShot)
	{
		CAMERAMANAGER->shakeCamera(2, 10);
	}
}

void player::release()
{
}


void player::move()
{
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		_state = STATE::WALK;

		_pos.x -= _staus.speed;
	}
	if (KEYMANAGER->isOnceKeyUp('A'))
	{
		_state = STATE::IDLE;
	}


	if (KEYMANAGER->isStayKeyDown('D'))
	{
		_state = STATE::WALK;
		_pos.x += _staus.speed;
	}
	if (KEYMANAGER->isOnceKeyUp('D'))
	{
		_state = STATE::IDLE;
	}

	if (KEYMANAGER->isStayKeyDown('W'))
	{
		_state = STATE::WALK;
		_pos.y -= _staus.speed;
	}
	if (KEYMANAGER->isOnceKeyUp('W'))
	{
		_state = STATE::IDLE;
	}

	if (KEYMANAGER->isStayKeyDown('S'))
	{
		_state = STATE::WALK;
		_pos.y += _staus.speed;
	}
	if (KEYMANAGER->isOnceKeyUp('S'))
	{
		_state = STATE::IDLE;
	}


	if (KEYMANAGER->isStayKeyDown(VK_SHIFT))
	{
		if (_state != STATE::RUN)
		{
			if (_isLeft)
				EFFECTMANAGER->play("runR_Effect", _pos.x + 40, _pos.y + 30, 50, 50);
			else
				EFFECTMANAGER->play("runL_Effect", _pos.x - 40, _pos.y + 30, 50, 50);
		}

		_state = STATE::RUN;
		_staus.speed = 8;

	}
	if (KEYMANAGER->isOnceKeyUp(VK_SHIFT))
	{
		_state = STATE::IDLE;
		_staus.speed = 5;
	}

	if (KEYMANAGER->isStayKeyDown(VK_RBUTTON))
	{
		_isAiming = true;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_RBUTTON))
	{
		_isAiming = false;
	}


	// ---------------- 플레이어 방향
	if (_ptMouse.x - WINSIZEX / 2 >= 0) _isLeft = false;
	else _isLeft = true;
	// ---------------- 플레이어 방향

	gunControl();

}

void player::spawnPos(MYPOINT pos)
{
	_pos = pos;
	_staus.hp = _staus.maxHp;
	_isDead = false;

}

void player::collision()
{
	_probeYTop = _pos.y - _img->getFrameHeight() * 0.2f;
	_probeYBottom = _pos.y + _img->getFrameHeight() * 0.3f;
	_probeXLeft = _pos.x - _img->getFrameWidth() * 0.3f;
	_probeXRight = _pos.x + _img->getFrameWidth() * 0.3f;

	// --------------------------- 픽셀 충돌 top --------------------------- //
	color = GetPixel(IMAGEMANAGER->findImage(_stageManager->getNowStage() + "_COLLISION")->getMemDC(), _pos.x, _probeYTop);

	r = GetRValue(color);
	g = GetGValue(color);
	b = GetBValue(color);

	if ((r == 255 && g == 0 && b == 255) || (r == 0 && g == 255 && b == 255))
	{
		_pos.y = _probeYTop + _img->getFrameHeight()  * 0.2f + _staus.speed;

	}
	// --------------------------- 픽셀 충돌 top --------------------------- //


	// --------------------------- 픽셀 충돌 bottom --------------------------- //
	color = GetPixel(IMAGEMANAGER->findImage(_stageManager->getNowStage() + "_COLLISION")->getMemDC(), _pos.x, _probeYBottom);
	r = GetRValue(color);
	g = GetGValue(color);
	b = GetBValue(color);

	if ((r == 255 && g == 0 && b == 255) || (r == 0 && g == 255 && b == 255))
	{
		_pos.y = _probeYBottom - _img->getFrameHeight() * 0.3f - _staus.speed;

	}
	// --------------------------- 픽셀 충돌 bottom --------------------------- //

	// --------------------------- 픽셀 충돌 left --------------------------- //
	color = GetPixel(IMAGEMANAGER->findImage(_stageManager->getNowStage() + "_COLLISION")->getMemDC(), _probeXLeft, _pos.y);
	r = GetRValue(color);
	g = GetGValue(color);
	b = GetBValue(color);

	if ((r == 255 && g == 0 && b == 255) || (r == 0 && g == 255 && b == 255))
	{
		_pos.x = _probeXLeft + _img->getFrameWidth() * 0.3f + _staus.speed;

	}
	// --------------------------- 픽셀 충돌 left --------------------------- //

	// --------------------------- 픽셀 충돌 right --------------------------- //
	color = GetPixel(IMAGEMANAGER->findImage(_stageManager->getNowStage() + "_COLLISION")->getMemDC(), _probeXRight, _pos.y);
	r = GetRValue(color);
	g = GetGValue(color);
	b = GetBValue(color);

	if ((r == 255 && g == 0 && b == 255) || (r == 0 && g == 255 && b == 255))
	{
		_pos.x = _probeXRight - _img->getFrameWidth() * 0.3f - _staus.speed;

	}
	// --------------------------- 픽셀 충돌 right --------------------------- //


}

void player::playerFrameRender()
{
	_frameCount++;
	if (_frameCount % 10 == 0)
	{
		switch (_state)
		{
		case STATE::IDLE:
			_img = IMAGEMANAGER->findImage(_name + "_IDLE");
			if (_isLeft)
			{
				_img->setFrameY(1);
				_img->setFrameX(_img->getFrameX() - 1);
				if (_img->getFrameX() < 0)
				{
					_img->setFrameX(_img->getMaxFrameX());
				}
			}
			else
			{
				_img->setFrameY(0);
				_img->setFrameX(_img->getFrameX() + 1);
				if (_img->getFrameX() >= _img->getMaxFrameX())
				{
					_img->setFrameX(0);
				}
			}
			break;
		case STATE::WALK:
			_img = IMAGEMANAGER->findImage(_name + "_WALK");
			if (_isLeft)
			{
				_img->setFrameY(1);
				_img->setFrameX(_img->getFrameX() - 1);
				if (_img->getFrameX() < 0)
				{
					_img->setFrameX(_img->getMaxFrameX());
				}
			}
			else
			{
				_img->setFrameY(0);
				_img->setFrameX(_img->getFrameX() + 1);
				if (_img->getFrameX() >= _img->getMaxFrameX())
				{
					_img->setFrameX(0);
				}
			}
			break;
		case STATE::RUN:
			_img = IMAGEMANAGER->findImage(_name + "_RUN");
			if (_isLeft)
			{
				_img->setFrameY(1);
				_img->setFrameX(_img->getFrameX() - 1);
				if (_img->getFrameX() < 0)
				{
					_img->setFrameX(_img->getMaxFrameX());
				}
			}
			else
			{
				_img->setFrameY(0);
				_img->setFrameX(_img->getFrameX() + 1);
				if (_img->getFrameX() >= _img->getMaxFrameX())
				{
					_img->setFrameX(0);
				}
			}
			break;
		case STATE::DASH:
			_img = IMAGEMANAGER->findImage(_name + "_DASH");
			if (_isLeft)
			{
				_img->setFrameY(1);
				_img->setFrameX(_img->getFrameX() - 1);
				if (_img->getFrameX() < 0)
				{
					_img->setFrameX(_img->getMaxFrameX());
				}
			}
			else
			{
				_img->setFrameY(0);
				_img->setFrameX(_img->getFrameX() + 1);
				if (_img->getFrameX() >= _img->getMaxFrameX())
				{
					_img->setFrameX(0);
				}
			}
			break;
		case STATE::HIT:
			_img = IMAGEMANAGER->findImage(_name + "_HIT");
			if (_isLeft)
			{
				_img->setFrameY(1);
				_img->setFrameX(_img->getFrameX() - 1);
				if (_img->getFrameX() < 0)
				{
					_img->setFrameX(_img->getMaxFrameX());
					_state = STATE::IDLE;
				}
			}
			else
			{
				_img->setFrameY(0);
				_img->setFrameX(_img->getFrameX() + 1);
				if (_img->getFrameX() >= _img->getMaxFrameX())
				{
					_img->setFrameX(0);
					_state = STATE::IDLE;
				}
			}
			break;
		case STATE::HOLO:
			_img = IMAGEMANAGER->findImage(_name + "_HOLO");
			if (_isLeft)
			{
				_img->setFrameY(1);
				_img->setFrameX(_img->getFrameX() - 1);
				if (_img->getFrameX() < 0)
				{
					_img->setFrameX(_img->getMaxFrameX());
				}
			}
			else
			{
				_img->setFrameY(0);
				_img->setFrameX(_img->getFrameX() + 1);
				if (_img->getFrameX() >= _img->getMaxFrameX())
				{
					_img->setFrameX(0);
				}
			}
			break;
		case STATE::TELEPORT:
			_img = IMAGEMANAGER->findImage(_name + "_TELEPORT");
			if (_isLeft)
			{
				_img->setFrameY(1);
				_img->setFrameX(_img->getFrameX() - 1);
				if (_img->getFrameX() < 0)
				{
					_img->setFrameX(_img->getMaxFrameX());

				}
			}
			else
			{
				_img->setFrameY(0);
				_img->setFrameX(_img->getFrameX() + 1);
				if (_img->getFrameX() >= _img->getMaxFrameX())
				{
					_img->setFrameX(0);

				}
			}
			break;
		case STATE::DEATH:
			_img = IMAGEMANAGER->findImage(_name + "_DEATH");
			if (_isLeft)
			{
				_img->setFrameY(1);
				_img->setFrameX(_img->getFrameX() - 1);
				if (_img->getFrameX() < 0)
				{
					_img->setFrameX(0);
					_isDead = true;
				}
			}
			else
			{
				_img->setFrameY(0);
				_img->setFrameX(_img->getFrameX() + 1);
				if (_img->getFrameX() >= _img->getMaxFrameX())
				{
					_img->setFrameX(_img->getMaxFrameX());
					_isDead = true;
				}
			}
			break;
		}


		_frameCount = 0;
	}

}

void player::refreshCenter()
{
	_pos.x = (_rc.left + _rc.right) / 2;
	_pos.y = (_rc.top + _rc.bottom) / 2;

	CAMERAMANAGER->setXY(_pos.x , _pos.y); // 카메라 셋팅
}

void player::gunSetting()
{
	_weapon[GUNTYPE::PISTOL] = new weapon;
	_weapon[GUNTYPE::PISTOL]->init(GUNTYPE::PISTOL);
	_weapon[GUNTYPE::SHOTGUN] = new weapon;
	_weapon[GUNTYPE::SHOTGUN]->init(GUNTYPE::SHOTGUN);
	_weapon[GUNTYPE::HEAVY] = new weapon;
	_weapon[GUNTYPE::HEAVY]->init(GUNTYPE::HEAVY);

	_myWeaponType = GUNTYPE::PISTOL;
}

void player::gunControl()
{
	_fireRateCount++;
	_weapon[_myWeaponType];
	//if (KEYMANAGER->isOnceKeyDown('1'))
	//{
	//	_myWeaponType = PISTOL;
	//}
	//if (KEYMANAGER->isOnceKeyDown('2'))
	//{
	//	_myWeaponType = SHOTGUN;
	//}
	//if (KEYMANAGER->isOnceKeyDown('3'))
	//{
	//	_myWeaponType = HEAVY;
	//}
	_isShot = false;
	_crossHair->setIsReload(_weapon[_myWeaponType]->getIsReload());

	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		if (_weapon[_myWeaponType]->getFireRate() > _fireRateCount) return;
		if (_weapon[_myWeaponType]->getIsReload() || _weapon[_myWeaponType]->getCarryBullet() <= 0)
		{
			return;
		}
		_isShot = true;
		_weapon[_myWeaponType]->setCarryBullet(_weapon[_myWeaponType]->getCarryBullet() - 1);

		_fireRateCount = 0;
		_ptPos.x = CAMERAMANAGER->getL() + _ptMouse.x;
		_ptPos.y = CAMERAMANAGER->getT() + _ptMouse.y;

		float angle = getAngle(_pos.x, _pos.y, _ptPos.x, _ptPos.y);

		MYPOINT tempPos = _pos;
		tempPos.y += 25;
		int damege = RND->getFromIntTo(15, 30);
		if (KEYMANAGER->isToggleKey('P'))
		{
			damege = 100;
		}
		if (_myWeaponType == PISTOL)
		{
			if (_isLeft) tempPos.x -= 50;
			else         tempPos.x += 55;

			_bullet->playerFire("pistolBullet", 2000, false, tempPos, angle, 20, damege);
			SOUNDMANAGER->play("권총", 0.1f);
		}
		else if (_myWeaponType == SHOTGUN)
		{
			if (_isLeft) tempPos.x -= 65;
			else         tempPos.x += 75;

			_bullet->playerFire("shotgunBullet", 1000, false, tempPos, angle - 0.4f, 30, damege);
			_bullet->playerFire("shotgunBullet", 1000, false, tempPos, angle - 0.2f, 30, damege);
			_bullet->playerFire("shotgunBullet", 1000, false, tempPos, angle, 30, damege);
			_bullet->playerFire("shotgunBullet", 1000, false, tempPos, angle + 0.2f, 30, damege);
			_bullet->playerFire("shotgunBullet", 1000, false, tempPos, angle + 0.4f, 30, damege);
			SOUNDMANAGER->play("샷건", 0.1f);
		}
		else
		{
			tempPos.y -= 10;
			if (_isLeft) tempPos.x -= 55;
			else         tempPos.x += 28;
			angle += RND->getFromFloatTo(-0.1f, 0.1f);
			_bullet->playerFire("heavyBullet", 3000, true, tempPos, angle, 20, damege);
			SOUNDMANAGER->play("권총", 0.1f);
		}

	}

}


void player::statusInit(CHARACTER charName)
{
	if (charName == JIMMY) // 지미 선택 시 스텟
	{

	}
	else                   // 다른 캐릭터 선택 시 스텟
	{

	}

}
