[Mesh]
  type = FileMesh
  file = exodus_stevens_mesh.e
  #uniform_refine = 1
[]

[GlobalParams]
    Ax = Ax
    Ay = Ay 
    Az = Az
[]


[Variables]
  [./Ax]
    order = FIRST
    family = LAGRANGE
  [../]
  [./Ay]
    order = FIRST
    family = LAGRANGE
  [../]
  [./Az]
    order = FIRST
    family = LAGRANGE
  [../]
  [./Q]
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
[]

[AuxKernels]
  [./aux_bx]
    type = BxCurlA
    variable = B_x
  [../]
  [./aux_by]
    type = ByCurlA
    variable = B_y
  [../]
  [./aux_bz]
    type = BzCurlA
    variable = B_z
  [../]
[]

[Kernels]
  [./b1_split] # Use a split to work in the Coulomb gauge
    type = DivASplit
    variable = Q
    Q = Q
    block = '1'	
  [../]
  [./b2_split]
    type = DivASplit
    variable = Q
    Q = Q
    block = '2'	
  [../]

  [./b1_Px] # Solve the vector Poisson equation for some split field variable Q
    type = PoissonAx
    variable = Ax
    Q = Q
    block = '1'
    Jx = 0
  [../]
  [./b1_Py]
    type = PoissonAy
    variable = Ay
    Q = Q
    block = '1'
    Jy = 0
  [../]
  [./b1_Pz]
    type = PoissonAz
    variable = Az
    Q = Q
    block = '1'
    Jz = 1e-3
  [../]

  [./b2_Px]
    type = PoissonAx
    variable = Ax
    Q = Q
    block = '2'
    Jx = 0
  [../]
  [./b2_Py]
    type = PoissonAy
    variable = Ay
    Q = Q
    block = '2'
    Jy = 0
  [../]
  [./b2_Pz]
    type = PoissonAz
    variable = Az
    Q = Q
    block = '2'
    Jz = 0
  [../]

[]


[BCs]
  [./1]
    type = DirichletBC
    variable = 'Q Ax Ay'
    boundary = '4'
    value = 0.0
  [../]

 # [./1]
 #   type = FarFieldBC
 #   variable = Q
 #   boundary = '1 2 3 4'
 # [../]
 # [./2]
 #   type = FarFieldBC
 #   variable = Ay
 #   boundary = '1 2 3 4'
 # [../]
 # [./3]
 #   type = FarFieldBC
 #   variable = Az
 #   boundary = '1 2 3 4'
 # [../]
[]

[Preconditioning]
  [./smp]
    type = SMP
    full = true
    petsc_options = '-snes_view -snes_linesearch_monitor -snes_converged_reason -ksp_converged_reason'
    #petsc_options_iname = '-ksp_type -ksp_gmres_restart  -snes_rtol -ksp_rtol -pc_type  -sub_pc_type -sub_pc_factor_shift_type   -sub_pc_factor_shift_amount'
    #petsc_options_value = '   gmres    40      1e-8      1e-8   bjacobi             lu    NONZERO                         1e-10      '

    petsc_options_iname = '-snes_type -ksp_type           -ksp_rtol     -pc_type -pc_factor_shift_type -pc_factor_shift_amount -pc_factor_mat_solver_package '
    petsc_options_value = '   ksponly preonly             1e-6          lu         NONZERO               1e-12         superlu_dist '
  [../]
[]

[Debug]
  show_var_residual_norms = true
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
