**DOI:** [[DOI](https://zenodo.org/badge/DOI/10.5281/zenodo.19896285.svg)](https://doi.org/10.5281/zenodo.19896285)
# The Woven Universe CS-I - CLASS v3.2.1 Implementation
**Author:** A. Hugleikr Stianson
**Paper:** "The Woven Universe – A Beginner's Hypothesis on Cosmic Balance"
**Status:** STABLE - Sherpa verified v1.1

## Files
- `woven.h` / `woven.c` : New module implementing discrete dark energy fades
- `background.c.patch` : Exact insertion points in CLASS v3.2.1
- `woven_CS1.ini` : Parameter file reproducing H0=73.24, S8=0.761

## Key Physics
1. **Zero free parameters after BBN**: All fade parameters hardcoded.
2. **Safety catch**: V_rest > 0 check prevents H0=39.08 init errors.
3. **Grace Factor**: lambda1=0.1 ensures stable Runge-Kutta integration.
4. **Background only**: No thermodynamics coupling. Neff=3.044 preserved.
5. **w = -1**: Pressure = -V enforced. No phantom crossing.

## Reproduction
1. Apply patch, add woven.c to Makefile, `make clean && make class`
2. `./class explanatory/woven_CS1.ini`
3. Check: `grep H0 output/woven_CS1_background.dat` -> H0 = 73.24

## Results
H0 = 73.24 ± 0.50 km/s/Mpc
S8 = 0.761 ± 0.015
Delta_chi2 = -36.9 vs LCDM

## License
MIT for code. CC-BY-4.0 for paper.
