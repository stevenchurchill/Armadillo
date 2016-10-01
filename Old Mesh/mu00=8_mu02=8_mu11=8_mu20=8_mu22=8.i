[Mesh]
  type = FileMesh
  file = sphere_medium_exodus.e
  block_id = '1 2'
  block_name = 'medium sphere'
  boundary_id = '1 2 3 4 5 6 7'
  boundary_name = '1 2 3 4 5 6 7'
 
[]

[Variables]
  active = 'PhiM'

  [./PhiM]
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

  [./B_mag]
    order = CONSTANT
    family = MONOMIAL
[]

[Kernels]

  [./lp]
    type = LaplaceMat
    variable = PhiM
    block = '1'
    mu00 = 1.0
    mu01 = 0
    mu02 = 0
    mu10 = 0
    mu11 = 1.0
    mu12 = 0
    mu20 = 0
    mu21 = 0
    mu22 = 1.0
  [../]

  [./lp2]
    type = LaplaceMat
    variable = PhiM
    block = '2'
    mu00 = 8.0
    mu01 = 0
    mu02 = 8.0
    mu10 = 0
    mu11 = 8.0
    mu12 = 0
    mu20 = 8.0
    mu21 = 0
    mu22 = 8.0	
  [../]
[]

[AuxKernels]

  [./lp3]
    PhiM = PhiM
    execute_on = 'timestep_end'
    type = BxFieldAux
    variable = B_x
  [../]

  [./lp4]
    PhiM = PhiM
    execute_on = 'timestep_end'
    type = ByFieldAux
    variable = B_y
  [../]

  [./lp5]
    PhiM = PhiM
    execute_on = 'timestep_end'
    type = BzFieldAux
    variable = B_z	
  [../]

  [./lp6]
    PhiM = PhiM
    execute_on = 'timestep_end'
    type = BMag
    variable = B_mag
[]

[BCs]
  active = '1 2'
  [./1]
    type = DirichletBC
    variable = PhiM
    boundary = '1'
    value = -1
  [../]

  [./2]
    type = DirichletBC
    variable = PhiM
    boundary = '2'
    value = 1
  [../]

[]

[Executioner]
  type = Steady
  solve_type = 'PJFNK'
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
