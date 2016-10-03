[Mesh]
  type = FileMesh
  file = exodus_stanadyne_arm0_baseline_new_066mm_size02.e
  #block 1: solenoid
  #block 2: armature
  #block 3: steel valve
  #block 4: encasing stator
  #block 5: media
[]

[GlobalParams]
    #-------------------#Mesh is in millimeters#---------------------------------#
    mu = 1.256e-3               #Henries/meter converted to T*mm/A
    i = 8.0                     #Amperes [A]-- SD uses 6.0 -- 10.0 [A]
    a = 4.45                    #millimeters [mm] according to some introspective CUBITing
    loc_x = 0.0                 #
    loc_y = 0.0                 #
    loc_z = -1.1628             #millimeters according to some introspective CUBITing
    N =  29.0                   #They have 29.5 --- does it make sense to have a half turn?
    solenoid_height = 5.36      #millimeters according to some introspective CUBITing
    translation_direction = 1.0 #Should make to a vector..see issue about refactoring
[]


[Variables]
  [./u]
    order = FIRST
    family = LAGRANGE
  [../]
[]

[AuxVariables]
  [./B_x]  #magnetic flux density        
    family = MONOMIAL
    order = FIRST
  [../]
  [./B_y]
    family = MONOMIAL
    order = FIRST
  [../]
  [./B_z]
    family = MONOMIAL
    order = FIRST
  [../]
  [./H_mag]
    family = MONOMIAL
    order = FIRST
  [../]
  [./mu_mag]
    family = MONOMIAL
    order = FIRST
  [../]
  [./F_z]
    family = MONOMIAL
    order = FIRST
  [../]
  [./F_x]
    family = MONOMIAL
    order = FIRST
  [../]
  [./F_y]
    family = MONOMIAL
    order = FIRST
  [../]
[]

[AuxKernels]
  #AuxKernels have an automatic dependency resolution so if c1 needs c2 and so on, then c1 is computed first.
  [./aux_bx]             #applied fields should be given in [T]
    type = SolenoidFieldx
    variable = B_x
    execute_on = 'initial'
  [../]
  [./aux_by]
    type = SolenoidFieldy
    variable = B_y
    execute_on = 'initial'
  [../]
  [./aux_bz]
    type = SolenoidFieldz
    variable = B_z
    execute_on = 'initial'
  [../]
  [./aux_Hmag]
    type = HMag
    variable = H_mag
    Hx = B_x
    Hy = B_y
    Hz = B_z
    execute_on = 'timestep_begin'
  [../]
  [./aux_Mumag]
    block = '2 5'
    type = MuMag
    variable = mu_mag
    Bx = B_x
    By = B_y
    Bz = B_z
    A = 1.42772 #From the fit of Fig 2 -- these are in [T, A, mm] 
    B = 7.68653
    C = -0.132035
    D = -0.374389
    E = 0.0745812
    execute_on = 'timestep_begin'
  [../]
  [./aux_Mumag_Stainless_Steel]
    block = '3'
    type = MuMag
    variable = mu_mag
    Bx = B_x
    By = B_y
    Bz = B_z
    A = 1.63694 #From stainless steel fit 
    B = 2.34778
    C = 0.0160949
    D = 1.64944
    E = 0.0470473
    execute_on = 'timestep_begin'
  [../]
  [./aux_fx]
    type = Fx
    variable = F_x
    mumag = mu_mag
    execute_on = 'timestep_end'
  [../]
  [./aux_fy]
    type = Fy
    variable = F_y
    mumag = mu_mag
    execute_on = 'timestep_end'
  [../]
  [./aux_fz]
    type = Fz
    variable = F_z
    mumag = mu_mag
    execute_on = 'timestep_end'
  [../]
[]

[Kernels]
  [./u_1_kern] #Note the Kernels and BC are arbitrary. We are just using MOOSE's API to compute the auxfields.
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

[Postprocessors]
   [./total_Fx] #gives result in kg mm/s^2 == 0.001 Newtons
    block = '2 3'
    type = ElementIntegralVariablePostprocessor
    variable = F_x
   [../]
   [./total_Fy] #gives result in kg mm/s^2 == 0.001 Newtons
    block = '2 3'
    type = ElementIntegralVariablePostprocessor
    variable = F_y
   [../]
   [./total_Fz] #gives result in kg mm/s^2 == 0.001 Newtons
    block = '2 3'
    type = ElementIntegralVariablePostprocessor
    variable = F_z
   [../]
   [./volume2]
    block = '2'
    type = VolumePostprocessor
   [../]
   [./volume3]
    block = '3'
    type = VolumePostprocessor
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
    file_base = solenoid_baseline_test_1
    elemental_as_nodal = true
    execute_on = 'timestep_end'
  [../]
[]

