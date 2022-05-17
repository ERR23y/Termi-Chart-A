#include "doctest.h"
#include "OrgChart.hpp"
#include <vector>
#include <iostream>

using namespace std;
using namespace ariel;

TEST_CASE("Chart of string cases"){

  SUBCASE("Create bad OrgChart object"){
    OrgChart badinization; // Bad organization - Badinization
    CHECK_THROWS(badinization.add_sub("Grant", "Grunt").add_root("MacDonald")); // Can't add another root to a sub and can't start with a sub if Chart is empty

    SUBCASE("add_root(), add_sub() method checks "){
      SUBCASE("add_root() checks"){
        OrgChart witcher;

        CHECK_NOTHROW(witcher.add_root("Geralt of Rivia"));
        string st = witcher.getHirearchy().front();
        CHECK_EQ(st == "Geralt of Rivia",true); // Verify that the function created root named Geralt of Rivia
        CHECK_NE(st == "Vasemir",true);        // Verify that the function created root named Geralt of Rivia (Geralt isn't Vasemir)

        // // Add sub then a root to check if it actually changes
        witcher.add_sub("Geralt of Rivia","Ciri").add_root("Vasemir");
        st = witcher.getHirearchy().front();
        CHECK_EQ(st == "Vasemir",true);          // Check one way if the function actually replace
        CHECK_EQ(st == "Geralt of Rivia",false); // Check other way around
      }
    }
    SUBCASE("add_sub() checks"){
      OrgChart fellowship_of_the_ring;
      fellowship_of_the_ring.add_root("Gandalf")
      .add_sub("Gandalf","Frodo")
      .add_sub("Gandalf","Samwise");

      vector<string> hirearchy;
      // Verify that Frodo follows Gandalf but not Sam
       for (auto it = fellowship_of_the_ring.begin_level_order(); it != fellowship_of_the_ring.end_level_order(); ++it){
          hirearchy.push_back(*(it)); // Pushing to the vector the root and it subs by level order
       }
      CHECK_EQ(hirearchy.at(1) != "Samwise", true);
      CHECK_EQ(hirearchy.at(2) == "Frodo", true);
      CHECK_EQ(hirearchy.at(3) == "Samwise", true);

      // Make Frodo follow the Witch-king and give him the one ring (BUT is the Witch king is part of the fellowship?)
      CHECK_THROWS(fellowship_of_the_ring.add_sub("The Witch-king of Angamar","Frodo"));
    }
  }

  
  /*-------------------------------------- 
  * Check if == operator works (both ways)
  *---------------------------------------
  */

  // Create & init 2 organizations
  OrgChart organization;
  CHECK_NOTHROW(organization.add_root("CEO")
      .add_sub("CEO", "CTO")         // Now the CTO is subordinate to the CEO
      .add_sub("CEO", "CFO")         // Now the CFO is subordinate to the CEO
      .add_sub("CEO", "COO")         // Now the COO is subordinate to the CEO
      .add_sub("CTO", "VP_SW") // Now the VP Software is subordinate to the CTO
      .add_sub("COO", "VP_BI"));      // Now the VP_BI is subordinate to the COO
  
  OrgChart organization2;
  CHECK_NOTHROW(organization2.add_root("CEO")
      .add_sub("CEO", "CTO")         // Now the CTO is subordinate to the CEO
      .add_sub("CEO", "CFO")         // Now the CFO is subordinate to the CEO
      .add_sub("CEO", "COO")         // Now the COO is subordinate to the CEO
      .add_sub("CTO", "VP_SW")       // Now the VP Software is subordinate to the CTO
      .add_sub("COO", "VP_BI"));     // Now the VP_BI is subordinate to the COO

  CHECK_EQ(organization == organization2, true); // Check if == works


  // Create another organization TEAM ROCKET
  OrgChart TeamRocket;
  CHECK_NOTHROW(TeamRocket.add_root("Boss/Giovanni")
  .add_sub("Boss/Giovanni","Administrator")
  .add_sub("Administrator","Executive")
  .add_sub("Administrator","Field Executive")
  .add_sub("Administrator","Elite Agent")
  .add_sub("Executive", "Class A agent")
  .add_sub("Executive", "Class B agent")
  .add_sub("Executive", "Grunt")
  .add_sub("Executive", "Trainee"));

  // Check if it returns false (the other way around)
  CHECK_EQ(organization == TeamRocket, false);


 /*
  *-------------------------------------- 
  * Verify orders are correct
  *---------------------------------------
  */
  SUBCASE("Verify orders are correct"){
    std::vector<std::string> v = {"CEO","CTO","CFO","COO","VP_SW","VP_BI"};
    size_t idx = 0;
    // Verifies order - CEO CTO CFO COO VP_SW VP_BI
    for (auto it = organization.begin_level_order(); it != organization.end_level_order(); ++it){
      CHECK((*it) == v.at(idx));
      idx++;
    } 

    v = {"VP_SW","VP_BI","CTO","CFO","COO","CEO"};
    idx = 0;
    // Verifies reverse order - VP_SW VP_BI CTO CFO COO CEO
    for (auto it = organization.begin_reverse_order(); it != organization.reverse_order(); ++it){
      CHECK((*it)== v.at(idx));
      idx++;
    }

    v = {"CEO", "CTO", "VP_SW", "CFO", "COO", "VP_BI"};
    idx = 0;
    // Verifies preorder order - CEO CTO VP_SW CFO COO VP_BI
    for (auto it=organization.begin_preorder(); it!=organization.end_preorder(); ++it) {
      CHECK((*it) == v.at(idx));
      idx++;
    } 

    v = {"CEO", "CTO", "CFO", "COO", "VP_SW", "VP_BI"};
    idx = 0;
    // Verifies order - CEO CTO CFO COO VP_SW VP_BI
    for (auto element : organization){ // Same as normal order
      CHECK((element) == v.at(idx));
      idx++;
    } 

    // Verify sizes of every title:
    vector<int> sizes = {3,3,3,3,5,5};
    idx = 0;
    for (auto it = organization.begin_level_order(); it != organization.end_level_order(); ++it){
      CHECK(it->size() == sizes.at(idx));
      idx++;
    } // Verify sizes: 3 3 3 3 5 5
    
    sizes = {5,5,3,3,3,3};
    idx = 0;
    // Reverse order sizes:
    for (auto it = organization.begin_reverse_order(); it != organization.reverse_order(); ++it){
      CHECK(it->size() == sizes.at(idx));
      idx++;
    } // Verify sizes: 5 5 3 3 3 3 
  }

  SUBCASE("Operator <<"){
    ostringstream os1;
    os1 << organization;
    CHECK(os1.str() == "CEO\n|--------|--------|\nCTO      CFO      COO\n|                 |\nVP_SW             VP_BI");
    /**
     * ---==The correct chart==---
     * CEO
       |--------|--------|
       CTO      CFO      COO
       |                 |
       VP_SW             VP_BI
     * 
     */
    CHECK(os1.str() != "CEO\n|--------|--------|\nCTO      CTO      COO\n|                 |\nVP_SW             VP_BI");
    CHECK(os1.str() != "CEO\n|--------|--------|\nCTO      CTO      CFO\n|                 |\nVP_SW             VP_BI");

  }

}

