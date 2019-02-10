#pragma once
#include "GraficObject.h"

enum PROYECTILE_TYPE {SNOW, FIRE};		// ¿la bola es un proyectil?

enum PROYECTILE_STATE {proy_MOVING, proy_DECAYING, proy_IMPACT, proy_FALLING};		// el proyectil decae cuando se detiene a los 3 casilleros y se cae


class Obj_Graf_Projectile :
	public Obj_Graf
{
public:
	Obj_Graf_Projectile();
	Obj_Graf_Projectile(double ID, PROYECTILE_TYPE type);
	~Obj_Graf_Projectile();

	void draw();
	void startDraw(Direction dir, void *state, POINT& pos);
	void destroy();
	void reset();
	bool secuenceOver();

private:
	PROYECTILE_TYPE type;
	PROYECTILE_STATE state;
	void loadBitmap(PROYECTILE_TYPE type);						// dependiendo del enemigo se le cargan determinadas imagenes
	ALLEGRO_BITMAP ** moveImages = NULL;
	ALLEGRO_BITMAP ** decayImages = NULL;
	ALLEGRO_BITMAP ** impactImages = NULL;
	ALLEGRO_BITMAP ** fallImages = NULL;
	unsigned int actualImpactImage;										// cuando se inicia la secuancia de impacto tiene que empezar si o si de 0 (el actualImage puede no estar en 0)
	unsigned int actualDecayImage;
};

