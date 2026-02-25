# Ballistic trajectory simulator
Cape Canaveral trajectory model with flat-Earth geometry and still-air assumptions.
Build: `make`; run: `echo "100 45 1 0.01" | ./trajectory`.
Inputs: speed m/s, elevation degrees, mass kg, quadratic drag kg/m.
Reports flight time, range and apex; drag acceleration opposes velocity.
Integrator: semi-implicit Euler, timestep 0.001 seconds, linear impact interpolation.
No targeting, navigation or live range inputs are provided.
Check: `python tests/check.py ./trajectory`.
