/*
 * Copyright (C) 2009 Niek Linnenbank
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __KERNEL_SCHEDULER_H
#define __KERNEL_SCHEDULER_H

#ifndef __ASSEMBLER__

#include <Vector.h>
#include <Macros.h>
#include <Queue.h>
#include "Process.h"
#include "ProcessManager.h"

/**
 * @addtogroup kernel
 * @{
 */

/**
 * A process scheduling algorithm using a multilevel feedback queue.
 */
class Scheduler {
public:
    /**
     * Result code
     */
    enum Result {
        Success,
        InvalidArgument
    };

    /**
     * Constructor function.
     */
    Scheduler();

    /**
     * Get number of processes on the schedule
     *
     * @return Number of processes on the schedule
     */
    Size count() const;

    /**
     * Add a Process to the run schedule.
     *
     * @param proc Process pointer
     * @param priority The priority of the process (higher is better)
     * @param ignoreState True to not check for the Process state prior to enqueue.
     *
     * @return Result code
     */
    Result enqueue(Process *proc, int priority, bool ignoreState);

    /**
     * Remove a Process from the run schedule.
     *
     * @param proc Process pointer
     * @param ignoreState True to not check for the Process state prior to dequeue.
     *
     * @return Result code
     */
    Result dequeue(Process *proc, bool ignoreState);

    /**
     * Select the next process to run.
     *
     * @return Process pointer or NULL if no matching process found
     */
    Process * select();

private:
    /** Contains processes in the highest-priority queue */
    Queue<Process *, MAX_PROCS> m_queueHigh;

    /** Contains processes in the medium-priority queue */
    Queue<Process *, MAX_PROCS> m_queueMedium;

    /** Contains processes in the low-priority queue */
    Queue<Process *, MAX_PROCS> m_queueLow;
};

/**
 * @}
 */

#endif /* __ASSEMBLER__ */
#endif /* __KERNEL_SCHEDULER_H */

