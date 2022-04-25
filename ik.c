#include "inc/ik.h"
#include "inc/stdout.h"

#define BASE_HGT 98 //base height
#define HUMERUS 118 //shoulder-to-elbow "bone"
#define ULNA 115 //elbow-to-wrist "bone"
#define GRIPPER 95 //gripper (incl.heavy duty wrist rotate mechanism) length "
const static float hum_sq = HUMERUS*HUMERUS;
const static float uln_sq = ULNA*ULNA;

void init_inv_kin() {
    x = 0;
    y = 128.0;
    z = 100.0;
    th = 10.0;
    grip = 5.0;
    inv_kin();
}

float rad_to_deg(float rad) {
    return (rad * 57296) / 1000;
}

float deg_to_rad(float deg) {
    return (deg * 1000) / 57296;
}

void inv_kin() {

   float grip_angle_r = deg_to_rad( th ); //grip angle in radians for use in calculations

   /* Base angle and radial distance from x,y coordinates */
   float bas_angle_d = rad_to_deg(atan2( x, y ));
   float rdist = sqrt(( x * x ) + ( y * y ));

   /* Grip offsets calculated based on grip angle */
   float grip_off_z = ( sin( grip_angle_r )) * GRIPPER;
   float grip_off_y = ( cos( grip_angle_r )) * GRIPPER;

   /* Wrist position */
   float wrist_z = ( z - grip_off_z ) - BASE_HGT;
   float wrist_y = y - grip_off_y;

   /* Shoulder to wrist distance ( AKA sw ) */
   float s_w = ( wrist_z * wrist_z ) + ( wrist_y * wrist_y );
   float s_w_sqrt = sqrt( s_w );

   /* s_w angle to ground */
   float a1 = atan2( wrist_z, wrist_y );

   /* s_w angle to humerus */
   float a2 = acos((( hum_sq - uln_sq ) + s_w ) / ( 2 * HUMERUS * s_w_sqrt ));

   /* shoulder angle */
   float shl_angle_r = a1 + a2;
   float shl_angle_d = rad_to_deg( shl_angle_r );

   /* elbow angle */
   float elb_angle_r = acos(( hum_sq + uln_sq - s_w ) / ( 2 * HUMERUS * ULNA ));
   float elb_angle_d = rad_to_deg( elb_angle_r );
   float elb_angle_dn = -( 180.0 - elb_angle_d );

   /* wrist angle */
   float wri_angle_d = ( th - elb_angle_dn ) - shl_angle_d;

   ang[0] = bas_angle_d + 90;
   ang[1] = shl_angle_d;
   ang[2] = elb_angle_d;
   ang[4] = wri_angle_d;
}
