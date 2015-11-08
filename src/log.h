#ifndef _LOG_H_
#define _LOG_H_

// This file is meant to include definitions for code that relate to debug
// logging. Since that has such widespread usage, it is included in internal.h
// as of writing.
//
// Not all of the code in this file is defined in log.c, due to scope issues
// some of it can be defined other places (this is similar to how internal.h
// works).

#if __GNUC__
#  define WLC_LOG_ATTR(x, y) __attribute__((format(printf, x, y)))
#else
#  define WLC_LOG_ATTR(x, y)
#endif

/** Types of debug for  wlc_dlog */
enum wlc_debug {
   WLC_DBG_HANDLE,
   WLC_DBG_RENDER,
   WLC_DBG_RENDER_LOOP,
   WLC_DBG_FOCUS,
   WLC_DBG_XWM,
   WLC_DBG_KEYBOARD,
   WLC_DBG_COMMIT,
   WLC_DBG_REQUEST,
   WLC_DBG_LAST,
};

/** Log through wlc's log system. */
WLC_NONULLV(2) WLC_LOG_ATTR(2, 3) void wlc_log(enum wlc_log_type type, const char *fmt, ...);

/** va_list version of wlc_log. */
WLC_NONULL void wlc_vlog(enum wlc_log_type type, const char *fmt, va_list ap);

/** Debug log, the output is controlled by WLC_DEBUG env variable. */
WLC_NONULLV(2) WLC_LOG_ATTR(2, 3) void wlc_dlog(enum wlc_debug dbg, const char *fmt, ...);

/** Use only on fatals, currently only wlc.c */
WLC_NONULLV(1) WLC_LOG_ATTR(1, 2) static inline void
die(const char *format, ...)
{
   va_list vargs;
   va_start(vargs, format);
   wlc_vlog(WLC_LOG_ERROR, format, vargs);
   va_end(vargs);
   exit(EXIT_FAILURE);
}

char* wlc_resource_text(struct wlc_resource *r);
void wlc_resource_log(enum wlc_log_type type, struct wlc_resource *r, const char *fmt, ...);

#endif
