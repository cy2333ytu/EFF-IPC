#pragma once

#if defined(__GNUC__) && defined(__linux__)
#   define IPC_DECL_EXPORT  __attribute__((visibility("default")))
#   define IPC_DECL_IMPORT  __attribute__((visibility("default")))
#endif

/**
 * Define IPC_EXPORT for exporting function & class.
*/

#ifndef IPC_EXPORT
#if defined(LIBIPC_LIBRARY_SHARED_BUILDING__)
#  define IPC_EXPORT IPC_DECL_EXPORT
#elif defined(LIBIPC_LIBRARY_SHARED_USING__)
#  define IPC_EXPORT IPC_DECL_IMPORT
#else
#  define IPC_EXPORT
#endif
#endif /*IPC_EXPORT*/