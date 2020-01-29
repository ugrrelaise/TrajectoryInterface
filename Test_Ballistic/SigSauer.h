#ifndef SIGSAUER_H
#define SIGSAUER_H

#include "Gun.h"
class LIB_BALLISTIC_EXPORT SigSauer: public Gun
{
public:
    SigSauer()
    {
        gun_dragfunction    = "G2";
        gun_muzzle_velocity = 411.0;
        gun_balcoefficient  = 0.151;
        gun_heightofsight   = 0.0;
        gun_gunelevation1   = 0.0;
        gun_airtemperature  = 15;
        gun_airpressure     = 760.0;
        gun_humidity        = 60.0;
        gun_altitude        = 0.0;
        gun_headwindspeed   = 0.0;
        gun_crosswindspeed  = 0.0;
        gun_grapXend        = 600;
        gun_step            = 5;
        gun_traj_range      = 500;
        gun_range2          = 75;
        gun_wall            = 90;
        gun_scalingat45deg  = 746.005;
    }

};
#endif // SIGSAUER_H
