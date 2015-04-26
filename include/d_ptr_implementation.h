#ifndef D_PTR_IMPLEMENTATION_H
#define D_PTR_IMPLEMENTATION_H

#include <utility>
#include "d_ptr.h"

namespace hanalysis {
//   namespace utils {

template <typename T>
d_ptr<T>::d_ptr()
    : d ( new T() )
{
}

template <typename T>
template <typename... Args>
d_ptr<T>::d_ptr ( Args &&... args )
    : d ( new T ( std::forward<Args> ( args )... ) )
{
}

template <typename T>
d_ptr<T>::~d_ptr()
{
}

template <typename T>
T *d_ptr<T>::operator->() const
{
    return d.get();
}

//   } // namespace utils
} // namespace kamd

#endif
