#ifndef MP5_H
#define MP5_H

#include "Gun.h"
class LIB_BALLISTIC_EXPORT MP5 : public Gun
{
public:
    MP5()
    {
        gun_dragfunction    = "G5";
        gun_muzzle_velocity = 400.0;
        gun_balcoefficient  = 0.149;
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
        gun_scalingat45deg  = 3792.45;
    }
};
#endif // MP5_H
