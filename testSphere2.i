[Mesh]
  type = FileMesh
  file = sphere_medium_exodus.e
  block_id = '1 2'
  block_name = 'medium sphere'
  boundary_id = '1 2 3 4 5 6 7'
  boundary_name = '1 2 3 4 5 6 7'
 
[]

[Variables]
  active = 'PhiM PhiM2'

  [./PhiM]
    order = FIRST
    family = LAGRANGE
  [../]

  [./PhiM2]
    order = FIRST
    family = LAGRANGE
  [../]
[]

[Kernels]

  [./lp]
    type = LaplaceMat
    variable = PhiM
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
    type = LaplaceMat2
    variable = PhiM2
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
[]

[BCs]
  active = '1 2 3 4 5 6 7'
  [./1]
    type = DirichletBC
    variable = PhiM
    boundary = '1'
    value = 10
  [../]

  [./2]
    type = DirichletBC
    variable = PhiM
    boundary = '2'
    value = 10
  [../]

  [./3]
    type = DirichletBC
    variable = PhiM
    boundary = '3'
    value = 10
  [../]

  [./4]
    type = DirichletBC
    variable = PhiM
    boundary = '4'
    value = -10
  [../]

  [./5]
    type = DirichletBC
    variable = PhiM
    boundary = '5'
    value = -10
  [../]

  [./6]
    type = DirichletBC
    variable = PhiM
    boundary = '6'
    value = -10
  [../]

  [./7]
    type = DirichletBC
    variable = PhiM2
    boundary = '7'
    value = 0
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
