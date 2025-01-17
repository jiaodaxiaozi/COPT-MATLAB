#ifndef __COPTMEX_H__
#define __COPTMEX_H__

#include "copt.h"
#include "mex.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#define mystrcmp _stricmp
#else
#include <strings.h>
#define mystrcmp strcasecmp
#endif

#ifndef NDEBUG
#define COPTMEX_CALL(func) \
  do {                                                                         \
    if ((retcode = (func)) != COPT_RETCODE_OK) {                               \
      mexPrintf("ERROR %d: %s:%d\n", retcode, __FILE__, __LINE__);             \
      goto exit_cleanup;                                                       \
    }                                                                          \
  } while (0)
#else
#define COPTMEX_CALL(func) \
  do { if ((retcode = (func)) != COPT_RETCODE_OK) goto exit_cleanup; } while (0)
#endif

/* The solution status in string format */
#define COPTMEX_STATUS_UNSTARTED   "unstarted"
#define COPTMEX_STATUS_OPTIMAL     "optimal"
#define COPTMEX_STATUS_INFEASIBLE  "infeasible"
#define COPTMEX_STATUS_UNBOUNDED   "unbounded"
#define COPTMEX_STATUS_INF_OF_UNB  "inf_or_unb"
#define COPTMEX_STATUS_NUMERICAL   "numerical"
#define COPTMEX_STATUS_NODELIMIT   "nodelimit"
#define COPTMEX_STATUS_TIMEOUT     "timeout"
#define COPTMEX_STATUS_UNFINISHED  "unfinished"
#define COPTMEX_STATUS_INTERRUPTED "interrupted"

/* The main part of model struct fields */
#define COPTMEX_MODEL_OBJSEN       "objsen"
#define COPTMEX_MODEL_OBJCON       "objcon"
#define COPTMEX_MODEL_A            "A"
#define COPTMEX_MODEL_OBJ          "obj"
#define COPTMEX_MODEL_LB           "lb"
#define COPTMEX_MODEL_UB           "ub"
#define COPTMEX_MODEL_VTYPE        "vtype"
#define COPTMEX_MODEL_VARNAME      "varnames"
#define COPTMEX_MODEL_SENSE        "sense"
#define COPTMEX_MODEL_LHS          "lhs"
#define COPTMEX_MODEL_RHS          "rhs"
#define COPTMEX_MODEL_CONNAME      "constrnames"

/* The optional part of model struct fields */
#define COPTMEX_MODEL_SOS          "sos"
#define COPTMEX_MODEL_SOSTYPE      "type"
#define COPTMEX_MODEL_SOSVARS      "vars"
#define COPTMEX_MODEL_SOSWEIGHT    "weights"

#define COPTMEX_MODEL_INDICATOR    "indicator"
#define COPTMEX_MODEL_INDICBINVAR  "binvar"
#define COPTMEX_MODEL_INDICBINVAL  "binval"
#define COPTMEX_MODEL_INDICROW     "a"
#define COPTMEX_MODEL_INDICSENSE   "sense"
#define COPTMEX_MODEL_INDICRHS     "rhs"

/* The result struct fields */
#define COPTMEX_RESULT_STATUS      "status"
#define COPTMEX_RESULT_SIMITER     "simplexiter"
#define COPTMEX_RESULT_NODECNT     "nodecnt"
#define COPTMEX_RESULT_BESTGAP     "bestgap"
#define COPTMEX_RESULT_SOLVETIME   "solvingtime"
#define COPTMEX_RESULT_OBJVAL      "objval"
#define COPTMEX_RESULT_BESTBND     "bestbnd"
#define COPTMEX_RESULT_VARBASIS    "varbasis"
#define COPTMEX_RESULT_CONBASIS    "constrbasis"
#define COPTMEX_RESULT_VALUE       "x"
#define COPTMEX_RESULT_REDCOST     "rc"
#define COPTMEX_RESULT_SLACK       "slack"
#define COPTMEX_RESULT_DUAL        "pi"

#define COPTMEX_RESULT_POOL        "pool"
#define COPTMEX_RESULT_POOLOBJ     "objval"
#define COPTMEX_RESULT_POOLXN      "xn"

/* The advanced information */
#define COPTMEX_ADVINFO_MIPSTART   "start"

/* The version fields */
#define COPTMEX_VERSION_MAJOR      "major"
#define COPTMEX_VERSION_MINOR      "minor"
#define COPTMEX_VERSION_TECHNICAL  "technical"

