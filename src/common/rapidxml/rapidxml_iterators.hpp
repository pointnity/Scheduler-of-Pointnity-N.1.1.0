#ifndef RAPIDXML_ITERATORS_HPP_INCLUDED
#define RAPIDXML_ITERATORS_HPP_INCLUDED
//! \file rapidxml_iterators.hpp This file contains rapidxml iterators

#include "rapidxml.hpp"

namespace rapidxml
{

    //! Iterator of child nodes of xml_node
    template<class Ch>
    class node_iterator
    {
    
    public:

        typedef typename xml_node<Ch> value_type;
        typedef typename xml_node<Ch> &reference;
