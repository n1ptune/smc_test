#ifndef SMC_PARSE_H
#define SMC_PARSE_H

//rsi func_id
#define SMCCC_VERSION 0x80000000
#define SMC32_PSCI_FID_MIN 0x84000000 
#define SMC32_PSCI_FID_MAX 0x84000014
#define SMC64_PSCI_FID_MIN 0xc4000000 
#define SMC64_PSCI_FID_MAX 0xc4000014
#define SMC_RSI_VERSION 0xc4000190
#define SMC_RSI_FEATURES 0xc4000191
#define SMC_RSI_ATTEST_TOKEN_INIT 0xc4000194
#define SMC_RSI_ATTEST_TOKEN_CONTINUE 0xc4000195
#define SMC_RSI_MEASUREMENT_READ 0xc4000192
#define SMC_RSI_MEASUREMENT_EXTEND 0xc4000193
#define SMC_RSI_REALM_CONFIG 0xc4000196
#define SMC_RSI_IPA_STATE_SET 0xc4000197
#define SMC_RSI_IPA_STATE_GET 0xc4000198
#define SMC_RSI_HOST_CALL 0xc4000199

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