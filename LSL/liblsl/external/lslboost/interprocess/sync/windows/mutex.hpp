//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2011. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.lslboost.org/LICENSE_1_0.txt)
//
// See http://www.lslboost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_DETAIL_WINDOWS_MUTEX_HPP
#define BOOST_INTERPROCESS_DETAIL_WINDOWS_MUTEX_HPP

#if (defined _MSC_VER) && (_MSC_VER >= 1200)
#  pragma once
#endif

#include <lslboost/interprocess/detail/config_begin.hpp>
#include <lslboost/interprocess/detail/workaround.hpp>
#include <lslboost/interprocess/detail/posix_time_types_wrk.hpp>
#include <lslboost/interprocess/detail/win32_api.hpp>
#include <lslboost/interprocess/detail/windows_intermodule_singleton.hpp>
#include <lslboost/interprocess/sync/windows/sync_utils.hpp>
#include <lslboost/interprocess/sync/windows/winapi_mutex_wrapper.hpp>
#include <lslboost/interprocess/exceptions.hpp>


namespace lslboost {
namespace interprocess {
namespace ipcdetail {

class windows_mutex
{
   windows_mutex(const windows_mutex &);
   windows_mutex &operator=(const windows_mutex &);
   public:

   windows_mutex();
   ~windows_mutex();

   void lock();
   bool try_lock();
   bool timed_lock(const lslboost::posix_time::ptime &abs_time);
   void unlock();
   void take_ownership(){};

   private:
   const sync_id id_;
};

inline windows_mutex::windows_mutex()
   : id_()
{
   sync_handles &handles =
      windows_intermodule_singleton<sync_handles>::get();
   //Create mutex with the initial count
   bool open_or_created;
   handles.obtain_mutex(this->id_, &open_or_created);
   //The mutex must be created, never opened
   assert(open_or_created);
   assert(open_or_created && winapi::get_last_error() != winapi::error_already_exists);
   (void)open_or_created;
}

inline windows_mutex::~windows_mutex()
{
   sync_handles &handles =
      windows_intermodule_singleton<sync_handles>::get();
   handles.destroy_handle(this->id_);
}

inline void windows_mutex::lock(void)
{
   sync_handles &handles =
      windows_intermodule_singleton<sync_handles>::get();
   //This can throw
   winapi_mutex_functions mut(handles.obtain_mutex(this->id_));
   mut.lock();
}

inline bool windows_mutex::try_lock(void)
{
   sync_handles &handles =
      windows_intermodule_singleton<sync_handles>::get();
   //This can throw
   winapi_mutex_functions mut(handles.obtain_mutex(this->id_));
   return mut.try_lock();
}

inline bool windows_mutex::timed_lock(const lslboost::posix_time::ptime &abs_time)
{
   sync_handles &handles =
      windows_intermodule_singleton<sync_handles>::get();
   //This can throw
   winapi_mutex_functions mut(handles.obtain_mutex(this->id_));
   return mut.timed_lock(abs_time);
}

inline void windows_mutex::unlock(void)
{
   sync_handles &handles =
      windows_intermodule_singleton<sync_handles>::get();
   //This can throw
   winapi_mutex_functions mut(handles.obtain_mutex(this->id_));
   return mut.unlock();
}

}  //namespace ipcdetail {
}  //namespace interprocess {
}  //namespace lslboost {

#include <lslboost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_DETAIL_WINDOWS_MUTEX_HPP
