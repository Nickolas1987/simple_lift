#pragma once
#include <list>
#include <cstdio>
namespace lift_np {
    template<class M> class subscriber;
    template<class M>
    class publisher {
    public:
        publisher();
        virtual ~publisher();
        bool subscribe(subscriber<M>& sub);
        bool unsubscribe(subscriber<M>& sub);
        bool is_subscribed(subscriber<M>& sub) const;
        size_t sub_count() const;
        int send(const M& msg);
    private:
        struct pub_impl {
            typedef std::list<void*> list_type;
            list_type subs;
            bool subscribe(void* sub);
            bool unsubscribe(void* sub);
            bool is_subscribed(void* sub) const;
            size_t sub_count() const;
        };
        pub_impl impl;
        publisher(const publisher&) = delete;
        publisher& operator=(const publisher&) = delete;
    };

    template<class M>
    class subscriber {
    public:
        subscriber();
        virtual ~subscriber();
        virtual bool action_on_msg(const publisher<M>& pub, const M& msg) = 0;
        void subscribed_msg(const publisher<M>& pub);
        void unsubscribed_msg(const publisher<M>& pub);
    private:
        virtual void subscribed_action(const publisher<M>& pub);
        virtual void unsubscribed_action(const publisher<M>& pub);
        typedef typename std::list<publisher<M>*> list_type;
        list_type pubs;
        subscriber(const subscriber&) = delete;
        subscriber& operator=(const subscriber&) = delete;
    };
    template<class M>
    bool publisher<M>::pub_impl::subscribe(void* sub) {
        if (is_subscribed(sub)) return 0;
        subs.push_back(sub);
        return 1;
    }
    template<class M>
    bool publisher<M>::pub_impl::unsubscribe(void* sub) {
        for (list_type::iterator it = subs.begin(), end = subs.end(); it != end; ++it) {
            if (*it == sub) {
                subs.erase(it);
                return 1;
            }
        }
        return 0;
    }
    template<class M>
    bool publisher<M>::pub_impl::is_subscribed(void* sub) const {
        for (list_type::const_iterator cit = subs.begin(), cend = subs.end(); cit != cend;
            ++cit) {
            if (*cit == sub) return 1;
        }
        return 0;
    }
    template<class M>
    size_t publisher<M>::pub_impl::sub_count() const {
        return subs.size();
    }
    template<class M>
    publisher<M>::publisher() {
    }
    template<class M>
    publisher<M>::~publisher() {
        for (typename pub_impl::list_type::const_iterator cit = impl.subs.begin(),
            cend = impl.subs.end(); cit != cend; ++cit) {
            subscriber<M>* psub = static_cast<subscriber<M>*>(*cit);
            psub->unsubscribed_msg(*this);
        }
    }
    template<class M>
    bool publisher<M>::subscribe(subscriber<M>& sub) {
        bool ret = impl.subscribe(&sub);
        if (ret) {
            sub.subscribed_msg(*this);
        }
        return ret;
    }
    template<class M>
    bool publisher<M>::unsubscribe(subscriber<M>& sub) {
        bool ret = impl.unsubscribe(&sub);
        if (ret) {
            sub.unsubscribed_msg(*this);
        }
        return ret;
    }
    template<class M>
    int publisher<M>::send(const M& msg) {
        int count = 0;
        for (typename pub_impl::list_type::iterator it = impl.subs.begin(),
            end = impl.subs.end(); it != end; ++count) {
            subscriber<M>* psub = static_cast<subscriber<M>*>(*it);

            bool ret = true;
            try { ret = psub->action_on_msg(*this, msg); }
            catch (...) {}  // игнорируем

            ++it;
            if (!ret) unsubscribe(*psub);
        }
        return count;
    }
    template<class M>
    bool publisher<M>::is_subscribed(subscriber<M>& sub) const {
        return impl.is_subscribed(&sub);
    }
    template<class M>
    size_t publisher<M>::sub_count() const {
        return impl.sub_count();
    }
    template<class M>
    subscriber<M>::subscriber() {
    }
    template<class M>
    subscriber<M>::~subscriber() {
        for (typename list_type::const_iterator cit = pubs.begin(), cend = pubs.end();
            cit != cend;) {
            (*(cit++))->unsubscribe(*this);
        }
    }
    template<class M>
    void subscriber<M>::subscribed_msg(const publisher<M>& val) {
        pubs.push_back(const_cast<publisher<M>*>(&val));
        try {
            subscribed_action(val);
        }
        catch (...) {
        }
    }
    template<class M>
    void subscriber<M>::unsubscribed_msg(const publisher<M>& val) {
        pubs.remove(const_cast<publisher<M>*>(&val));
        try {
            unsubscribed_action(val);
        }
        catch (...) {
        }
    }
    template<class M>
    void subscriber<M>::subscribed_action(const publisher<M>& pub) {
    }
    template<class M>
    void subscriber<M>::unsubscribed_action(const publisher<M>& pub) {
    }
}
