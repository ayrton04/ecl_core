/**
 * @file /src/test/timestamp.cpp
 *
 * @brief Unit Test for timestamp objects.
 *
 * @date May 2009
 **/
/*****************************************************************************
** Includes
*****************************************************************************/

#include <cstdlib>
#include <gtest/gtest.h>
#include "../../include/ecl/time/timestamp.hpp"

/*****************************************************************************
** Platform Check
*****************************************************************************/

#ifdef ECL_HAS_TIMESTAMP

/*****************************************************************************
** Using
*****************************************************************************/

using ecl::TimeStamp;

/*****************************************************************************
** Variables
*****************************************************************************/

bool verbose = true;

/*****************************************************************************
** Tests
*****************************************************************************/

TEST(TimeStampTests,construction) {
    TimeStamp time;
    SUCCEED();
    TimeStamp time_pair(3,123456789L);
    EXPECT_FLOAT_EQ(3.123456789,time_pair);
    TimeStamp time_double(3.00001);
    EXPECT_FLOAT_EQ(3.00001,time_double);
}

TEST(TimeStampTests,timestamps) {
    TimeStamp time;
    time.stamp();
    long t = time.sec();
    t = time.msec();
    t = time.usec();
    t = time.nsec();
    SUCCEED();
    time.stamp(3,1425);
    EXPECT_FLOAT_EQ(3.000001425,time);
    time.stamp(4.00000142);
    EXPECT_FLOAT_EQ(4.00000142,time);
}

TEST(TimeStampTests,copyConstruction) {
    TimeStamp time(3,100);
	TimeStamp time_copy(time);
	EXPECT_EQ(3,time_copy.sec());
	EXPECT_EQ(100,time_copy.nsec());
}

TEST(TimeStampTests,copyAssignment) {
    TimeStamp time(3,100);
	TimeStamp time_copy;
    time_copy = time;
	EXPECT_EQ(3,time_copy.sec());
	EXPECT_EQ(100,time_copy.nsec());
}

TEST(TimeStampTests,comparisonOperators) {
    TimeStamp time(3,100);
	TimeStamp time_copy(time);
	EXPECT_TRUE(time==time_copy);
	EXPECT_FALSE(time!=time_copy);
	EXPECT_TRUE(time<=time_copy);
	EXPECT_TRUE(time>=time_copy);
	EXPECT_FALSE(time<time_copy);
	EXPECT_FALSE(time>time_copy);
    time.stamp();
	EXPECT_FALSE(time==time_copy);
	EXPECT_TRUE(time!=time_copy);
	EXPECT_FALSE(time<=time_copy);
	EXPECT_TRUE(time>=time_copy);
	EXPECT_FALSE(time<time_copy);
	EXPECT_TRUE(time>time_copy);
}

TEST(TimeStampTests,mathematicalOperators) {
	TimeStamp time, time_copy;
    time.stamp(1,100100100L);
    time_copy.stamp(1,900100100L);
    time += time_copy;
    EXPECT_EQ(3,time.sec());
    EXPECT_EQ(200200,time.nsec());
    time.stamp(1,100100100L);
    time = time + time_copy;
    EXPECT_EQ(3,time.sec());
    EXPECT_EQ(200200,time.nsec());
    time.stamp(2,100100100L);
    time -= time_copy;
    EXPECT_EQ(0,time.sec());
    EXPECT_EQ(200000000,time.nsec());
    time.stamp(2,100100100L);
    time = time - time_copy;
    EXPECT_EQ(0,time.sec());
    EXPECT_EQ(200000000,time.nsec());
}

