// http://www.boost.org/doc/libs/1_65_1/libs/geometry/doc/html/geometry/quickstart.html
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>

#include <boost/geometry/geometries/adapted/c_array.hpp>

BOOST_GEOMETRY_REGISTER_C_ARRAY_CS(cs::cartesian)

#include <boost/geometry/geometries/adapted/boost_tuple.hpp>

BOOST_GEOMETRY_REGISTER_BOOST_TUPLE_CS(cs::cartesian)

#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/index/rtree.hpp>

#include <boost/foreach.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/variant.hpp>

#include <boost/geometry/geometries/ring.hpp>
#include <boost/geometry/geometries/linestring.hpp>

#include <cmath>
#include <vector>
#include <map>
#include <iostream>
#include <hdf5_hl.h>
#include "termcolor/termcolor.hpp"

namespace boost {
    namespace geometry {
        namespace index {

            template<typename Box>
            struct indexable<boost::shared_ptr<Box> > {
                typedef boost::shared_ptr<Box> V;

                typedef Box const &result_type;

                result_type operator()(V const &v) const { return *v; }
            };

        }
    }
} // namespace boost::geometry::index

template <typename Container>
class my_indexable
{
        typedef typename Container::size_type size_t;
        typedef typename Container::const_reference cref;
        Container const& container;

    public:
        typedef cref result_type;
        explicit my_indexable(Container const& c) : container(c) {}
        result_type operator()(size_t i) const { return container[i]; }
};

