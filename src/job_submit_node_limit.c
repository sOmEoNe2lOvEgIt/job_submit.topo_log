// ATOS PROJECT, 2022
// TEST_PLUGIN_SLURM
// File description:
// Wow, such plugin, much test!

#include "config.h"
#include "src/slurmctld/slurmctld.h"
#include "src/common/slurm_xlator.h"
#include <slurm/slurm.h>
#include <string.h>
#include <stdio.h>

const char plugin_name[] = "Node restriction.";
const char plugin_type[] = "job_submit/enoughnodes";
const uint32_t plugin_version = SLURM_VERSION_NUMBER;

int init (void)
{
    return (SLURM_SUCCESS);
}

int job_submit(struct job_descriptor *job_desc, uint32_t submit_uid, char **error_msg)
{
    FILE *log_file = fopen("/var/log/slurm/job_top.log", "a");

    if (log_file == NULL)
        log_file = fopen("/var/log/slurm/job_top.log", "w+"); //This is due to a current bug where the file is not accessible by the slurmuser. A script will be made to fix this issue.
    if (log_file == NULL) {
        *error_msg = xstrdup("Error opening log file.\n");
        printf("Error opening log file. Error %d\n", errno);
        return (ESLURM_DISABLED);
    }
    if (job_desc->min_nodes > 4) {
        *error_msg = xstrdup("Not enough nodes. Please try to request a job with at most 4 nodes.");
        fprintf(log_file, "Job %d did not work.\n", job_desc->job_id);
        fclose(log_file);
        return (ESLURM_INVALID_NODE_COUNT);
    } else
        fprintf(log_file, "Job %d worked.\n", job_desc->job_id);
    fclose(log_file);
    return (SLURM_SUCCESS);
}

int job_modify(struct job_descriptor *job_desc, job_record_t *job_ptr, uint32_t modify_uid)
{
    FILE *log_file = fopen("/var/log/job_top.log", "a");

    if (job_ptr->best_switch)
        fprintf(log_file, "Job %d went through min ammount of switches.\n", job_ptr->job_id);
    else
        fprintf(log_file, "Job %d did not go through min ammount of switches.\n", job_ptr->job_id);
    fclose(log_file);
    return (SLURM_SUCCESS);
}

void fini (void)
{
}