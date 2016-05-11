#ifndef PLAYER_H_
#define PLAYER_H_


#include "MoveableObject.h"
#include "Weapons/Weapon.h"
#include "Vector2D.h"
#include "Singletons/InputHandler.h"
#include "Singletons/TextureManager.h"
#include "Singletons/GameTimeHelper.h"
#include "Utils/TiposDefinidos.h"
#include "Weapons/BasicWeapon.h"


class Player : public MoveableObject
{
public:

	//constructor sin argumento: setea m_controllable siempre en true
    Player();
    //constructor que permite determinar si el player reacciona o no a eventos de input. Si se puede o no controlar
    Player(bool canControl);
    virtual ~Player() {}

    virtual void load(int x, int y, int width, int height, int textureID, int numFrames);

    virtual void draw();
    virtual void update();
    virtual void handleInput(InputMessage dataMsg);
    virtual void clean();

    void sendDrawMessage(bool isAlive);

    virtual void collision();

    void setConnected(bool connected) { m_connected = connected; }
    void setShootingSpeed(int speed);
    void setShootingCooldown(int cooldown);
    //Getters
    bool isDead() { return m_dead; }
    bool isDying() { return m_dying; }
    bool isConnected() { return m_connected; }


private:

    Weapon* m_currentWeapon;
    Vector2D m_shootOffset;
    // Determina si el usuario puede controlar este player o no. Sirve por si hay varias instancias de Player en juego.
    // Si m_controllable es false, el Player no reaccionará a eventos de Input
    bool m_connected;
    bool m_doingFlip;

    //Tiempo de animacion de giro
    int m_flipAnimationTime;
    int m_flipRemainingTime;

    //UN timer para esperar un par de milisegundos desde que el jguador dejo de moverse para arrastrarlo
    const int m_holdQuietTimer;
    int m_currentHoldQuietTime;

    void updateFlipAnimation();

    // variables de control de estado
    bool m_dead;
    bool m_dying;

    //Modifica el estado del juego de acuerdo al input del jugador
};


#endif /* PLAYER_H_ */
