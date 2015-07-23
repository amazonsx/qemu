/*
 * Event loop thread
 *
 * Copyright Red Hat Inc., 2013
 *
 * Authors:
 *  Stefan Hajnoczi   <stefanha@redhat.com>
 *
 * This work is licensed under the terms of the GNU GPL, version 2 or later.
 * See the COPYING file in the top-level directory.
 *
 */

#ifndef IOTHREAD_H
#define IOTHREAD_H

#include "block/aio.h"
#include "qemu/thread.h"

#define TYPE_IOTHREAD "iothread"

typedef struct {
    Object parent_obj;

    /* What the relationship between 
     * a IOThread and a I/O request or a I/O device?
     * I guess, each I/O device need a IOThread queue?
     * How does the GuestOS I/O request send to the I/O thread?
     * by shixiao
     */
    QemuThread thread;
    /* Use the GMainLoop IO multiplexing poll mechanism.
     * by shixiao
     */
    AioContext *ctx;
    /* For what?
     * by shixiao
     */
    QemuMutex init_done_lock;
    /* Condition Variable?
     * by shixiao
     */
    QemuCond init_done_cond;    /* is thread initialization done? */
    bool stopping;
    int thread_id;
} IOThread;

#define IOTHREAD(obj) \
   OBJECT_CHECK(IOThread, obj, TYPE_IOTHREAD)

IOThread *iothread_find(const char *id);
char *iothread_get_id(IOThread *iothread);
AioContext *iothread_get_aio_context(IOThread *iothread);

#endif /* IOTHREAD_H */