int main() {
    using namespace boost::geometry;

    std::cout << termcolor::on_yellow << termcolor::bold << termcolor::underline << "Quick Start" << termcolor::reset
              << std::endl;

    std::cout << termcolor::bold << termcolor::underline << "Distance between two points" << termcolor::reset
              << std::endl;
    {
        model::d2::point_xy<int> p1(1, 1), p2(2, 2);
        std::cout << "Distance p1-p2 is: " << distance(p1, p2) << std::endl;
    }

    std::cout << termcolor::bold << termcolor::underline << "Other types as points" << termcolor::reset << std::endl;
    {
        int a[2] = {1, 1};
        int b[2] = {2, 3};
        double d = distance(a, b);
        std::cout << "Distance a-b is: " << d << std::endl;
    }

    std::cout << termcolor::bold << termcolor::underline << "Point within polygon" << termcolor::reset << std::endl;
    {
        double points[][2] = {{2.0, 1.3},
                              {4.1, 3.0},
                              {5.3, 2.6},
                              {2.9, 0.7},
                              {2.0, 1.3}};
        model::polygon<model::d2::point_xy<double> > poly;
        append(poly, points);
        boost::tuple<double, double> p = boost::make_tuple(3.7, 2.0);
        std::cout << "Point p is in polygon? " << std::boolalpha << within(p, poly) << std::endl;
        std::cout << "Area: " << area(poly) << std::endl;
        int a[2] = {1, 1};
        double d2 = distance(a, p);
        std::cout << "Distance a-p is: " << d2 << std::endl;
    }

    std::cout << termcolor::bold << termcolor::underline << "Non-Cartesian" << termcolor::reset << std::endl;
    {
        // We approximate the Earth as a sphere and calculate the distance between Amsterdam and Paris:
        typedef boost::geometry::model::point
                <double, 2, boost::geometry::cs::spherical_equatorial<boost::geometry::degree>> spherical_point;

        spherical_point amsterdam(4.90, 52.37);
        spherical_point paris(2.35, 48.86);

        double const earth_radius = 3959; // miles
        std::cout << "Distance in miles: " << distance(amsterdam, paris) * earth_radius << std::endl;
    }

    std::cout << termcolor::on_yellow << termcolor::bold << termcolor::underline << "Spatial Indexes"
              << termcolor::reset
              << std::endl;

    namespace bg = boost::geometry;
    namespace bgi = boost::geometry::index;

    std::cout << termcolor::bold << termcolor::underline << "R-Tree" << termcolor::reset << std::endl;
    {
        typedef bg::model::point<float, 2, bg::cs::cartesian> point;
        typedef bg::model::box<point> box;
        typedef std::pair<box, unsigned> value;

        // create the rtree using default constructor
        bgi::rtree<value, bgi::dynamic_rstar> rtree(bgi::dynamic_rstar(16));
        // create some values
        for (unsigned i = 0; i < 10; ++i) {
            // create a box
            box b(point(i + 0.0f, i + 0.0f), point(i + 0.5f, i + 0.5f));
            // insert new value
            rtree.insert(std::make_pair(b, i));
        }
        // find values intersecting some area defined by a box
        box query_box(point(0, 0), point(5, 5));
        std::vector<value> result_s;
        rtree.query(bgi::intersects(query_box), std::back_inserter(result_s));
        // find 5 nearest values to a point
        std::vector<value> result_n;
        rtree.query(bgi::nearest(point(0, 0), 5), std::back_inserter(result_n));
        // display results
        std::cout << "spatial query box:" << std::endl;
        std::cout << bg::wkt<box>(query_box) << std::endl;
        std::cout << "spatial query result:" << std::endl;
        BOOST_FOREACH(value const &v, result_s) {
                        std::cout << bg::wkt<box>(v.first) << " - " << v.second << std::endl;
                    }

        std::cout << "knn query point:" << std::endl;
        std::cout << bg::wkt<point>(point(0, 0)) << std::endl;
        std::cout << "knn query result:" << std::endl;
        BOOST_FOREACH(value const &v, result_n) {
                        std::cout << bg::wkt<box>(v.first) << " - " << v.second << std::endl;
                    }

        std::vector<value> result;
        rtree.query(index::contains(query_box), std::back_inserter(result));
        rtree.query(index::covered_by(query_box), std::back_inserter(result));
        rtree.query(index::covers(query_box), std::back_inserter(result));
        //rtree.query(index::disjont(query_box), std::back_inserter(result));
        rtree.query(index::intersects(query_box), std::back_inserter(result));
        rtree.query(index::overlaps(query_box), std::back_inserter(result));
        rtree.query(index::within(query_box), std::back_inserter(result));
        rtree.query(index::intersects(query_box) && !index::within(query_box),
                    std::back_inserter(result));
    }

    std::cout << termcolor::bold << termcolor::underline << "R-tree from vector" << termcolor::reset << std::endl;
    {
        typedef bg::model::point<float, 2, bg::cs::cartesian> point;
        typedef bg::model::box<point> box;
        typedef bg::model::polygon<point, false, false> polygon; // ccw, open polygon
        typedef std::pair<box, unsigned> value;

        // polygons
        std::vector<polygon> polygons;

        // create some polygons
        for (unsigned i = 0; i < 10; ++i) {
            // create a polygon
            polygon p;
            for (float a = 0; a < 6.28316f; a += 1.04720f) {
                float x = i + int(10 * ::cos(a)) * 0.1f;
                float y = i + int(10 * ::sin(a)) * 0.1f;
                p.outer().push_back(point(x, y));
            }

            // add polygon
            polygons.push_back(p);
        }

        // display polygons
        std::cout << "generated polygons:" << std::endl;
        BOOST_FOREACH(polygon const &p, polygons) {
                        std::cout << bg::wkt<polygon>(p) << std::endl;
                    }

        // create the rtree using default constructor
        bgi::rtree<value, bgi::rstar<16, 4> > rtree;

        // fill the spatial index
        for (unsigned i = 0; i < polygons.size(); ++i) {
            // calculate polygon bounding box
            box b = bg::return_envelope<box>(polygons[i]);
            // insert new value
            rtree.insert(std::make_pair(b, i));
        }

        // find values intersecting some area defined by a box
        box query_box(point(0, 0), point(5, 5));
        std::vector<value> result_s;
        rtree.query(bgi::intersects(query_box), std::back_inserter(result_s));

        // find 5 nearest values to a point
        std::vector<value> result_n;
        rtree.query(bgi::nearest(point(0, 0), 5), std::back_inserter(result_n));

        // note: in Boost.Geometry the WKT representation of a box is polygon

        // note: the values store the bounding boxes of polygons
        // the polygons aren't used for querying but are printed

        // display results
        std::cout << "spatial query box:" << std::endl;
        std::cout << bg::wkt<box>(query_box) << std::endl;
        std::cout << "spatial query result:" << std::endl;
        BOOST_FOREACH(value const &v, result_s) {
                        std::cout << bg::wkt<polygon>(polygons[v.second]) << std::endl;
                    }

        std::cout << "knn query point:" << std::endl;
        std::cout << bg::wkt<point>(point(0, 0)) << std::endl;
        std::cout << "knn query result:" << std::endl;
        BOOST_FOREACH(value const &v, result_n) {
                        std::cout << bg::wkt<polygon>(polygons[v.second]) << std::endl;
                    }
    }

    std::cout << termcolor::bold << termcolor::underline << "Shared pointers to polygons" << termcolor::reset
              << std::endl;
    {
        typedef bg::model::point<float, 2, bg::cs::cartesian> point;
        typedef bg::model::box<point> box;
        typedef bg::model::polygon<point, false, false> polygon; // ccw, open polygon
        typedef boost::shared_ptr<polygon> shp;
        typedef std::pair<box, shp> value;

        // create the rtree using default constructor
        bgi::rtree<value, bgi::linear<16, 4> > rtree;

        std::cout << "filling index with polygons shared pointers:" << std::endl;

        // create some polygons and fill the spatial index
        for (unsigned i = 0; i < 10; ++i) {
            // create a polygon
            shp p(new polygon());
            for (float a = 0; a < 6.28316f; a += 1.04720f) {
                float x = i + int(10 * ::cos(a)) * 0.1f;
                float y = i + int(10 * ::sin(a)) * 0.1f;
                p->outer().push_back(point(x, y));
            }

            // display new polygon
            std::cout << bg::wkt<polygon>(*p) << std::endl;

            // calculate polygon bounding box
            box b = bg::return_envelope<box>(*p);
            // insert new value
            rtree.insert(std::make_pair(b, p));
        }

        // find values intersecting some area defined by a box
        box query_box(point(0, 0), point(5, 5));
        std::vector<value> result_s;
        rtree.query(bgi::intersects(query_box), std::back_inserter(result_s));

        // find 5 nearest values to a point
        std::vector<value> result_n;
        rtree.query(bgi::nearest(point(0, 0), 5), std::back_inserter(result_n));

        // note: in Boost.Geometry the WKT representation of a box is polygon

        // note: the values store the bounding boxes of polygons
        // the polygons aren't used for querying but are printed

        // display results
        std::cout << "spatial query box:" << std::endl;
        std::cout << bg::wkt<box>(query_box) << std::endl;
        std::cout << "spatial query result:" << std::endl;
        BOOST_FOREACH(value const &v, result_s) {
                        std::cout << bg::wkt<polygon>(*v.second) << std::endl;
                    }

        std::cout << "knn query point:" << std::endl;
        std::cout << bg::wkt<point>(point(0, 0)) << std::endl;
        std::cout << "knn query result:" << std::endl;
        BOOST_FOREACH(value const &v, result_n) {
                        std::cout << bg::wkt<polygon>(*v.second) << std::endl;
                    }
    }

    std::cout << termcolor::bold << termcolor::underline << "Iterators of a map storing variant geometries"
              << termcolor::reset << std::endl;
    {
        typedef bg::model::point<float, 2, bg::cs::cartesian> point;
        typedef bg::model::box<point> box;
        typedef bg::model::polygon<point, false, false> polygon; // ccw, open polygon
        typedef bg::model::ring<point, false, false> ring; // ccw, open ring
        typedef bg::model::linestring<point> linestring;
        typedef boost::variant<polygon, ring, linestring> geometry;

        typedef std::map<unsigned, geometry> map;
        typedef std::pair<box, map::iterator> value;

        auto fill = [](unsigned i, auto &container) {
            for (float a = 0; a < 6.28316f; a += 1.04720f) {
                float x = i + int(10 * ::cos(a)) * 0.1f;
                float y = i + int(10 * ::sin(a)) * 0.1f;
                container.push_back(point(x, y));
            }
        };

        struct print_visitor
                : public boost::static_visitor<> {
            void operator()(polygon const &g) const { std::cout << bg::wkt<polygon>(g) << std::endl; }

            void operator()(ring const &g) const { std::cout << bg::wkt<ring>(g) << std::endl; }

            void operator()(linestring const &g) const { std::cout << bg::wkt<linestring>(g) << std::endl; }
        };

        struct envelope_visitor
                : public boost::static_visitor<box> {
            box operator()(polygon const &g) const { return bg::return_envelope<box>(g); }

            box operator()(ring const &g) const { return bg::return_envelope<box>(g); }

            box operator()(linestring const &g) const { return bg::return_envelope<box>(g); }
        };

        // geometries container
        map geometries;

        // create some geometries
        for (unsigned i = 0; i < 10; ++i) {
            unsigned c = rand() % 3;

            if (0 == c) {
                // create polygon
                polygon p;
                fill(i, p.outer());
                geometries.insert(std::make_pair(i, geometry(p)));
            } else if (1 == c) {
                // create ring
                ring r;
                fill(i, r);
                geometries.insert(std::make_pair(i, geometry(r)));
            } else if (2 == c) {
                // create linestring
                linestring l;
                fill(i, l);
                geometries.insert(std::make_pair(i, geometry(l)));
            }
        }

        // display geometries
        std::cout << "generated geometries:" << std::endl;
        BOOST_FOREACH(map::value_type const& p, geometries) {
                        boost::apply_visitor(print_visitor(), p.second);
                    }

        // create the rtree using default constructor
        bgi::rtree<value, bgi::quadratic<16, 4> > rtree;

        // fill the spatial index
        for (map::iterator it = geometries.begin(); it != geometries.end(); ++it) {
            // calculate polygon bounding box
            box b = boost::apply_visitor(envelope_visitor(), it->second);
            // insert new value
            rtree.insert(std::make_pair(b, it));
        }

        // find values intersecting some area defined by a box
        box query_box(point(0, 0), point(5, 5));
        std::vector<value> result_s;
        rtree.query(bgi::intersects(query_box), std::back_inserter(result_s));

        // find 5 nearest values to a point
        std::vector<value> result_n;
        rtree.query(bgi::nearest(point(0, 0), 5), std::back_inserter(result_n));

        // note: in Boost.Geometry the WKT representation of a box is polygon

        // note: the values store the bounding boxes of geometries
        // the geometries aren't used for querying but are printed

        // display results
        std::cout << "spatial query box:" << std::endl;
        std::cout << bg::wkt<box>(query_box) << std::endl;
        std::cout << "spatial query result:" << std::endl;
        BOOST_FOREACH(value const &v, result_s) {
                        boost::apply_visitor(print_visitor(), v.second->second);
                    }

        std::cout << "knn query point:" << std::endl;
        std::cout << bg::wkt<point>(point(0, 0)) << std::endl;
        std::cout << "knn query result:" << std::endl;
        BOOST_FOREACH(value const &v, result_n) {
                        boost::apply_visitor(print_visitor(), v.second->second);
                    }
    }

    std::cout << termcolor::bold << termcolor::underline
              << "index::indexable function object - storing shared pointers in the rtree" << termcolor::reset
              << std::endl;
    {
        typedef bg::model::point<float, 2, bg::cs::cartesian> point;
        typedef bg::model::box<point> box;
        typedef boost::shared_ptr<box> shp;
        typedef shp value;

        // create the rtree using default constructor
        bgi::rtree<value, bgi::linear<16, 4> > rtree;

        std::cout << "filling index with boxes shared pointers:" << std::endl;

        // fill the spatial index
        for (unsigned i = 0; i < 10; ++i) {
            // create a box
            shp b(new box(point(i + 0.0f, i + 0.0f), point(i + 0.5f, i + 0.5f)));

            // display new box
            std::cout << bg::wkt<box>(*b) << std::endl;

            // insert new value
            rtree.insert(b);
        }

        // find values intersecting some area defined by a box
        box query_box(point(0, 0), point(5, 5));
        std::vector<value> result_s;
        rtree.query(bgi::intersects(query_box), std::back_inserter(result_s));

        // find 5 nearest values to a point
        std::vector<value> result_n;
        rtree.query(bgi::nearest(point(0, 0), 5), std::back_inserter(result_n));

        // note: in Boost.Geometry the WKT representation of a box is polygon

        // display results
        std::cout << "spatial query box:" << std::endl;
        std::cout << bg::wkt<box>(query_box) << std::endl;
        std::cout << "spatial query result:" << std::endl;
        BOOST_FOREACH(value const &v, result_s) {
                                std::cout << bg::wkt<box>(*v) << std::endl;
                    }

        std::cout << "knn query point:" << std::endl;
        std::cout << bg::wkt<point>(point(0, 0)) << std::endl;
        std::cout << "knn query result:" << std::endl;
        BOOST_FOREACH(value const &v, result_n) {
                                std::cout << bg::wkt<box>(*v) << std::endl;
                    }
    }

    std::cout << termcolor::bold << termcolor::underline << "Using IndexableGetter function object - storing indexes of external container's elements" << termcolor::reset << std::endl;
    {


        typedef bg::model::point<float, 2, bg::cs::cartesian> point;
        typedef bg::model::box<point> box;
        typedef std::vector<box>::size_type value;
        typedef bgi::rstar<16, 4> parameters;
        typedef my_indexable< std::vector<box> > indexable_getter;

        // boxes
        std::vector<box> boxes;

        // create some boxes
        for ( unsigned i = 0 ; i < 10 ; ++i )
        {
            // add a box
            boxes.push_back(box(point(i+0.0f, i+0.0f), point(i+0.5f, i+0.5f)));
        }

        // display boxes
        std::cout << "generated boxes:" << std::endl;
        BOOST_FOREACH(box const& b, boxes)
                        std::cout << bg::wkt<box>(b) << std::endl;

        // create the rtree
        parameters params;
        indexable_getter ind(boxes);
        bgi::rtree<value, parameters, indexable_getter> rtree(params, ind);

        // fill the spatial index
        for ( size_t i = 0 ; i < boxes.size() ; ++i )
            rtree.insert(i);

        // find values intersecting some area defined by a box
        box query_box(point(0, 0), point(5, 5));
        std::vector<value> result_s;
        rtree.query(bgi::intersects(query_box), std::back_inserter(result_s));

        // find 5 nearest values to a point
        std::vector<value> result_n;
        rtree.query(bgi::nearest(point(0, 0), 5), std::back_inserter(result_n));

        // note: in Boost.Geometry the WKT representation of a box is polygon

        // display results
        std::cout << "spatial query box:" << std::endl;
        std::cout << bg::wkt<box>(query_box) << std::endl;
        std::cout << "spatial query result:" << std::endl;
        BOOST_FOREACH(value i, result_s)
                        std::cout << bg::wkt<box>(boxes[i]) << std::endl;

        std::cout << "knn query point:" << std::endl;
        std::cout << bg::wkt<point>(point(0, 0)) << std::endl;
        std::cout << "knn query result:" << std::endl;
        BOOST_FOREACH(value i, result_n)
                        std::cout << bg::wkt<box>(boxes[i]) << std::endl;
    }
}