/* Error types */
#define COPTMEX_ERROR_BAD_TYPE     0
#define COPTMEX_ERROR_BAD_NAME     1
#define COPTMEX_ERROR_BAD_DATA     2
#define COPTMEX_ERROR_BAD_NUM      3
#define COPTMEX_ERROR_BAD_API      4

typedef struct coptmex_mversion_s {
  mxArray *major;
  mxArray *minor;
  mxArray *technical;
} coptmex_mversion;

typedef struct coptmex_cprob_s {
  /* The main part of problem */
  int    nCol;
  int    nRow;
  int    nElem;
  int    nObjSen;
  double dObjConst;

  int    *colMatBeg;
  int    *colMatIdx;
  double *colMatElem;

  double *colCost;
  double *colLower;
  double *colUpper;
  double *rowLower;
  double *rowUpper;

  char   *colType;
  char   *rowSense;
  char   **colNames;
  char   **rowNames;

  /* The optional SOS part */
  int    nSos;
  int    nSosSize;
  int    *sosType;
  int    *sosMatBeg;
  int    *sosMatCnt;
  int    *sosMatIdx;
  double *sosMatWt;

  /* The optional indicator part */
  int    nIndicator;

  /* The optional advanced information */
  int    hasBasis;
  int    *colBasis;
  int    *rowBasis;
} coptmex_cprob;

typedef struct coptmex_mprob_s {
  /* The main part of model */
  mxArray *objsen;
  mxArray *objcon;
  mxArray *A;
  mxArray *obj;
  mxArray *lb;
  mxArray *ub;
  mxArray *vtype;
  mxArray *varnames;
  mxArray *sense;
  mxArray *lhs;
  mxArray *rhs;
  mxArray *constrnames;

  /* The optional sos part of model */
  mxArray *sos;

  /* The optional indicator part of model */
  mxArray *indicator;

  /* The optional advanced information */
  mxArray *varbasis;
  mxArray *constrbasis;

  mxArray *value;
  mxArray *slack;
  mxArray *dual;
  mxArray *redcost;

  mxArray *mipstart;
} coptmex_mprob;

typedef struct coptmex_clpsol_s {
  int    nRow;
  int    nCol;
  int    hasBasis;
  int    hasLpSol;

  int    nStatus;
  int    nSimplexIter;
  double dSolvingTime;
  double dObjVal;

  int    *colBasis;
  int    *rowBasis;
  double *colValue;
  double *colDual;
  double *rowSlack;
  double *rowDual;
} coptmex_clpsol;

typedef struct coptmex_cmipsol_s {
  int    nRow;
  int    nCol;
  int    hasMipSol;

  int    nStatus;
  int    nSimplexIter;
  int    nNodeCnt;
  double dBestGap;
  double dSolvingTime;
  double dObjVal;
  double dBestBnd;

  double *colValue;

  int    nSolPool;
} coptmex_cmipsol;

typedef struct coptmex_mlpsol_s {
  mxArray *status;
  mxArray *simplexiter;
  mxArray *solvingtime;
  mxArray *objval;
  mxArray *varbasis;
  mxArray *constrbasis;
  mxArray *value;
  mxArray *redcost;
  mxArray *slack;
  mxArray *dual;
} coptmex_mlpsol;

typedef struct coptmex_mmipsol_s {
  mxArray *status;
  mxArray *simplexiter;
  mxArray *nodecnt;
  mxArray *bestgap;
  mxArray *solvingtime;
  mxArray *objval;
  mxArray *bestbnd;
  mxArray *value;

  mxArray *solpool;
} coptmex_mmipsol;

/* Display error message */
void COPTMEX_errorMsg(int errcode, const char *errinfo);
/* Display banner */
int COPTMEX_dispBanner(void);

/* Extract version of COPT */
int COPTMEX_getVersion(mxArray **out_version);
/* Extract objective sense */
int COPTMEX_getObjsen(const mxArray *in_objsen, int *out_objsen);
/* Extract and save result */
int COPTMEX_getResult(copt_prob *prob, mxArray **out_result);
/* Extract model data */
int COPTMEX_getModel(copt_prob *prob, int nfiles, const mxArray **in_files, mxArray **out_model);

/* Load parameters to problem */
int COPTMEX_setParam(copt_prob *prob, const mxArray *in_param);
/* Read optional information from file */
int COPTMEX_readInfo(copt_prob *prob, const mxArray *in_info);
/* Read model from file */
int COPTMEX_readModel(copt_prob *prob, const mxArray *in_model);
/* Write model to file */
int COPTMEX_writeModel(copt_prob *prob, const mxArray *out_file);
/* Extract and load data to model */
int COPTMEX_loadModel(copt_prob *prob, const mxArray *in_model);

#endif
