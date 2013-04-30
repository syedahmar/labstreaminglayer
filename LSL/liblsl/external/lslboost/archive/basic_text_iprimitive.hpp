#ifndef BOOST_ARCHIVE_BASIC_TEXT_IPRIMITIVE_HPP
#define BOOST_ARCHIVE_BASIC_TEXT_IPRIMITIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// basic_text_iprimitive.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com . 
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.lslboost.org/LICENSE_1_0.txt)

//  See http://www.lslboost.org for updates, documentation, and revision history.

// archives stored as text - note these are templated on the basic
// stream templates to accommodate wide (and other?) kind of characters
//
// Note the fact that on libraries without wide characters, ostream is
// not a specialization of basic_ostream which in fact is not defined
// in such cases.   So we can't use basic_ostream<IStream::char_type> but rather
// use two template parameters

#include <lslboost/assert.hpp>
#include <locale>
#include <cstddef> // size_t

#include <lslboost/config.hpp>
#if defined(BOOST_NO_STDC_NAMESPACE)
namespace std{ 
    using ::size_t; 
    #if ! defined(BOOST_DINKUMWARE_STDLIB) && ! defined(__SGI_STL_PORT)
        using ::locale;
    #endif
} // namespace std
#endif

#include <lslboost/detail/workaround.hpp>
#if BOOST_WORKAROUND(BOOST_DINKUMWARE_STDLIB, == 1)
#include <lslboost/archive/dinkumware.hpp>
#endif

#include <lslboost/limits.hpp>
#include <lslboost/io/ios_state.hpp>
#include <lslboost/scoped_ptr.hpp>
#include <lslboost/static_assert.hpp>

#include <lslboost/serialization/throw_exception.hpp>
#include <lslboost/archive/archive_exception.hpp>
#include <lslboost/archive/basic_streambuf_locale_saver.hpp>
#include <lslboost/archive/detail/abi_prefix.hpp> // must be the last header

namespace lslboost {
namespace archive {

/////////////////////////////////////////////////////////////////////////
// class basic_text_iarchive - load serialized objects from a input text stream
#if defined(_MSC_VER)
#pragma warning( push )
#pragma warning( disable : 4244 4267 )
#endif

template<class IStream>
class basic_text_iprimitive
{
#ifndef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
protected:
#else
public:
#endif
    IStream &is;
    io::ios_flags_saver flags_saver;
    io::ios_precision_saver precision_saver;

    #ifndef BOOST_NO_STD_LOCALE
    lslboost::scoped_ptr<std::locale> archive_locale;
    basic_streambuf_locale_saver<
        BOOST_DEDUCED_TYPENAME IStream::char_type, 
        BOOST_DEDUCED_TYPENAME IStream::traits_type
    > locale_saver;
    #endif

    template<class T>
    void load(T & t)
    {
        if(! is.fail()){
            is >> t;
            return;
        }
        lslboost::serialization::throw_exception(
            archive_exception(archive_exception::input_stream_error)
        );
    }

    void load(char & t)
    {
        short int i;
        load(i);
        t = i;
    }
    void load(signed char & t)
    {
        short int i;
        load(i);
        t = i;
    }
    void load(unsigned char & t)
    {
        unsigned short int i;
        load(i);
        t = i;
    }

    #ifndef BOOST_NO_INTRINSIC_WCHAR_T
    void load(wchar_t & t)
    {
        BOOST_STATIC_ASSERT(sizeof(wchar_t) <= sizeof(int));
        int i;
        load(i);
        t = i;
    }
    #endif
    BOOST_ARCHIVE_OR_WARCHIVE_DECL(BOOST_PP_EMPTY()) 
    basic_text_iprimitive(IStream  &is, bool no_codecvt);
    BOOST_ARCHIVE_OR_WARCHIVE_DECL(BOOST_PP_EMPTY()) 
    ~basic_text_iprimitive();
public:
    BOOST_ARCHIVE_OR_WARCHIVE_DECL(void)
    load_binary(void *address, std::size_t count);
};

#if defined(_MSC_VER)
#pragma warning( pop )
#endif

} // namespace archive
} // namespace lslboost

#include <lslboost/archive/detail/abi_suffix.hpp> // pop pragmas

#endif // BOOST_ARCHIVE_BASIC_TEXT_IPRIMITIVE_HPP
