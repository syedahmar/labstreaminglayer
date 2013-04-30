#ifndef BOOST_THREAD_WIN32_MUTEX_HPP
#define BOOST_THREAD_WIN32_MUTEX_HPP
// (C) Copyright 2005-7 Anthony Williams
// (C) Copyright 2011-2012 Vicente J. Botet Escriba
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.lslboost.org/LICENSE_1_0.txt)

#include <lslboost/thread/win32/basic_timed_mutex.hpp>
#include <lslboost/thread/exceptions.hpp>
#include <lslboost/thread/locks.hpp>

#include <lslboost/config/abi_prefix.hpp>

namespace lslboost
{
    namespace detail
    {
        typedef ::lslboost::detail::basic_timed_mutex underlying_mutex;
    }

    class mutex:
        public ::lslboost::detail::underlying_mutex
    {
    public:
        BOOST_THREAD_NO_COPYABLE(mutex)
        mutex()
        {
            initialize();
        }
        ~mutex()
        {
            destroy();
        }

        typedef unique_lock<mutex> scoped_lock;
        typedef detail::try_lock_wrapper<mutex> scoped_try_lock;
    };

    typedef mutex try_mutex;

    class timed_mutex:
        public ::lslboost::detail::basic_timed_mutex
    {
    public:
        BOOST_THREAD_NO_COPYABLE(timed_mutex)
        timed_mutex()
        {
            initialize();
        }

        ~timed_mutex()
        {
            destroy();
        }

        typedef unique_lock<timed_mutex> scoped_timed_lock;
        typedef detail::try_lock_wrapper<timed_mutex> scoped_try_lock;
        typedef scoped_timed_lock scoped_lock;
    };
}

#include <lslboost/config/abi_suffix.hpp>

#endif
