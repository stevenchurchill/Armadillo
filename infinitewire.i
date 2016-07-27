[Mesh]
  type = FileMesh
  file = exodus_stevens_mesh.e
[]


[GlobalParams]
    Hx = Hx
    Hy = Hy
    Hz = Hz
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
    block = '2'
    Jx = 0
    Jy = 0
    Jz = 0	
  [../]

  [./lp2]
    type = ExternalFieldy
    variable = Hy
    block = '2'
    Jx = 0
    Jy = 0
    Jz = 0		
  [../]

  [./lp3]
    type = ExternalFieldz
    variable = Hz
    block = '2'
    Jx = 0
    Jy = 0
    Jz = 0		
  [../]

  [./lpDivHx]
    type = DivHx
    variable = Hx
    block = '1'
  [../]
  [./lpDivHy]
    type = DivHy
    variable = Hy
    block = '1'	
  [../]
  [./lpDivHz]
    type = DivHz
    variable = Hz
    block = '1'	
  [../]

  [./lpDivHx1]
    type = DivHx
    variable = Hx
    block = '2'
  [../]
  [./lpDivHy1]
    type = DivHy
    variable = Hy
    block = '2'	
  [../]
  [./lpDivHz1]
    type = DivHz
    variable = Hz
    block = '2'	
  [../]



  [./lp4]
    type = ExternalFieldx
    variable = Hx
    block = '1'
    Jx = 0
    Jy = 0
    Jz = 1e-2
  [../]

  [./lp5]
    type = ExternalFieldy
    variable = Hy
    block = '1'
    Jx = 0
    Jy = 0
    Jz = 1e-2
  [../]

  [./lp6]
    type = ExternalFieldz
    variable = Hz
    block = '1'
    Jx = 0
    Jy = 0
    Jz = 1e-2
  [../]
[]


[BCs]
 # [./1]
 #   type = PresetBC
 #   variable = 'Hz'
 #   boundary = '8 9'
 #   value = 0
 # [../]

  [./2]
    type = DirichletBC
    variable = Hz
    boundary = '1 2 3 4 6 7 8 9'
    value = 0
  [../]

  [./3]
    type = DirichletBC
    variable = 'Hy Hz'
    boundary = '1 3'
    value = 0
  [../]

  [./4]
    type = DirichletBC
    variable = 'Hx Hz'
    boundary = '2 4'
    value = 0
  [../]


[]

[Preconditioning]
  [./smp]
    type = SMP
    full = true
    petsc_options = '-snes_view -snes_linesearch_monitor -snes_converged_reason -ksp_converged_reason'
    #petsc_options_iname = '-ksp_gmres_restart  -snes_rtol -ksp_rtol -pc_type -sub_pc_type   -sub_pc_factor_shift_type   -sub_pc_factor_shift_amount'
    #petsc_options_value = '    121                1e-6      1e-8    bjacobi       lu                  NONZERO                        1e-10'

    petsc_options_iname = '-snes_type -ksp_type           -ksp_rtol     -pc_type -pc_factor_shift_type -pc_factor_shift_amount -pc_factor_mat_solver_package '
    petsc_options_value = '   ksponly preonly             1e-6          lu         NONZERO               1e-12         superlu_dist '
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
