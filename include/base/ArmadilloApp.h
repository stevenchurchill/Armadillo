#ifndef ARMADILLOAPP_H
#define ARMADILLOAPP_H

#include "MooseApp.h"

class ArmadilloApp;

template<>
InputParameters validParams<ArmadilloApp>();

class ArmadilloApp : public MooseApp
{
public:
  ArmadilloApp(InputParameters parameters);
  virtual ~ArmadilloApp();

  static void registerApps();
  static void registerObjects(Factory & factory);
  static void associateSyntax(Syntax & syntax, ActionFactory & action_factory);
};

#endif /* ARMADILLOAPP_H */
