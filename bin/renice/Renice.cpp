#include "Renice.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <String.h>
#include <unistd.h>
#include <math.h>
#include <errno.h>
#include <ProcessClient.h>


Renice::Renice(int argc, char **argv)
    : POSIXApplication(argc, argv)
{
    parser().setDescription("Set priority for different processes on a scale of 1-5");
    parser().registerPositional("NEW_PRIORITY", "new priority level");
    parser().registerPositional("PROC_ID", "selected process");
    parser().registerFlag('n', "priority", "change priority level");
}

Renice::~Renice()
{
}

Renice::Result Renice::exec()
{
    if(arguments().get("priority")) {
        const ProcessClient process;
        ProcessID procID = (atoi(arguments().get("PROC_ID")));
        int newPriority = (atoi(arguments().get("NEW_PRIORITY")));

        ProcessClient::Info info;
        const ProcessClient::Result result = process.processInfo(procID, info);
        Renicepid(procID, newPriority, 0, 0);
    }
    return Success;
}
