#include "stdafx.h"
#include "gruntEnemy.h"

HRESULT gruntEnemy::init(string enemyName, MYPOINT pos)
{
	enemy::init(enemyName, pos);
	_progressBar = new progressBar;
	_progressBar->init(_rc.left - 30, _rc.top - 50, 100, 10);


	return S_OK;
}

void gruntEnemy::render()
{
	enemy::render();
	if (_state != ENEMYSTATE::EGG && _state != ENEMYSTATE::EGGDESTROY && _state != ENEMYSTATE::DEATH)
	{
		_progressBar->render();
	}
}

void gruntEnemy::update(string nowStageName, MYPOINT playerPos)
{
	enemy::update(nowStageName, playerPos);
	_progressBar->setGauge(_hp, _maxHp);
	_progressBar->update();
	_progressBar->setX(_rc.left - 30);
	_progressBar->setY(_rc.top - 50);

	if (_state != ENEMYSTATE::EGG && _state != ENEMYSTATE::EGGDESTROY && _state != ENEMYSTATE::DEATH)
	{
		findPlayer(nowStageName, playerPos);

	}
}

void gruntEnemy::release()
{
	enemy::release();
}

void gruntEnemy::findPlayer(string nowStageName, MYPOINT playerPos)
{
	if (!_isBlock && (getDistance(_pos.x, _pos.y, playerPos.x, playerPos.y) <= 800))
	{
		_angle = getAngle(_pos.x, _pos.y, playerPos.x - 26, playerPos.y - 60);

		if (_pos.x <= playerPos.x) _isLeft = false;
		else					   _isLeft = true;

		_speed = 1.0f;

		if (getDistance(_pos.x, _pos.y, playerPos.x, playerPos.y) <= 500)
		{
			if (!_isFindEffect)
			{
				EFFECTMANAGER->play("findPlayer_effect", _pos.x, _rc.top - 50);
				_isFindEffect = true;
			}
			_speed = 0.0f;
			fire(playerPos);
		}


		if (_speed > 0)
		{
			if (_state != ENEMYSTATE::HIT)
				_state = ENEMYSTATE::WALK;
		}

		else if (_speed <= 0)
		{
			if (_state != ENEMYSTATE::HIT)
				_state = ENEMYSTATE::ATTACK;
		}

		_pos.x += cosf(_angle) * _speed;
		_pos.y += -sinf(_angle) * _speed;
	}
	else if(getDistance(_pos.x, _pos.y, playerPos.x, playerPos.y) > 800)
	{
		_isFindEffect = false;
	}
	_rc.MYRectMakeCenter(_pos.x, _pos.y, _img->getFrameWidth() * 0.5f, _img->getFrameHeight() * 0.6f);
}

void gruntEnemy::fire(MYPOINT pos)
{
	_fireCount++;
	if (_fireCount % 100 == 0)
	{
		_fireCount = 0;
		float angle = getAngle(_pos.x, _pos.y, pos.x, pos.y);

		if (_enemyName == "tutle1" || _enemyName == "duck1")
		{
			_bullet->enemyFire("pistolBullet", 2000, false, _pos, angle, 10);
		}
		else if (_enemyName == "tutle2" || _enemyName == "duck2")
		{
			_bullet->enemyFire("heavyBullet", 2000, true, _pos, angle, 10);
		}
		else if (_enemyName == "boss")
		{
			_bullet->enemyFire("heavyBullet", 3000, true, _pos, angle, 5);
		}
		else
		{
			_bullet->enemyFire("shotgunBullet", 1000, false, _pos, angle - 0.4f, 20);
			_bullet->enemyFire("shotgunBullet", 1000, false, _pos, angle - 0.2f, 20);
			_bullet->enemyFire("shotgunBullet", 1000, false, _pos, angle, 20);
			_bullet->enemyFire("shotgunBullet", 1000, false, _pos, angle + 0.2f, 20);
			_bullet->enemyFire("shotgunBullet", 1000, false, _pos, angle + 0.2f, 20);
		}
	}
}
