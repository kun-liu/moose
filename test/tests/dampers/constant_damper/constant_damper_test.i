[Mesh]
  dim = 2
  file = square.e
[]

[Variables]
  active = 'u'

  [./u]
    order = FIRST
    family = LAGRANGE
  [../]
[]

[Kernels]
  active = 'diff'

  [./diff]
    type = Diffusion
    variable = u
  [../]
[]

[BCs]
  active = 'left right'

  [./left]
    type = DirichletBC
    variable = u
    boundary = 1
    value = 0
  [../]

  [./right]
    type = DirichletBC
    variable = u
    boundary = 2
    value = 1
  [../]
[]

[Dampers]
  [./u_damp]
    type = ConstantDamper
    variable = u
    damping = 0.9
  [../]
[]

[Executioner]
  type = Steady
  petsc_options = '-snes_mf_operator'
[]

[Output]
  file_base = out
  output_initial = true
  interval = 1
  exodus = true
  perf_log = true
[]

