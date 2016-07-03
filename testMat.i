[Mesh]
  type = GeneratedMesh
  dim = 3
  nx = 15 #number of elements along x
  ny = 15 #number of elements along y
  nz = 15 #number of elements along z
  xmin = -12
  xmax = 12
  ymin = -12
  ymax = 12
  zmin = -12
  zmax = 12
 
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
