[Mesh]
  type = FileMesh
  file = exodus_stevens_mesh.e
  block_id = '1 2'
  block_name = 'medium cylinder'
  boundary_id = '1 2 3 4 5 6 7 8 9'
  boundary_name = '1 2 3 4 5 6 7 8 9'
 
[]

[Variables]

  [./H]
    order = FIRST
    family = LAGRANGE
  [../]

[]

[Kernels]

  [./lp1]
    type = ExternalFieldx
    variable = H
    Hx = Hx
    Hy = Hy
    Hz = Hz
    Jx = 1.0
    Jy = 1.0
    Jz = 1.0
  [../]

  [./lp2]
    type = ExternalFieldy
    variable = H
    Hx = Hx
    Hy = Hy
    Hz = Hz
    Jx = 1.0
    Jy = 1.0
    Jz = 1.0	
  [../]

  [./lp3]
    type = ExternalFieldz
    variable = H
    Hx = Hx
    Hy = Hy
    Hz = Hz
    Jx = 1.0
    Jy = 1.0
    Jz = 1.0	
  [../]

[]

[BCs]
  [./1]
    type = DirichletBC
    variable = H
    boundary = '1'
    value = -1
  [../]

  [./2]
    type = DirichletBC
    variable = H
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
