#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

#define DEVICE_NAME "/dev/smc_fuzz"
#define IOCTL_SET_MSG _IOR('a', 1, struct arm_smccc_args *)
#define IOCTL_GET_MSG _IOR('a', 2, struct arm_smccc_args *)

struct arm_smccc_args {
	unsigned long args[8];
};
struct arm_smccc_res {
	unsigned long a0;
	unsigned long a1;
	unsigned long a2;
	unsigned long a3;
};
struct msg {
    struct arm_smccc_args smc_args;
    struct arm_smccc_res smc_res;
};

int main() {
    int fd;
    struct arm_smccc_args smc_args = {
        .args[0] = 0x1234,
        .args[1] = 0x1,
        .args[2] = 0x2,
        .args[3] = 0x3,
        .args[4] = 0x4,
        .args[5] = 0x5,
        .args[6] = 0x6,
        .args[7] = 0x7
    };
    struct arm_smccc_res smc_res = {0};
    struct msg msg = {
        .smc_args = smc_args,
        .smc_res = smc_res
    };
    fd = open(DEVICE_NAME, O_RDWR);
    if (fd < 0) {
        perror("Failed to open the device");
        return EXIT_FAILURE;
    }

    if (ioctl(fd, IOCTL_SET_MSG, &msg) < 0) {
        perror("Failed to set message");
        close(fd);
        return EXIT_FAILURE;
    }

    if (ioctl(fd, IOCTL_GET_MSG, &msg) < 0) {
        perror("Failed to get message");
        close(fd);
        return EXIT_FAILURE;
    }

    printf("Message from kernel: func_id = %lx, ret = %lx\n", msg.smc_args.args[0], msg.smc_res.a0);

    close(fd);
    return EXIT_SUCCESS;
}