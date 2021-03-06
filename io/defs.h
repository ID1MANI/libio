/*
 * Copyright (c) 2011, Wouter Coene <wouter@irdc.nl>
 * 
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef IO_DEFS_H
#define IO_DEFS_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <sys/types.h>

/*
 * C++ compatibility
 */
#ifdef __cplusplus
# define IO_BEGIN_DECLS	extern "C" {
# define IO_END_DECLS	}
#else
# define IO_BEGIN_DECLS
# define IO_END_DECLS
#endif

/*
 * Public API
 */
#define IOAPI	extern

IO_BEGIN_DECLS

/*
 * Types of handle
 */
struct ioloop;
struct ioevent;
struct ioendpoint;
struct ioqueue;

enum ioevent_kind;
enum ioevent_opt;

/**
 * Type of an event callback function.
 *
 * \param num	Argument whose meaning depends on the kind of event:
 *		 - \link ioevent_read() Read\endlink or \link ioevent_write()
 *		   write\endlink events: the file descriptor that is being
 *		   monitored.
 *		 - \link ioevent_signal() Signal\endlink events: the signal
 *		   that is being monitored.
 *		 - \link ioevent_child() Child\endlink events: the exit code
 *		   the child process being monitored terminated with.
 *		 - For all other events, this parameter has no meaning.
 * \param arg	Additional argument passed to the event allocation function.
 */
typedef void (ioevent_cb_t)(int num, void *arg);

/**
 * I/O buffer structure for scatter/gather I/O. Should be compatible with
 * struct iovec, but since we'd rather not rely on <sys/uio.h> we provide
 * our own.
 */
struct iobuf {
	void	*base;			/**< Buffer starting address. */
	size_t	 len;			/**< Length of buffer in bytes. */
};

/**
 * I/O parameter structure, for configuring I/O queues. These are identified
 * by their address.
 */
struct ioparam {
	const char	*name;		/**< Parameter name, for debugging
					 *   purposes. */
};

/**
 * Parameter initialisation structure.
 */
struct ioparam_init {
	const struct ioparam	*param;
	uintptr_t		 value;
};

IO_END_DECLS

#endif /* IO_DEFS_H */
