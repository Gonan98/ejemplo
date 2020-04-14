#include "Enemigo.h"

Enemigo::Enemigo() : Entidad(){
	da�o = 0;
	vida = 5;
	tipo = TipoEnemigo::ORCO;
}
Enemigo::Enemigo(Animacion* animacion, sf::Texture &t, TipoEnemigo tipo, int x, int y) : Entidad(animacion, t, x, y) {
	vida = 5;
	da�o = 0;
	this->tipo = tipo;
	switch (this->tipo)
	{
	case TipoEnemigo::ORCO:
		vida = 15;
		da�o = 3;
		dx = dy = 6;
		break;
	case TipoEnemigo::ESQUELETO:
		vida = 10;
		da�o = 3;
		dx = dy = 6;
		break;
	case TipoEnemigo::MURCIELAGO:
		vida = 5;
		da�o = 2;
		dx = dy = 12;
		break;
	case TipoEnemigo::ESPECTRO:
		vida = 10;
		da�o = 4;
		dx = dy = 8;
		break;
	case TipoEnemigo::SEGADOR:
		vida = 10;
		da�o = 5;
		dx = dy = 8;
		break;
	}
}
Enemigo::~Enemigo(){}

int Enemigo::getDa�o() { return da�o; }
int Enemigo::getVida() { return vida; }

void Enemigo::setDa�o(int value) { da�o = value; }
void Enemigo::setVida(int value) { vida = value; }

void Enemigo::dibujar(sf::RenderWindow& w, int** matriz){
	mover(matriz);
	sprite.setTextureRect(animacion->update(TipoEntidad::ENEMIGO));
	w.draw(sprite);
}
void Enemigo::mover(int** matriz){
	switch (animacion->getTipoMovimiento())
	{
	case Movimiento::ARRIBA:
		if (matriz[(y - dy) / 48][(x + dx) / 48] != 1 && matriz[(y - dy) / 48][(x + ancho - dx) / 48] != 1)
			y -= dy;
		else {
			direccion_random();
		}
		break;
	case Movimiento::ABAJO:
		if (matriz[(y + alto) / 48][(x + dx) / 48] != 1 && matriz[(y + alto) / 48][(x + ancho - dx) / 48] != 1)
			y += dy;
		else {
			direccion_random();
		}
		break;
	case Movimiento::DERECHA:
		if (matriz[(y) / 48][(x + ancho) / 48] != 1 && matriz[(y + alto - dy) / 48][(x + ancho) / 48] != 1)
			x += dx;
		else {
			direccion_random();
		}
		break;
	case Movimiento::IZQUIERDA:
		if (matriz[(y) / 48][(x - dx) / 48] != 1 && matriz[(y + alto - dy) / 48][(x - dx) / 48] != 1)
			x -= dx;
		else {
			direccion_random();
		}
		break;
	case Movimiento::NINGUNO:
		break;
	}
	sprite.setPosition((float)x, (float)y);
}

void Enemigo::direccion_contra(Movimiento tipo) {
	switch (tipo)
	{
	case Movimiento::NINGUNO:
		break;
	case Movimiento::ARRIBA:
		animacion->setTipoMovimiento(Movimiento::ABAJO);
		break;
	case Movimiento::ABAJO:
		animacion->setTipoMovimiento(Movimiento::ARRIBA);
		break;
	case Movimiento::DERECHA:
		animacion->setTipoMovimiento(Movimiento::IZQUIERDA);
		break;
	case Movimiento::IZQUIERDA:
		animacion->setTipoMovimiento(Movimiento::DERECHA);
		break;
	default:
		break;
	}
}

void Enemigo::direccion_random() {
	Movimiento temp = animacion->getTipoMovimiento();
	animacion->setTipoMovimiento(Movimiento(rand() % 4 + 1));
	if (temp == animacion->getTipoMovimiento())
		direccion_contra(animacion->getTipoMovimiento());
}