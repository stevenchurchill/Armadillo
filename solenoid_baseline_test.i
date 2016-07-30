[Mesh]
  type = FileMesh
  file = exodus_stanadyne_arm0_baseline.e
  #block 1: solenoid
  #block 2: armature
  #block 3: medium around these structures
[]

[GlobalParams]
    #Mesh is in millimeters.
    mu = 0.00125664. #Henries/meter converted to T*mm/A. [T] = Teslas
    i = 0.036     #Amperes [A]-- SD uses 0.036 [A]
    a = 4.25      #millimeters [mm] according to some introspective CUBITing
    loc_x = 0.0
    loc_y = 0.0
    loc_z = -1.1628 #millimeters according to some introspective CUBITing
    N =  29.0 #They have 29.5 --- WHAT DO?
    solenoid_height = -5.36 #millimeters according to some introspective CUBITing
    translation_direction = 1.0 #Should make to a vector..see issue about refactoring
[]


[Variables]
  [./u]
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
  [./H_mag]
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./mu_mag]
    order = CONSTANT
    family = MONOMIAL
  [../]
[]

[AuxKernels]
  [./aux_bx] #field should be given in [T]
    type = SolenoidFieldx
    variable = B_x
    execute_on = 'timestep_end'
  [../]
  [./aux_by]
    type = SolenoidFieldy
    variable = B_y
    execute_on = 'timestep_end'
  [../]
  [./aux_bz]
    type = SolenoidFieldz
    variable = B_z
    execute_on = 'timestep_end'
  [../]
  [./aux_Hmag]
    type = HMag
    variable = H_mag
    Hx = B_x
    Hy = B_y
    Hz = B_z
    execute_on = 'timestep_end'
  [../]
  [./aux_Mumag]
    block = '2'
    type = MuMag
    variable = mu_mag
    Hx = B_x
    Hy = B_y
    Hz = B_z
    A = 0.0250778 #From the fit -- these are in [T*A/mm]
    B = 0.0847837
    mu00 = 0
    mu01 = 0
    mu02 = 0
    mu10 = 0
    mu11 = 0
    mu12 = 0
    mu20 = 0
    mu21 = 0
    mu22 = 0
    execute_on = 'timestep_end'
  [../]
[]

[Kernels]
  [./u_1_kern] #Note the Kernels and BC are arbitrary. We are just using MOOSE's API to compute the fields.
    type = Diffusion
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
    petsc_options_value = '  1e-2      1e-2 '
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

