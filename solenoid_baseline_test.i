[Mesh]
  type = FileMesh
  file = exodus_stanadyne_arm0_baseline.e
[]

[GlobalParams]
    mu = 1.0
    i = 1.0
    a = 4.45 #according to some introspective CUBITing
    loc_x = 0.0
    loc_y = 0.0
    loc_z = -1.1628 #according to some introspective CUBITing
    N =  29.0 #They have 29.5 --- WHAT DO
    solenoid_height = -5.36 #according to some introspective CUBITing
    translation_direction = 1.0 #make to a vector..
[]


[Variables]
  [./u]
    order = FIRST
    family = LAGRANGE
  [../]
[]

[AuxVariables]
  [./B_x]
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./B_y]
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./B_z]
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./H_mag]
    order = CONSTANT
    family = MONOMIAL
  [../]
[]

[AuxKernels]
  [./aux_bx]
    type = SolenoidFieldx
    variable = B_x
    execute_on = 'timestep_end'
  [../]
  [./aux_by]
    type = SolenoidFieldy
    variable = B_y
    execute_on = 'timestep_end'
  [../]
  [./aux_bz]
    type = SolenoidFieldz
    variable = B_z
    execute_on = 'timestep_end'
  [../]
  [./aux_Hmag]
    type = HMag
    variable = H_mag
    Hx = B_x
    Hy = B_y
    Hz = B_z
    execute_on = 'timestep_end'
  [../]
[]

[Kernels]
  [./u_1_kern] #Note the Kernels and BC are arbitrary. We are just using MOOSE's API to compute the fields.
    type = Diffusion
    variable = u
  [../]
[]


[BCs]
  [./bc1]
    type = DirichletBC
    variable = u
    boundary = '1'
    value = 0.0
  [../]
  [./bc2]
    type = DirichletBC
    variable = u
    boundary = '2'
    value = 1.0
  [../]
[]

[Preconditioning]
  [./smp]
    type = SMP
    full = true
    petsc_options_iname = '-snes_rtol -ksp_rtol'
    petsc_options_value = '  1e-2      1e-2 '
  [../]
[]

[Executioner]
  type = Steady
  solve_type = 'NEWTON'
[]

[Outputs]
  print_perf_log = true
  [./out]
    type = Exodus
    elemental_as_nodal = true
    execute_on = 'timestep_end'
  [../]
[]

