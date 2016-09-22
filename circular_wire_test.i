[Mesh]
  type = GeneratedMesh
  dim = 3
  nx = 60
  ny = 60
  nz = 60
  xmin = -10
  xmax = 10
  ymin = -10
  ymax = 10
  zmin = -10
  zmax = 10
  elem_type = HEX8
[]

[GlobalParams]
    mu = 1.0
    i = 5.0
    a = 10.0
    loc_x = 0.0
    loc_y = 0.0
    loc_z = 0.0
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
    type = CircularWireFieldx
    variable = B_x
    execute_on = 'timestep_end'
  [../]
  [./aux_by]
    type = CircularWireFieldy
    variable = B_y
    execute_on = 'timestep_end'
  [../]
  [./aux_bz]
    type = CircularWireFieldz
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
  [./u_1_kern]
    type = Diffusion
    variable = u
  [../]
[]


[BCs]
  [./bc1]
    type = DirichletBC
    variable = u
    boundary = 'top bottom'
    value = 0.0
  [../]
  [./bc2]
    type = DirichletBC
    variable = u
    boundary = 'left right'
    value = 1.0
  [../]

[]

[Preconditioning]
  [./smp]
    type = SMP
    full = true
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

[]
