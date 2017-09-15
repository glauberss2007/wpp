#pragma once

#include "utility.h"
#include "http_request.h"
#include "http_response.h"

namespace wpp
{
    namespace detail
    {
        // define context for a list of middlewares
        template <typename ... Middlewares>
        struct partial_context
            // pop_back compile time array
            : public const_str::pop_back<Middlewares...>::template rebind<partial_context>
              // get the last element of the compile time array (as context)
            , public const_str::last_element_type<Middlewares...>::type::context
        {
            using parent_context = typename const_str::pop_back<Middlewares...>::template rebind<::wpp::detail::partial_context>;
            template <int N>
            using partial = typename std::conditional<N == sizeof...(Middlewares)-1, partial_context, typename parent_context::template partial<N>>::type;

            template <typename T>
            typename T::context& get()
            {
                return static_cast<typename T::context&>(*this);
            }
        };

        // defines context when there are no middlewares
        template <>
        struct partial_context<>
        {
            template <int>
            using partial = partial_context;
        };

        // function that calls all middlewares
        template <int N, typename Context, typename Container, typename CurrentMW, typename ... Middlewares>
        bool middleware_call_helper(Container& middlewares, request& req, response& res, Context& ctx);

        // full context
        template <typename ... Middlewares>
        struct context : private partial_context<Middlewares...>
        //struct context : private Middlewares::context... // simple but less type-safe
        {
            template <int N, typename Context, typename Container>
            friend typename std::enable_if<(N==0)>::type after_handlers_call_helper(Container& middlewares, Context& ctx, request& req, response& res);
            template <int N, typename Context, typename Container>
            friend typename std::enable_if<(N>0)>::type after_handlers_call_helper(Container& middlewares, Context& ctx, request& req, response& res);

            template <int N, typename Context, typename Container, typename CurrentMW, typename ... Middlewares2>
            friend bool middleware_call_helper(Container& middlewares, request& req, response& res, Context& ctx);

            template <typename T> 
            typename T::context& get()
            {
                return static_cast<typename T::context&>(*this);
            }

            template <int N>
            using partial = typename partial_context<Middlewares...>::template partial<N>;
        };
    }
}
