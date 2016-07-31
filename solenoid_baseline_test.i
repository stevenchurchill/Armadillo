[Mesh]
  type = FileMesh
  file = exodus_stanadyne_arm0_baseline.e
  #block 1: solenoid
  #block 2: armature
  #block 3: medium around these structures
[]

[GlobalParams]
    #-------------------#Mesh is in millimeters#---------------------------------#
    mu = 0.12            #Henries/meter converted to T*mm/A. [T] = Teslas 
#!!!! mu is a fudge factor possibly to MATCH SD results since some factors of mu are floating around probably..
    i = 6.0                     #Amperes [A]-- SD uses 6.0 -- 10.0 [A]
    a = 4.25                    #millimeters [mm] according to some introspective CUBITing
    loc_x = 0.0                 #
    loc_y = 0.0                 #
    loc_z = -1.1628             #millimeters according to some introspective CUBITing
    N =  29.5                   #They have 29.5 --- does it make sense to have a half turn?
    solenoid_height = -5.36     #millimeters according to some introspective CUBITing
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
    order = CONSTANT
  [../]
  [./H_y]
    family = MONOMIAL
    order = CONSTANT
  [../]
  [./H_z]
    family = MONOMIAL
    order = CONSTANT
  [../]
  [./H_mag]
    family = MONOMIAL
    order = CONSTANT
  [../]
  [./mu_mag]
    family = MONOMIAL
    order = FIRST
  [../]
  [./f_Mag]
    family = MONOMIAL
    order = CONSTANT
  [../]
[]

[AuxKernels]
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
    execute_on = 'timestep_end'
  [../]
  [./aux_Mumag]
    block = '2'
    type = MuMag
    variable = mu_mag
    Hx = H_x
    Hy = H_y
    Hz = H_z
    A = 1.42772 #From the fit of Fig 2 -- these are in [T, A, mm] 
    B = 7.68652
    C = -0.132035
    D = 0.374388
    E = 0.074
    mu00 = 0   #this stuff can be removed in the auxkernel
    mu01 = 0
    mu02 = 0
    mu10 = 0
    mu11 = 0
    mu12 = 0
    mu20 = 0
    mu21 = 0
    mu22 = 0
    execute_on = 'timestep_begin'
  [../]

  [./aux_fMAg]
    type = fMag
    variable = f_Mag
    mumag = mu_mag
    execute_on = 'timestep_end'
  [../]
[]

[Kernels]
  [./u_1_kern] #Note the Kernels and BC are arbitrary. We are just using MOOSE's API to compute the fields.
    type = Diffusion
    variable = u
  [../]
  [./u_t_1_kern] 
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
   [./total_F] #gives result in kg mm/s^2 == milliNewtons
    block = '2'
    type = ElementAverageValue
    variable = f_Mag
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
  num_steps =  1
[]

[Outputs]
  print_perf_log = true
  [./out]
    type = Exodus
    elemental_as_nodal = true
    execute_on = 'timestep_end'
  [../]
[]

