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
  active = 'PhiM_x PhiM_y PhiM_z'

  [./PhiM_x]
    order = CONSTANT
    family = MONOMIAL
  [../]

  [./PhiM_y]
    order = CONSTANT
    family = MONOMIAL
  [../]

  [./PhiM_z]
    order = CONSTANT
    family = MONOMIAL
  [../]
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
    mu00 = 2.0
    mu01 = 0
    mu02 = 0
    mu10 = 2.0
    mu11 = 0
    mu12 = 0
    mu20 = 2.0
    mu21 = 2.0
    mu22 = 2.0	
  [../]
[]

[AuxKernels]

  [./lp3]
    type = BxFieldAux
    variable = PhiM_x
  [../]

  [./lp4]
    type = ByFieldAux
    variable = PhiM_y
  [../]

  [./lp5]
    type = BzFieldAux
    variable = PhiM_z	
  [../]
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
  execute_on = 'timestep_end'
  exodus = true
[]
