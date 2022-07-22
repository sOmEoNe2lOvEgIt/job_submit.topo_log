# Topo_Log
## Hello!

### What do i do ?

This plugin needs some setup to function propperly.

When slurm installs, it creates a log file to store the logs of its doings.

Slurm logs are stored in a file contained at */var/log/slurm/* directory.

This plugin needs to have a log file created in the same directory under the name *job_top.log* (**touch /var/log/slurm/job_top.log**).

This folder can only be written as root so you will need to create the file as root.

You will then need to grant access to the file to the user slurm (**chown slurm /var/log/slurm/job_top.log**) as it is the user that runs the plugin.
