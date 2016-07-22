[Mesh]
  type = FileMesh
  file = exodus_stevens_mesh.e
  block_id = '1 2'
  block_name = 'cube cylinder'
  boundary_id = '1 2 3 4 5 6 7 8 9'
  boundary_name = '1 2 3 4 5 6 7 8 9'
 
[]

[Variables]

  [./Hx]
    order = FIRST
    family = LAGRANGE
  [../]

  [./Hy]
    order = FIRST
    family = LAGRANGE
  [../]

  [./Hz]
    order = FIRST
    family = LAGRANGE
  [../]

[]

[Kernels]

  [./lp1]
    type = ExternalFieldx
    variable = Hx
    block = '1'
    Hx = Hx
    Hy = Hy
    Hz = Hz
    Jx = 0
    Jy = 0
    Jz = 1e-4	
  [../]

  [./lp2]
    type = ExternalFieldy
    variable = Hy
    block = '1'
    Hx = Hx
    Hy = Hy
    Hz = Hz
    Jx = 0
    Jy = 0
    Jz = 1e-4		
  [../]

  [./lp3]
    type = ExternalFieldz
    variable = Hz
    block = '1'
    Hx = Hx
    Hy = Hy
    Hz = Hz
    Jx = 0
    Jy = 0
    Jz = 1e-4		
  [../]

  [./lp4]
    type = ExternalFieldx
    variable = Hx
    block = '2'
    Hx = Hx
    Hy = Hy
    Hz = Hz
    Jx = 0
    Jy = 0
    Jz = 0	
  [../]

  [./lp5]
    type = ExternalFieldy
    variable = Hy
    block = '2'
    Hx = Hx
    Hy = Hy
    Hz = Hz
    Jx = 0
    Jy = 0
    Jz = 0
  [../]

  [./lp6]
    type = ExternalFieldz
    variable = Hz
    block = '2'
    Hx = Hx
    Hy = Hy
    Hz = Hz
    Jx = 0
    Jy = 0
    Jz = 0	
  [../]
[]

[BCs]
  [./1]
    type = DirichletBC
    variable = 'Hx Hy Hz'
    boundary = '1'
    value = 0
  [../]

  [./2]
    type = DirichletBC
    variable = 'Hx Hy Hz'
    boundary = '2'
    value = 0
  [../]

  [./3]
    type = DirichletBC
    variable = 'Hx Hy Hz'
    boundary = '3'
    value = 0
  [../]

  [./4]
    type = DirichletBC
    variable = 'Hx Hy Hz'
    boundary = '4'
    value = 0
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
