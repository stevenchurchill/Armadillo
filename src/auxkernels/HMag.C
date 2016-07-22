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
   _Hz(coupledValue("Hz")),
   _Hx_grad(coupledGradient("Hx")),
   _Hy_grad(coupledGradient("Hy")),
   _Hz_grad(coupledGradient("Hz"))
{
}

Real
HMag::computeValue()

{
    return std::pow(_Hx_grad[_qp](1)*_Hx_grad[_qp](2)+_Hy_grad[_qp](0)*_Hy_grad[_qp](2)+_Hz_grad[_qp](0)*_Hz_grad[_qp](1),0.5);
}
