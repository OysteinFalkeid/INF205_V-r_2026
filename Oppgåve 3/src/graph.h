
#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <list>
#include <unordered_map>
#include <map>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <set>
#include <utility> 
#include <ranges>

namespace db{
    class Node;
    class Graph;
    class Matrix;
    class Edge;
    class Node_controller;
}

// example of namespace. db stands for data base
namespace db{

    class Node_database_interface{
        protected:

        std::stringstream buffer;

        private:
        
        virtual void parse_buffer() = 0;
        virtual void print(std::ostream& os) const;
        
        public:
        
        Node_database_interface();
        Node_database_interface(std::string file_path);
        virtual ~Node_database_interface();

    
        friend std::ostream& operator<<(std::ostream& os, const Node_database_interface& node_database_interface);
        
        virtual void clear();


        virtual void insert_edge(std::string node_a_label, std::string edge_label, std::string node_b_label) = 0;
        virtual void remove_node(std::string node_label) = 0;
        virtual void disconnect(std::string node_a_label, std::string node_b_label) = 0;

        //returns a list of node labels
        virtual std::list<std::string> get_nodes() = 0;

        // returns a list of sets containing the edge label and node label the edge is pointing to
        virtual std::list<std::pair<std::string, std::string>> get_node_edges(std::string node_label) = 0;

        bool read_file(std::string file_path);
        bool write_to_file(std::string file_path);

    };
    
    
    class Node {
        private:
        void print(std::ostream& os) const;
        
        public:
        
        Node(std::string node_label);
        
        // destructor
        ~Node();
        
        void clear();

        friend std::ostream& operator<<(std::ostream& os, const Node& node);
        
        std::string label;
        std::list<Edge*> edges;
        
        void add_edge(std::string edge_label, Node* node_ptr);
        void remove_edge(Node* node_ptr);

    };
    
    class Edge {
        private:
        void print(std::ostream& os) const;

        public:
        
        Edge(std::string label, Node* node_ptr);
        ~Edge();
        
        void clear();


        friend std::ostream& operator<<(std::ostream& os, const Edge& edge);

        Node* pointing_to_node;
        std::string label;
    };
    
    class Graph : public Node_database_interface {
        private:
        
        // std::stringstream buffer;
        void parse_buffer() override;

        void print(std::ostream& os) const override;
        
        public:
        
        Graph() : Node_database_interface() { }
        Graph(std::string file_path) : Node_database_interface(file_path) { }
        
        // ### rule of five ###
        // destructor
        // ~Graph();
        //copy constructure
        Graph(const Graph& other);
        // copy assignment operator
        Graph& operator=(const Graph& other);
        // move constructor
        Graph(Graph&& other);
        // move assignment operator
        Graph& operator=(Graph&& other);
        
        
        std::map<std::string, Node*> node_pointer_list;
        
        void clear() override;
        void insert_edge(std::string node_a_label, std::string edge_label, std::string node_b_label) override;
        void remove_node(std::string node_label) override;
        void disconnect(std::string node_a_label, std::string node_b_label) override;


        std::list<std::string> get_nodes() override;
        std::list<std::pair<std::string, std::string>> get_node_edges(std::string node_label) override;

        void cleanup();
        
    };
    

    class Matrix : public Node_database_interface {
        private:
        
        // std::stringstream buffer;

        void parse_buffer() override;
        
        void print(std::ostream& os) const override;

        public:
        
        Matrix() : Node_database_interface() { }
        Matrix(std::string file_path) : Node_database_interface(file_path) { }
        // ~Matrix();
        
        std::vector<std::string> nodes;
        std::vector<std::vector<std::list<std::string>>> matrix;
        
        void clear() override;
        void insert_edge(std::string node_a_label, std::string edge_label, std::string node_b_label) override;
        void remove_node(std::string node_label) override;
        void disconnect(std::string node_a_label, std::string node_b_label) override;

        std::list<std::string> get_nodes() override;
        std::list<std::pair<std::string, std::string>> get_node_edges(std::string node_label) override;
        
    };
    
    
};

#endif