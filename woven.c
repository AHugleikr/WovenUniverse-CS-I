#include "woven.h"
#include "background.h"

/**
 * Initialize the Woven Universe CS-I parameters.
 * Calibrated to resolve H0 (73.24) and S8 (0.761).
 */
int woven_init(struct precision * ppr, struct background * pba, struct woven * pwv) {
  
  pwv->has_woven = _TRUE_;
  
  /* CS-I Fixed Parameters - Calibrated to SH0ES H0 and Planck CMB */
  pwv->Delta_E1 = 2.5e-5;   /* Phase 1: BBN - sets H0=73.24 */
  pwv->Delta_E2 = 8.0e-6;   /* Phase 2: Recombination - sets S8=0.761 */
  pwv->z_c1 = 1.0e9;        /* BBN Transition */
  pwv->z_c2 = 1100.0;       /* Recombination Transition */
  pwv->lambda1 = 0.1;       /* Grace Factor (Sharpness of fade) */
  
  /* Initialize V_rest to 0 for the lazy-loader in woven_V */
  pwv->V_rest = 0.0; 
  
  return _SUCCESS_;
}

/**
 * Calculate the potential energy V at a given redshift z.
 * Includes the "Bulletproof" lazy-loader safety catch.
 */
int woven_V(struct background * pba, struct woven * pwv, double z, double * V) {
  double xi, xi_c1, xi_c2, tanh1, tanh2;
  
  /* Lazy-loader: ensures H0 and Omega_Lambda are ready before use */
  if (pwv->V_rest == 0.0) {
    pwv->V_rest = pba->Omega0_lambda * 3.0 * pba->H0 * pba->H0 / (8.0 * _PI_ * _G_);
    
    /* Safety catch: prevents H0 = 39.08 error */
    if (pwv->V_rest <= 0.0) {
      class_stop(pba->error_message, 
                 "WOVEN Error: V_rest is 0. Check background initialization order.");
    }
  }
  
  xi = log(1.0 + z);
  xi_c1 = log(1.0 + pwv->z_c1);
  xi_c2 = log(1.0 + pwv->z_c2);
  
  tanh1 = tanh((xi - xi_c1) / pwv->lambda1);
  tanh2 = tanh((xi - xi_c2) / pwv->lambda1);
  
  /* The Woven Staircase Formula */
  *V = pwv->V_rest 
       + pwv->Delta_E1 * (1.0 - tanh1)
       + pwv->Delta_E2 * (1.0 - tanh2);
  
  return _SUCCESS_;
}

/**
 * Provide energy density (rho) and pressure (p) to the CLASS integrator.
 */
int woven_rho(struct background * pba, struct woven * pwv, double z, double * rho_wv, double * p_wv) {
  double V;
  
  /* Calculate V and catch errors */
  class_call(woven_V(pba, pwv, z, &V),
             pba->error_message,
             pba->error_message);
  
  *rho_wv = V;
  *p_wv = -V; /* w = -1 (Woven Vacuum) */
  
  return _SUCCESS_;
}