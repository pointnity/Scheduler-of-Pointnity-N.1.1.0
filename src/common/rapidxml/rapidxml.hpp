#ifndef RAPIDXML_HPP_INCLUDED
#define RAPIDXML_HPP_INCLUDED
#if !defined(RAPIDXML_NO_STDLIB)
    #include <cstdlib>      // For std::size_t
    #include <cassert>      // For assert
    #include <new>          // For placement new
#endif

// On MSVC, disable "conditional expression is constant" warning (level 4). 
// This warning is almost impossible to avoid with certain types of templated code
#ifdef _MSC_VER
    #pragma warning(push)
    #pragma warning(disable:4127)   // Conditional expression is constant
#endif

///////////////////////////////////////////////////////////////////////////
// RAPIDXML_PARSE_ERROR
    
#if defined(RAPIDXML_NO_EXCEPTIONS)

#define RAPIDXML_PARSE_ERROR(what, where) { parse_error_handler(what, where); assert(0); }

namespace rapidxml
{
    //! When exceptions are disabled by defining RAPIDXML_NO_EXCEPTIONS, 
    //! this function is called to notify user about the error.
    //! It must be defined by the user.
    //! <br><br>
    //! This function cannot return. If it does, the results are undefined.
    //! <br><br>
    //! A very simple definition might look like that:
    //! <pre>
    //! void %rapidxml::%parse_error_handler(const char *what, void *where)
    //! {
    //!     std::cout << "Parse error: " << what << "\n";
    //!     std::abort();
    //! }
    //! </pre>
    //! \param what Human readable description of the error.
    //! \param where Pointer to character data where error was detected.
    void parse_error_handler(const char *what, void *where);
}

#else
    
#include <exception>    // For std::exception

#define RAPIDXML_PARSE_ERROR(what, where) throw parse_error(what, where)

namespace rapidxml
{

    //! Parse error exception. 
    //! This exception is thrown by the parser when an error occurs. 
    //! Use what() function to get human-readable error message. 
    //! Use where() function to get a pointer to position within source text where error was detected.
    //! <br><br>
    //! If throwing exceptions by the parser is undesirable, 
    //! it can be disabled by defining RAPIDXML_NO_EXCEPTIONS macro before rapidxml.hpp is included.
    //! This will cause the parser to call rapidxml::parse_error_handler() function instead of throwing an exception.
    //! This function must be defined by the user.
