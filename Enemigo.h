#pragma once
#include "stdafx.h"

using namespace sf;

class Enemigo {
	Texture _enemigoTex;
	Sprite _enemigoSprite;
    bool _estaVivo;
    bool _estaVisible;
    sf::Clock _clock;
    float _tiempoVisible;
    float _tiempoApagado;
    Vector2f _randomPos(Vector2u maxPos) {
        Vector2f random((float)(rand() % maxPos.x), (float)(rand() % maxPos.y));
        return random;
    }
public:
    Enemigo() {
        _enemigoTex.loadFromFile("et.png");
        _enemigoSprite.setTexture(_enemigoTex);
        _enemigoSprite.setScale(0.1f, 0.1f);
        _estaVivo = true;
        _estaVisible = false;
        _tiempoVisible = 2.0f;
        _tiempoApagado = 0.5f;

    }

	bool EstaVivo() {
		return _estaVivo;
	}

    bool EstaActivo() {
        return _estaVivo && _estaVisible;
    }

    bool EstaEncima(float x, float y) {
        sf::FloatRect bounds = _enemigoSprite.getGlobalBounds();
        return bounds.contains(x, y);
    }

    void Derrotar() {
        _estaVivo = false;
    }

    void Dibujar(RenderWindow* _wnd) {
        _wnd->draw(_enemigoSprite);
    }

    void Actualizar(RenderWindow* _wnd) {
        if (!_estaVivo)
            return;
        if (!_estaVisible) {//tiramos una probabilidad para ver si la activamos
            if (_clock.getElapsedTime().asSeconds() > _tiempoApagado) {
                _clock.restart();
                if (rand() % 100 < 25) {
                    _estaVisible = true;
                    _enemigoSprite.setPosition(_randomPos(_wnd->getSize()));
                }

            }

        }
        else {
            if (_clock.getElapsedTime().asSeconds() > _tiempoVisible) {
                _estaVisible = false;
                _clock.restart();
            }
        }
    }

};
