#ifndef D_PTR_H
#define D_PTR_H

#include <memory>

namespace hanalysis{
  class d_ptr;
}

// namespace kamd {
//   namespace utils {

template <typename T>
class d_ptr
{
private:
    std::unique_ptr<T> d;

public:
    d_ptr();

    template <typename... Args>
    d_ptr ( Args &&... );

    ~d_ptr();

    T *operator->() const;
};

#define D_PTR             \
    class HTagPrivate;        \
    friend class HTagPrivate; \
    const hanalysis::d_ptr<HTagPrivate> d

//   } // namespace utils
// } // namespace kamd

#endif
