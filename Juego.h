#pragma once
#include "stdafx.h"
#include "Jugador.h"
#include "Enemigo.h"

using namespace sf;

class Juego {
	RenderWindow* _wnd;
	Jugador* _jugador;
	Enemigo* _enemigos;
	Font _fuente;
	Text _puntaje;
	int _puntos;

	void _actualizarPuntaje() {
		char pts[100];
		_itoa_s(_puntos, pts, 10);
		_puntaje.setString(pts);
	}
public:
	Juego() {
		_wnd = new RenderWindow(VideoMode(800, 600), "Crosshair y Enemigos");
		_jugador = new Jugador();
		_enemigos = new Enemigo[5];
		_puntos = 0;
		_fuente.loadFromFile("Fantasik.otf");
		_puntaje.setFont(_fuente);
		_puntaje.setPosition(20.0f, 20.0f);
		_puntaje.setCharacterSize(50);
		_puntaje.setFillColor(Color::Black);
		_actualizarPuntaje();
	}
	void Loop() {
		_wnd->setMouseCursorVisible(false);

		while (_wnd->isOpen()) {
			ProcesarEventos();
			Actualizar();
			Dibujar();
		}
	}
	void ProcesarEventos() {
		Event evt;
		while (_wnd->pollEvent(evt)) {
			switch (evt.type) {
			case Event::Closed:
				_wnd->close();
				break;
			case Event::MouseMoved:
				_jugador->Posicionar((float)evt.mouseMove.x, (float)evt.mouseMove.y);
				break;
			case Event::MouseButtonPressed:
				if (evt.mouseButton.button == Mouse::Button::Left)
					Disparar();
				break;
			}
		}
	}
	void Actualizar() {
		//Actualiza la posicion del Crosshair
		for (size_t i = 0; i < 10; i++) {
			_enemigos[i].Actualizar(_wnd);
		}
	}
	void Disparar() {
		//Chequeamos colisiones con el disparo
		Vector2f jugadorPos = _jugador->ObtenerPosicion();
		for (int i = 0; i < 10; i++) {
			if (_enemigos[i].EstaActivo()) {
				if (_enemigos[i].EstaEncima(jugadorPos.x, jugadorPos.y)) {
					_enemigos[i].Derrotar();
					_puntos++;
				}
			}
		}
		_actualizarPuntaje();
	}
	void Dibujar() {
		_wnd->clear(Color::White);

		//Dibujar los elementos del juego

		for (int i = 0; i < 10; i++) {
			if (_enemigos[i].EstaActivo())
				_enemigos[i].Dibujar(_wnd);
		}

		_wnd->draw(_puntaje);
		_jugador->Dibujar(_wnd);
		_wnd->display();
	}
	~Juego() {
		delete _enemigos;
		delete _jugador;
		delete _wnd;
	}
};