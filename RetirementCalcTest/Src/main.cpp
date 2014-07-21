#define BOOST_TEST_MODULE Lorei_Test
#include <boost/test/unit_test.hpp>

// We need this here so we can use Qt in the unit tests.
// if we don't have this we get memory leaks
#include <QCoreApplication>
QCoreApplication mainApp(boost::unit_test::framework::master_test_suite().argc, boost::unit_test_framework::master_test_suite_t().argv);