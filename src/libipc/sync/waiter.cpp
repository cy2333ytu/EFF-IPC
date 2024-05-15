#include "libipc/waiter.h"
#include "libipc/platform/detail.h"
#include "libipc/platform/linux/mutex.h"


namespace ipc {
namespace detail {

void waiter::init() {
    ipc::detail::sync::mutex::init();
}

} // namespace detail
} // namespace ipc
