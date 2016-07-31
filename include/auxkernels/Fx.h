#ifndef FX_H
#define FX_H

#include "AuxKernel.h"


//Forward declarations
class Fx;

template<>
InputParameters validParams<Fx>();

class Fx : public AuxKernel
{
public:
  Fx(const InputParameters & parameters);

  virtual ~Fx() {}

protected:
  virtual Real computeValue();

private:
  const VariableGradient & _mumag_grad;

};

#endif /* FX_H */
