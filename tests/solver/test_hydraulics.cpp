/*
 ******************************************************************************
 Project:      OWA EPANET
 Version:      2.2
 Module:       test_hydraulics.cpp
 Description:  Tests EPANET toolkit api functions
 Authors:      see AUTHORS
 Copyright:    see AUTHORS
 License:      see LICENSE
 Last Updated: 03/21/2019
 ******************************************************************************
*/

#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include "test_toolkit.hpp"


BOOST_AUTO_TEST_SUITE (test_hydraulics)

BOOST_FIXTURE_TEST_CASE(test_solveH, FixtureOpenClose)
{
    error = EN_solveH(ph);
    BOOST_REQUIRE(error == 0);
}

BOOST_FIXTURE_TEST_CASE(test_hyd_step, FixtureOpenClose)
{
    int flag = 00;
    long t, tstep;

    error = EN_openH(ph);
    BOOST_REQUIRE(error == 0);

    error = EN_initH(ph, flag);
    BOOST_REQUIRE(error == 0);

    do {
        error = EN_runH(ph, &t);
        BOOST_REQUIRE(error == 0);

        error = EN_nextH(ph, &tstep);
        BOOST_REQUIRE(error == 0);

    } while (tstep > 0);

    error = EN_closeH(ph);
    BOOST_REQUIRE(error == 0);
}

BOOST_FIXTURE_TEST_CASE(test_hydr_save, FixtureOpenClose)
{
    error = EN_solveH(ph);
    BOOST_REQUIRE(error == 0);

    error = EN_saveH(ph);
    BOOST_REQUIRE(error == 0);

    error = EN_report(ph);
    BOOST_REQUIRE(error == 0);
}

BOOST_FIXTURE_TEST_CASE(test_hydr_savefile, FixtureOpenClose)
{
    error = EN_solveH(ph);
    BOOST_REQUIRE(error == 0);

    error = EN_savehydfile(ph, "test_savefile.hyd");
    BOOST_REQUIRE(error == 0);

    BOOST_CHECK(boost::filesystem::exists("test_savefile.hyd") == true);
}

BOOST_FIXTURE_TEST_CASE(test_hydr_usefile, FixtureOpenClose, * boost::unit_test::depends_on("test_hydraulics/test_hydr_savefile"))
{
    error = EN_usehydfile(ph, "test_savefile.hyd");
    BOOST_REQUIRE(error == 0);

    error = EN_solveQ(ph);
    BOOST_REQUIRE(error == 0);
}

BOOST_FIXTURE_TEST_CASE(test_pda_model, FixtureOpenClose)

{
    int error = 0;
    int index;
    double count, reduction;

    // Set Demand Multiplier to 10 to cause negative pressures
    error = EN_setoption(ph, EN_DEMANDMULT, 10);
    BOOST_REQUIRE(error == 0);

    // Run single period analysis
    error = EN_settimeparam(ph, EN_DURATION, 0);
    BOOST_REQUIRE(error == 0);

    // Solve hydraulics with default DDA option
    // which will return with neg. pressure warning code
    error = EN_solveH(ph);
    BOOST_REQUIRE(error == 6);

    // Check that 4 demand nodes have negative pressures
    error = EN_getstatistic(ph, EN_DEFICIENTNODES, &count);
    BOOST_REQUIRE(error == 0);
    BOOST_CHECK(count == 4);

    // Switch to PDA with pressure limits of 20 - 100 psi
    error = EN_setdemandmodel(ph, EN_PDA, 20, 100, 0.5);
    BOOST_REQUIRE(error == 0);

    // Solve hydraulics again
    error = EN_solveH(ph);
    BOOST_REQUIRE(error == 0);

    // Check that 6 nodes had demand reductions totaling 32.66%
    error = EN_getstatistic(ph, EN_DEFICIENTNODES, &count);
    BOOST_REQUIRE(error == 0);
    BOOST_CHECK(count == 6);
    error = EN_getstatistic(ph, EN_DEMANDREDUCTION, &reduction);
    BOOST_REQUIRE(error == 0);
    BOOST_CHECK(abs(reduction - 32.66) < 0.01);

    // Check that Junction 12 had full demand
    error = EN_getnodeindex(ph, (char *)"12", &index);
    BOOST_REQUIRE(error == 0);
    error = EN_getnodevalue(ph, index, EN_DEMANDDEFICIT, &reduction);
    BOOST_REQUIRE(error == 0);
    BOOST_CHECK(abs(reduction) < 0.01);

    // Check that Junction 21 had a demand deficit of 413.67
    error = EN_getnodeindex(ph, (char *)"21", &index);
    BOOST_REQUIRE(error == 0);
    error = EN_getnodevalue(ph, index, EN_DEMANDDEFICIT, &reduction);
    BOOST_REQUIRE(error == 0);
    BOOST_CHECK(abs(reduction - 413.67) < 0.01);
}

