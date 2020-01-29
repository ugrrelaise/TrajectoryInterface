#ifndef BORA12_H
#define BORA12_H

#include "Gun.h"

class LIB_BALLISTIC_EXPORT Bora12 :public Gun
{
public:
    Bora12()
    {
        gun_dragfunction    = "G6";
        gun_muzzle_velocity = 840.0;
        gun_balcoefficient  = 0.360;
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
        gun_scalingat45deg  = 3964.49;
    }

};
#endif // BORA12_H
