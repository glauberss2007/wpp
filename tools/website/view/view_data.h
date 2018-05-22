//
// Created by Alan de Freitas on 10/02/17.
//

#ifndef WPP_REGISTER_VIEW_DATA_H_H
#define WPP_REGISTER_VIEW_DATA_H_H

#include <string>
#include <utility>
#include <functional>
#include <tuple>
#include <ctime>

#include <w++>

using string_type = std::string;
using lambda_type = std::function<string_type(const string_type &)>;
using namespace std;
using namespace wpp;

void register_view_data(application &app) {

    ////////////////////////////////////////////////////////////////
    //          DATA ATTACHED TO CERTAIN VIEWS OR PARTIALS        //
    ////////////////////////////////////////////////////////////////

    app.view_data("layouts/partials/navbar.html",[&app]() {
        wpp::json context;
        context["menu"] = {
                {{"name", "Features"},  {"link",     app.url_for("features")}},
                {{"name", "Pricing"},   {"link",     app.url_for("pricing")}},
                {{"name", "Login"},     {"link",     app.url_for("login")}},
                {{"name", "Info"},      {"link",     app.url_for("info")}},
                //{{"title", "Pages"},     {"dropdown", {
                //                                             {{"title", "Career"}, {"link", "career.html"}},
                //                                             {{"title", "Blog Single"}, {"link", "blog-item.html"}},
                //                                             {{"title", "Pricing"}, {"link", "pricing.html"}},
                //                                             {{"title", "404"}, {"link", "404.html"}},
                //                                             {{"title", "Registration"}, {"link", "about-us.html"}},
                //                                             {{"divider", true}},
                //                                             {{"title", "Privacy Policy"}, {"link", "privacy.html"}},
                //                                             {{"title", "Terms of Use"}, {"link", "terms.html"}}
                //                                     }}},
                {{"name", "Get Started FREE"},      {"link",     app.url_for("signup")}, {"bgcolor","#2ecc71"}, {"color","white"}}
                //{{"title", "Contact"},   {"link",     app.url_for("contact-us")}}
        };
        return context;
    });

    app.view_data("layouts/partials/tools.html",[&app]() {
        wpp::json context;
        context["tools"] = {
                {{"name", "Task and Project Management"}, {"thumbnail", app.asset("images/portfolio/recent/item1.png")}, {"img", app.asset("images/portfolio/full/item1.jpg")}},
                {{"name", "Timelines"}, {"thumbnail", app.asset("images/portfolio/recent/item3.png")}, {"img", app.asset("images/portfolio/full/item1.jpg")}},
                {{"name", "Integrations"}, {"thumbnail", app.asset("images/portfolio/recent/item2.png")}, {"img", app.asset("images/portfolio/full/item1.jpg")}},
                {{"name", "Mobile apps"}, {"thumbnail", app.asset("images/portfolio/recent/item1.png")}, {"img", app.asset("images/portfolio/full/item1.jpg")}},
                {{"name", "Full website"}, {"thumbnail", app.asset("images/portfolio/recent/item3.png")}, {"img", app.asset("images/portfolio/full/item1.jpg")}},
                {{"name", "e-commerce"}, {"thumbnail", app.asset("images/portfolio/recent/item2.png")}, {"img", app.asset("images/portfolio/full/item1.jpg")}},
        };
        return context;
    });

    app.view_data("layouts/partials/testimonial.html",[&app]() {
        wpp::json context;
        context["testimonials"] = {
                {{"text", "Small businesses"}, {"details", "Smart LAO has the perfect tools to manage your team and reach your clients"}},
                {{"text", "Corporations"}, {"details", "Our big data systems allow management to minimal details"}},
                {{"text", "Services"}, {"details", "Reach people with your brand app and website"}},
                {{"text", "Retail"}, {"details", "Set up your e-commerce in no time"}},
        };
        context["testimonials_title"] = "Thousands of companies get more done with Smart LAO";
        context["testimonials_subtitle"] = "Have a look at the apps that can boost your business";
        return context;
    });

    app.view_data("layouts/partials/bottom_links.html",[&app]() {
        wpp::json context;
        context["bottom_links"] = {
                {{"title", "Company"}, {"links", {
                                                         {{"title", "About"}, {"link", app.url_for("about-us")}},
                                                         {{"title", "Press Kit"}, {"link", app.url_for("press-kit")}},
                                                         {{"title", "Careers"}, {"link", app.url_for("careers")}},
                                                         {{"title", "Site Map"}, {"link", app.url_for("site-map")}},
                                                         {{"title", "Help Center"}, {"link", app.url_for("help-center")}},
                                                         {{"title", "Contact Us"}, {"link", app.url_for("contact-us")}},
                                                 }}},
                {{"title", "Smart LAO"}, {"links", {
                                                         {{"title", "Project Management Templates"}, {"link", app.url_for("Project Management Templates")}},
                                                         {{"title", "Case Studies"}, {"link", app.url_for("Case Studies")}},
                                                         {{"title", "Integrations"}, {"link", app.url_for("Integrations")}},
                                                         {{"title", "API"}, {"link", app.url_for("API")}},
                                                         {{"title", "Apps"}, {"link", app.url_for("Apps")}},
                                                 }}},
                {{"title", "Customers"}, {"links", {
                                                         {{"title", "Marketing and Creative"}, {"link", app.url_for("Marketing and Creative")}},
                                                         {{"title", "IT Teams"}, {"link", app.url_for("IT Teams")}},
                                                         {{"title", "Management Teams"}, {"link", app.url_for("Management Teams")}},
                                                         {{"title", "Remote Teams"}, {"link", app.url_for("Remote Teams")}},
                                                         {{"title", "Non-Profit and Education"}, {"link", app.url_for("Non-Profit and Education")}},
                                                 }}},
                {{"title", "Solutions"}, {"links", {
                                                         {{"title", "Project Management"}, {"link", app.url_for("Project Management")}},
                                                         {{"title", "Task Management"}, {"link", app.url_for("Task Management")}},
                                                         {{"title", "Gantt"}, {"link", app.url_for("Gantt")}},
                                                         {{"title", "Kanban Boards"}, {"link", app.url_for("Kanban Boards")}},
                                                 }}}
        };
        context["testimonials_title"] = "Thousands of companies get more done with Smart LAO";
        context["testimonials_subtitle"] = "Have a look at the apps that can boost your business";
        return context;
    });

    app.view_data("layouts/partials/slider.html",[&app]() {
        wpp::json context;
        context["carousel_items"] = {
                {{"background-image", /*1920 × 750*/app.asset("images/slider/bg1.jpg")},
                        {"item1", "Get more done"},
                        {"item2", "Optimize your business with easy tools for big data mining. Make your workflow easier so your teams will never be lost again."},
                        {"active", true},
                        {"index", 0},
                        {"boxed", true},
                        {"learn-more", app.url_for("login")},
                        {"learn-more-text", "Try for free"},
                        {"text-centered", false},
                        {"animation", "//player.vimeo.com/video/79098420?title=0&amp;byline=0&amp;portrait=0&amp;color=a22c2f"}
                },
                {{"background-image",               app.asset("images/slider/bg2.jpg")},
                        {"item1", "Manage your business professionaly."},
                        {"item2", "Organize tasks. Keep track of products. Manage your team with our project management tools."},
                        {"active", false},
                        {"boxed", true},
                        {"index", 1},
                        {"learn-more", app.url_for("login")},
                        {"learn-more-text", "Try now for free"},
                        {"text-centered", true}
                },
                {{"background-image",               app.asset("images/slider/bg3.jpg")},
                        {"item1", "Find your clients."},
                        {"item2", "Use our analytic tools to find and keep your clients happy. Manage websites, e-commerce, marketing for any place."},
                        {"active", false},
                        {"boxed", true},
                        {"index", 2},
                        {"text-centered", true},
                        {"learn-more", app.url_for("login")},
                        {"learn-more-text", "Try for free"}
                }
        };
        return context;
    });

    app.view_data("layouts/partials/footer.html",[&app]() {
        wpp::json context;
        time_t t = time(0);   // get time now
        struct tm * now = localtime( & t );
        context["year"] = to_string((now->tm_year + 1900));
        context["footer_links"] = {
                {{"title","Facebook"},{"link","http://www.facebook.com"}},
                {{"title","About us"},{"link",app.url_for("about-us")}},
                {{"title","Help Center"},{"link",app.url_for("help-center")}},
                {{"title","Contact Us"},{"link",app.url_for("contact-us")}}
        };
        return context;
    });

    app.view_data("layouts/partials/head.html",[&app]() {
        wpp::json context;
        context["title"] = "Smart LAO";
        context["full_title"] = "Smart Logistics, Analytics, and Optimization | Smart LAO";
        return context;
    });

    app.view_data("layouts/partials/services.html",[&app]() {
        wpp::json context;
        context["services"] = {
                {{"media-heading", "Project Management"},
                 {"description", "Be 100% aware of what is going on with your team. Assign tasks and analyse performance."},
                 {"icon", "fa fa-calendar-plus-o"}},
                {{"media-heading", "Product Management"},
                 {"description", "Use our big data tools and never miss opportunities for your products. Use that information in our marketing and e-commerce tools."},
                 {"icon", "fa fa-shopping-basket"}},
                {{"media-heading", "Client Management"},
                 {"description", "Know exactly where your clients and potential clients are. Know what they like. Know how to keep them."},
                 {"icon", "fa fa-users"}}
            };
        return context;
    });

} // end (void register_view_lambdas(application &app))


#endif //WPP_REGISTER_VIEW_DATA_H_H
