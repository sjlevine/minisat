/*****************************************************************************************[Main.cc]
These C bindings were written by Steve Levine -- please see license in other files.
**************************************************************************************************/

#include "minisat/utils/System.h"
#include "minisat/core/SolverTypes.h"
#include "minisat/simp/SimpSolver.h"

using namespace Minisat;

extern "C" void minisat_initialize_new_solver();

extern "C" void minisat_shutdown_solver();

extern "C" void minisat_begin_new_clause();

extern "C" void minisat_add_literal_to_current_clause(int var, bool positive);

extern "C" void minisat_add_current_clause();

extern "C" bool minisat_solve();

extern "C" int minisat_nvars();

extern "C" int minisat_nclauses();

extern "C" int minisat_nlearnts();


//=================================================================================================

// Some global / static variables, to be used between calls
// Main solver instance
static SimpSolver* solver = NULL;
// The current clause being constructed
static vec<Lit> lits;

//=================================================================================================
// Main Bindings:

void minisat_initialize_new_solver() {
  // setX86FPUPrecision();
  if (solver) {
    delete solver;
  }
  lits.clear();
  solver = new SimpSolver;
  solver->verbosity = 0; // Set to silent
}

void minisat_shutdown_solver() {
  if (solver) {
    delete solver;
  }
  lits.clear();
}

void minisat_begin_new_clause() {
  lits.clear();
}

void minisat_add_literal_to_current_clause(int var, bool positive) {
  var--; // Variables are integer based in Minisat, but we assume they're
         // 1 based in input
  while (var >= solver->nVars()) {solver->newVar();}
  lits.push( positive ? mkLit(var) : ~mkLit(var) );
}


void minisat_add_current_clause() {
  solver->addClause_(lits);
}


bool minisat_solve() {
  // We could optionally set some resource limits (CPU, memory) here
  solver->eliminate(true);
  if (!solver->okay()) {
    // Unsatisfiable!
    return false;
  }
  vec<Lit> dummy;
  lbool ret = solver->solveLimited(dummy);
  return (ret == l_True);
}

int minisat_nvars() {
  return solver->nVars();
}

int minisat_nclauses() {
  return solver->nClauses();
}

int minisat_nlearnts() {
  return solver->nLearnts();
}
