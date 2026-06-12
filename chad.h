#ifndef CHAD_H
#define CHAD_H
/* Libchad
 *
 * This is the central libchad header, it simply includes all other libchad headers.
 * <chad.h" is not recommended to be used outside of prototying as its neither informative,
 *  or good for compile times.
 */

#include <chad/XXX.h>
#include <chad/dictate.h>
#include <chad/dyrect.h>
#include <chad/ini_file.h>
#include <chad/memory-units.h>
#include <chad/plumblism.h>
#include <chad/qx.h>
#include <chad/random/random.h>
#include <chad/remove_all.h>
#include <chad/roman.h>
#include <chad/sds.h>
#include <chad/slurp.h>
#include <chad/strlist.h>
#include <chad/terry.h>
#include <chad/change_directory.h>
#include <chad/utils.h>

// XXX: mega broken, plz fork
// c23 stuff and <these-fucking-things.h>
// #include <chad/hvec.h>
// #include <chad/hlist.h>

// XXX: <internal code"; will have to go
#include <chad/experimental/timespec.h>
#include <chad/experimental/ro.h>
#include <chad/experimental/terminal.h>
#include <chad/narg.h>

#endif
