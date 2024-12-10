#include "smc_parse.h"

#include <linux/arm-smccc.h>

#define RSI_RANGE 
#define RMI_RANGE

unsigned long smc_parse(struct arm_smccc_args* smc,
		   struct arm_smccc_res *res) {
    //struct arm_smccc_res res;
    arm_smccc_smc(smc->args[0], smc->args[1], smc->args[2],
			      smc->args[3], smc->args[4], smc->args[5],
			      smc->args[6], smc->args[7],  res);
    return res->a0;
}