TEST(TimeStampTests,negatives) {
  std::vector<TimeStamp> timestamps = { TimeStamp(1.7),
                                        TimeStamp(0.7),
                                        TimeStamp(-0.7),
                                        TimeStamp(-1.7),
  };
  if ( verbose ) {
    std::cout << "Stream Operator: ";
    for ( const TimeStamp& timestamp : timestamps) {
      std::cout << timestamp << " ";
    }
    std::cout << std::endl;
  }
  EXPECT_EQ(1, timestamps[0].sec());
  EXPECT_EQ(700000000, timestamps[0].nsec());
  EXPECT_EQ(0, timestamps[1].sec());
  EXPECT_EQ(700000000, timestamps[1].nsec());
  EXPECT_EQ(0, timestamps[2].sec());
  EXPECT_EQ(-700000000, timestamps[2].nsec());
  EXPECT_EQ(-1, timestamps[3].sec());
  EXPECT_EQ(-700000000, timestamps[3].nsec());

  std::vector<float> double_representations;
  for ( const TimeStamp& timestamp : timestamps) {
    double_representations.push_back(timestamp);
  }
  if ( verbose ) {
    std::cout << "Doubles: ";
    for ( const float& d : double_representations ) {
      std::cout << d << " ";
    }
    std::cout << std::endl;
  }
  EXPECT_FLOAT_EQ(1.7, double_representations[0]);
  EXPECT_FLOAT_EQ(0.7, double_representations[1]);
  EXPECT_FLOAT_EQ(-0.7, double_representations[2]);
  EXPECT_FLOAT_EQ(-1.7, double_representations[3]);
  double_representations.clear();
  double_representations.push_back(ecl::TimeStamp(1.3) - ecl::TimeStamp(5.1));
  double_representations.push_back(ecl::TimeStamp(1.3) - ecl::TimeStamp(5.8));
  double_representations.push_back(ecl::TimeStamp(1.3) - ecl::TimeStamp(1.5));
  double_representations.push_back(ecl::TimeStamp(-1.3) - ecl::TimeStamp(1.5));
  double_representations.push_back(ecl::TimeStamp(-1.3) - ecl::TimeStamp(-0.8));
  double_representations.push_back(ecl::TimeStamp(-1.3) - ecl::TimeStamp(-5.8));
  if ( verbose ) {
    std::cout << "Differences: ";
    std::cout << (ecl::TimeStamp(1.3) - ecl::TimeStamp(5.1)) << " ";
    std::cout << (ecl::TimeStamp(1.3) - ecl::TimeStamp(5.8)) << " ";
    std::cout << (ecl::TimeStamp(1.3) - ecl::TimeStamp(1.5)) << " ";
    std::cout << (ecl::TimeStamp(-1.3) - ecl::TimeStamp(1.5)) << " ";
    std::cout << (ecl::TimeStamp(-1.3) - ecl::TimeStamp(-0.8)) << " ";
    std::cout << (ecl::TimeStamp(-1.3) - ecl::TimeStamp(-5.8)) << " ";
    std::cout << std::endl;
  }
  EXPECT_FLOAT_EQ(-3.8, double_representations[0]);
  EXPECT_FLOAT_EQ(-4.5, double_representations[1]);
  EXPECT_FLOAT_EQ(-0.2, double_representations[2]);
  EXPECT_FLOAT_EQ(-2.8, double_representations[3]);
  EXPECT_FLOAT_EQ(-0.5, double_representations[4]);
  EXPECT_FLOAT_EQ(4.5, double_representations[5]);

  double_representations.clear();
  ecl::TimeStamp t, time1_3(1.3), time1_3_bd(-1.3);
  t = time1_3; t -= ecl::TimeStamp(5.1);
  double_representations.push_back(t);
  t = time1_3; t -= ecl::TimeStamp(5.8);
  double_representations.push_back(t);
  t = time1_3; t -= ecl::TimeStamp(1.5);
  double_representations.push_back(t);
  t = time1_3_bd; t -= ecl::TimeStamp(1.5);
  double_representations.push_back(t);
  t = time1_3_bd; t -= ecl::TimeStamp(-0.8);
  double_representations.push_back(t);
  t = time1_3_bd; t -= ecl::TimeStamp(-5.8);
  double_representations.push_back(t);
  if ( verbose ) {
    std::cout << "Differences: ";
    for (const double& d : double_representations) {
      std::cout << d << " ";
    }
    std::cout << std::endl;
  }
  EXPECT_FLOAT_EQ(-3.8, double_representations[0]);
  EXPECT_FLOAT_EQ(-4.5, double_representations[1]);
  EXPECT_FLOAT_EQ(-0.2, double_representations[2]);
  EXPECT_FLOAT_EQ(-2.8, double_representations[3]);
  EXPECT_FLOAT_EQ(-0.5, double_representations[4]);
  EXPECT_FLOAT_EQ(4.5, double_representations[5]);
}

#endif /* ECL_HAS_TIMESTAMP */

/*****************************************************************************
** Main program
*****************************************************************************/

int main(int argc, char **argv) {

  ecl::TimeStamp time1(1437453731.8);
  ecl::TimeStamp time2(1437453731.1);
  ecl::TimeStamp diff12 = time1 - time2;
  std::cout << "Diff12 : " << diff12 << std::endl;
  ecl::TimeStamp diff21 = time2 - time1;
  std::cout << "Diff21 : " << diff21 << std::endl;

//	TimeStamp time;
//	std::cout << time << std::endl;
//	time.stamp();
//	std::cout << time << std::endl;
    testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}
