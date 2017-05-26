//
// Created by Alan de Freitas on 03/02/17.
//

#ifndef DATATRANSFORMATION_STATS_H
#define DATATRANSFORMATION_STATS_H

#include <vector>
#include <algorithm>
//#include "generator.h"
#include <math.h>

using namespace std;

namespace utils {

    template <class Container>
    vector<size_t> sorted_origin(const Container &v){
        // allocate vector for ranks
        vector<size_t> sorted_indexes(v.size());
        // insert 0,1,2,3,4...n-1
        size_t i = 0;
        std::for_each(sorted_indexes.begin(), sorted_indexes.end(), [&i](auto& elem)
        {
            elem = i++;
        });
        // "sort" by reference
        sort(sorted_indexes.begin(),sorted_indexes.end(),[&v](auto x, auto y){return v[x] < v[y];});
        // return
        return sorted_indexes;
    }

    template <class Container>
    vector<size_t> rank(const Container &v){
        // which elements would be in the sorted array
        auto indexes = sorted_origin(v);
        // puts it in a new array
        vector<size_t> ranks(v.size());
        for (int i = 0; i < v.size(); ++i) {
            ranks[indexes[i]] = i;
        }
        // return
        return ranks;
    }

    template <class Container>
    vector<size_t> ranks(const Container &v) {
        // which elements would be in the sorted array
        return utils::rank(v);
    }

    template <class Container>
    vector<size_t> ranking(const Container &v) {
        // which elements would be in the sorted array
        return utils::rank(v);
    }

        template <class Container>
    double mean(const Container &v){
        return accumulate(v.begin(),v.end(),0.0)/v.size();
    }

    template <class Container>
    double var(const Container &v, double pre_processed_mean){
        return accumulate(v.begin(),v.end(),0.0,[&pre_processed_mean](auto &x, auto &y){return x + pow(y-pre_processed_mean,2);})/(v.size()-1);
    }

    template <class Container>
    double var(const Container &v){
        const double mean = accumulate(v.begin(),v.end(),0.0)/v.size();
        return var(v,mean);
    }

    template <class Container>
    double stdev(const Container &v, double pre_processed_variance) {
        return sqrt(pre_processed_variance);
    }

    template <class Container>
    double stdev(const Container &v) {
        return stdev(v, var(v));
    }

    template <class Container>
    double ttest(const Container &v, double population_mean, double pre_processed_mean) {
        const double X = pre_processed_mean;
        const double s = stdev(v, var(v, X));
        const double n = v.size();
        return (X-population_mean)/(s/sqrt(n));
    }

    template <class Container>
    double ttest(const Container &v, double population_mean = 0) {
        const double X = mean(v);
        return ttest(v,population_mean,X);
    }

    template <class Container>
    double ttest(const Container &v, const Container &v2, double population_mean = 0) {
        Container v3 = v;
        for (int i = 0; i < v2.size(); ++i) {
            v3[i] -= v2[i];
        }
        const double X = mean(v3);
        return ttest(v3,population_mean,X);
    }

    // equal or unequal sample sizes / same variance
    template <class Container>
    double ttest2(const Container &v1, const Container &v2) {
        const double X = mean(v1);
        const double Y = mean(v2);
        const double sX = stdev(v1, var(v1, X));
        const double sY = stdev(v2, var(v2, Y));
        const double n = v1.size();
        const double m = v2.size();
        const double sP = sqrt(((n-1)*(std::pow(sX,2))+(m-1)*(std::pow(sY,2)))/(n+m-2));
        return (X-Y)/(sP*sqrt(1/n+1/m));
    }

    // insensitive to equality of the variances regardless of whether the sample sizes are similar
    // https://en.wikipedia.org/wiki/Welch%27s_t-test
    template <class Container>
    double ttest2_welchs(const Container &v1, const Container &v2) {
        const double X = mean(v1);
        const double Y = mean(v2);
        const double sX = stdev(v1, var(v1, X));
        const double sY = stdev(v2, var(v2, Y));
        const double n = v1.size();
        const double m = v2.size();
        const double s_delta = sqrt(std::pow(sX,2)/n+std::pow(sY,2)/m);
        return (X-Y)/(s_delta);
    }

    template <class Container>
    double ttest2_paired(const Container &v1, const Container &v2, double population_mean = 0.0) {
        return ttest(v1,v2,population_mean);
    }

//    template <class Container>
//    double shapiro(const Container &v, double distribution_mean = 0, double distribution_stddev = 1) {
//        double preprocessed_mean = mean(v);
//        Container v_copy = v;
//        sort(v_copy.begin(),v_copy.end());
//        // expected values
//        vector<double> m(v_copy.size());
//        for (int i = 0; i < v_copy.size(); ++i) {
//            m[i] = utils::normal(distribution_mean,distribution_stddev);
//        }
//        sort(m.begin(),m.end());
//        // covariance matrix
//        // to be continued...
//        return 0;
//    }



    // Normality test
    // https://en.wikipedia.org/wiki/Shapiro–Wilk_test
    // https://en.wikipedia.org/wiki/Kolmogorov–Smirnov
    // https://en.wikipedia.org/wiki/Q–Q_plot
    // Equações todas estão nas descrições das funções no matlab

    // The two populations being compared should have the same variance
    // https://en.wikipedia.org/wiki/F-test_of_equality_of_variances
    // https://en.wikipedia.org/wiki/Levene%27s_test
    // https://en.wikipedia.org/wiki/Bartlett%27s_test
    // https://en.wikipedia.org/wiki/Brown–Forsythe_test
    // https://en.wikipedia.org/wiki/Q–Q_plot

    // The data used to carry out the test should be sampled independently
    // Most two-sample t-tests are robust to all but large deviations from the assumptions

    // If the sample sizes in the two groups being compared are equal, Student's original t-test is highly robust to the presence of unequal variances




}

#endif //DATATRANSFORMATION_STATS_H
