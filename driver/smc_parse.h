#ifndef SMC_PARSE_H
#define SMC_PARSE_H

#include <linux/arm-smccc.h>
struct arm_smccc_args {
	unsigned long args[8];
};
struct msg {
    struct arm_smccc_args smc_args;
    struct arm_smccc_res smc_res;
};
unsigned long smc_parse(struct arm_smccc_args* smc,
		   struct arm_smccc_res *res);




#endif