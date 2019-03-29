#ifndef RAPIDXML_UTILS_HPP_INCLUDED
#define RAPIDXML_UTILS_HPP_INCLUDED
//! \file rapidxml_utils.hpp This file contains high-level rapidxml utilities that can be useful
//! in certain simple scenarios. They should probably not be used if maximizing performance is the main objective.

#include "rapidxml.hpp"
#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>

namespace rapidxml
{

    //! Represents data loaded from a file
    template<class Ch = char>
    class file
    {
        
    public:
        
        //! Loads file into the memory. Data will be automatically destroyed by the destructor.
        //! \param filename Filename to load.
        file(const char *filename)
        {
            using namespace std;

            // Open stream
            basic_ifstream<Ch> stream(filename, ios::binary);
            if (!stream)
                throw runtime_error(string("cannot open file ") + filename);
            stream.unsetf(ios::skipws);
            
            // Determine stream size
            stream.seekg(0, ios::end);
            size_t size = stream.tellg();
            stream.seekg(0);   
            
            // Load data and add terminating 0
            m_data.resize(size + 1);
            stream.read(&m_data.front(), static_cast<streamsize>(size));
            m_data[size] = 0;
        }

        //! Loads file into the memory. Data will be automatically destroyed by the destructor
        //! \param stream Stream to load from
