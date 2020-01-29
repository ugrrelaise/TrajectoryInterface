#ifndef MK19BOMB_H
#define MK19BOMB_H

#include "Gun.h"

class LIB_BALLISTIC_EXPORT MK19Bomb: public Gun
{
public:
    MK19Bomb()
    {
        gun_dragfunction    = "GS";
        gun_muzzle_velocity = 241.0;
        gun_balcoefficient  = 0.380;
        gun_heightofsight   = 0.0;
        gun_gunelevation1   = 0.00;
        gun_airtemperature  = 15.0;
        gun_airpressure     = 760.0;
        gun_humidity        = 60.0;
        gun_altitude        = 0;
        gun_headwindspeed   = 0.0;
        gun_crosswindspeed  = 0.0;
        gun_grapXend        = 900;
        gun_step            = 100;
        gun_traj_range      = 800;
        gun_range2          = 400;
        gun_wall            = 25;
        gun_scalingat45deg  = 3687.86;
    }

};
#endif // MK19BOMB_H
