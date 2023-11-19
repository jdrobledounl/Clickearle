#pragma once
#include "stdafx.h"

using namespace sf;

class Jugador {
	Texture _miraTex;
	Sprite _miraSprite;

public:
	Jugador() {
		_miraTex.loadFromFile("crosshair.png");
		_miraSprite.setTexture(_miraTex);
		_miraSprite.setScale(0.5f, 0.5f);
		Vector2u size = _miraTex.getSize();
		_miraSprite.setOrigin(size.x/2.0f, size.y/2.0f);
	}

	void Dibujar(RenderWindow *wnd) {
		wnd->draw(_miraSprite);
	}

	void Posicionar(float x, float y) {
		_miraSprite.setPosition(x, y);
	}

	Vector2f ObtenerPosicion() {
		return _miraSprite.getPosition();
	}

};