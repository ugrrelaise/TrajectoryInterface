#ifndef KILINC2000_H
#define KILINC2000_H

#include "Gun.h"

class LIB_BALLISTIC_EXPORT Kilinc2000: public Gun
{
public:
    Kilinc2000()
    {
        gun_dragfunction    = "G6";
        gun_muzzle_velocity = 354.0;
        gun_balcoefficient  = 0.160;
        gun_heightofsight   = 0.0;
        gun_gunelevation1   = 0.00;
        gun_airtemperature  = 15.0;
        gun_airpressure     = 760.0;
        gun_humidity        = 60.0;
        gun_altitude        = 0;
        gun_headwindspeed   = 0.0;
        gun_crosswindspeed  = 0.0;
        gun_grapXend        = 600;
        gun_step            = 5;
        gun_gridxm          = 20;
        gun_traj_range      = 500;
        gun_range2          = 75;
        gun_wall            = 90;
        gun_scalingat45deg  = 744.914;
    }
};

#endif // KILINC2000_H
