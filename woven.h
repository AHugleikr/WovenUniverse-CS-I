#ifndef _WOVEN_H_
#define _WOVEN_H_

#include "common.h"
#include "background.h"

typedef struct woven {
  short has_woven;
  double Delta_E1; /* Phase 1 BBN fade [Mpl^4] */
  double Delta_E2; /* Phase 2 recombination fade [Mpl^4] */
  double z_c1; /* BBN redshift */
  double z_c2; /* Recombination redshift */
  double lambda1; /* Grace Factor */
  double V_rest; /* Calculated to match Omega_Lambda */
} woven;

int woven_init(struct precision * ppr, struct background * pba, struct woven * pwv);
int woven_rho(struct background * pba, struct woven * pwv, double z, double * rho_wv, double * p_wv);
double woven_V(struct woven * pwv, double xi);

#endif