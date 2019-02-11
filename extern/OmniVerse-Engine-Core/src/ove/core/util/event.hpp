#pragma once

/**
 * TODO:
 * Revise
 */

#include <assert.h>
#include <functional>
#include <memory>
#include <stdlib.h>
#include <unordered_map>
#include <utility>
#include <vector>

#include <ove/core/util/guard.hpp>

/**
 * @brief Events
 */

struct base_signal_t {
    virtual ~base_signal_t() {}
    virtual void operator()(const void* p) = 0;

protected:
    static size_t reg_id()
    {
        static size_t counter = -1;
        return ++counter;
    }
};

template <typename E>
struct signal_t : public base_signal_t {
    explicit signal_t(std::function<void(const E&)> sigFn)
        : m_sigFn(sigFn)
    {
    }
    virtual void operator()(const void* p)
    {
        m_sigFn(*(static_cast<const E*>(p)));
    }

    static size_t id()
    {
        static const size_t id = reg_id();
        return id;
    }

private:
    std::function<void(const E&)> m_sigFn;
};

using sig_handle = std::pair<size_t, size_t>;

struct receiver_t {
    ~receiver_t()
    {
        if (m_sigHandles.size() > 0)
            m_clearSigFn(m_sigHandles);
    }

private:
    friend class eventbus_t;
    std::function<void(std::vector<sig_handle>&)> m_clearSigFn;
    std::vector<sig_handle> m_sigHandles;
};

class eventbus_t : nocopy {
public:
    using sig_sptr = std::shared_ptr<base_signal_t>;

    eventbus_t() {}
    ~eventbus_t()
    {
        // TODO, clean memory
    }

    template <typename E, typename R>
    void subscribe(R& receiver)
    {
        if (receiver.m_sigHandles.size() == 0) {
            receiver.m_clearSigFn = std::bind(&eventbus_t::clear, this, std::placeholders::_1);
        }

        void (R::*receive)(const E&) = &R::receive;
        auto signal = new signal_t<E>(std::bind(receive, &receiver, std::placeholders::_1));

        auto& sigSlots = slot_for(signal_t<E>::id());
        sigSlots.second[sigSlots.first] = sig_sptr(signal);

        receiver.m_sigHandles.emplace_back(
            std::make_pair(signal_t<E>::id(), sigSlots.first));

        sigSlots.first++;
    }

    template <typename E, typename R>
    void unsubscribe(R& receiver)
    {
        auto& sigSlots = slot_for(signal_t<E>::id());
        for (auto handle : receiver.m_sigHandles) {
            if (handle.first == signal_t<E>::id())
                sigSlots.second.erase(handle.second);
        }
    }

    template <typename E, typename... Args>
    void broadcast(Args... args)
    {
        broadcast(E(args...));
    }

    template <typename E>
    void broadcast(const E& event)
    {
        auto& sigSlots = slot_for(signal_t<E>::id());
        for (auto sig : sigSlots.second) {
            (*sig.second)(static_cast<const void*>(&event));
        }
    }

private:
    using sig_slot_t = std::unordered_map<size_t, sig_sptr>;

    std::pair<size_t, sig_slot_t>& slot_for(size_t id)
    {
        if (id >= m_bus.size())
            m_bus.resize(id + 1);
        return m_bus[id];
    }

    void clear(std::vector<sig_handle>& sigHandles)
    {
        for (auto handle : sigHandles) {
            auto& sigSlots = slot_for(handle.first);
            sigSlots.second.erase(handle.second);
        }
    }

    std::vector<std::pair<size_t, sig_slot_t>> m_bus;
};
