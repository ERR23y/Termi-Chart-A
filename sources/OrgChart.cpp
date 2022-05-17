/**
 * @file OrgChart.cpp
 * @author Ohad Maday (maday.ohad@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-05-17
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "OrgChart.hpp"


/**
 * @brief OrgChart object source file - To be implemented - overall explanation being found in header file (OrgChart.hpp)
 * 
 */

namespace ariel{
        

        bool OrgChart::Node::operator==(const Node& a){
            return (this->son == a.son && this->val == a.val) ? true : false;
        }

        OrgChart::OrgChart() : size(0){}
        OrgChart& OrgChart::add_root(const std::string &value){
            this->size++;
            this->hirearchy.resize(size);
            this->hirearchy.push_back(value);
            return *this;    
        }
        OrgChart& OrgChart::add_sub(const std::string &father,const std::string &son){
            this->size++;
            this->hirearchy.resize(size);
            this->hirearchy.push_back(son);
            this->size++;
            return *this;
        }

        std::vector<std::string>::iterator OrgChart::begin(){

            std::vector<std::string>::iterator it;
            it = this->hirearchy.begin();
            return it;
        }
        std::vector<std::string>::iterator OrgChart::end(){
            std::vector<std::string>::iterator it;
            it = this->hirearchy.end();
            return it;
        }

        std::vector<std::string>::iterator OrgChart::begin_level_order(){
            std::vector<std::string>::iterator it;
            it = this->hirearchy.begin();
            return it;
        }
        std::vector<std::string>::iterator OrgChart::end_level_order(){
            std::vector<std::string>::iterator it;
            it = this->hirearchy.begin();
            return it;
        }

        std::vector<std::string>::iterator OrgChart::begin_reverse_order(){
             std::vector<std::string>::iterator it;
            it = this->hirearchy.begin();
            return it;           
        }
        std::vector<std::string>::iterator OrgChart::reverse_order(){
            std::vector<std::string>::iterator it;
            it = this->hirearchy.begin();
            return it;
        }

        std::vector<std::string>::iterator OrgChart::begin_preorder(){
            std::vector<std::string>::iterator it;
            it = this->hirearchy.begin();
            return it;
        }
        std::vector<std::string>::iterator OrgChart::end_preorder(){
            std::vector<std::string>::iterator it;
            it = this->hirearchy.begin();
            return it;
        }

        std::ostream& operator<<( std::ostream& os, const OrgChart& chart){
            return os;
        }

        bool OrgChart::operator==(const OrgChart& a) const{
            return true;
        }

        OrgChart::Node& OrgChart::getRoot(){
            return *this->root;
        }

        std::vector<std::string> OrgChart::getHirearchy(){
            return this->hirearchy;
        }

}