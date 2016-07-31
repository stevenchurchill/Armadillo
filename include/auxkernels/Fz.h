#ifndef Fz_H
#define Fz_H

#include "AuxKernel.h"


//Forward declarations
class Fz;

template<>
InputParameters validParams<Fz>();

class Fz : public AuxKernel
{
public:
  Fz(const InputParameters & parameters);

  virtual ~Fz() {}

protected:
  virtual Real computeValue();

private:
  const VariableGradient & _mumag_grad;

};

#endif /* FZ_H */
