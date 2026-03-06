#include <string>
#include <list>
#include <unordered_map>
#include <map>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>


// example of namespace. db stands for data base
namespace db{
    class Node;
    class Graph;
    class Edge;
    
    std::ostream& operator<<(std::ostream&, const Graph&);
    std::ostream& operator<<(std::ostream&, const Matrix&);
    std::ostream& operator<<(std::ostream&, const Node*);
    std::ostream& operator<<(std::ostream&, const Edge*);
    
    class Node_controller{
        private:
    
        std::stringstream buffer;
        virtual void parse_buffer() = 0;
    
        public:
    
        Node_controller() = default;
        Node_controller(std::string file_path);
        ~Node_controller() = default;
        
        virtual void clear() = 0;
        virtual void insert_edge(std::string node_a_label, std::string edge_label, std::string node_b_label) = 0;
        virtual void remove_node(std::string node_label) = 0;
        virtual void disconnect(std::string node_a_label, std::string node_b_label) = 0;
    
        bool read_file(std::string file_path);
        bool write_to_file(std::string file_path);
    };
    
    
    class Node{
        private:
        
    
        public:
    
        Node(std::string node_label);
        
        // destructor
        ~Node();

        void clear();
        
        std::string label;
        std::list<Edge*> edges;
    
        void add_edge(std::string edge_label, Node* node_ptr);
        void remove_edge(Node* node_ptr);
    };
    
    class Edge{
        private:
        
        public:
    
        Edge(std::string label, Node* node_ptr);
        ~Edge();
        
        Node* pointing_to_node;
        std::string label;
    };
    
    class Graph : public Node_controller {
        private:
    
        std::stringstream buffer;
        void parse_buffer() override;
    
        public:
    
        Graph() : Node_controller() { }
        Graph(std::string file_path) : Node_controller(file_path) { }
    
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
    
        // int read_file(std::string file_path) override;
        // int write_to_file(std::string file_path) override;
    
    };
    
    // TODO
    class Matrix : public Node_controller {
        private:
    
        std::stringstream buffer;
        void parse_buffer() override;
    
        public:
    
        Matrix() : Node_controller() { }
        Matrix(std::string file_path) : Node_controller(file_path) { }
        
        std::vector<std::string> nodes;
        std::vector<std::vector<std::list<std::string>>> matrix;
        
        void clear() override;
        void insert_edge(std::string node_a_label, std::string edge_label, std::string node_b_label) override;
        void remove_node(std::string node_label) override;
        void disconnect(std::string node_a_label, std::string node_b_label) override;
    
        // int read_file(std::string file_path) override;
        // int write_to_file(std::string file_path) override;
    };
    

}    

