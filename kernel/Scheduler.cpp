/*
 * Copyright (C) 2015 Niek Linnenbank
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

#include <Log.h>
#include "Kernel.h"
#include "Scheduler.h"

// Constructor
Scheduler::Scheduler()
{
    DEBUG("");
}

// Returns the number of processes in the queue
Size Scheduler::count() const
{
    return m_queue.count();
}

// Adds a process to the queue
Scheduler::Result Scheduler::enqueue(Process *proc, bool ignoreState)
{
    // If the process is not in the Ready state and ignoreState is not set, return an error
    if (proc->getState() != Process::Ready && !ignoreState)
    {
        ERROR("process ID " << proc->getID() << " not in Ready state");
        return InvalidArgument;
    }

    // Add the process to the end of the queue
    m_queue.push(proc);
    return Success;
}

// Removes a process from the queue
Scheduler::Result Scheduler::dequeue(Process *proc, bool ignoreState)
{
    // If the process is in the Ready state and ignoreState is not set, return an error
    if (proc->getState() == Process::Ready && !ignoreState)
    {
        ERROR("process ID " << proc->getID() << " is in Ready state");
        return InvalidArgument;
    }

    // Traverse the queue to find the process to remove
    Size count = m_queue.count();
    for (Size i = 0; i < count; i++)
    {
        Process *p = m_queue.pop();

        // If the process is found, remove it from the queue and return Success
        if (p == proc)
            return Success;
        else
            // If the process is not the one to remove, add it back to the queue
            m_queue.push(p);
    }

    // If the process was not found in the queue, return an error
    FATAL("process ID " << proc->getID() << " is not in the schedule");
    return InvalidArgument;
}

// Returns the next process in the queue
Process * Scheduler::select()
{
    // If there are processes in the queue, return the first one
    if (m_queue.count() > 0)
    {
        Process *p = m_queue.pop();
        m_queue.push(p);

        return p;
    }

    // If there are no processes in the queue, return NULL
    return (Process *) NULL;
}
