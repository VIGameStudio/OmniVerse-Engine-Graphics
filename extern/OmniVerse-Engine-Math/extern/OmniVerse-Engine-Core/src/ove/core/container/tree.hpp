#pragma once

#include <ove/core/util/types.hpp>
#include <vector>

namespace core {

struct tree_t {
    template <typename T>
    struct node_t;

    struct inode_t {
        virtual size_t id() const { return -1; }

        template <typename T2>
        bool is() const
        {
            return node_t<T2>::type_id() == id();
        }

        bool isNull() const { return m_obj == nullptr; }

        template <typename T2>
        T2* get()
        {
            // static_assert(is<T2>(), "Invalid type!");

            if (isNull())
                return nullptr;
            return static_cast<T2*>(m_obj);
        }

        template <typename T2>
        void set(T2* obj)
        {
            // static_assert(is<T2>(), "Invalid type!");

            m_obj = static_cast<void*>(obj);
        }

        template <typename T2>
        void add(node_t<T2> node)
        {
            m_nodes.emplace_back(node);
        }

        template <typename T2>
        node_t<T2> add(T2* obj)
        {
            auto node = node_t<T2>(obj);
            add<T2>(node);
            return node;
        }

        std::vector<inode_t>::iterator begin() { return m_nodes.begin(); }
        std::vector<inode_t>::iterator end() { return m_nodes.end(); }
        size_t size() const { return m_nodes.size(); }

        void remove()
        {
            /// TODO: implement this.
        }

    protected:
        static size_t reg_type()
        {
            static size_t s_counter = 0;
            return s_counter++;
        }

    private:
        void* m_obj;
        std::vector<inode_t> m_nodes;
    };

    template <typename T>
    struct node_t : inode_t {
        node_t(T* obj) { set(obj); }

        virtual size_t id() const { return type_id(); }

        static size_t type_id()
        {
            static const size_t s_id = reg_type();
            return s_id;
        }
    };

    inode_t root;
};
}
