#include "HMag.h"


template<>

InputParameters validParams<HMag>()

{
  InputParameters params = validParams<AuxKernel>();
  params.addCoupledVar("Hx", "Magnetic Field_x");
  params.addCoupledVar("Hy", "Magnetic Field_y");
  params.addCoupledVar("Hz", "Magnetic Field_z");
  return params;
}


HMag::HMag(const InputParameters & parameters) :
  AuxKernel(parameters),
   _Hx_var(coupled("Hx")),
   _Hy_var(coupled("Hy")),
   _Hz_var(coupled("Hz")),
   _Hx(coupledValue("Hx")),
   _Hy(coupledValue("Hy")),
   _Hz(coupledValue("Hz"))
{
}

Real
HMag::computeValue()

{
    return std::pow(std::pow(_Hx[_qp],2.0)+std::pow(_Hy[_qp],2)+std::pow(_Hz[_qp],2),0.5);
}
