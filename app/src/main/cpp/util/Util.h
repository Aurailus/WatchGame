template<class C, typename Ret, typename ... Ts>
std::function<Ret(Ts...)> bind_this(C* c, Ret (C::*m)(Ts...)) {
    return [=](auto&& ... args) { return (c->*m)(std::forward<decltype(args)>(args)...); };
}

template<class C, typename Ret, typename ... Ts>
std::function<Ret(Ts...)> bind_this(const C* c, Ret (C::*m)(Ts...) const) {
    return [=](auto&& ... args) { return (c->*m)(std::forward<decltype(args)>(args)...); };
}