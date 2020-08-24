#include "stdafx.h"
#include "boss.h"

HRESULT boss::init(string enemyName, MYPOINT pos)
{
	enemy::init(enemyName, pos);
	_hp = _maxHp = 4000;
	_eggHP = 10;
	_state = ENEMYSTATE::EGG;
	_gunImg = IMAGEMANAGER->findImage("bossGun");
	_progressBar = new progressBar;
	_progressBar->init(_rc.left - 30, _rc.top - 100, 4000, 400);

	return S_OK;
}

void boss::render()
{
	enemy::render();

	if (_state != ENEMYSTATE::EGG && _state != ENEMYSTATE::EGGDESTROY && _state != ENEMYSTATE::DEATH)
	{
		if (_isLeft)
			CAMERAMANAGER->frameRender(getMemDC(), _gunImg, _rc.left - 130, _rc.top + 60, 1, 0);
		else
			CAMERAMANAGER->frameRender(getMemDC(), _gunImg, _rc.left + 20, _rc.top + 60, 0, 0);
		_progressBar->render();
	}
}

void boss::update(string nowStageName, MYPOINT playerPos)
{
	enemy::update(nowStageName, playerPos);

	_progressBar->setGauge(_hp, _maxHp);
	_progressBar->update();
	_progressBar->setX(_rc.left - 30);
	_progressBar->setY(_rc.top - 100);


	if (_state != ENEMYSTATE::EGG && _state != ENEMYSTATE::EGGDESTROY && _state != ENEMYSTATE::DEATH)
	{
		findPlayer(playerPos);

		_fireCount++;
		if (_hp < 5100 && _hp > 1000)
		{
			attack1(playerPos);
		}

		if (_hp > 1000 && _hp < 2500)
		{
			attack2(playerPos);
		}
		else if (_hp > 0 && _hp <= 1000)
		{
	
			attack3(playerPos);
		}
		
	}
	if (_hp <= 0 && _state != ENEMYSTATE::DEATH)
	{
		_state = ENEMYSTATE::DEATH;
		if (_isLeft)
		{
			_frameIndexX = 12;
		}
		else
		{
			_frameIndexX = 0;
		}
	}
}

void boss::release()
{
}

void boss::attack1(MYPOINT playerPos)
{
	if (_fireCount % 50 == 0)
	{
		_fireCount = 0;
		MYPOINT temp = _pos;
		temp.y += 25;
		if (_isLeft)
		{
			temp.x -= 250;
		}
		else
		{
			temp.x += 250;
		}
		_angle = getAngle(temp.x, temp.y, playerPos.x, playerPos.y);
		_bullet->setBossBullet("bossBullet2", 3000, false, temp, _angle, 6);
	}
}

void boss::attack2(MYPOINT playerPos)
{
	if (_fireCount % 50 == 0)
	{
		_angle = 0;
		for (int i = 0; i < 30; i++)
		{
			_angle += PI2 / 30;

			_bullet->setBossBullet("bossBullet3", 3000, true, _pos, _angle, 6);
		}

		_fireCount = 0;
	}
}

void boss::attack3(MYPOINT playerPos)
{
	if (_fireCount % 5 == 0)
	{
		_fireCount = 0;
		MYPOINT temp = _pos;
		temp.y += 25;
		if (_isLeft)
		{
			temp.x -= 250;
		}
		else
		{
			temp.x += 250;
		}

		_angle = getAngle(temp.x, temp.y, playerPos.x, playerPos.y) + RND->getFromFloatTo(-0.3f,0.3f);
		_bullet->setBossBullet("bossBullet3", 3000, true, temp, _angle, 7);

	}
}

void boss::findPlayer(MYPOINT playerPos)
{
	if (!_isBlock && (getDistance(_pos.x, _pos.y, playerPos.x, playerPos.y) <= 900))
	{
		_angle = getAngle(_pos.x, _pos.y, playerPos.x - 26, playerPos.y - 60);

		if (_pos.x <= playerPos.x) _isLeft = false;
		else					   _isLeft = true;

		if (!_isFindEffect)
		{
			EFFECTMANAGER->play("findPlayerBoss_effect", _pos.x, _rc.top - 100);

			_isFindEffect = true;
		}
		_speed = 1.0f;

		if (getDistance(_pos.x, _pos.y, playerPos.x, playerPos.y) <= 600)
		{
			_speed = 0.0f;
		}

		if (_speed > 0)
		{
			_state = ENEMYSTATE::WALK;
		}

		else if (_speed <= 0)
		{
			_state = ENEMYSTATE::ATTACK;
		}

		_pos.x += cosf(_angle) * _speed;
		_pos.y += -sinf(_angle) * _speed;
	}
	else if (getDistance(_pos.x, _pos.y, playerPos.x, playerPos.y) > 800)
	{
		_isFindEffect = false;
	}

	_rc.MYRectMakeCenter(_pos.x, _pos.y, _img->getFrameWidth() * 0.5f, _img->getFrameHeight() * 0.6f);
}

void boss::patternChange()
{
}

