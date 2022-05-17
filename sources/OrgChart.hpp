/**
 * @file OrgChart.hpp
 * @author Ohad Maday (maday.ohad@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-05-17
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>

namespace ariel{
    /**
     * @brief OrgChart header file - suppose to represent an hirerachy of roles
     * 
     * --TBC-- (Just first part)
     * 
     */
    class OrgChart{
        /**
         * @brief Inner class Node - maybe find useful in implementation
         * 
         */
        class Node{
            public:
                std::string val; // Value which Node holds
                Node *son;       // A connection between a node and the other
                
                /**
                 * @brief Construct a new Node object
                 * 
                 * @param val 
                 */
                Node(const std::string& val) : val(val), son(nullptr) {} 
                /**
                 * @brief Construct a new Node object - copy constructor
                 * 
                 * @param val 
                 * @param _son 
                 */
                Node(const std::string& val, Node& _son) : val(val), son(&_son) {} 
                /**
                 * @brief Operator == if a Node equals to another
                 * 
                 * @param a 
                 * @return true 
                 * @return false 
                 */
                bool operator==(const Node& a);
        };

        Node *root;                                 // Root of the chart
        size_t size;                                // Size of the chart so can resize vectors
        std::vector<std::string> hirearchy;         // Vector which holds all the roles

        public:
        /**
         * @brief Construct a new Org Chart object
         * 
         */
        OrgChart();
        /**
         * @brief add root to the tree - if called again; overrides the previous root
         * 
         * @param value 
         * @return OrgChart& 
         */
        OrgChart& add_root(const std::string &value);
        /**
         * @brief Adds a sub to a root (a child to a root)
         * 
         * @param father 
         * @param son 
         * @return OrgChart& 
         */
        OrgChart& add_sub(const std::string &father,const std::string &son);

        /**
         * @brief Iterator begins
         * 
         * @return std::vector<std::string>::iterator 
         */
        std::vector<std::string>::iterator begin();
        /**
         * @brief Iterator ends
         * 
         * @return std::vector<std::string>::iterator 
         */
        std::vector<std::string>::iterator end();

        /**
         * @brief Iterator of level order
         * 
         * @return std::vector<std::string>::iterator 
         */
        std::vector<std::string>::iterator begin_level_order();
        
        /**
         * @brief End of level order iterator
         * 
         * @return std::vector<std::string>::iterator 
         */
        std::vector<std::string>::iterator end_level_order();

        /**
         * @brief Reverse order iterator start
         * 
         * @return std::vector<std::string>::iterator 
         */
        std::vector<std::string>::iterator begin_reverse_order();

        /**
         * @brief End reverse order iterator
         * 
         * @return std::vector<std::string>::iterator 
         */
        std::vector<std::string>::iterator reverse_order(); 

        /**
         * @brief Preorder iterator 
         * 
         * @return std::vector<std::string>::iterator 
         */
        std::vector<std::string>::iterator begin_preorder();

        /**
         * @brief End preorder iterator
         * 
         * @return std::vector<std::string>::iterator 
         */
        std::vector<std::string>::iterator end_preorder();

        /**
         * @brief Get the Hirearchy vector
         * 
         * @return std::vector<std::string> 
         */
        std::vector<std::string> getHirearchy();

        /**
         * @brief Print operator 
         * 
         * @param os 
         * @param chart 
         * @return std::ostream& 
         */
        friend std::ostream& operator<<( std::ostream& os, const OrgChart& chart);
        
        /**
         * @brief Chart equals to the other
         * 
         * @param a 
         * @return true 
         * @return false 
         */
        bool operator==(const OrgChart& a) const;
        
        /**
         * @brief Get the Root of the chart
         * 
         * @return Node& 
         */
        Node& getRoot();


    };

 
}