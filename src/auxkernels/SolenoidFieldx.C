#include "SolenoidFieldx.h"

template<>

InputParameters validParams<SolenoidFieldx>()

{
  InputParameters params = validParams<AuxKernel>();
  params.addRequiredParam<Real>("N", "number of turns");
  params.addRequiredParam<Real>("a", "coil radius");
  params.addRequiredParam<Real>("i", "current");
  params.addRequiredParam<Real>("loc_x", "x coord location of bottom of solenoid");
  params.addRequiredParam<Real>("loc_y", "y coord location of bottom of solenoid");
  params.addRequiredParam<Real>("loc_z", "z coord location of bottom of solenoid");
  params.addRequiredParam<Real>("mu", "susceptibility of medium");
  params.addRequiredParam<Real>("translation_direction", "translation direction");
  params.addRequiredParam<Real>("solenoid_height", "solenoid height");
  return params;
}

SolenoidFieldx::SolenoidFieldx(const InputParameters & parameters) :
  AuxKernel(parameters),
   _N(getParam<Real>("N")),
   _a(getParam<Real>("a")),
   _i(getParam<Real>("i")),
   _loc_x(getParam<Real>("loc_x")),
   _loc_y(getParam<Real>("loc_y")),
   _loc_z(getParam<Real>("loc_z")),
   _mu(getParam<Real>("mu")),
   _translation_direction(getParam<Real>("translation_direction")),
   _solenoid_height(getParam<Real>("solenoid_height"))
{
}

Real
SolenoidFieldx::computeValue()

{
  Real x = 0.0;
  Real y = 0.0;
  Real z = 0.0;
  Real r = 0.0;
  Real alpsq = 0.0;
  Real betsq = 0.0;
  Real ksq = 0.0;
  Real C = _mu * _i / (pi);
  Real rho = 0.0;
  Real pi = 3.14159265359;
  Real asymptotK = 0.0;
  Real asymptotE = 0.0;

  Real z1 = 0.0;
  Real translation_param = _solenoid_height / _N;
  Real sum = 0.0;

  x +=  _q_point[_qp](0) - _loc_x;
  y +=  _q_point[_qp](1) - _loc_y;
  z +=  _q_point[_qp](2) - _loc_z;

  rho  += std::pow(std::pow(x, 2.0) + std::pow(y, 2.0), 0.5);
  r +=  std::pow(std::pow(x, 2.0)+ std::pow(y, 2.0)+ std::pow(z, 2.0), 0.5);

  alpsq +=  std::pow(_a, 2.0) + std::pow(r, 2.0) - 2 * _a * rho;
  betsq +=  std::pow(_a, 2.0) + std::pow(r, 2.0) + 2 * _a * rho;
  ksq +=  1.0 -  alpsq/betsq;

  asymptotK += pi / 2.0 + (pi * ksq)/8.0 + (9 * pi * std::pow(ksq, 2.0))/128.0 + ( 25.0*pi* std::pow(ksq,3.0))/512.0 + (1225.0 *pi* std::pow(ksq,4.0))/32768.0 + ( 3969.0 *pi *std::pow(ksq,5.0))/131072.0 + (53361.0* pi *std::pow(ksq,6.0))/2097152.0 + ( 184041.0 *pi* std::pow(ksq,7.0))/8388608.0 + (41409225.0* pi *std::pow(ksq,8.0))/2147483648.0;
  asymptotE += pi / 2.0 - (pi * ksq)/8.0 - (3.0 * pi * std::pow(ksq, 2.0))/128.0 - (5 * pi * std::pow(ksq,3.0))/512.0 - ( 175.0 *pi* std::pow(ksq,4.0))/32768.0 - (441.0* pi* std::pow(ksq,5.0))/131072.0 - ( 4851.0 *pi *std::pow(ksq,6.0))/2097152.0 - (14157.0* pi * std::pow(ksq,7.0))/8388608 - ( 2760615 * pi * std::pow(ksq,8.0))/2147483648.0;

  sum += (C * x * z / (2.0 * alpsq * std::pow(betsq, 0.5) * std::pow(rho, 2.0)) ) * (( std::pow(_a, 2.0) + std::pow(r, 2.0) ) * asymptotK - alpsq * asymptotE  );

  Real sum1 = 0.0;
  z1 += _q_point[_qp](2) - _loc_z;

   for (unsigned int j = 1; j < _N; ++j)
   {
     Real r = 0.0;

     Real alpsq = 0.0;
     Real betsq = 0.0;
     Real ksq = 0.0;

     Real asymptotK = 0.0;
     Real asymptotE = 0.0;

     z =  z1 + j * translation_param;

     r +=  std::pow(std::pow(x, 2.0)+ std::pow(y, 2.0)+ std::pow(z, 2.0), 0.5);

     alpsq +=  std::pow(_a, 2.0) + std::pow(r, 2.0) - 2 * _a * rho;
     betsq +=  std::pow(_a, 2.0) + std::pow(r, 2.0) + 2 * _a * rho;
     ksq +=  1.0 -  alpsq/betsq;

     asymptotK += pi / 2.0 + (pi * ksq) / 8.0 + (9 * pi * std::pow(ksq, 2.0)) / 128.0 + ( 25.0 * pi * std::pow(ksq, 3.0))/512.0 + (1225.0 * pi * std::pow(ksq, 4.0)) / 32768.0 + (3969.0 * pi * std::pow(ksq, 5.0)) / 131072.0 + (53361.0 * pi *std::pow(ksq,6.0)) / 2097152.0 + ( 184041.0 *pi* std::pow(ksq, 7.0)) / 8388608.0 + (41409225.0 * pi *std::pow(ksq,8.0))/2147483648.0;
     asymptotE += pi / 2.0 - (pi * ksq) / 8.0 - (3.0 * pi * std::pow(ksq, 2.0)) / 128.0 - (5 * pi * std::pow(ksq, 3.0))/512.0 - ( 175.0 * pi * std::pow(ksq, 4.0)) / 32768.0 - (441.0 * pi * std::pow(ksq, 5.0)) / 131072.0 - (4851.0 * pi * std::pow(ksq,6.0))/2097152.0 - (14157.0* pi * std::pow(ksq,7.0)) / 8388608 - ( 2760615 * pi * std::pow(ksq,8.0)) / 2147483648.0;

     sum1 += (C * x * z / (2.0 * alpsq * std::pow(betsq, 0.5) * std::pow(rho, 2.0)) ) * (( std::pow(_a, 2.0) + std::pow(r, 2.0) ) * asymptotK - alpsq * asymptotE  );
   }

   return sum + sum1;
}
