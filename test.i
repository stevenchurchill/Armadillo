[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 125 #number of elements along x
  ny = 125 #number of elements along y
  xmin = -12
  xmax = 12
  ymin = -12
  ymax = 12
 
[]

[Variables]
  active = 'PhiM'

  [./PhiM]
    order = FIRST
    family = LAGRANGE
  [../]
[]

[Kernels]

  [./lp]
    type = laplace
    variable = PhiM
    mu = 1.0
  [../]
[]

[BCs]
  active = 'bottom top'
  #left right bottom top front back (+x, -x, +y, -y, +z, -z)
  [./bottom]
    type = DirichletBC
    variable = PhiM
    boundary = 'bottom'
    value = 10
  [../]

  [./top]
    type = DirichletBC
    variable = PhiM
    boundary = 'top'
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
