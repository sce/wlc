#include <stdlib.h>
#include <stdarg.h>
#include <chck/string/string.h>
#include "wlc/wlc.h"
#include "resources/resources.h"
#include "log.h"

void
wlc_log(enum wlc_log_type type, const char *fmt, ...)
{
   va_list argp;
   va_start(argp, fmt);
   wlc_vlog(type, fmt, argp);
   va_end(argp);
}

void
wlc_dlog(enum wlc_debug dbg, const char *fmt, ...)
{
   static struct {
      const char *name;
      bool active;
      bool checked;
   } channels[WLC_DBG_LAST] = {
      { "handle", false, false },
      { "render", false, false },
      { "render-loop", false, false },
      { "focus", false, false },
      { "xwm", false, false },
      { "keyboard", false, false },
      { "commit", false, false },
      { "request", false, false },
   };

   if (!channels[dbg].checked) {
      const char *name = channels[dbg].name;
      const char *s = getenv("WLC_DEBUG");
      for (size_t len = strlen(name); s && *s && !chck_cstrneq(s, name, len); s += strcspn(s, ",") + 1);
      channels[dbg].checked = true;
      if (!(channels[dbg].active = (s && *s != 0)))
         return;
   } else if (!channels[dbg].active) {
      return;
   }

   va_list argp;
   va_start(argp, fmt);
   wlc_vlog(WLC_LOG_INFO, fmt, argp);
   va_end(argp);
}