BOOST_FIXTURE_TEST_CASE(test_tank_overflow, FixtureOpenClose)

{
    int error = 0;
    int Nindex, Lindex;
    double level, spillage, spillage2, inflow;
    char testFile[] = "test_overflow.inp";

    // Get index of the tank and its inlet/outlet pipe
    error = EN_getnodeindex(ph, (char *)"2", &Nindex);
    BOOST_REQUIRE(error == 0);
    error = EN_getlinkindex(ph, (char *)"110", &Lindex);
    BOOST_REQUIRE(error == 0);

    // Set initial & maximum level to 130
    error = EN_setnodevalue(ph, Nindex, EN_TANKLEVEL, 130);
    BOOST_REQUIRE(error == 0);
    error = EN_setnodevalue(ph, Nindex, EN_MAXLEVEL, 130);
    BOOST_REQUIRE(error == 0);

    // Set duration to 1 hr
    error = EN_settimeparam(ph, EN_DURATION, 3600);
    BOOST_REQUIRE(error == 0);

    // Solve hydraulics with default of no tank spillage allowed
    error = EN_solveH(ph);
    BOOST_REQUIRE(error == 0);

    // Check that tank remains full
    error = EN_getnodevalue(ph, Nindex, EN_TANKLEVEL, &level);
    BOOST_REQUIRE(error == 0);
    BOOST_CHECK(abs(level - 130.0) < 0.0001);

    // Check that there is no spillage
    error = EN_getnodevalue(ph, Nindex, EN_DEMAND, &spillage);
    BOOST_REQUIRE(error == 0);
    BOOST_CHECK(abs(spillage) < 0.0001);

    // Check that inflow link is closed
    error = EN_getlinkvalue(ph, Lindex, EN_FLOW, &inflow);
    BOOST_REQUIRE(error == 0);
    BOOST_CHECK(abs(inflow) < 0.0001);

    // Turn tank overflow option on
    error = EN_setnodevalue(ph, Nindex, EN_CANOVERFLOW, 1);
    BOOST_REQUIRE(error == 0);

    // Solve hydraulics again
    error = EN_solveH(ph);
    BOOST_REQUIRE(error == 0);

    // Check that tank remains full
    error = EN_getnodevalue(ph, Nindex, EN_TANKLEVEL, &level);
    BOOST_REQUIRE(error == 0);
    BOOST_CHECK(abs(level - 130.0) < 0.0001);

    // Check that there is spillage equal to tank inflow
    // (inflow has neg. sign since tank is start node of inflow pipe)
    error = EN_getnodevalue(ph, Nindex, EN_DEMAND, &spillage);
    BOOST_REQUIRE(error == 0);
    BOOST_CHECK(spillage > 0.0001);
    error = EN_getlinkvalue(ph, Lindex, EN_FLOW, &inflow);
    BOOST_REQUIRE(error == 0);
    BOOST_CHECK(abs(-inflow - spillage) < 0.0001);

    // Save project to file and then close it
    error = EN_saveinpfile(ph, testFile);
    BOOST_REQUIRE(error == 0);
    error = EN_close(ph);
    BOOST_REQUIRE(error == 0);

    // Re-open saved file & run it
    error = EN_open(ph, testFile, DATA_PATH_RPT, "");
    BOOST_REQUIRE(error == 0);
    error = EN_solveH(ph);
    BOOST_REQUIRE(error == 0);

    // Check that tank spillage has same value as before
    error = EN_getnodevalue(ph, Nindex, EN_DEMAND, &spillage2);
    BOOST_REQUIRE(error == 0);
    BOOST_CHECK(abs(spillage - spillage2) < 0.0001);
}


BOOST_AUTO_TEST_SUITE_END()
