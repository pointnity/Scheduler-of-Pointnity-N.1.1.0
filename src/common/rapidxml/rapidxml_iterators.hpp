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
        typedef typename xml_node<Ch> *pointer;
        typedef std::ptrdiff_t difference_type;
        typedef std::bidirectional_iterator_tag iterator_category;
        
        node_iterator()
            : m_node(0)
        {
        }

        node_iterator(xml_node<Ch> *node)
            : m_node(node->first_node())
        {
        }
        
        reference operator *() const
        {
            assert(m_node);
            return *m_node;
        }

        pointer operator->() const
        {
            assert(m_node);
            return m_node;
        }

        node_iterator& operator++()
        {
            assert(m_node);
            m_node = m_node->next_sibling();
            return *this;
        }

        node_iterator operator++(int)
        {
            node_iterator tmp = *this;
            ++this;
            return tmp;
        }

        node_iterator& operator--()
        {
            assert(m_node && m_node->previous_sibling());
            m_node = m_node->previous_sibling();
            return *this;
        }

        node_iterator operator--(int)
        {
            node_iterator tmp = *this;
            ++this;
            return tmp;
        }

        bool operator ==(const node_iterator<Ch> &rhs)
        {
            return m_node == rhs.m_node;
        }

        bool operator !=(const node_iterator<Ch> &rhs)
        {
            return m_node != rhs.m_node;
        }

    private:
