#include <stdlib.h>
#include <stdio.h>
#include <simlib.h>

// Header with with model parameters
// #include "cr_2020_no_vaccine.h"
// #include "cr_2021_vaccine.h"

// #include "ex1/ex1_effectivity_93.h"
// #include "ex1/ex1_effectivity_83.h"
// #include "ex1/ex1_effectivity_73.h"
// #include "ex1/ex1_effectivity_63.h"
// #include "ex1/ex1_effectivity_73.h"

// #include "ex2/ex2_vaccination_40.h"
// #include "ex2/ex2_vaccination_50.h"
// #include "ex2/ex2_vaccination_60.h"
// #include "ex2/ex2_vaccination_70.h"
// #include "ex2/ex2_vaccination_80.h"

// #include "ex3/ex3_e_53_v_40.h"
// #include "ex3/ex3_e_53_v_50.h"
// #include "ex3/ex3_e_53_v_60.h"
// #include "ex3/ex3_e_53_v_70.h"
// #include "ex3/ex3_e_53_v_80.h"

// #include "ex3/ex3_e_63_v_40.h"
// #include "ex3/ex3_e_63_v_50.h"
// #include "ex3/ex3_e_63_v_60.h"
// #include "ex3/ex3_e_63_v_70.h"
// #include "ex3/ex3_e_63_v_80.h"

// #include "ex3/ex3_e_73_v_40.h"
// #include "ex3/ex3_e_73_v_50.h"
// #include "ex3/ex3_e_73_v_60.h"
// #include "ex3/ex3_e_73_v_70.h"
// #include "ex3/ex3_e_73_v_80.h"

// #include "ex3/ex3_e_83_v_40.h"
// #include "ex3/ex3_e_83_v_50.h"
// #include "ex3/ex3_e_83_v_60.h"
// #include "ex3/ex3_e_83_v_70.h"
// #include "ex3/ex3_e_83_v_80.h"

// #include "ex3/ex3_e_93_v_40.h"
// #include "ex3/ex3_e_93_v_50.h"
// #include "ex3/ex3_e_93_v_60.h"
// #include "ex3/ex3_e_93_v_70.h"
// #include "ex3/ex3_e_93_v_80.h"

// Model
struct SEIR {
    // N = S + E + I + Q + R + D + V
    Integrator S, E, I, Q, R, D, V;

    SEIR(
        double lambda,
        double beta,
        double alpha,
        double mu,
        double gamma,
        double sigma,
        double delta,
        double kappa,
        double theta,
        double rho
    ) :
        S(lambda - beta*S*I - alpha*S - mu*S, (double) S0),
        E(beta*S*I - gamma*E + sigma*beta*V*I - mu*E, (double) E0),
        I(gamma*E - delta*I - mu*I, (double) I0),
        Q(delta*I - (1 - kappa)*theta*Q - kappa*rho*Q - mu*Q, (double) Q0),
        R((1 - kappa)*theta*Q - mu*R, (double) R0),
        D(kappa*rho*Q, (double) D0),
        V(alpha*S - sigma*beta*V*I - mu*V, (double) V0) {}
};

// Create model instance
SEIR seir(LAMBDA, BETA, ALPHA, MU, GAMMA, SIGMA, DELTA, KAPPA, THETA, RHO);

void Sample() {
    Print("%6.2f,%.5g,%.5g,%.5g,%.5g,%.5g,%.5g,%.5g\n", T.Value(), seir.S.Value(), seir.E.Value(), seir.I.Value(), seir.Q.Value(), seir.R.Value(), seir.D.Value(), seir.V.Value());
}

Sampler S(Sample, 1);        // Output step 

int main() {
    double maxtime = MAX_TIME;
    printf("S: %d\n", S0);
    printf("%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf\n", (double) LAMBDA, ((double) BETA),(double)  ALPHA,(double)  MU,(double)  GAMMA,(double)  SIGMA,(double)  DELTA,(double)  KAPPA,(double)  THETA,(double)  RHO);
    SetOutput(OUT_FILE);    // Redirect output to file
    Print("time,susceptible,exposed,infectious,quarantined,recovered,dead,vaccinated\n");
    Init(0, maxtime);           // Initialize simulator
    SetAccuracy(1e-8);          // Required accuracy
    Run();                      // Simulate
    return 0;
}