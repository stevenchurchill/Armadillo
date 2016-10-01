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
    #-------------------#Mesh is in millimeters#---------------------------------#
    mu = 0.000049474            #Henries/meter converted to T*mm/A. converted to T*in/A.
    i = 8.0                     #Amperes [A]-- SD uses 6.0 -- 10.0 [A]
    a = 4.25                    #inches [in] according to some introspective CUBITing
    loc_x = 0.0                 # F = 3.57 for i = 8.0 with block restrict mumag
    loc_y = 0.0                 #
    loc_z = -1.1628             #inches according to some introspective CUBITing
    N =  29.0                   #They have 29.5 --- does it make sense to have a half turn?
    solenoid_height = -5.36     #inches according to some introspective CUBITing
    translation_direction = 1.0 #Should make to a vector..see issue about refactoring
[]


[Variables]
  [./u]
    order = FIRST
    family = LAGRANGE
  [../]
[]

[AuxVariables]
  [./H_x]          
    family = MONOMIAL
    order = FIRST
  [../]
  [./H_y]
    family = MONOMIAL
    order = FIRST
  [../]
  [./H_z]
    family = MONOMIAL
    order = FIRST
  [../]
  [./H_mag]
    family = MONOMIAL
    order = FIRST
  [../]
[]

[AuxKernels]
  #AuxKernels have an automatic dependency resolution so if B needs A, then A is computed first.
  [./aux_bx]             #applied fields should be given in [T]
    type = SolenoidFieldx
    variable = H_x
    execute_on = 'initial'
  [../]
  [./aux_by]
    type = SolenoidFieldy
    variable = H_y
    execute_on = 'initial'
  [../]
  [./aux_bz]
    type = SolenoidFieldz
    variable = H_z
    execute_on = 'initial'
  [../]
  [./aux_Hmag]
    type = HMag
    variable = H_mag
    Hx = H_x
    Hy = H_y
    Hz = H_z
    execute_on = 'timestep_begin'
  [../]
[]

[Kernels]
  [./u_1_kern] #Note the Kernels and BC are arbitrary. We are just using MOOSE's API to compute the fields.
    type = Diffusion
    variable = u
  [../]
  [./u_t1_kern] 
    type = TimeDerivative
    variable = u
  [../]
[]


[BCs]
  [./bc1]
    type = DirichletBC
    variable = u
    boundary = '1'
    value = 0.0
  [../]
  [./bc2]
    type = DirichletBC
    variable = u
    boundary = '2'
    value = 1.0
  [../]
[]

[Preconditioning]
  [./smp]
    type = SMP
    full = true
    petsc_options_iname = '-snes_rtol -ksp_rtol'
    petsc_options_value = '  1e-1      1e-1 '
  [../]
[]

[Executioner]
  type = Transient
  solve_type = 'NEWTON'
  num_steps = 2
[]

[Outputs]
  print_perf_log = true
  [./out]
    type = Exodus
    file_base = solenoid_test
    elemental_as_nodal = true
    execute_on = 'timestep_end'
  [../]
[]

